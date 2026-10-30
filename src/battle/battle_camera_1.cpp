// Battle camera work states, part 1 (game/include/p3fes/game/battle_camera_1.h), hand-decompiled from SLUS_216.21.
// Phase 5 slice `battle_camera` (battle_camera.cpp has the band's overview, battle_camera_cpu.h the register-faithful
// Cpu view and the cycle model); tests/game/test_battle_camera_1.cpp runs each body against its __recomp body.
#include "battle_camera_cpu.h"
#include "p3fes/game/battle_camera_1.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);  // (n) (battle_data)
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);   // btlUnit home position (unit, out, 0, 0)
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);   // btlUnit position (unit, out)
void fn_sub_280870_00280870(p3fes::EEContext&);   // a side's centre (side, 0, out, 0, 0, 1)
void fn_sub_2880E0_002880e0(p3fes::EEContext&);
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_sub_2D1DE0_002d1de0(p3fes::EEContext&);
void fn_sub_2D1F30_002d1f30(p3fes::EEContext&);   // the angle between two rotations (q0, q1) -> $f0
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_2D6290_002d6290(p3fes::EEContext&);   // (action)
void fn_sub_2FDBB0_002fdbb0(p3fes::EEContext&);
void fn_sub_351BB0_00351bb0(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);   // rotate a rotation about an axis (q, axis, n; $f12 angle)
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);   // rotate a vector by a rotation (out, in, 1, q)
void fn_sub_4BE310_004be310(p3fes::EEContext&);   // slerp setup (q0, q1, out: the two axes, sin / angle terms)
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);   // vector normalise (out, in)
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6AF0_004c6af0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);   // 2-D normalise (out, in)
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
void fn_tanf_0052e930(p3fes::EEContext&);
// this slice
void fn_sub_2A2290_002a2290(p3fes::EEContext&);   // camera: reset its key ring (camera, position, rotation, flags)
void fn_sub_2A3110_002a3110(p3fes::EEContext&);   // camera: field of view ($f12)
void fn_sub_2A3380_002a3380(p3fes::EEContext&);
void fn_sub_2A3420_002a3420(p3fes::EEContext&);
void fn_sub_2A3520_002a3520(p3fes::EEContext&);
void fn_sub_2A3550_002a3550(p3fes::EEContext&);
void fn_sub_2A3590_002a3590(p3fes::EEContext&);
void fn_sub_2A3E80_002a3e80(p3fes::EEContext&);
void fn_sub_2A4470_002a4470(p3fes::EEContext&);   // copy a 28-byte camera key (out, in)
void fn_sub_2A4690_002a4690(p3fes::EEContext&);   // look-at rotation (out, eye, target, up)
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

using namespace btl_cam;

// The camera work record (the camera table's functions get it in $a0: gBtl + 32) and the constants these states use.
namespace btl_cam1 {
inline constexpr s32 kCwKey = 156;      // 28 bytes: the work's camera key (position f32[3], rotation f32[4])
inline constexpr s32 kCwFov = 184;      // f32: its field of view
inline constexpr s32 kCwSubject = 224;  // u32: the btlAction the camera follows
inline constexpr s32 kActUnit = 48;     // btlAction: its btlUnit
// guest vectors (.data): `lui 0x69; addiu lo`
inline constexpr s32 kVecUpLo = 30848;   // 0x697880 (0, 1, 0): the up axis
inline constexpr s32 kVecFwdLo = 30880;  // 0x6978A0 (0, 0, -1): the camera's forward axis
inline constexpr s32 kVecXLo = 30832;    // 0x697870 (1, 0, 0)
inline constexpr s32 kVecZLo = 30864;    // 0x697890 (0, 0, 1): a unit's facing axis (rotated by unit+28)
}  // namespace btl_cam1
using namespace btl_cam1;

class Cpu1 final : public Cpu {
public:
    using Cpu::Cpu;
#define P3FES_BCAM_BODY_1(name, addr) void name();
    P3FES_BCAM_BODIES_1(P3FES_BCAM_BODY_1)
#undef P3FES_BCAM_BODY_1

private:
    // `lui r, hi; addiu r, r, lo`: a guest address
    void la(Gpr& r, u32 hi, s32 lo) {
        r = lui(hi);
        r = addiu(r, lo);
    }
    // `addiu d, sp, off`
    void spa(Gpr& d, s32 off) { d = addiu(sp, off); }
    void slerp_toward(s32 qa, s32 qb, s32 qc, s32 qr, u32 link, s32 k9, s32 k7, unsigned ft = F20, unsigned fnum = F1);
    void rand3_pick(unsigned f, u32 neg_hi, u32 pos_hi);
    void reset_2A54F0();
    void min_height_25(s32 off, u64 next);
    void position_plus(s32 dst);
    void frame_2A79F0(u32 l_sub, u32 l_tan, u32 l_norm, u32 min_hi, u64 scaled);
    void toward_2A79F0(s32 dst, u32 l_norm, bool reload);
    void fmax_to(unsigned fa, unsigned fb);
    void yaw_2A8150(bool negative, u32 pos_hi, u32 neg_hi, u32 l_pos, u32 l_neg);
    void eye_2A8150(u32 l_turn, bool first);
    void eye_point_2A8D20(s32 dir, unsigned fs, s32 out);
    void facing_point_2A8D20(unsigned fy);
    void key_point_2A8D20();
    void turn_point_2A95D0(u32 l_look, u32 l_rot, u32 l_turn);
    void tan_fov_2A95D0(u32 link);
    void shoulder_2A95D0();
    void side_2A95D0();
    void turn_limited(s32 qa, s32 qb, s32 qc, s32 qr, s32 eye, s32 tgt, u32 l_slerp, u32 l_rot, u32 l_look, u32 l_small);
};

// The limited turn the camera states share: the rotation at sp+qa slerped toward sp+qb by t = fnum / $f0 (in ft) into
// sp+qr. sub_4BE310(sp+qa, sp+qb, sp+qc) leaves the two scaled rotations (qc+0 / qc+16, f32[4] each), the angle (qc+32)
// and a "nearly equal" flag (qc+36). t <= 0 copies sp+qa, t >= 1 copies sp+qb; otherwise the weights are 1 - t and t, or
// with the flag clear sin((1 - t) * angle) and sin(t * angle) as odd polynomials (the $gp coefficients k9, -32696, k7,
// -32688, -32684, -32680), and sp+qr = qc+0.. * w0 + qc+16.. * w1. 13 + (10 | 6 + 10 | 6 + 4 [+ 37] + 28) cycles.
void Cpu1::slerp_toward(s32 qa, s32 qb, s32 qc, s32 qr, u32 link, s32 k9, s32 k7, unsigned ft, unsigned fnum) {
    charge(13);
    div_s(ft, fnum, F0);
    spa(a0, qa);
    spa(a1, qb);
    spa(a2, qc);
    jal(link, rg::fn_sub_4BE310_004be310);
    mtc1(zero, F11);
    c_le_s(ft, F11);
    if (cc()) {
        charge(10);
        copy_vec4(sp, qa, sp, qr);
        return;
    }
    charge(6);
    lif(v0, 0x3f80, F0);
    c_le_s(F0, ft);
    if (cc()) {
        charge(10);
        copy_vec4(sp, qb, sp, qr);
        return;
    }
    charge(4);
    sub_s(F0, F0, ft);
    lw(v0, sp, qc + 36);
    if (v0 == 0) {
        charge(37);
        lwc1(F10, sp, qc + 32);
        mul_s(F4, F0, F10);
        mul_s(F3, F4, F4);
        lwc1(F9, gp, k9);
        lwc1(F8, gp, -32696);
        adda_s(F11, F8);
        madd_s(F0, F9, F3);
        lwc1(F7, gp, k7);
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
        mul_s(F4, ft, F10);
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
        madd_s(ft, F1, F2);
    }
    charge(28);
    lwc1(F1, sp, qc);
    mul_s(F5, F1, F0);
    swc1(F5, sp, qr);
    lwc1(F1, sp, qc + 4);
    mul_s(F4, F1, F0);
    swc1(F4, sp, qr + 4);
    lwc1(F1, sp, qc + 8);
    mul_s(F3, F1, F0);
    swc1(F3, sp, qr + 8);
    lwc1(F1, sp, qc + 16);
    mtc1(zero, F2);
    adda_s(F2, F5);
    madd_s(F1, F1, ft);
    swc1(F1, sp, qr);
    lwc1(F1, sp, qc + 20);
    adda_s(F2, F4);
    madd_s(F1, F1, ft);
    swc1(F1, sp, qr + 4);
    lwc1(F1, sp, qc + 24);
    adda_s(F2, F3);
    madd_s(F1, F1, ft);
    swc1(F1, sp, qr + 8);
    lwc1(F2, sp, qc + 12);
    lwc1(F1, sp, qc + 28);
    mula_s(F1, ft);
    madd_s(F0, F2, F0);
    swc1(F0, sp, qr + 12);
}

// The look-at rotation sp+qb kept within 30 degrees (gp-32528) of the key rotation sp+qa, with their angle (sub_2D1F30)
// in $f0: beyond it the key rotation is turned 30 degrees toward the look-at (slerp_toward into sp+qr), the eye sp+eye
// becomes the target sp+tgt + the forward axis rotated by that, and the look-at is rebuilt from it (sub_2A4690); below 5
// degrees (gp-32524) the look-at is turned about the up axis by sub_4BDDE0(sp+qb, up, 2; $f12 = gp-32520).
void Cpu1::turn_limited(s32 qa, s32 qb, s32 qc, s32 qr, s32 eye, s32 tgt, u32 l_slerp, u32 l_rot, u32 l_look,
                        u32 l_small) {
    lwc1(F1, gp, -32528);
    c_le_s(F0, F1);
    if (!cc()) {
        slerp_toward(qa, qb, qc, qr, l_slerp, -32464, -32488);
        charge(28);
        spa(a0, eye);
        la(a1, 0x69, kVecFwdLo);
        a2 = li(1);
        spa(a3, qr);
        jal(l_rot, rg::fn_sub_4BE1E0_004be1e0);
        for (int k = 0; k < 3; ++k) {
            lwc1(F1, sp, eye + 4 * k);
            lwc1(F0, sp, tgt + 4 * k);
            add_s(F0, F1, F0);
            swc1(F0, sp, eye + 4 * k);
        }
        spa(a0, qb);
        spa(a1, eye);
        spa(a2, tgt);
        la(a3, 0x69, kVecUpLo);
        jal(l_look, rg::fn_sub_2A4690_002a4690);
    } else {
        charge(4);
        lwc1(F1, gp, -32524);
        c_lt_s(F0, F1);
        if (cc()) {
            charge(7);
            spa(a0, qb);
            la(a1, 0x69, kVecUpLo);
            lwc1(F12, gp, -32520);
            a2 = li(2);
            jal(l_small, rg::fn_sub_4BDDE0_004bdde0);
        }
    }
}

// =====================================================================================================================
// The camera work states (table 0x6939F0; $a0 = the camera work record gBtl+32)
// =====================================================================================================================

// 0x2A7390 sub_2A7390(work) [row 20 init]: a camera on the subject unit's home position. The work key (+156) is copied
// to sp+64; the target = the unit's home position (sub_27F7C0) raised to (unit+132 * unit+44 + unit+140 * unit+44 *
// 0.15). The look-at rotation from the key position (its height set to that target height) to the target is sp+104.
// When it is more than 30 degrees (gp-32528) from the key's own rotation (sub_2D1F30), the key rotation is slerped
// toward it by 30 degrees / angle and the eye moved to target + forward rotated by that (then the look-at again);
// below 5 degrees (gp-32524) the look-at is turned by sub_4BDDE0(.., up, 2; $f12 = gp-32520 = 30). The final eye:
// the forward axis rotated by the look-at, scaled by 375 / tan(fov * 0.5 * 1.2), shifted sideways by its xz direction *
// 0.21875 * that distance * tan(...) (sub_4C6B20), at least 25 high; the camera reset to it (sub_2A2290(work, key,
// eye, 1)) with the field of view gp-32456 (sub_2A3110).
void Cpu1::sub_2A7390() {
    enter(46);
    sp = addiu(sp, -240);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s0 = a0;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, kActUnit);
    spa(a0, 64);
    a1 = addiu(s0, kCwKey);
    jal(0x2a73b8, rg::fn_sub_2A4470_002a4470);
    a0 = s1;
    spa(a1, 200);
    a2 = 0;
    a3 = 0;
    jal(0x2a73d0, rg::fn_sub_27F7C0_0027f7c0);
    lwc1(F1, s1, 44);
    lwc1(F0, s1, 132);
    mula_s(F0, F1);
    lwc1(F0, s1, 140);
    mul_s(F1, F0, F1);
    lwc1(F0, gp, -32620);
    madd_s(F1, F0, F1);
    swc1(F1, sp, 204);
    spa(a1, 216);
    ld(v0, sp, 64);
    lwc1(F0, sp, 72);
    sd(v0, sp, 216);
    swc1(F0, sp, 224);
    swc1(F1, sp, 220);
    spa(a0, 104);
    spa(a2, 200);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a7420, rg::fn_sub_2A4690_002a4690);
    spa(a0, 76);
    spa(a1, 104);
    jal(0x2a7430, rg::fn_sub_2D1F30_002d1f30);
    turn_limited(76, 104, 128, 176, 216, 200, 0x2a7460, 0x2a760c, 0x2a7658, 0x2a768c);
    charge(78);
    spa(a0, 216);
    la(a1, 0x69, kVecFwdLo);
    a2 = li(1);
    spa(a3, 104);
    jal(0x2a76a8, rg::fn_sub_4BE1E0_004be1e0);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s0, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(0x2a76c8, rg::fn_tanf_0052e930);
    v0 = li(375);
    mtc1(v0, F1);
    cvt_s_w(F1, F1);
    div_s(F20, F1, F0);
    for (int k = 0; k < 3; ++k) {
        lwc1(F0, sp, 216 + 4 * k);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 216 + 4 * k);
    }
    lif(v0, 0x3f00, F1);
    lwc1(F0, s0, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(0x2a7720, rg::fn_tanf_0052e930);
    mul_s(F1, F20, F0);
    lif(v0, 0x3e60, F0);
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 216);
    swc1(F0, sp, 232);
    lwc1(F0, sp, 224);
    swc1(F0, sp, 236);
    spa(a0, 232);
    a1 = a0;
    jal(0x2a7754, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 236);
    lwc1(F0, sp, 200);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F3, F1, F20);
    swc1(F3, sp, 200);
    lwc1(F1, sp, 232);
    lwc1(F0, sp, 208);
    adda_s(F2, F0);
    msub_s(F2, F1, F20);
    swc1(F2, sp, 208);
    lwc1(F0, sp, 216);
    add_s(F0, F3, F0);
    swc1(F0, sp, 92);
    lwc1(F1, sp, 204);
    lwc1(F0, sp, 220);
    add_s(F1, F1, F0);
    swc1(F1, sp, 96);
    lwc1(F0, sp, 224);
    add_s(F0, F2, F0);
    swc1(F0, sp, 100);
    lif(v0, 0x41c8, F0);  // 25.0: the lowest eye height
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 96);
    }
    charge(17);
    a0 = s0;
    spa(a1, 64);
    spa(a2, 92);
    a3 = li(1);
    jal(0x2a77e0, rg::fn_sub_2A2290_002a2290);
    a0 = s0;
    lwc1(F12, gp, -32456);
    jal(0x2a77f0, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 240);
}

// 0x2A5FD0 sub_2A5FD0(work) [row 17 init]: a camera over the subject's shoulder toward its first target. The actor
// unit (subject +48) at sp+240 (sub_27FFB0), raised by 0.15 * unit+140 * unit+44 and at least 100; the first target's
// unit (subject +56 -> +48) at sp+224, set to that height. The distance the key keeps: |key - actor| (sub_4C6AC0) *
// gp-32672, at least 600. The direction actor -> target (normalised, sub_4C69F0), turned around when it points away from
// the key's xz direction (sub_4C6B20), places the look point (actor + dir * target+144 * target+44, sp+256) and the eye
// (actor + dir * actor+144 * actor+44 * 5, its height the target's + 0.5 * target+140 * target+44, sp+288). The
// look-at rotation eye -> look point (sp+136) is turned at most gp-32460 from the key's (sub_2D1F30 / slerp_toward,
// the eye then recomputed from the look point and the forward axis); the camera is reset (sub_2A2290(work, key, look
// point + forward * distance, 1)) with the field of view 1.0 (sub_2A3110).
void Cpu1::sub_2A5FD0() {
    enter(40);
    sp = addiu(sp, -304);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s1 = a0;
    lw(v0, a0, kCwSubject);
    lw(s0, v0, kActUnit);
    lw(v0, v0, kActTargets);
    lw(s2, v0, kActUnit);
    spa(a0, 96);
    a1 = addiu(s1, kCwKey);
    jal(0x2a6008, rg::fn_sub_2A4470_002a4470);
    a0 = s0;
    spa(a1, 240);
    jal(0x2a6018, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s2;
    spa(a1, 224);
    jal(0x2a6028, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s0, 140);
    lwc1(F0, s0, 44);
    mul_s(F3, F1, F0);
    lwc1(F2, gp, -32620);
    lwc1(F1, sp, 244);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F1, F2, F3);
    swc1(F1, sp, 244);
    lif(v0, 0x42c8, F0);  // 100.0
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 244);
    }
    charge(54);
    for (int k = 0; k < 3; ++k) {
        lwc1(F1, sp, 96 + 4 * k);
        lwc1(F0, sp, 240 + 4 * k);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 272 + 4 * k);
    }
    spa(a0, 272);
    jal(0x2a60a8, rg::fn_sub_4C6AC0_004c6ac0);
    lwc1(F1, gp, -32672);
    mul_s(F21, F0, F1);
    lwc1(F0, sp, 272);
    swc1(F0, sp, 88);
    lwc1(F0, sp, 280);
    swc1(F0, sp, 92);
    spa(a0, 88);
    a1 = a0;
    jal(0x2a60d0, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F2, sp, 244);
    swc1(F2, sp, 228);
    lwc1(F1, sp, 224);
    lwc1(F0, sp, 240);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 272);
    sub_s(F0, F2, F2);
    swc1(F0, sp, 276);
    lwc1(F1, sp, 232);
    lwc1(F0, sp, 248);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 280);
    spa(a0, 272);
    a1 = a0;
    jal(0x2a6110, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F3, sp, 272);
    swc1(F3, sp, 80);
    lwc1(F2, sp, 280);
    swc1(F2, sp, 84);
    lwc1(F1, sp, 88);
    lwc1(F0, sp, 92);
    mula_s(F2, F0);
    mtc1(zero, F0);
    madd_s(F1, F3, F1);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(7);
        neg_s(F0, F3);
        swc1(F0, sp, 272);
        lwc1(F0, sp, 276);
        neg_s(F0, F0);
        swc1(F0, sp, 276);
        neg_s(F0, F2);
        swc1(F0, sp, 280);
    }
    charge(75);
    lwc1(F0, s2, 144);
    lwc1(F9, s2, 44);
    mul_s(F1, F0, F9);
    lwc1(F5, sp, 272);
    mul_s(F0, F5, F1);
    swc1(F0, sp, 288);
    lwc1(F4, sp, 276);
    mul_s(F2, F4, F1);
    swc1(F2, sp, 292);
    lwc1(F3, sp, 280);
    mul_s(F1, F3, F1);
    swc1(F1, sp, 296);
    lwc1(F8, sp, 240);
    add_s(F0, F8, F0);
    swc1(F0, sp, 256);
    lwc1(F7, sp, 244);
    add_s(F0, F7, F2);
    swc1(F0, sp, 260);
    lwc1(F6, sp, 248);
    add_s(F0, F6, F1);
    swc1(F0, sp, 264);
    lwc1(F1, s0, 144);
    lwc1(F0, s0, 44);
    mul_s(F1, F1, F0);
    lif(v0, 0x40a0, F0);  // 5.0
    mul_s(F1, F0, F1);
    mul_s(F2, F5, F1);
    swc1(F2, sp, 272);
    mul_s(F0, F4, F1);
    swc1(F0, sp, 276);
    mul_s(F1, F3, F1);
    swc1(F1, sp, 280);
    add_s(F5, F8, F2);
    swc1(F5, sp, 288);
    add_s(F0, F7, F0);
    swc1(F0, sp, 292);
    add_s(F4, F6, F1);
    swc1(F4, sp, 296);
    lwc1(F0, s2, 140);
    mul_s(F3, F0, F9);
    lif(v0, 0x3f00, F2);
    lwc1(F1, sp, 228);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F1, F2, F3);
    swc1(F1, sp, 292);
    sub_s(F0, F5, F8);
    swc1(F0, sp, 272);
    sub_s(F0, F1, F7);
    swc1(F0, sp, 276);
    sub_s(F0, F4, F6);
    swc1(F0, sp, 280);
    spa(a0, 272);
    a1 = a0;
    jal(0x2a6250, rg::fn_sub_4C69F0_004c69f0);
    spa(a0, 136);
    spa(a1, 288);
    spa(a2, 256);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a626c, rg::fn_sub_2A4690_002a4690);
    spa(a0, 108);
    spa(a1, 136);
    jal(0x2a627c, rg::fn_sub_2D1F30_002d1f30);
    lwc1(F1, gp, -32460);
    c_le_s(F0, F1);
    if (!cc()) {
        slerp_toward(108, 136, 160, 208, 0x2a62ac, -32464, -32488);
        charge(26);
        spa(a0, 272);
        la(a1, 0x69, kVecFwdLo);
        a2 = li(1);
        spa(a3, 208);
        jal(0x2a6458, rg::fn_sub_4BE1E0_004be1e0);
        for (int k = 0; k < 3; ++k) {
            lwc1(F1, sp, 256 + 4 * k);
            lwc1(F0, sp, 272 + 4 * k);
            add_s(F0, F1, F0);
            swc1(F0, sp, 288 + 4 * k);
        }
        spa(a0, 136);
        spa(a1, 288);
        spa(a2, 256);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a64a4, rg::fn_sub_2A4690_002a4690);
    }
    charge(6);
    lif(v0, 0x4416, F0);  // 600.0
    c_lt_s(F21, F0);
    if (cc()) {
        charge(1);
        mov_s(F21, F0);
    }
    charge(38);
    lwc1(F0, sp, 272);
    mul_s(F3, F0, F21);
    swc1(F3, sp, 272);
    lwc1(F0, sp, 276);
    mul_s(F2, F0, F21);
    swc1(F2, sp, 276);
    lwc1(F0, sp, 280);
    mul_s(F1, F0, F21);
    swc1(F1, sp, 280);
    lwc1(F0, sp, 256);
    add_s(F0, F0, F3);
    swc1(F0, sp, 124);
    lwc1(F0, sp, 260);
    add_s(F0, F0, F2);
    swc1(F0, sp, 128);
    lwc1(F0, sp, 264);
    add_s(F0, F0, F1);
    swc1(F0, sp, 132);
    a0 = s1;
    spa(a1, 96);
    spa(a2, 124);
    a3 = li(1);
    jal(0x2a6520, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x3f80, F12);
    a0 = s1;
    jal(0x2a6534, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 304);
}

// 0x2A65F0 sub_2A65F0(work) [row 18 init]: a two-shot camera framing the actor and its first target from the side. The
// actor's anchor (unit+220, +132 * +44, +228; sp+264) and the target unit's position (sub_27FFB0, sp+248); the height
// = both units' 0.15 * +140 * +44 terms added to their heights, the reach $f20 = actor +232 + its +144 * +44 + the
// target's +144 * +44. The look point (sp+296) = the target + the normalised anchor-target direction * reach / 4 at
// half the height; work+268 = actor +232 * 0.5, work+256..264 = the look point. The look-at from the key position at
// that height (sp+344) is kept within 30 degrees of the key rotation (turn_limited). The distance: the larger of the
// two units' radius sum and 675, as 0.75 * it / tan(fov * 0.6) ($f23). The forward axis rotated by the look-at; when it
// faces the line between the units at a sharper angle than the line from the nearer unit, the eye is moved to either
// side of that unit and the side whose look-at turns less from the key is taken. The eye = look point + forward *
// distance, shifted sideways by its xz direction * 0.21875 * distance * tan(...); both key and eye clamped by
// sub_2A3590; the camera reset (sub_2A2290(work, key, eye, 1)) with the field of view 2.0.
void Cpu1::sub_2A65F0() {
    enter(134);
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
    lw(s0, v0, kActUnit);
    lw(v0, v0, kActTargets);
    lw(s1, v0, kActUnit);
    spa(a0, 80);
    a1 = addiu(s2, kCwKey);
    jal(0x2a6630, rg::fn_sub_2A4470_002a4470);
    lwc1(F0, s0, 220);
    swc1(F0, sp, 264);
    lwc1(F1, s0, 132);
    lwc1(F0, s0, 44);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 268);
    lwc1(F0, s0, 228);
    swc1(F0, sp, 272);
    a0 = s1;
    spa(a1, 248);
    jal(0x2a6660, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F6, s0, 44);
    lwc1(F0, s0, 140);
    mul_s(F1, F0, F6);
    lwc1(F5, gp, -32620);
    lwc1(F0, sp, 268);
    mtc1(zero, F3);
    adda_s(F3, F0);
    madd_s(F4, F5, F1);
    lwc1(F2, s1, 44);
    lwc1(F0, s1, 140);
    mul_s(F1, F0, F2);
    lwc1(F0, sp, 252);
    adda_s(F3, F0);
    madd_s(F0, F5, F1);
    add_s(F22, F4, F0);
    lwc1(F1, s0, 232);
    lwc1(F0, s0, 144);
    adda_s(F3, F1);
    madda_s(F0, F6);
    lwc1(F0, s1, 144);
    madd_s(F20, F0, F2);
    sw(zero, sp, 252);
    sw(zero, sp, 268);
    lwc1(F1, s0, 220);
    lwc1(F0, sp, 248);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 328);
    lwc1(F0, s0, 224);
    sub_s(F0, F0, F3);
    swc1(F0, sp, 332);
    lwc1(F1, s0, 228);
    lwc1(F0, sp, 256);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 336);
    spa(a0, 328);
    a1 = a0;
    jal(0x2a66fc, rg::fn_sub_4C69F0_004c69f0);
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
    spa(a1, 344);
    ld(v0, sp, 80);
    lwc1(F0, sp, 88);
    sd(v0, sp, 344);
    swc1(F0, sp, 352);
    swc1(F22, sp, 348);
    lwc1(F0, s0, 232);
    mul_s(F0, F1, F0);
    swc1(F0, s2, 268);
    spa(a2, 296);
    copy_vec3(sp, 296, s2, 256);
    spa(a0, 120);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a67bc, rg::fn_sub_2A4690_002a4690);
    lwc1(F2, s0, 144);
    lwc1(F1, s0, 44);
    mtc1(zero, F0);
    adda_s(F0, F20);
    madda_s(F2, F1);
    lwc1(F1, s1, 144);
    lwc1(F0, s1, 44);
    madd_s(F22, F1, F0);
    spa(a0, 92);
    spa(a1, 120);
    jal(0x2a67f0, rg::fn_sub_2D1F30_002d1f30);
    turn_limited(92, 120, 144, 224, 344, 296, 0x2a6820, 0x2a69cc, 0x2a6a18, 0x2a6a4c);
    charge(7);
    v0 = li(675);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    c_lt_s(F22, F0);
    if (cc()) {
        charge(1);
        mov_s(F22, F0);
    }
    charge(42);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s2, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(0x2a6a8c, rg::fn_tanf_0052e930);
    lif(v0, 0x3fc0, F2);  // 1.5
    lif(v0, 0x3f00, F1);
    mul_s(F1, F1, F22);
    mul_s(F1, F2, F1);
    div_s(F23, F1, F0);
    spa(a0, 344);
    la(a1, 0x69, kVecFwdLo);
    a2 = li(1);
    spa(a3, 120);
    jal(0x2a6ac8, rg::fn_sub_4BE1E0_004be1e0);
    lwc1(F0, sp, 348);
    swc1(F0, sp, 332);
    spa(a0, 328);
    a1 = a0;
    jal(0x2a6ae0, rg::fn_sub_4C69F0_004c69f0);
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
    // the nearer unit: the actor when the forward axis points along the line, else the target
    if (cc()) {
        charge(7);
        lwc1(F1, s1, 144);
        lwc1(F0, s1, 44);
        mul_s(F22, F1, F0);
        ld(v0, sp, 248);
        lwc1(F0, sp, 256);
    } else {
        charge(9);
        lwc1(F1, s0, 144);
        lwc1(F0, s0, 44);
        mul_s(F22, F1, F0);
        ld(v0, sp, 264);
        lwc1(F0, sp, 272);
    }
    sd(v0, sp, 280);
    swc1(F0, sp, 288);
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
    spa(a0, 312);
    a1 = a0;
    jal(0x2a6bb4, rg::fn_sub_4C69F0_004c69f0);
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
    bool side = !cc();
    if (side) {
        charge(3);
        c_eq_s(F3, F2);
        side = !cc();
    }
    if (side) {
        charge(3);
        c_eq_s(F3, F20);
        side = !cc();
    }
    if (side) {
        // the eye at either side of the nearer unit (sp+280): the look-at that turns less from the key wins
        charge(65);
        lwc1(F1, sp, 296);
        lwc1(F0, sp, 280);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 376);
        lwc1(F20, sp, 288);
        lwc1(F0, sp, 304);
        sub_s(F0, F0, F20);
        swc1(F0, sp, 380);
        spa(a0, 376);
        jal(0x2a6c38, rg::fn_sub_4C6AF0_004c6af0);
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
        spa(a0, 192);
        spa(a1, 360);
        spa(a2, 296);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a6c98, rg::fn_sub_2A4690_002a4690);
        spa(a0, 92);
        spa(a1, 192);
        jal(0x2a6ca8, rg::fn_sub_2D1F30_002d1f30);
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
        spa(a0, 208);
        spa(a1, 360);
        spa(a2, 296);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a6cf4, rg::fn_sub_2A4690_002a4690);
        spa(a0, 92);
        spa(a1, 208);
        jal(0x2a6d04, rg::fn_sub_2D1F30_002d1f30);
        c_lt_s(F21, F0);
        if (cc()) {
            charge(10);
            copy_vec4(sp, 192, sp, 120);
        } else {
            charge(8);
            copy_vec4(sp, 208, sp, 120);
        }
        charge(7);
        spa(a0, 344);
        la(a1, 0x69, kVecFwdLo);
        a2 = li(1);
        spa(a3, 120);
        jal(0x2a6d74, rg::fn_sub_4BE1E0_004be1e0);
    }
    charge(82);
    for (int k = 0; k < 3; ++k) {
        lwc1(F0, sp, 344 + 4 * k);
        mul_s(F0, F0, F23);
        swc1(F0, sp, 344 + 4 * k);
    }
    lif(v0, 0x3f00, F1);
    lwc1(F0, s2, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(0x2a6db8, rg::fn_tanf_0052e930);
    mul_s(F1, F23, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 344);
    swc1(F0, sp, 376);
    lwc1(F0, sp, 352);
    swc1(F0, sp, 380);
    spa(a0, 376);
    a1 = a0;
    jal(0x2a6dec, rg::fn_sub_4C6B20_004c6b20);
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
    spa(a0, 80);
    a1 = a0;
    jal(0x2a6e54, rg::fn_sub_2A3590_002a3590);
    spa(a0, 108);
    a1 = a0;
    jal(0x2a6e64, rg::fn_sub_2A3590_002a3590);
    a0 = s2;
    spa(a1, 80);
    spa(a2, 108);
    a3 = li(1);
    jal(0x2a6e7c, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4000, F12);
    a0 = s2;
    jal(0x2a6e90, rg::fn_sub_2A3110_002a3110);
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

// 0x2A54F0 sub_2A54F0(work, a1 = reset, a2 = degrees, a3 = degrees): a camera that follows the subject
// unit from behind. Follow (a1 == 0): the look point = the unit's position (sub_27FFB0) + its facing axis (0x697890
// rotated by unit+28) * half its radius (unit+144 * +44), raised by a quarter of its height (+140 * +44); the eye =
// the key position at a height between the party's (sub_280870(3, ...)) and the unit's. While the look-at from there
// turns no more than a2 degrees from the key rotation (gp-32536 = pi/180) it is kept; up to a3 degrees the key rotation
// turns a2 degrees toward it (slerp_toward, $f21, the eye rebuilt from the forward axis); beyond a3 the camera is set up
// anew as below. The distance: |key - look point| * 0.6, at least 1.5 * radius / tan(fov / 2) and 550; both heights at
// least 25; the camera reset to them (sub_2A2290) with the field of view max(1, a2 degrees / the remaining angle), at
// most 2 (2 when no angle is left) (sub_2A3110). Reset (a1 != 0, or beyond a3): reset_2A54F0.
void Cpu1::sub_2A54F0() {
    enter(16);
    sp = addiu(sp, -416);
    sd(ra, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s3 = a0;
    s2 = a2;
    s0 = a3;
    lw(v0, a0, kCwSubject);
    lw(s1, v0, kActUnit);
    bool reset = a1 != 0;
    if (!reset) {
        charge(67);
        spa(a0, 96);
        a1 = addiu(s3, kCwKey);
        jal(0x2a5538, rg::fn_sub_2A4470_002a4470);
        lwc1(F1, s1, 144);
        lwc1(F0, s1, 44);
        mul_s(F22, F1, F0);
        a0 = s1;
        spa(a1, 368);
        jal(0x2a5554, rg::fn_sub_27FFB0_0027ffb0);
        spa(a0, 384);
        la(a1, 0x69, kVecZLo);
        a2 = li(1);
        a3 = addiu(s1, 28);
        jal(0x2a5570, rg::fn_sub_4BE1E0_004be1e0);
        lif(v0, 0x3f00, F0);
        mul_s(F1, F0, F22);
        lwc1(F0, sp, 384);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 400);
        lwc1(F0, sp, 388);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 404);
        lwc1(F0, sp, 392);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 408);
        lwc1(F0, sp, 368);
        add_s(F0, F0, F3);
        swc1(F0, sp, 320);
        lwc1(F0, sp, 372);
        add_s(F3, F0, F2);
        swc1(F3, sp, 324);
        lwc1(F0, sp, 376);
        add_s(F0, F0, F1);
        swc1(F0, sp, 328);
        lwc1(F1, s1, 140);
        lwc1(F0, s1, 44);
        mul_s(F2, F1, F0);
        lif(v0, 0x3e80, F1);  // 0.25
        mtc1(zero, F0);
        adda_s(F0, F3);
        madd_s(F0, F1, F2);
        swc1(F0, sp, 324);
        a0 = li(3);
        a1 = 0;
        a2 = 0;
        spa(a3, 412);
        t0 = 0;
        t1 = li(1);
        jal(0x2a5610, rg::fn_sub_280870_00280870);
        ld(v0, sp, 96);
        lwc1(F0, sp, 104);
        sd(v0, sp, 400);
        swc1(F0, sp, 408);
        lwc1(F2, sp, 404);
        lwc1(F0, sp, 412);
        c_lt_s(F0, F2);
        if (cc()) {
            charge(3);
            swc1(F0, sp, 404);
        } else {
            charge(6);
            lwc1(F1, s1, 44);
            lwc1(F0, s1, 140);
            mul_s(F0, F0, F1);
            c_le_s(F0, F2);
            if (!cc()) {
                charge(1);
                swc1(F0, sp, 404);
            }
        }
        charge(19);
        spa(a0, 136);
        spa(a1, 400);
        spa(a2, 320);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a5678, rg::fn_sub_2A4690_002a4690);
        spa(a0, 108);
        spa(a1, 136);
        jal(0x2a5688, rg::fn_sub_2D1F30_002d1f30);
        mtc1(s2, F1);
        cvt_s_w(F1, F1);
        lwc1(F2, gp, -32536);
        mul_s(F20, F2, F1);
        c_le_s(F0, F20);
        if (!cc()) {
            charge(7);
            mtc1(s0, F1);
            cvt_s_w(F1, F1);
            mul_s(F1, F2, F1);
            c_le_s(F0, F1);
            if (!cc()) {
                reset = true;
            } else {
                slerp_toward(108, 136, 160, 224, 0x2a56e4, -32532, -32692, F21, F20);
                charge(26);
                spa(a0, 384);
                la(a1, 0x69, kVecFwdLo);
                a2 = li(1);
                spa(a3, 224);
                jal(0x2a5890, rg::fn_sub_4BE1E0_004be1e0);
                for (int k = 0; k < 3; ++k) {
                    lwc1(F1, sp, 336 + 4 * k);
                    lwc1(F0, sp, 384 + 4 * k);
                    add_s(F0, F1, F0);
                    swc1(F0, sp, 400 + 4 * k);
                }
                spa(a0, 136);
                spa(a1, 400);
                spa(a2, 336);
                la(a3, 0x69, kVecUpLo);
                jal(0x2a58dc, rg::fn_sub_2A4690_002a4690);
            }
        }
    }
    if (!reset) {
        charge(34);
        for (int k = 0; k < 3; ++k) {
            lwc1(F1, sp, 96 + 4 * k);
            lwc1(F0, sp, 320 + 4 * k);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 384 + 4 * k);
        }
        spa(a0, 384);
        a1 = a0;
        jal(0x2a591c, rg::fn_sub_4C69F0_004c69f0);
        lwc1(F1, gp, -32572);
        mul_s(F21, F0, F1);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s3, kCwFov);
        mul_s(F12, F1, F0);
        jal(0x2a593c, rg::fn_tanf_0052e930);
        lif(v0, 0x3fc0, F1);  // 1.5
        mul_s(F1, F1, F22);
        div_s(F0, F1, F0);
        c_le_s(F0, F21);
        if (!cc()) {
            charge(1);
            mov_s(F21, F0);
        }
        charge(7);
        v0 = li(550);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        c_lt_s(F21, F0);
        if (cc()) {
            charge(1);
            mov_s(F21, F0);
        }
        charge(32);
        spa(a0, 384);
        la(a1, 0x69, kVecFwdLo);
        a2 = li(1);
        spa(a3, 136);
        jal(0x2a59a4, rg::fn_sub_4BE1E0_004be1e0);
        lwc1(F0, sp, 384);
        mul_s(F3, F0, F21);
        swc1(F3, sp, 400);
        lwc1(F0, sp, 388);
        mul_s(F2, F0, F21);
        swc1(F2, sp, 404);
        lwc1(F0, sp, 392);
        mul_s(F1, F0, F21);
        swc1(F1, sp, 408);
        lwc1(F0, sp, 320);
        add_s(F0, F0, F3);
        swc1(F0, sp, 124);
        lwc1(F0, sp, 324);
        add_s(F0, F0, F2);
        swc1(F0, sp, 128);
        lwc1(F0, sp, 328);
        add_s(F0, F0, F1);
        swc1(F0, sp, 132);
        min_height_25(100, 7);
        min_height_25(128, 11);
        spa(a0, 108);
        spa(a1, 136);
        jal(0x2a5a3c, rg::fn_sub_2D1F30_002d1f30);
        lif(v0, 0x4000, F21);  // 2.0
        mtc1(zero, F1);
        c_le_s(F0, F1);
        if (!cc()) {
            charge(9);
            div_s(F0, F20, F0);
            lif(v0, 0x3f80, F21);
            c_le_s(F0, F21);
            if (!cc()) {
                charge(1);
                mul_s(F21, F0, F21);
            }
            charge(6);
            lif(v0, 0x4000, F0);
            c_le_s(F21, F0);
            if (!cc()) {
                charge(1);
                mov_s(F21, F0);
            }
        }
        charge(12);
        a0 = s3;
        spa(a1, 96);
        spa(a2, 124);
        a3 = li(1);
        jal(0x2a5ab4, rg::fn_sub_2A2290_002a2290);
        a0 = s3;
        mov_s(F12, F21);
        jal(0x2a5ac4, rg::fn_sub_2A3110_002a3110);
    } else {
        reset_2A54F0();
    }
    charge(11);
    ld(ra, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 416);
}

// sub_2A54F0's set-up (s3 = work, s1 = the subject's unit; sp the 416-byte frame): the unit's position (sub_27FFB0,
// sp+320) raised by a quarter of its height; the view direction (sp+352): the unit's facing (0x697890 rotated by
// unit+28) when the subject has one target, its own unit; else the direction from the unit to the target's position
// (sub_2D6290 ? the first target's unit : the centre of the targets' side, btlTargetGetSideMask / sub_280870) through sub_2D1DE0.
// A random yaw (datCalcRand(3): -30, 30 or 0 degrees about the up axis) and pitch (-15, 15 or 0 about the x axis) build a
// matrix (sub_4C31B0 x2) that turns the direction (sub_4C6C60, sp+384). The key = position + turned direction * 4 *
// radius / tan(fov / 2), looking at the position; the eye = position + view direction * 2.5 * radius / tan(...), the
// same; the subject's unit gets sub_2A3E80(.., 0, 0, 1; 0.0); both heights at least 25; the camera reset (sub_2A2290)
// with the field of view 3.0.
void Cpu1::reset_2A54F0() {
    charge(24);
    lw(a0, s3, kCwSubject);
    jal(0x2a5ad8, rg::fn_sub_2D6290_002d6290);
    s0 = v0;
    a0 = s1;
    spa(a1, 320);
    jal(0x2a5aec, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s1, 140);
    lwc1(F0, s1, 44);
    mul_s(F3, F1, F0);
    lif(v0, 0x3e80, F2);
    lwc1(F1, sp, 324);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F3);
    swc1(F0, sp, 324);
    lw(v1, s3, kCwSubject);
    lhu(v0, v1, kActTargetCount);
    a2 = li(1);
    bool facing = false;
    if (v0 == a2) {
        charge(4);
        lw(v0, v1, kActTargets);
        lw(v0, v0, kActUnit);
        facing = s1 == v0;
    }
    if (facing) {
        charge(8);
        spa(a0, 352);
        la(a1, 0x69, kVecZLo);
        a3 = addiu(s1, 28);
        jal(0x2a5b54, rg::fn_sub_4BE1E0_004be1e0);
    } else {
        charge(2);
        if (s0 != 0) {
            charge(7);
            lw(v0, v1, kActTargets);
            lw(a0, v0, kActUnit);
            spa(a1, 304);
            jal(0x2a5b78, rg::fn_sub_27FFB0_0027ffb0);
        } else {
            charge(11);
            a0 = addiu(v1, kActTargets);
            jal(0x2a5b8c, rg::fn_btlTargetGetSideMask_002d1600);
            a0 = v0 & 0xffff;
            a1 = li(1);
            spa(a2, 304);
            a3 = 0;
            t0 = 0;
            t1 = a1;
            jal(0x2a5bac, rg::fn_sub_280870_00280870);
        }
        charge(12);
        spa(a0, 208);
        spa(a1, 320);
        spa(a2, 304);
        jal(0x2a5bc0, rg::fn_sub_2D1DE0_002d1de0);
        spa(a0, 352);
        la(a1, 0x69, kVecZLo);
        a2 = li(1);
        spa(a3, 208);
        jal(0x2a5bdc, rg::fn_sub_4BE1E0_004be1e0);
    }
    charge(17);
    lwc1(F1, s1, 44);
    lwc1(F0, s1, 144);
    mul_s(F1, F0, F1);
    lif(v0, 0x4080, F0);  // 4.0
    mul_s(F22, F0, F1);
    lif(v0, 0x4020, F0);  // 2.5
    mul_s(F20, F0, F1);
    a0 = li(3);
    jal(0x2a5c14, rg::fn_datCalcRand_002ffbc0);
    rand3_pick(F21, 0xc1f0, 0x41f0);  // -30 / 30 / 0 degrees
    charge(6);
    a0 = li(3);
    jal(0x2a5c60, rg::fn_datCalcRand_002ffbc0);
    rand3_pick(F12, 0xc170, 0x4170);  // -15 / 15 / 0
    charge(110);
    spa(a0, 240);
    la(a1, 0x69, kVecXLo);
    a2 = 0;
    jal(0x2a5cb8, rg::fn_sub_4C31B0_004c31b0);
    spa(a0, 240);
    la(a1, 0x69, kVecUpLo);
    mov_s(F12, F21);
    a2 = li(2);
    jal(0x2a5cd4, rg::fn_sub_4C31B0_004c31b0);
    spa(a0, 384);
    spa(a1, 352);
    spa(a2, 240);
    jal(0x2a5ce8, rg::fn_sub_4C6C60_004c6c60);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s3, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(0x2a5d08, rg::fn_tanf_0052e930);
    div_s(F1, F22, F0);
    lwc1(F0, sp, 384);
    mul_s(F5, F0, F1);
    swc1(F5, sp, 384);
    lwc1(F0, sp, 388);
    mul_s(F4, F0, F1);
    swc1(F4, sp, 388);
    lwc1(F0, sp, 392);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 392);
    position_plus(96);
    spa(a0, 108);
    spa(a1, 96);
    spa(a2, 336);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a5d84, rg::fn_sub_2A4690_002a4690);
    lif(v0, 0x3f00, F1);
    lwc1(F0, s3, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(0x2a5da4, rg::fn_tanf_0052e930);
    div_s(F1, F20, F0);
    lwc1(F0, sp, 352);
    mul_s(F5, F0, F1);
    swc1(F5, sp, 384);
    lwc1(F0, sp, 356);
    mul_s(F4, F0, F1);
    swc1(F4, sp, 388);
    lwc1(F0, sp, 360);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 392);
    position_plus(124);
    spa(a0, 136);
    spa(a1, 124);
    spa(a2, 336);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a5e20, rg::fn_sub_2A4690_002a4690);
    mtc1(zero, F12);
    lw(a0, s3, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(0x2a5e3c, rg::fn_sub_2A3E80_002a3e80);
    min_height_25(100, 7);
    min_height_25(128, 11);
    a0 = s3;
    spa(a1, 96);
    spa(a2, 124);
    a3 = li(1);
    jal(0x2a5e94, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4040, F12);  // 3.0
    a0 = s3;
    jal(0x2a5ea8, rg::fn_sub_2A3110_002a3110);
}

// The datCalcRand(3) result in $v0 picked into $f`f`: 1 -> neg, 0 -> pos (float high halves), else 0.0.
void Cpu1::rand3_pick(unsigned f, u32 neg_hi, u32 pos_hi) {
    v1 = li(1);
    if (v0 == v1) {
        charge(4);
        lif(v0, neg_hi, f);
    } else {
        charge(2);
        if (v0 == 0) {
            charge(4);
            lif(v0, pos_hi, f);
        } else {
            charge(2);
            charge(1);
            mtc1(zero, f);
        }
    }
}

// The frame float sp+off raised to at least 25 (`lwc1; lui 0x41C8; mtc1; c.lt.s; bc1f`), then `next` cycles of the
// following block.
void Cpu1::min_height_25(s32 off, u64 next) {
    lwc1(F1, sp, off);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, off);
    }
    charge(next);
}

// sp+336.. = the position sp+320..; sp+dst.. = it + the scaled direction ($f5, $f4, $f3)
void Cpu1::position_plus(s32 dst) {
    lwc1(F0, sp, 320);
    swc1(F0, sp, 336);
    lwc1(F2, sp, 324);
    swc1(F2, sp, 340);
    lwc1(F1, sp, 328);
    swc1(F1, sp, 344);
    add_s(F0, F0, F5);
    swc1(F0, sp, dst);
    add_s(F0, F2, F4);
    swc1(F0, sp, dst + 4);
    add_s(F0, F1, F3);
    swc1(F0, sp, dst + 8);
}

// sub_2A79F0's two framings share this (s0 = work, s1 = the subject's unit, $f23 = the party's spread; the 336-byte
// frame: the unit's position sp+320, the party's centre sp+304 and height sp+332): a unit with a sub-object (+2560) has
// it set up (sub_2880E0(.., 0)) and noted in work+288 / +292 = 1; both heights become 0.75 * the party's height; the
// distance $f22 = spread / tan(fov / 2 * 1.2), at least `min_hi` (a float's high half); the direction party -> unit
// (normalised, or 0x697890 when they share x and z) scaled by the spread is added to the party's centre (sp+288).
// `scaled` = the cycles of the block that scales it.
void Cpu1::frame_2A79F0(u32 l_sub, u32 l_tan, u32 l_norm, u32 min_hi, u64 scaled) {
    charge(3);
    lw(a0, s1, 2560);
    if (a0 != 0) {
        charge(7);
        a1 = 0;
        jal(l_sub, rg::fn_sub_2880E0_002880e0);
        lw(v0, s1, 2560);
        sw(v0, s0, 288);
        v0 = li(1);
        sh(v0, s0, 292);
    }
    charge(23);
    lif(v0, 0x3f40, F1);  // 0.75
    lwc1(F0, sp, 332);
    mul_s(F0, F1, F0);
    swc1(F0, sp, 308);
    swc1(F0, sp, 324);
    lif(v0, 0x3f00, F21);
    lwc1(F20, gp, -32656);
    lwc1(F0, s0, kCwFov);
    mul_s(F0, F21, F0);
    mul_s(F12, F20, F0);
    jal(l_tan, rg::fn_tanf_0052e930);
    div_s(F22, F23, F0);
    lif(v0, min_hi, F0);
    c_lt_s(F22, F0);
    if (cc()) {
        charge(1);
        mov_s(F22, F0);
    }
    charge(5);
    lwc1(F3, sp, 320);
    lwc1(F2, sp, 304);
    c_eq_s(F2, F3);
    bool same = cc();
    if (same) {
        charge(5);
        lwc1(F1, sp, 312);
        lwc1(F0, sp, 328);
        c_eq_s(F1, F0);
        same = cc();
    }
    if (same) {
        charge(8);
        v0 = lui(0x69);
        ld(v1, v0, kVecZLo);
        v0 = lui(0x69);
        lwc1(F0, v0, kVecZLo + 8);
        sd(v1, sp, 272);
        swc1(F0, sp, 280);
    } else {
        charge(14);
        sub_s(F0, F2, F3);
        swc1(F0, sp, 272);
        lwc1(F1, sp, 308);
        lwc1(F0, sp, 324);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 276);
        lwc1(F1, sp, 312);
        lwc1(F0, sp, 328);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 280);
        spa(a0, 272);
        a1 = a0;
        jal(l_norm, rg::fn_sub_4C69F0_004c69f0);
    }
    charge(scaled);
    lwc1(F0, sp, 272);
    mul_s(F3, F0, F23);
    swc1(F3, sp, 272);
    lwc1(F0, sp, 276);
    mul_s(F2, F0, F23);
    swc1(F2, sp, 276);
    lwc1(F0, sp, 280);
    mul_s(F1, F0, F23);
    swc1(F1, sp, 280);
    lwc1(F4, sp, 304);
    add_s(F0, F4, F3);
    swc1(F0, sp, 288);
    lwc1(F0, sp, 308);
    add_s(F0, F0, F2);
    swc1(F0, sp, 292);
    lwc1(F2, sp, 312);
    add_s(F0, F2, F1);
    swc1(F0, sp, 296);
}

// The point toward sp+288 (at the height sp+308) from the party's centre sp+304, at gp-32616 * the distance: sp+240
// (through sp+dst.. and the direction sp+256). The far framing computes it twice, the common tail once more.
void Cpu1::toward_2A79F0(s32 dst, u32 l_norm, bool reload) {
    ld(v0, sp, 288);
    lwc1(F0, sp, 296);
    sd(v0, sp, dst);
    swc1(F0, sp, dst + 8);
    lwc1(F1, sp, 308);
    swc1(F1, sp, dst + 4);
    lwc1(F0, sp, dst);
    sub_s(F0, F0, F4);
    swc1(F0, sp, 256);
    sub_s(F0, F1, F1);
    swc1(F0, sp, 260);
    lwc1(F0, sp, dst + 8);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 264);
    spa(a0, 256);
    a1 = a0;
    jal(l_norm, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F1, gp, -32616);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 256);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 240);
    lwc1(F0, sp, 260);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 244);
    lwc1(F0, sp, 264);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 248);
    if (reload) {  // (the far framing keeps the centre in $f4 / $f2 for the tail)
        lwc1(F4, sp, 304);
        add_s(F0, F3, F4);
        swc1(F0, sp, 240);
        lwc1(F0, sp, 308);
        add_s(F0, F2, F0);
        swc1(F0, sp, 244);
        lwc1(F2, sp, 312);
        add_s(F0, F1, F2);
        swc1(F0, sp, 248);
    } else {
        lwc1(F0, sp, 304);
        add_s(F0, F3, F0);
        swc1(F0, sp, 240);
        lwc1(F0, sp, 308);
        add_s(F0, F2, F0);
        swc1(F0, sp, 244);
        lwc1(F0, sp, 312);
        add_s(F0, F1, F0);
        swc1(F0, sp, 248);
    }
}

// 0x2A79F0 sub_2A79F0(work): a wide shot of the party behind the subject. The unit's position (sub_27FFB0,
// sp+320) and the party's centre / spread / height (sub_280870(3, 1, sp+304, sp+332) -> $f23). With sub_2A3420 or
// sub_2A3380 set the near framing (distance at least 1000, the eye height 1.25 * the party's), else the far one (at
// least 1200, gp-32576 * the height but at most 200) -- frame_2A79F0. The look point sp+240 = the party's centre moved
// toward the eye by gp-32616 * the distance; the look-at sp+104; the eye = look point + its direction * distance,
// shifted sideways by 0.21875 * distance * tan(...) (sub_4C6B20); a second eye at 30 degrees about the up axis
// (sub_4C31B0, the side by sub_357FD0(0) bit 0) gives the key (sp+64, its look-at sp+76); sub_351BB0(12); both clamped
// by sub_2A3590 and at least 25 high; the camera reset (sub_2A2290(work, key, eye, 1)) with the field of view 10.0.
void Cpu1::sub_2A79F0() {
    enter(33);
    sp = addiu(sp, -336);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    spa(a0, 64);
    a1 = addiu(s0, kCwKey);
    jal(0x2a7a1c, rg::fn_sub_2A4470_002a4470);
    lw(v0, s0, kCwSubject);
    lw(s1, v0, kActUnit);
    a0 = s1;
    spa(a1, 320);
    jal(0x2a7a34, rg::fn_sub_27FFB0_0027ffb0);
    a0 = li(3);
    a1 = li(1);
    spa(a2, 304);
    spa(a3, 332);
    t0 = 0;
    t1 = 0;
    jal(0x2a7a54, rg::fn_sub_280870_00280870);
    mov_s(F23, F0);
    a0 = s0;
    jal(0x2a7a64, rg::fn_sub_2A3420_002a3420);
    bool near = v0 != 0;
    if (!near) {
        charge(5);
        a0 = s0;
        jal(0x2a7a78, rg::fn_sub_2A3380_002a3380);
        near = v0 != 0;
    }
    if (near) {
        frame_2A79F0(0x2a7a98, 0x2a7ae0, 0x2a7b88, 0x447a, 25);  // 1000
        lif(v0, 0x3fa0, F1);  // 1.25
        lwc1(F0, sp, 332);
        mul_s(F0, F1, F0);
        swc1(F0, sp, 292);
    } else {
        frame_2A79F0(0x2a7c04, 0x2a7c4c, 0x2a7cf4, 0x4496, 28);  // 1200
        lwc1(F1, gp, -32576);
        lwc1(F0, sp, 332);
        mul_s(F1, F1, F0);
        swc1(F1, sp, 292);
        lif(v0, 0x4348, F0);  // 200.0
        c_le_s(F1, F0);
        if (!cc()) {
            charge(1);
            swc1(F0, sp, 292);
        }
        charge(38);
        toward_2A79F0(224, 0x2a7db0, true);
    }
    charge(113);
    toward_2A79F0(200, 0x2a7e48, false);
    spa(a0, 104);
    spa(a1, 288);
    spa(a2, 240);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a7eb4, rg::fn_sub_2A4690_002a4690);
    for (int k = 0; k < 3; ++k) {
        lwc1(F1, sp, 288 + 4 * k);
        lwc1(F0, sp, 240 + 4 * k);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 272 + 4 * k);
    }
    spa(a0, 272);
    a1 = a0;
    jal(0x2a7ef4, rg::fn_sub_4C69F0_004c69f0);
    lwc1(F0, s0, kCwFov);
    mul_s(F0, F21, F0);
    mul_s(F12, F20, F0);
    jal(0x2a7f08, rg::fn_tanf_0052e930);
    mul_s(F1, F22, F0);
    lif(v0, 0x3e60, F0);  // 0.21875
    mul_s(F20, F1, F0);
    lwc1(F0, sp, 272);
    swc1(F0, sp, 216);
    lwc1(F0, sp, 280);
    swc1(F0, sp, 220);
    spa(a0, 216);
    a1 = a0;
    jal(0x2a7f3c, rg::fn_sub_4C6B20_004c6b20);
    lwc1(F1, sp, 220);
    lwc1(F0, sp, 240);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F5, F1, F20);
    swc1(F5, sp, 240);
    lwc1(F1, sp, 216);
    lwc1(F0, sp, 248);
    adda_s(F2, F0);
    msub_s(F4, F1, F20);
    swc1(F4, sp, 248);
    lwc1(F0, sp, 272);
    mul_s(F3, F0, F22);
    swc1(F3, sp, 256);
    lwc1(F0, sp, 276);
    mul_s(F2, F0, F22);
    swc1(F2, sp, 260);
    lwc1(F0, sp, 280);
    mul_s(F1, F0, F22);
    swc1(F1, sp, 264);
    add_s(F0, F5, F3);
    swc1(F0, sp, 92);
    lwc1(F0, sp, 244);
    add_s(F0, F0, F2);
    swc1(F0, sp, 96);
    add_s(F0, F4, F1);
    swc1(F0, sp, 100);
    a0 = 0;
    jal(0x2a7fb8, rg::fn_sub_357FD0_00357fd0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        charge(10);
        lif(v0, 0xc1f0, F12);  // -30 degrees
        spa(a0, 128);
        la(a1, 0x69, kVecUpLo);
        a2 = 0;
        jal(0x2a7fe4, rg::fn_sub_4C31B0_004c31b0);
    } else {
        charge(8);
        lif(v0, 0x41f0, F12);  // 30 degrees
        spa(a0, 128);
        la(a1, 0x69, kVecUpLo);
        a2 = 0;
        jal(0x2a800c, rg::fn_sub_4C31B0_004c31b0);
    }
    charge(48);
    spa(a0, 256);
    spa(a1, 272);
    spa(a2, 128);
    jal(0x2a8020, rg::fn_sub_4C6C60_004c6c60);
    for (int k = 0; k < 3; ++k) {
        lwc1(F0, sp, 256 + 4 * k);
        mul_s(static_cast<unsigned>(F3 - k), F0, F22);
        swc1(static_cast<unsigned>(F3 - k), sp, 256 + 4 * k);
    }
    for (int k = 0; k < 3; ++k) {
        lwc1(F0, sp, 240 + 4 * k);
        add_s(F0, F0, static_cast<unsigned>(F3 - k));
        swc1(F0, sp, 64 + 4 * k);
    }
    spa(a0, 76);
    spa(a1, 64);
    spa(a2, 240);
    la(a3, 0x69, kVecUpLo);
    jal(0x2a8084, rg::fn_sub_2A4690_002a4690);
    a0 = li(12);
    jal(0x2a8090, rg::fn_sub_351BB0_00351bb0);
    spa(a0, 64);
    a1 = a0;
    jal(0x2a80a0, rg::fn_sub_2A3590_002a3590);
    spa(a0, 92);
    a1 = a0;
    jal(0x2a80b0, rg::fn_sub_2A3590_002a3590);
    min_height_25(68, 7);
    min_height_25(96, 21);
    a0 = s0;
    spa(a1, 64);
    spa(a2, 92);
    a3 = li(1);
    jal(0x2a8108, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4120, F12);  // 10.0
    a0 = s0;
    jal(0x2a811c, rg::fn_sub_2A3110_002a3110);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 336);
}

// `c.le.s fa, fb; bc1t` max idiom: fa = max(fa, fb), 1 cycle when fb wins, 2 otherwise
void Cpu1::fmax_to(unsigned fa, unsigned fb) {
    c_le_s(fa, fb);
    if (cc()) {
        charge(1);
        mov_s(fa, fb);
    } else {
        charge(2);
    }
}

// The side pick of sub_2A8150: sp+208 = the yaw matrix of +deg or -deg (a float's high half) about the up axis
// (sub_4C31B0), by the sign the caller left in the FPU condition.
void Cpu1::yaw_2A8150(bool negative, u32 pos_hi, u32 neg_hi, u32 l_pos, u32 l_neg) {
    if (!negative) {
        charge(10);
        lif(v0, pos_hi, F12);
        spa(a0, 208);
        la(a1, 0x69, kVecUpLo);
        a2 = 0;
        jal(l_pos, rg::fn_sub_4C31B0_004c31b0);
    } else {
        charge(8);
        lif(v0, neg_hi, F12);
        spa(a0, 208);
        la(a1, 0x69, kVecUpLo);
        a2 = 0;
        jal(l_neg, rg::fn_sub_4C31B0_004c31b0);
    }
}

// The eye of sub_2A8150 from the turned facing (sp+368 = sp+352 through the matrix sp+208, sub_4C6C60): sp+384 = the
// centre sp+432 (+ $f21 / $f20 kept from it) + it * $f27, its height gp-32644 * the second unit's height when that is
// the higher (`c.lt.s $f25, $f24`). `first` = the 37.5-degree pass ($f21 / $f20 reloaded from the centre).
void Cpu1::eye_2A8150(u32 l_turn, bool first) {
    spa(a0, 368);
    spa(a1, 352);
    spa(a2, 208);
    jal(l_turn, rg::fn_sub_4C6C60_004c6c60);
    lwc1(F0, sp, 368);
    mul_s(F3, F0, F27);
    swc1(F3, sp, 368);
    lwc1(F0, sp, 372);
    mul_s(F2, F0, F27);
    swc1(F2, sp, 372);
    lwc1(F0, sp, 376);
    mul_s(F1, F0, F27);
    swc1(F1, sp, 376);
    lwc1(F0, sp, 432);
    add_s(F0, F3, F0);
    swc1(F0, sp, 384);
    if (first) lwc1(F21, sp, 436);
    add_s(F0, F2, F21);
    swc1(F0, sp, 388);
    if (first) lwc1(F20, sp, 440);
    add_s(F0, F1, F20);
    swc1(F0, sp, 392);
    c_lt_s(F25, F24);
    if (cc()) {
        charge(3);
        lwc1(F0, gp, -32644);
        mul_s(F0, F0, F24);
        swc1(F0, sp, 388);
    }
}

// 0x2A8150 sub_2A8150(work, a1 = rumble, a2 = keep key): a camera on the subject unit and its sub-object (+2560: a
// summoned persona). s1 = sub_2A3520(work) || sub_2A3550(work). Both positions (sub_27FFB0: unit sp+416, sub-object
// sp+400) and half heights ($f25 / $f24), radii ($f22 / $f26). Unless s1, a sub-object whose ENEMY-like record (88 bytes
// at *(gp-18628), index sub-object+164) has bit 0 set gets the close-up (sub_2880E0(.., 1)): the centre = the
// sub-object's position at a quarter height, the eye along the unit's facing (0x697890 rotated by unit+28) at radius,
// the distance 1.25 * max(radius, half height) / tan(fov / 2) (at least radius + 375). Otherwise: without s1 the
// sub-object is set up (sub_2880E0(.., 0)), the centre = the midpoint of the two and the distance 1.75 * the largest of
// the four centre distances (+ radii); with s1 the centre = the unit's position, the second height its + 1, the distance
// 5.5 * radius. Then two eyes 37.5 and 70 degrees off the unit's facing (the side by the facing against the key
// direction), each looking at the centre (sub_2A4690) and shifted sideways (0.21875 * distance * tan(...)). Both
// heights at least 25; without a2 the key becomes the eye; sub_2A3E80(subject, 0, 0, 1; 0.0); the camera reset
// (sub_2A2290(work, key, eye, 1)) with the field of view 2.5; a1 -> sub_351BB0(12).
void Cpu1::sub_2A8150() {
    enter(23);
    sp = addiu(sp, -448);
    sd(ra, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    for (int k = 7; k >= 0; --k) swc1(static_cast<unsigned>(F20 + k), sp, 4 * k);
    s4 = a0;
    s3 = a1;
    s5 = a2;
    jal(0x2a819c, rg::fn_sub_2A3520_002a3520);
    bool special = v0 != 0;
    if (!special) {
        charge(5);
        a0 = s4;
        jal(0x2a81b0, rg::fn_sub_2A3550_002a3550);
        special = v0 != 0;
    }
    if (special) {
        charge(3);
        s1 = li(1);
    } else {
        charge(1);
        s1 = 0;
    }
    charge(33);
    lw(v0, s4, kCwSubject);
    lw(s0, v0, kActUnit);
    lw(s2, s0, 2560);
    a0 = s0;
    spa(a1, 416);
    jal(0x2a81e4, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s2;
    spa(a1, 400);
    jal(0x2a81f4, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F5, s0, 44);
    lwc1(F0, s0, 140);
    mul_s(F1, F0, F5);
    lif(v0, 0x3f00, F4);
    lwc1(F0, sp, 420);
    mtc1(zero, F3);
    adda_s(F3, F0);
    madd_s(F25, F4, F1);
    lwc1(F2, s2, 44);
    lwc1(F0, s2, 140);
    mul_s(F1, F0, F2);
    lwc1(F0, sp, 404);
    adda_s(F3, F0);
    madd_s(F24, F4, F1);
    lwc1(F0, s0, 144);
    mul_s(F22, F0, F5);
    lwc1(F0, s2, 144);
    mul_s(F26, F0, F2);
    bool close_up = false;
    if (s1 == 0) {
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
        v0 = v0 & 0x1;
        close_up = v0 != 0;
    }
    if (!close_up) {
        charge(2);
        if (s1 == 0) {
            charge(55);
            a0 = s2;
            a1 = 0;
            jal(0x2a8294, rg::fn_sub_2880E0_002880e0);
            // the centre sp+432 = the midpoint of the two positions
            lwc1(F7, sp, 416);
            lwc1(F0, sp, 400);
            add_s(F6, F7, F0);
            swc1(F6, sp, 432);
            lwc1(F5, sp, 420);
            lwc1(F0, sp, 404);
            add_s(F4, F5, F0);
            swc1(F4, sp, 436);
            lwc1(F3, sp, 424);
            lwc1(F0, sp, 408);
            add_s(F2, F3, F0);
            swc1(F2, sp, 440);
            lif(v0, 0x3f00, F1);
            mul_s(F0, F6, F1);
            swc1(F0, sp, 432);
            mul_s(F21, F4, F1);
            swc1(F21, sp, 436);
            mul_s(F20, F2, F1);
            swc1(F20, sp, 440);
            sub_s(F0, F7, F0);
            swc1(F0, sp, 368);
            sub_s(F0, F5, F21);
            swc1(F0, sp, 372);
            sub_s(F0, F3, F20);
            swc1(F0, sp, 376);
            spa(a0, 368);
            jal(0x2a830c, rg::fn_sub_4C6AC0_004c6ac0);
            add_s(F23, F0, F22);
            ld(v0, sp, 416);
            lwc1(F0, sp, 424);
            sd(v0, sp, 384);
            swc1(F0, sp, 392);
            swc1(F25, sp, 388);
            lwc1(F1, sp, 384);
            lwc1(F0, sp, 432);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 368);
            sub_s(F0, F25, F21);
            swc1(F0, sp, 372);
            lwc1(F0, sp, 392);
            sub_s(F0, F0, F20);
            swc1(F0, sp, 376);
            spa(a0, 368);
            jal(0x2a8354, rg::fn_sub_4C6AC0_004c6ac0);
            fmax_to(F23, F0);
            charge(36);
            lwc1(F1, sp, 400);
            lwc1(F0, sp, 432);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 368);
            lwc1(F22, sp, 436);
            lwc1(F0, sp, 404);
            sub_s(F0, F0, F22);
            swc1(F0, sp, 372);
            lwc1(F21, sp, 440);
            lwc1(F0, sp, 408);
            sub_s(F0, F0, F21);
            swc1(F0, sp, 376);
            spa(a0, 368);
            jal(0x2a83a8, rg::fn_sub_4C6AC0_004c6ac0);
            add_s(F20, F0, F26);
            ld(v0, sp, 400);
            lwc1(F0, sp, 408);
            sd(v0, sp, 384);
            swc1(F0, sp, 392);
            swc1(F24, sp, 388);
            lwc1(F1, sp, 384);
            lwc1(F0, sp, 432);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 368);
            sub_s(F0, F24, F22);
            swc1(F0, sp, 372);
            lwc1(F0, sp, 392);
            sub_s(F0, F0, F21);
            swc1(F0, sp, 376);
            spa(a0, 368);
            jal(0x2a83f0, rg::fn_sub_4C6AC0_004c6ac0);
            fmax_to(F20, F0);
            charge(7);
            ld(v0, sp, 432);
            lwc1(F0, sp, 440);
            sd(v0, sp, 336);
            swc1(F0, sp, 344);
            fmax_to(F23, F20);
            charge(6);
            lif(v0, 0x3fe0, F0);  // 1.75
            mul_s(F27, F23, F0);
        } else {
            charge(18);
            ld(v0, sp, 416);
            lwc1(F0, sp, 424);
            sd(v0, sp, 312);
            swc1(F0, sp, 320);
            ld(v0, sp, 312);
            lwc1(F0, sp, 320);
            sd(v0, sp, 432);
            swc1(F0, sp, 440);
            sd(v0, sp, 336);
            swc1(F0, sp, 344);
            lif(v0, 0x3f80, F0);
            add_s(F24, F0, F25);
            lif(v0, 0x40b0, F0);  // 5.5
            mul_s(F27, F0, F22);
        }
        charge(38);
        lwc1(F1, s4, kCwKey);
        lwc1(F0, sp, 336);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 280);
        lwc1(F1, s4, kCwKey + 8);
        lwc1(F0, sp, 344);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 284);
        spa(a0, 280);
        a1 = a0;
        jal(0x2a84c0, rg::fn_sub_4C6B20_004c6b20);
        spa(a0, 352);
        la(a1, 0x69, kVecZLo);
        a2 = li(1);
        a3 = addiu(s0, 28);
        jal(0x2a84dc, rg::fn_sub_4BE1E0_004be1e0);
        lwc1(F0, sp, 360);
        swc1(F0, sp, 272);
        lwc1(F0, sp, 352);
        neg_s(F0, F0);
        swc1(F0, sp, 276);
        spa(a0, 272);
        a1 = a0;
        jal(0x2a8500, rg::fn_sub_4C6B20_004c6b20);
        lwc1(F3, sp, 272);
        lwc1(F2, sp, 280);
        lwc1(F1, sp, 276);
        lwc1(F0, sp, 284);
        mula_s(F1, F0);
        mtc1(zero, F0);
        madd_s(F22, F3, F2);
        c_lt_s(F22, F0);
        yaw_2A8150(cc(), 0x4216, 0xc216, 0x2a8548, 0x2a8570);  // +-37.5 degrees
        charge(26);
        eye_2A8150(0x2a8584, true);
        charge(86);
        for (int k = 0; k < 3; ++k) {
            lwc1(F1, sp, 384 + 4 * k);
            lwc1(F0, sp, 336 + 4 * k);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 368 + 4 * k);
        }
        spa(a0, 368);
        a1 = a0;
        jal(0x2a8624, rg::fn_sub_4C69F0_004c69f0);
        spa(a0, 184);
        spa(a1, 384);
        spa(a2, 336);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a8640, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s4, kCwFov);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32656);
        mul_s(F12, F0, F1);
        jal(0x2a8660, rg::fn_tanf_0052e930);
        div_s(F26, F27, F0);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s4, kCwFov);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32656);
        mul_s(F12, F0, F1);
        jal(0x2a868c, rg::fn_tanf_0052e930);
        mul_s(F1, F26, F0);
        lif(v0, 0x3e60, F0);  // 0.21875
        mul_s(F23, F1, F0);
        lwc1(F0, sp, 368);
        swc1(F0, sp, 328);
        lwc1(F0, sp, 376);
        swc1(F0, sp, 332);
        spa(a0, 328);
        a1 = a0;
        jal(0x2a86c0, rg::fn_sub_4C6B20_004c6b20);
        lwc1(F1, sp, 332);
        lwc1(F0, sp, 336);
        mtc1(zero, F5);
        adda_s(F5, F0);
        madd_s(F6, F1, F23);
        swc1(F6, sp, 336);
        lwc1(F1, sp, 328);
        lwc1(F0, sp, 344);
        adda_s(F5, F0);
        msub_s(F4, F1, F23);
        swc1(F4, sp, 344);
        lwc1(F0, sp, 368);
        mul_s(F3, F0, F26);
        swc1(F3, sp, 384);
        lwc1(F0, sp, 372);
        mul_s(F2, F0, F26);
        swc1(F2, sp, 388);
        lwc1(F0, sp, 376);
        mul_s(F1, F0, F26);
        swc1(F1, sp, 392);
        add_s(F0, F6, F3);
        swc1(F0, sp, 172);
        lwc1(F0, sp, 340);
        add_s(F0, F0, F2);
        swc1(F0, sp, 176);
        add_s(F0, F4, F1);
        swc1(F0, sp, 180);
        c_lt_s(F22, F5);
        yaw_2A8150(cc(), 0x428c, 0xc28c, 0x2a875c, 0x2a8784);  // +-70 degrees
        charge(24);
        eye_2A8150(0x2a8798, false);
        charge(78);
        for (int k = 0; k < 3; ++k) {
            lwc1(F1, sp, 384 + 4 * k);
            lwc1(F0, sp, 336 + 4 * k);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 368 + 4 * k);
        }
        spa(a0, 368);
        a1 = a0;
        jal(0x2a8830, rg::fn_sub_4C69F0_004c69f0);
        spa(a2, 336);
        ld(v0, sp, 432);
        lwc1(F0, sp, 440);
        sd(v0, sp, 336);
        swc1(F0, sp, 344);
        spa(a0, 156);
        spa(a1, 384);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a885c, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s4, kCwFov);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32656);
        mul_s(F12, F0, F1);
        jal(0x2a887c, rg::fn_tanf_0052e930);
        mul_s(F1, F26, F0);
        lif(v0, 0x3e60, F0);
        mul_s(F20, F1, F0);
        lwc1(F0, sp, 368);
        swc1(F0, sp, 328);
        lwc1(F0, sp, 376);
        swc1(F0, sp, 332);
        spa(a0, 328);
        a1 = a0;
        jal(0x2a88b0, rg::fn_sub_4C6B20_004c6b20);
        lwc1(F1, sp, 332);
        lwc1(F0, sp, 336);
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F5, F1, F20);
        swc1(F5, sp, 336);
        lwc1(F1, sp, 328);
        lwc1(F0, sp, 344);
        adda_s(F2, F0);
        msub_s(F4, F1, F20);
        swc1(F4, sp, 344);
        lwc1(F0, sp, 368);
        mul_s(F3, F0, F26);
        swc1(F3, sp, 384);
        lwc1(F0, sp, 372);
        mul_s(F2, F0, F26);
        swc1(F2, sp, 388);
        lwc1(F0, sp, 376);
        mul_s(F1, F0, F26);
        swc1(F1, sp, 392);
        add_s(F0, F5, F3);
        swc1(F0, sp, 144);
        lwc1(F0, sp, 340);
        add_s(F0, F0, F2);
        swc1(F0, sp, 148);
        add_s(F0, F4, F1);
        swc1(F0, sp, 152);
    } else {
        // the close-up of the sub-object
        charge(77);
        a0 = s2;
        a1 = li(1);
        jal(0x2a8938, rg::fn_sub_2880E0_002880e0);
        ld(v0, sp, 400);
        lwc1(F0, sp, 408);
        sd(v0, sp, 296);
        swc1(F0, sp, 304);
        ld(v1, sp, 296);
        lwc1(F1, sp, 304);
        sd(v1, sp, 432);
        swc1(F1, sp, 440);
        lif(v0, 0x3e80, F0);  // 0.25
        mul_s(F0, F0, F24);
        swc1(F0, sp, 436);
        sd(v1, sp, 336);
        swc1(F1, sp, 344);
        lwc1(F0, gp, -32640);
        mul_s(F0, F0, F24);
        swc1(F0, sp, 340);
        spa(a0, 352);
        la(a1, 0x69, kVecZLo);
        a2 = li(1);
        a3 = addiu(s0, 28);
        jal(0x2a899c, rg::fn_sub_4BE1E0_004be1e0);
        lwc1(F0, sp, 352);
        mul_s(F1, F0, F26);
        swc1(F1, sp, 368);
        lwc1(F0, sp, 356);
        mul_s(F4, F0, F26);
        swc1(F4, sp, 372);
        lwc1(F0, sp, 360);
        mul_s(F2, F0, F26);
        swc1(F2, sp, 376);
        lwc1(F0, sp, 432);
        add_s(F3, F1, F0);
        swc1(F3, sp, 384);
        lwc1(F1, sp, 436);
        add_s(F0, F4, F1);
        swc1(F0, sp, 388);
        lwc1(F0, sp, 440);
        add_s(F2, F2, F0);
        swc1(F2, sp, 392);
        lwc1(F0, gp, -32636);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 388);
        lwc1(F0, sp, 336);
        sub_s(F0, F3, F0);
        swc1(F0, sp, 368);
        lwc1(F0, sp, 340);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 372);
        lwc1(F0, sp, 344);
        sub_s(F0, F2, F0);
        swc1(F0, sp, 376);
        spa(a0, 368);
        a1 = a0;
        jal(0x2a8a24, rg::fn_sub_4C69F0_004c69f0);
        spa(a0, 184);
        spa(a1, 384);
        spa(a2, 336);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a8a40, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0x3f00, F1);
        mul_s(F20, F1, F24);
        c_le_s(F26, F20);
        if (!cc()) {
            charge(16);
            lwc1(F0, s4, kCwFov);
            mul_s(F1, F1, F0);
            lwc1(F0, gp, -32656);
            mul_s(F12, F0, F1);
            jal(0x2a8a74, rg::fn_tanf_0052e930);
            lif(v0, 0x3fa0, F1);  // 1.25
            mul_s(F1, F1, F26);
            div_s(F20, F1, F0);
        } else {
            charge(9);
            lwc1(F0, s4, kCwFov);
            mul_s(F12, F1, F0);
            jal(0x2a8aac, rg::fn_tanf_0052e930);
            lif(v0, 0x3fa0, F1);
            mul_s(F1, F1, F20);
            div_s(F20, F1, F0);
        }
        charge(8);
        sub_s(F1, F20, F26);
        v0 = li(375);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            add_s(F20, F0, F26);
        }
        charge(67);
        lwc1(F0, sp, 368);
        mul_s(F3, F0, F20);
        swc1(F3, sp, 384);
        lwc1(F0, sp, 372);
        mul_s(F2, F0, F20);
        swc1(F2, sp, 388);
        lwc1(F0, sp, 376);
        mul_s(F1, F0, F20);
        swc1(F1, sp, 392);
        lwc1(F0, sp, 336);
        add_s(F0, F0, F3);
        swc1(F0, sp, 172);
        lwc1(F0, sp, 340);
        add_s(F0, F0, F2);
        swc1(F0, sp, 176);
        lwc1(F0, sp, 344);
        add_s(F0, F0, F1);
        swc1(F0, sp, 180);
        spa(a2, 336);
        ld(v0, sp, 416);
        lwc1(F0, sp, 424);
        sd(v0, sp, 336);
        swc1(F0, sp, 344);
        swc1(F25, sp, 340);
        lwc1(F0, sp, 352);
        mul_s(F3, F0, F26);
        swc1(F3, sp, 368);
        lwc1(F0, sp, 356);
        mul_s(F2, F0, F26);
        swc1(F2, sp, 372);
        lwc1(F0, sp, 360);
        mul_s(F1, F0, F26);
        swc1(F1, sp, 376);
        lwc1(F0, sp, 336);
        add_s(F0, F3, F0);
        swc1(F0, sp, 384);
        add_s(F0, F2, F25);
        swc1(F0, sp, 388);
        lwc1(F0, sp, 344);
        add_s(F0, F1, F0);
        swc1(F0, sp, 392);
        spa(a0, 156);
        spa(a1, 384);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a8ba0, rg::fn_sub_2A4690_002a4690);
        lwc1(F0, gp, -32632);
        mul_s(F1, F0, F20);
        lwc1(F0, sp, 352);
        mul_s(F3, F0, F1);
        swc1(F3, sp, 384);
        lwc1(F0, sp, 356);
        mul_s(F2, F0, F1);
        swc1(F2, sp, 388);
        lwc1(F0, sp, 360);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 392);
        lwc1(F0, sp, 336);
        add_s(F0, F0, F3);
        swc1(F0, sp, 144);
        lwc1(F0, sp, 340);
        add_s(F0, F0, F2);
        swc1(F0, sp, 148);
        lwc1(F0, sp, 344);
        add_s(F0, F0, F1);
        swc1(F0, sp, 152);
    }
    charge(7);
    min_height_25(148, 7);
    min_height_25(176, 2);
    if (s5 == 0) {
        charge(14);
        copy_vec3(sp, 172, sp, 144);
        copy_vec4(sp, 184, sp, 156);
    }
    charge(20);
    mtc1(zero, F12);
    lw(a0, s4, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(0x2a8c8c, rg::fn_sub_2A3E80_002a3e80);
    a0 = s4;
    spa(a1, 144);
    spa(a2, 172);
    a3 = li(1);
    jal(0x2a8ca4, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4020, F12);  // 2.5
    a0 = s4;
    jal(0x2a8cb8, rg::fn_sub_2A3110_002a3110);
    if (s3 != 0) {
        charge(3);
        a0 = li(12);
        jal(0x2a8ccc, rg::fn_sub_351BB0_00351bb0);
    }
    charge(18);
    ld(ra, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    for (int k = 7; k >= 0; --k) lwc1(static_cast<unsigned>(F20 + k), sp, 4 * k);
    sp = addiu(sp, 448);
}

// 0x2A8D20 sub_2A8D20(work, a1 = rumble): the summon camera (a front view of the subject unit and its sub-object +2560).
// Both positions (unit sp+288, sub-object sp+272), half heights ($f27 / $f26), radii ($f20 / $f28). A sub-object whose
// ENEMY-like record (88 bytes at *(gp-18628), index +164) has bit 0 set gets the close-up (sub_2880E0(.., 1)): the
// centre = its position at gp-32632 * its height, the look point at gp-32668 * it, the eye along the unit's facing
// (0x697890 rotated by unit+28) at its radius (height gp-32636 * ...), the distance 1.25 * max(radius, half height) /
// tan(fov / 2), at least radius + 350; the key one gp-32572 * the distance from the unit's position at its half height.
// Otherwise (sub_2880E0(.., 0)): the centre = the midpoint, the distance gp-32484 * the largest centre distance (+
// radii), the eye along the facing at half the larger height, the key 0.75 * the distance from the unit's position at
// 0.75 * its half height. Both heights at least 25; sub_2A3E80(subject, 0, 0, 1; 0.0); the camera reset (sub_2A2290(
// work, key, eye, 1)) with the field of view 2.0; a1 -> sub_351BB0(12).
void Cpu1::sub_2A8D20() {
    enter(60);
    sp = addiu(sp, -320);
    sd(ra, sp, 112);
    sq(s3, sp, 96);
    sq(s2, sp, 80);
    sq(s1, sp, 64);
    sq(s0, sp, 48);
    for (int k = 8; k >= 0; --k) swc1(static_cast<unsigned>(F20 + k), sp, 4 * k);
    s3 = a0;
    s2 = a1;
    lw(v0, a0, kCwSubject);
    lw(s0, v0, kActUnit);
    lw(s1, s0, 2560);
    a0 = s0;
    spa(a1, 288);
    jal(0x2a8d78, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s1;
    spa(a1, 272);
    jal(0x2a8d88, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F5, s0, 44);
    lwc1(F0, s0, 140);
    mul_s(F1, F0, F5);
    lif(v0, 0x3f00, F4);
    lwc1(F0, sp, 292);
    mtc1(zero, F3);
    adda_s(F3, F0);
    madd_s(F27, F4, F1);
    lwc1(F2, s1, 44);
    lwc1(F0, s1, 140);
    mul_s(F1, F0, F2);
    lwc1(F0, sp, 276);
    adda_s(F3, F0);
    madd_s(F26, F4, F1);
    lwc1(F0, s0, 144);
    mul_s(F20, F0, F5);
    lwc1(F0, s1, 144);
    mul_s(F28, F0, F2);
    lhu(v1, s1, 164);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    lw(v0, gp, -18628);
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        charge(55);
        a0 = s1;
        a1 = 0;
        jal(0x2a8e18, rg::fn_sub_2880E0_002880e0);
        lwc1(F7, sp, 288);
        lwc1(F0, sp, 272);
        add_s(F6, F7, F0);
        swc1(F6, sp, 304);
        lwc1(F5, sp, 292);
        lwc1(F0, sp, 276);
        add_s(F4, F5, F0);
        swc1(F4, sp, 308);
        lwc1(F3, sp, 296);
        lwc1(F0, sp, 280);
        add_s(F2, F3, F0);
        swc1(F2, sp, 312);
        lif(v0, 0x3f00, F1);
        mul_s(F0, F6, F1);
        swc1(F0, sp, 304);
        mul_s(F23, F4, F1);
        swc1(F23, sp, 308);
        mul_s(F22, F2, F1);
        swc1(F22, sp, 312);
        sub_s(F0, F7, F0);
        swc1(F0, sp, 240);
        sub_s(F0, F5, F23);
        swc1(F0, sp, 244);
        sub_s(F0, F3, F22);
        swc1(F0, sp, 248);
        spa(a0, 240);
        jal(0x2a8e90, rg::fn_sub_4C6AC0_004c6ac0);
        add_s(F25, F0, F20);
        ld(v0, sp, 288);
        lwc1(F0, sp, 296);
        sd(v0, sp, 256);
        swc1(F0, sp, 264);
        swc1(F27, sp, 260);
        lwc1(F1, sp, 256);
        lwc1(F0, sp, 304);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 240);
        sub_s(F0, F27, F23);
        swc1(F0, sp, 244);
        lwc1(F0, sp, 264);
        sub_s(F0, F0, F22);
        swc1(F0, sp, 248);
        spa(a0, 240);
        jal(0x2a8ed8, rg::fn_sub_4C6AC0_004c6ac0);
        fmax_to(F25, F0);
        charge(36);
        lwc1(F1, sp, 272);
        lwc1(F0, sp, 304);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 240);
        lwc1(F21, sp, 308);
        lwc1(F0, sp, 276);
        sub_s(F0, F0, F21);
        swc1(F0, sp, 244);
        lwc1(F20, sp, 312);
        lwc1(F0, sp, 280);
        sub_s(F0, F0, F20);
        swc1(F0, sp, 248);
        spa(a0, 240);
        jal(0x2a8f2c, rg::fn_sub_4C6AC0_004c6ac0);
        add_s(F24, F0, F28);
        ld(v0, sp, 272);
        lwc1(F0, sp, 280);
        sd(v0, sp, 256);
        swc1(F0, sp, 264);
        swc1(F26, sp, 260);
        lwc1(F1, sp, 256);
        lwc1(F0, sp, 304);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 240);
        sub_s(F0, F26, F21);
        swc1(F0, sp, 244);
        lwc1(F0, sp, 264);
        sub_s(F0, F0, F20);
        swc1(F0, sp, 248);
        spa(a0, 240);
        jal(0x2a8f74, rg::fn_sub_4C6AC0_004c6ac0);
        fmax_to(F24, F0);
        charge(7);
        ld(v0, sp, 304);
        lwc1(F0, sp, 312);
        sd(v0, sp, 208);
        swc1(F0, sp, 216);
        c_lt_s(F27, F26);
        if (cc()) {
            charge(4);
            lwc1(F0, gp, -32636);
            mul_s(F0, F0, F26);
        } else {
            charge(2);
            lwc1(F0, gp, -32636);
            mul_s(F0, F0, F27);
        }
        charge(4);
        swc1(F0, sp, 212);
        fmax_to(F25, F24);
        charge(28);
        lwc1(F0, gp, -32484);
        mul_s(F20, F25, F0);
        spa(a0, 224);
        la(a1, 0x69, kVecZLo);
        a2 = li(1);
        a3 = addiu(s0, 28);
        jal(0x2a9000, rg::fn_sub_4BE1E0_004be1e0);
        lwc1(F0, sp, 224);
        mul_s(F3, F0, F20);
        swc1(F3, sp, 240);
        lwc1(F0, sp, 228);
        mul_s(F2, F0, F20);
        swc1(F2, sp, 244);
        lwc1(F0, sp, 232);
        mul_s(F1, F0, F20);
        swc1(F1, sp, 248);
        lwc1(F0, sp, 304);
        add_s(F0, F3, F0);
        swc1(F0, sp, 256);
        add_s(F0, F2, F23);
        swc1(F0, sp, 260);
        add_s(F0, F1, F22);
        swc1(F0, sp, 264);
        c_lt_s(F27, F26);
        if (cc()) {
            charge(6);
            lif(v0, 0x3f00, F0);
            mul_s(F2, F0, F26);
        } else {
            charge(4);
            lif(v0, 0x3f00, F0);
            mul_s(F2, F0, F27);
        }
        charge(109);
        swc1(F2, sp, 260);
        lwc1(F1, sp, 256);
        lwc1(F0, sp, 208);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 240);
        lwc1(F0, sp, 212);
        sub_s(F0, F2, F0);
        swc1(F0, sp, 244);
        lwc1(F1, sp, 264);
        lwc1(F0, sp, 216);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 248);
        spa(a0, 240);
        a1 = a0;
        jal(0x2a90b4, rg::fn_sub_4C69F0_004c69f0);
        spa(a0, 168);
        spa(a1, 256);
        spa(a2, 208);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a90d0, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0x3f00, F1);
        lwc1(F0, s3, kCwFov);
        mul_s(F1, F1, F0);
        lwc1(F0, gp, -32656);
        mul_s(F12, F0, F1);
        jal(0x2a90f0, rg::fn_tanf_0052e930);
        div_s(F20, F20, F0);
        eye_point_2A8D20(240, F20, 156);
        spa(a2, 208);
        ld(v0, sp, 288);
        lwc1(F0, sp, 296);
        sd(v0, sp, 208);
        swc1(F0, sp, 216);
        lif(v0, 0x3f40, F0);  // 0.75
        mul_s(F4, F0, F27);
        swc1(F4, sp, 212);
        facing_point_2A8D20(F4);
        spa(a0, 140);
        spa(a1, 256);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a91c8, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0x3f40, F0);
        mul_s(F1, F0, F20);
        key_point_2A8D20();
    } else {
        // the close-up of the sub-object
        charge(75);
        a0 = s1;
        a1 = li(1);
        jal(0x2a9238, rg::fn_sub_2880E0_002880e0);
        ld(v0, sp, 272);
        lwc1(F0, sp, 280);
        sd(v0, sp, 192);
        swc1(F0, sp, 200);
        ld(v0, sp, 192);
        lwc1(F1, sp, 200);
        sd(v0, sp, 304);
        swc1(F1, sp, 312);
        lwc1(F0, gp, -32632);
        mul_s(F0, F0, F26);
        swc1(F0, sp, 308);
        sd(v0, sp, 208);
        swc1(F1, sp, 216);
        lwc1(F0, gp, -32668);
        mul_s(F0, F0, F26);
        swc1(F0, sp, 212);
        spa(a0, 224);
        la(a1, 0x69, kVecZLo);
        a2 = li(1);
        a3 = addiu(s0, 28);
        jal(0x2a9294, rg::fn_sub_4BE1E0_004be1e0);
        lwc1(F0, sp, 224);
        mul_s(F1, F0, F28);
        swc1(F1, sp, 240);
        lwc1(F0, sp, 228);
        mul_s(F4, F0, F28);
        swc1(F4, sp, 244);
        lwc1(F0, sp, 232);
        mul_s(F2, F0, F28);
        swc1(F2, sp, 248);
        lwc1(F0, sp, 304);
        add_s(F3, F1, F0);
        swc1(F3, sp, 256);
        lwc1(F1, sp, 308);
        add_s(F0, F4, F1);
        swc1(F0, sp, 260);
        lwc1(F0, sp, 312);
        add_s(F2, F2, F0);
        swc1(F2, sp, 264);
        lwc1(F0, gp, -32636);
        mul_s(F1, F0, F1);
        swc1(F1, sp, 260);
        lwc1(F0, sp, 208);
        sub_s(F0, F3, F0);
        swc1(F0, sp, 240);
        lwc1(F0, sp, 212);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 244);
        lwc1(F0, sp, 216);
        sub_s(F0, F2, F0);
        swc1(F0, sp, 248);
        spa(a0, 240);
        a1 = a0;
        jal(0x2a931c, rg::fn_sub_4C69F0_004c69f0);
        spa(a0, 168);
        spa(a1, 256);
        spa(a2, 208);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a9338, rg::fn_sub_2A4690_002a4690);
        lif(v0, 0x3f00, F1);
        mul_s(F20, F1, F26);
        c_le_s(F28, F20);
        if (!cc()) {
            charge(16);
            lwc1(F0, s3, kCwFov);
            mul_s(F1, F1, F0);
            lwc1(F0, gp, -32656);
            mul_s(F12, F0, F1);
            jal(0x2a936c, rg::fn_tanf_0052e930);
            lif(v0, 0x3fa0, F1);  // 1.25
            mul_s(F1, F1, F28);
            div_s(F20, F1, F0);
        } else {
            charge(9);
            lwc1(F0, s3, kCwFov);
            mul_s(F12, F1, F0);
            jal(0x2a93a4, rg::fn_tanf_0052e930);
            lif(v0, 0x3fa0, F1);
            mul_s(F1, F1, F20);
            div_s(F20, F1, F0);
        }
        charge(7);
        sub_s(F1, F20, F28);
        lif(v0, 0x43af, F0);  // 350.0
        c_lt_s(F1, F0);
        if (cc()) {
            charge(1);
            add_s(F20, F0, F28);
        }
        charge(67);
        eye_point_2A8D20(240, F20, 156);
        spa(a2, 208);
        ld(v0, sp, 288);
        lwc1(F0, sp, 296);
        sd(v0, sp, 208);
        swc1(F0, sp, 216);
        swc1(F27, sp, 212);
        facing_point_2A8D20(F27);
        spa(a0, 140);
        spa(a1, 256);
        la(a3, 0x69, kVecUpLo);
        jal(0x2a9494, rg::fn_sub_2A4690_002a4690);
        lwc1(F0, gp, -32572);
        mul_s(F1, F0, F20);
        key_point_2A8D20();
    }
    charge(7);
    min_height_25(132, 7);
    min_height_25(160, 20);
    mtc1(zero, F12);
    lw(a0, s3, kCwSubject);
    a1 = 0;
    a2 = 0;
    a3 = li(1);
    jal(0x2a9540, rg::fn_sub_2A3E80_002a3e80);
    a0 = s3;
    spa(a1, 128);
    spa(a2, 156);
    a3 = li(1);
    jal(0x2a9558, rg::fn_sub_2A2290_002a2290);
    lif(v0, 0x4000, F12);  // 2.0
    a0 = s3;
    jal(0x2a956c, rg::fn_sub_2A3110_002a3110);
    if (s2 != 0) {
        charge(3);
        a0 = li(12);
        jal(0x2a9580, rg::fn_sub_351BB0_00351bb0);
    }
    charge(17);
    ld(ra, sp, 112);
    lq(s3, sp, 96);
    lq(s2, sp, 80);
    lq(s1, sp, 64);
    lq(s0, sp, 48);
    for (int k = 8; k >= 0; --k) lwc1(static_cast<unsigned>(F20 + k), sp, 4 * k);
    sp = addiu(sp, 320);
}

// sub_2A8D20: sp+dst.. = the direction sp+dir.. * $f`fs` (through $f3, $f2, $f1) and the point sp+208.. + it -> the
// three words at sp+out (as `sp+256..264 = dir * s; sp+out.. = sp+208.. + sp+256..`).
void Cpu1::eye_point_2A8D20(s32 dir, unsigned fs, s32 out) {
    lwc1(F0, sp, dir);
    mul_s(F3, F0, fs);
    swc1(F3, sp, 256);
    lwc1(F0, sp, dir + 4);
    mul_s(F2, F0, fs);
    swc1(F2, sp, 260);
    lwc1(F0, sp, dir + 8);
    mul_s(F1, F0, fs);
    swc1(F1, sp, 264);
    lwc1(F0, sp, 208);
    add_s(F0, F0, F3);
    swc1(F0, sp, out);
    lwc1(F0, sp, 212);
    add_s(F0, F0, F2);
    swc1(F0, sp, out + 4);
    lwc1(F0, sp, 216);
    add_s(F0, F0, F1);
    swc1(F0, sp, out + 8);
}

// sub_2A8D20: sp+240.. = the facing sp+224.. * the sub-object's radius ($f28); sp+256.. = the unit's point sp+208.. +
// it, its height from $f`fy` (+ the y term).
void Cpu1::facing_point_2A8D20(unsigned fy) {
    lwc1(F0, sp, 224);
    mul_s(F3, F0, F28);
    swc1(F3, sp, 240);
    lwc1(F0, sp, 228);
    mul_s(F2, F0, F28);
    swc1(F2, sp, 244);
    lwc1(F0, sp, 232);
    mul_s(F1, F0, F28);
    swc1(F1, sp, 248);
    lwc1(F0, sp, 208);
    add_s(F0, F3, F0);
    swc1(F0, sp, 256);
    add_s(F0, F2, fy);
    swc1(F0, sp, 260);
    lwc1(F0, sp, 216);
    add_s(F0, F1, F0);
    swc1(F0, sp, 264);
}

// sub_2A8D20: the key sp+128.. = the unit's point sp+208.. + the facing sp+224.. * $f1 (through sp+256..).
void Cpu1::key_point_2A8D20() {
    lwc1(F0, sp, 224);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 256);
    lwc1(F0, sp, 228);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 260);
    lwc1(F0, sp, 232);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 264);
    lwc1(F0, sp, 208);
    add_s(F0, F0, F3);
    swc1(F0, sp, 128);
    lwc1(F0, sp, 212);
    add_s(F0, F0, F2);
    swc1(F0, sp, 132);
    lwc1(F0, sp, 216);
    add_s(F0, F0, F1);
    swc1(F0, sp, 136);
}

// 0x2A95D0 sub_2A95D0(work, a1 = rumble, a2 = keep key): the summon's attack camera: the subject unit (s1), its
// sub-object (+2560, s2: the persona) and its first target's unit (s3). s5 = sub_2FDBB0(subject, sub-object) != 0;
// s0 = sub_2A3520(work) || sub_2A3550(work). Positions (sub_27FFB0: unit sp+416, sub-object sp+384, target sp+400)
// at half height ($f23 / $f21 / $f22); unless s5 or s0 the unit takes the sub-object's height when that is higher
// (its point raised to a quarter of their sum) and its radius ($f24, at least 50); the target's height at most 450.
// s5 = sub_2A3420(work): without s0 / s5 a sub-object whose ENEMY-like record (88 bytes at *(gp-18628), index +164)
// has bit 0 set moves the unit's point up (gp-32672 / gp-32624 * the height by 750) and the target's (gp-32620), and
// the scale $f20 = 1.5. The direction target -> unit (sp+336, length $f25) places the look point (gp-32616 * it from
// the target, sp+352); the key's xz direction (sub_4C6B20, sp+248). With s5, or sub_357FD0(0) bit 0 and sub_2A3380,
// the over-the-shoulder shot (sub_2880E0(sub-object, 1), work+288 = it, +292 = 0, field of view 3.0); otherwise the
// side shot (sub_2880E0(.., record bit 0), work+292 = 1, field of view 2.25). Both build the eye beside a unit (the
// side by the facing against the key direction), the look-at (sub_2A4690) and the forward axis, the turn point
// (sub_2D1FD0) and the distance / tan(fov / 2); without a2 the key becomes the eye; sub_2A3E80(subject, unit+4, key,
// 3; 50.0); the camera reset (sub_2A2290(work, key, eye, 1)) with that field of view; a1 -> sub_351BB0(12).
void Cpu1::sub_2A95D0() {
    enter(35);
    sp = addiu(sp, -432);
    sd(ra, sp, 160);
    sq(s7, sp, 144);
    sq(s6, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    for (int k = 5; k >= 0; --k) swc1(static_cast<unsigned>(F20 + k), sp, 4 * k);
    s4 = a0;
    s6 = a1;
    s7 = a2;
    lw(a0, a0, kCwSubject);
    lw(s1, a0, kActUnit);
    lw(v0, a0, kActTargets);
    lw(s3, v0, kActUnit);
    lw(s2, s1, 2560);
    lif(v0, 0x3f80, F20);
    a1 = s2;
    jal(0x2a963c, rg::fn_sub_2FDBB0_002fdbb0);
    s5 = sltu(zero, v0);
    a0 = s4;
    jal(0x2a964c, rg::fn_sub_2A3520_002a3520);
    bool special = v0 != 0;
    if (!special) {
        charge(5);
        a0 = s4;
        jal(0x2a9660, rg::fn_sub_2A3550_002a3550);
        special = v0 != 0;
    }
    if (special) {
        charge(3);
        s0 = li(1);
    } else {
        charge(1);
        s0 = 0;
    }
    charge(26);
    a0 = s1;
    spa(a1, 416);
    jal(0x2a9688, rg::fn_sub_27FFB0_0027ffb0);
    a0 = s2;
    spa(a1, 384);
    jal(0x2a9698, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s1, 140);
    lwc1(F0, s1, 44);
    mul_s(F1, F1, F0);
    lif(v0, 0x3f00, F3);
    lwc1(F0, sp, 420);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F23, F3, F1);
    lwc1(F1, s2, 140);
    lwc1(F0, s2, 44);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 388);
    adda_s(F2, F0);
    madd_s(F21, F3, F1);
    if (s5 == 0) {
        charge(3);
        c_lt_s(F23, F21);
        if (cc()) {
            charge(2);
            if (s0 == 0) {
                charge(7);
                add_s(F1, F23, F21);
                lif(v0, 0x3e80, F0);  // 0.25
                mul_s(F0, F0, F1);
                swc1(F0, sp, 420);
                mov_s(F23, F21);
            }
        }
    }
    charge(8);
    lwc1(F1, s1, 144);
    lwc1(F0, s1, 44);
    mul_s(F24, F1, F0);
    lwc1(F1, s2, 144);
    lwc1(F0, s2, 44);
    mul_s(F0, F1, F0);
    if (s5 == 0) {
        charge(3);
        c_lt_s(F24, F0);
        if (cc()) {
            charge(2);
            if (s0 == 0) {
                charge(1);
                mov_s(F24, F0);
            }
        }
    }
    charge(6);
    lif(v0, 0x4248, F0);  // 50.0
    c_lt_s(F24, F0);
    if (cc()) {
        charge(1);
        mov_s(F24, F0);
    }
    charge(20);
    a0 = s3;
    spa(a1, 400);
    jal(0x2a9774, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s3, 44);
    lwc1(F0, s3, 140);
    mul_s(F4, F0, F1);
    lif(v0, 0x3f00, F0);
    lwc1(F3, sp, 404);
    mtc1(zero, F2);
    adda_s(F2, F3);
    madd_s(F22, F0, F4);
    lif(v0, 0x43e1, F1);  // 450.0
    c_lt_s(F22, F1);
    if (!cc()) {
        charge(5);
        lwc1(F0, gp, -32628);
        adda_s(F2, F3);
        msub_s(F0, F0, F4);
        swc1(F0, sp, 404);
        mov_s(F22, F1);
    }
    charge(6);
    a0 = s4;
    jal(0x2a97d4, rg::fn_sub_2A3420_002a3420);
    s5 = v0;
    if (s0 == 0) {
        charge(2);
        if (s5 == 0) {
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
            v0 = v0 & 0x1;
            if (v0 != 0) {
                charge(7);
                v0 = li(750);
                mtc1(v0, F0);
                cvt_s_w(F0, F0);
                c_lt_s(F21, F0);
                if (cc()) {
                    charge(5);
                    lwc1(F0, gp, -32672);
                    mul_s(F0, F0, F21);
                    swc1(F0, sp, 420);
                } else {
                    charge(3);
                    lwc1(F0, gp, -32624);
                    mul_s(F0, F0, F21);
                    swc1(F0, sp, 420);
                }
                charge(5);
                lwc1(F0, gp, -32620);
                mul_s(F0, F0, F22);
                swc1(F0, sp, 404);
                lif(v0, 0x3fc0, F20);  // 1.5
            }
        }
    }
    charge(49);
    for (int k = 0; k < 3; ++k) {
        lwc1(F1, sp, 416 + 4 * k);
        lwc1(F0, sp, 400 + 4 * k);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 336 + 4 * k);
    }
    spa(a0, 336);
    a1 = a0;
    jal(0x2a98a8, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F25, F0);
    lwc1(F1, gp, -32616);
    mul_s(F1, F1, F0);
    lwc1(F0, sp, 336);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 352);
    lwc1(F0, sp, 340);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 356);
    lwc1(F0, sp, 344);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 360);
    lwc1(F0, sp, 400);
    add_s(F2, F2, F0);
    swc1(F2, sp, 352);
    lwc1(F0, sp, 404);
    add_s(F0, F3, F0);
    swc1(F0, sp, 356);
    lwc1(F0, sp, 408);
    add_s(F1, F1, F0);
    swc1(F1, sp, 360);
    lwc1(F0, s4, kCwKey);
    sub_s(F0, F0, F2);
    swc1(F0, sp, 248);
    lwc1(F0, s4, kCwKey + 8);
    sub_s(F0, F0, F1);
    swc1(F0, sp, 252);
    spa(a0, 248);
    a1 = a0;
    jal(0x2a9924, rg::fn_sub_4C6B20_004c6b20);
    bool shoulder = s5 != 0;
    if (!shoulder) {
        charge(6);
        a0 = 0;
        jal(0x2a9938, rg::fn_sub_357FD0_00357fd0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            charge(5);
            a0 = s4;
            jal(0x2a9950, rg::fn_sub_2A3380_002a3380);
            shoulder = v0 != 0;
        }
    }
    if (shoulder) {
        shoulder_2A95D0();
    } else {
        side_2A95D0();
    }
    charge(2);
    if (s7 == 0) {
        charge(14);
        copy_vec3(sp, 204, sp, 176);
        copy_vec4(sp, 216, sp, 188);
    }
    charge(20);
    lif(v0, 0x4248, F12);  // 50.0
    lw(a0, s4, kCwSubject);
    a1 = addiu(s1, 4);
    spa(a2, 176);
    a3 = li(3);
    jal(0x2aa224, rg::fn_sub_2A3E80_002a3e80);
    a0 = s4;
    spa(a1, 176);
    spa(a2, 204);
    a3 = li(1);
    jal(0x2aa23c, rg::fn_sub_2A2290_002a2290);
    a0 = s4;
    mov_s(F12, F20);
    jal(0x2aa24c, rg::fn_sub_2A3110_002a3110);
    if (s6 != 0) {
        charge(3);
        a0 = li(12);
        jal(0x2aa260, rg::fn_sub_351BB0_00351bb0);
    }
    charge(18);
    ld(ra, sp, 160);
    lq(s7, sp, 144);
    lq(s6, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    for (int k = 5; k >= 0; --k) lwc1(static_cast<unsigned>(F20 + k), sp, 4 * k);
    sp = addiu(sp, 432);
}

// The turn point of sub_2A95D0 (both shots): the look-at sp+188 from the eye sp+320 to the look point sp+352, the
// forward axis by it (sp+336), and sub_2D1FD0(look point xz, eye xz, unit xz, sp+288) -> $f0.
void Cpu1::turn_point_2A95D0(u32 l_look, u32 l_rot, u32 l_turn) {
    spa(a0, 188);
    spa(a1, 320);
    spa(a2, 352);
    la(a3, 0x69, kVecUpLo);
    jal(l_look, rg::fn_sub_2A4690_002a4690);
    spa(a0, 336);
    la(a1, 0x69, kVecFwdLo);
    a2 = li(1);
    spa(a3, 188);
    jal(l_rot, rg::fn_sub_4BE1E0_004be1e0);
    lwc1(F0, sp, 352);
    swc1(F0, sp, 256);
    lwc1(F0, sp, 360);
    swc1(F0, sp, 260);
    lwc1(F0, sp, 320);
    swc1(F0, sp, 264);
    lwc1(F0, sp, 328);
    swc1(F0, sp, 268);
    lwc1(F0, sp, 368);
    swc1(F0, sp, 296);
    lwc1(F0, sp, 376);
    swc1(F0, sp, 300);
    spa(a0, 256);
    spa(a1, 264);
    spa(a2, 296);
    spa(a3, 288);
    jal(l_turn, rg::fn_sub_2D1FD0_002d1fd0);
}

// The tan(fov / 2) of the work (`lui 0x3F00; mtc1 $f1; lwc1 $f0, 184(s4); mul; lwc1 gp-32656; mul $f12; jal tanf`)
void Cpu1::tan_fov_2A95D0(u32 link) {
    lif(v0, 0x3f00, F1);
    lwc1(F0, s4, kCwFov);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -32656);
    mul_s(F12, F0, F1);
    jal(link, rg::fn_tanf_0052e930);
}

// sub_2A95D0's over-the-shoulder shot: the sub-object set up (sub_2880E0(.., 1)), work+288 = it, +292 = 0; the eye
// beside the unit (sp+368: its point) at 2.25 * radius on the side the facing (the direction's normal) shows against the
// key direction ($f21 = their dot), at the unit's height +- gp-32720 * its half height; on the far side the look point
// moves to half the direction from the target. The look-at, the turn point (sub_2D1FD0), the distance (gp-32612 *
// scale + radius * ... / tan) along the forward axis (shifted sideways on the far side); the eye heights at least 25;
// field of view 3.0.
void Cpu1::shoulder_2A95D0() {
    charge(30);
    a0 = s2;
    a1 = li(1);
    jal(0x2a9968, rg::fn_sub_2880E0_002880e0);
    sw(s2, s4, 288);
    sh(zero, s4, 292);
    s1 = s3;
    ld(v0, sp, 416);
    lwc1(F0, sp, 424);
    sd(v0, sp, 368);
    swc1(F0, sp, 376);
    lif(v0, 0x4010, F0);  // 2.25
    mul_s(F6, F0, F24);
    lwc1(F0, gp, -32612);
    mul_s(F20, F0, F20);
    lwc1(F4, sp, 344);
    swc1(F4, sp, 240);
    lwc1(F3, sp, 336);
    neg_s(F2, F3);
    swc1(F2, sp, 244);
    lwc1(F1, sp, 248);
    lwc1(F0, sp, 252);
    mula_s(F2, F0);
    mtc1(zero, F2);
    madd_s(F21, F4, F1);
    c_lt_s(F23, F22);
    if (cc()) {
        charge(7);
        lwc1(F0, gp, -32720);
        lwc1(F1, sp, 372);
        adda_s(F2, F1);
        madd_s(F1, F0, F23);
        swc1(F1, sp, 324);
    } else {
        charge(5);
        lwc1(F0, gp, -32720);
        lwc1(F1, sp, 372);
        adda_s(F2, F1);
        msub_s(F1, F0, F23);
        swc1(F1, sp, 324);
    }
    charge(5);
    mtc1(zero, F2);
    c_lt_s(F21, F2);
    if (!cc()) {
        charge(10);
        lwc1(F1, sp, 368);
        adda_s(F2, F1);
        madd_s(F1, F4, F6);
        swc1(F1, sp, 320);
        lwc1(F1, sp, 376);
        adda_s(F2, F1);
        msub_s(F1, F3, F6);
        swc1(F1, sp, 328);
    } else {
        charge(30);
        lwc1(F5, sp, 344);
        lwc1(F1, sp, 368);
        adda_s(F2, F1);
        msub_s(F1, F5, F6);
        swc1(F1, sp, 320);
        lwc1(F3, sp, 336);
        lwc1(F1, sp, 376);
        adda_s(F2, F1);
        madd_s(F1, F3, F6);
        swc1(F1, sp, 328);
        lif(v0, 0x3f00, F1);
        mul_s(F2, F1, F25);
        mul_s(F4, F3, F2);
        swc1(F4, sp, 352);
        lwc1(F1, sp, 340);
        mul_s(F3, F1, F2);
        swc1(F3, sp, 356);
        mul_s(F2, F5, F2);
        swc1(F2, sp, 360);
        lwc1(F1, sp, 400);
        add_s(F1, F4, F1);
        swc1(F1, sp, 352);
        lwc1(F1, sp, 404);
        add_s(F1, F3, F1);
        swc1(F1, sp, 356);
        lwc1(F1, sp, 408);
        add_s(F1, F2, F1);
        swc1(F1, sp, 360);
    }
    charge(80);
    lwc1(F2, s3, 140);
    lwc1(F1, s3, 44);
    mul_s(F3, F2, F1);
    lwc1(F2, sp, 356);
    mtc1(zero, F1);
    adda_s(F1, F2);
    madd_s(F0, F0, F3);
    swc1(F0, sp, 356);
    turn_point_2A95D0(0x2a9af4, 0x2a9b10, 0x2a9b58);
    mtc1(zero, F2);
    adda_s(F2, F0);
    madd_s(F20, F24, F20);
    lwc1(F0, sp, 288);
    swc1(F0, sp, 320);
    lif(v0, 0x3e80, F1);
    lwc1(F0, sp, 372);
    adda_s(F2, F0);
    madd_s(F0, F1, F23);
    swc1(F0, sp, 324);
    lwc1(F0, sp, 292);
    swc1(F0, sp, 328);
    tan_fov_2A95D0(0x2a9bb0);
    div_s(F20, F20, F0);
    for (int k = 0; k < 3; ++k) {
        lwc1(F0, sp, 336 + 4 * k);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 336 + 4 * k);
    }
    mtc1(zero, F0);
    c_lt_s(F21, F0);
    if (cc()) {
        charge(37);
        tan_fov_2A95D0(0x2a9c14);
        mul_s(F1, F20, F0);
        lif(v0, 0x3e60, F0);  // 0.21875
        mul_s(F1, F1, F0);
        lif(v0, 0x3fa0, F0);  // 1.25
        mul_s(F20, F1, F0);
        lwc1(F0, sp, 336);
        swc1(F0, sp, 280);
        lwc1(F0, sp, 344);
        swc1(F0, sp, 284);
        spa(a0, 280);
        a1 = a0;
        jal(0x2a9c58, rg::fn_sub_4C6B20_004c6b20);
        lwc1(F1, sp, 284);
        lwc1(F0, sp, 320);
        mtc1(zero, F2);
        adda_s(F2, F0);
        madd_s(F0, F1, F20);
        swc1(F0, sp, 320);
        lwc1(F1, sp, 280);
        lwc1(F0, sp, 328);
        adda_s(F2, F0);
        msub_s(F0, F1, F20);
        swc1(F0, sp, 328);
    }
    charge(26);
    copy_vec4(sp, 188, sp, 216);
    lwc1(F5, sp, 336);
    lwc1(F0, sp, 320);
    add_s(F0, F0, F5);
    swc1(F0, sp, 204);
    lwc1(F4, sp, 340);
    lwc1(F0, sp, 324);
    add_s(F1, F0, F4);
    swc1(F1, sp, 208);
    lwc1(F3, sp, 344);
    lwc1(F0, sp, 328);
    add_s(F0, F0, F3);
    swc1(F0, sp, 212);
    lif(v0, 0x41c8, F0);  // 25.0
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 208);
    }
    charge(21);
    lwc1(F2, gp, -32620);
    lwc1(F1, sp, 324);
    mtc1(zero, F0);
    adda_s(F0, F1);
    msub_s(F1, F2, F23);
    swc1(F1, sp, 324);
    lwc1(F0, sp, 320);
    add_s(F0, F0, F5);
    swc1(F0, sp, 176);
    add_s(F1, F1, F4);
    swc1(F1, sp, 180);
    lwc1(F0, sp, 328);
    add_s(F0, F0, F3);
    swc1(F0, sp, 184);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 180);
    }
    charge(4);
    lif(v0, 0x4040, F20);  // 3.0
}

// sub_2A95D0's side shot: the sub-object set up (sub_2880E0(.., its record bit 0)), work+288 = it, +292 = 1; the eye
// beside the target (sp+368: its point, at least 125 high) at 1.25 * its radius on the side the facing shows against
// the key direction ($f20), the look-at and turn point, the distance 1.5 * scale + the target's radius over tan(fov /
// 2), at least 550, along the forward axis (on the near side shifted back by half its radius along the direction);
// then the key from the eye toward the unit's point (raised by a quarter of its height) at gp-32632 * the distance;
// heights at least 25; field of view 2.25.
void Cpu1::side_2A95D0() {
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
    v0 = v0 & 0x1;
    if (v0 == 0) {
        charge(6);
        a0 = s2;
        a1 = 0;
        jal(0x2a9d9c, rg::fn_sub_2880E0_002880e0);
    } else {
        charge(4);
        a0 = s2;
        a1 = li(1);
        jal(0x2a9db4, rg::fn_sub_2880E0_002880e0);
    }
    charge(25);
    sw(s2, s4, 288);
    v0 = li(1);
    sh(v0, s4, 292);
    ld(v0, sp, 400);
    lwc1(F0, sp, 408);
    sd(v0, sp, 368);
    swc1(F0, sp, 376);
    lwc1(F1, s3, 144);
    lwc1(F0, s3, 44);
    mul_s(F1, F1, F0);
    lif(v0, 0x3fa0, F0);  // 1.25
    mul_s(F5, F0, F1);
    lif(v0, 0x3fc0, F0);  // 1.5
    mul_s(F21, F0, F20);
    lwc1(F1, sp, 372);
    lif(v0, 0x42fa, F0);  // 125.0
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 372);
    }
    charge(15);
    lwc1(F4, sp, 344);
    swc1(F4, sp, 240);
    lwc1(F3, sp, 336);
    neg_s(F1, F3);
    swc1(F1, sp, 244);
    lwc1(F2, sp, 248);
    lwc1(F0, sp, 252);
    mula_s(F1, F0);
    mtc1(zero, F1);
    madd_s(F20, F4, F2);
    lwc1(F0, sp, 372);
    swc1(F0, sp, 324);
    c_lt_s(F20, F1);
    if (!cc()) {
        charge(14);
        lwc1(F0, sp, 368);
        adda_s(F1, F0);
        madd_s(F0, F4, F5);
        swc1(F0, sp, 320);
        lwc1(F0, sp, 376);
        adda_s(F1, F0);
        msub_s(F0, F3, F5);
        swc1(F0, sp, 328);
        ld(v0, sp, 336);
        lwc1(F0, sp, 344);
        sd(v0, sp, 304);
        swc1(F0, sp, 312);
    } else {
        charge(8);
        lwc1(F0, sp, 368);
        adda_s(F1, F0);
        msub_s(F0, F4, F5);
        swc1(F0, sp, 320);
        lwc1(F0, sp, 376);
        adda_s(F1, F0);
        madd_s(F0, F3, F5);
        swc1(F0, sp, 328);
    }
    charge(63);
    turn_point_2A95D0(0x2a9ecc, 0x2a9ee8, 0x2a9f30);
    lwc1(F2, s3, 144);
    lwc1(F1, s3, 44);
    mul_s(F2, F2, F1);
    mtc1(zero, F1);
    adda_s(F1, F0);
    madd_s(F21, F21, F2);
    lwc1(F0, sp, 288);
    swc1(F0, sp, 320);
    lwc1(F0, sp, 372);
    swc1(F0, sp, 324);
    lwc1(F0, sp, 292);
    swc1(F0, sp, 328);
    tan_fov_2A95D0(0x2a9f84);
    div_s(F1, F21, F0);
    v0 = li(550);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        mov_s(F1, F0);
    }
    charge(14);
    for (int k = 0; k < 3; ++k) {
        lwc1(F0, sp, 336 + 4 * k);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 336 + 4 * k);
    }
    mtc1(zero, F3);
    c_lt_s(F20, F3);
    if (!cc()) {
        charge(17);
        lwc1(F1, s3, 144);
        lwc1(F0, s3, 44);
        mul_s(F1, F1, F0);
        lif(v0, 0x3f00, F0);
        mul_s(F2, F0, F1);
        lwc1(F1, sp, 312);
        lwc1(F0, sp, 320);
        adda_s(F3, F0);
        msub_s(F0, F1, F2);
        swc1(F0, sp, 320);
        lwc1(F1, sp, 304);
        lwc1(F0, sp, 328);
        adda_s(F3, F0);
        madd_s(F0, F1, F2);
        swc1(F0, sp, 328);
    }
    charge(91);
    for (int k = 0; k < 3; ++k) {
        lwc1(F1, sp, 320 + 4 * k);
        lwc1(F0, sp, 336 + 4 * k);
        add_s(F0, F1, F0);
        swc1(F0, sp, 176 + 4 * k);
    }
    copy_vec4(sp, 188, sp, 216);
    copy_vec3(sp, 176, sp, 204);
    for (int k = 0; k < 3; ++k) {
        lwc1(F1, sp, 416 + 4 * k);
        lwc1(F0, sp, 204 + 4 * k);
        sub_s(F0, F1, F0);
        swc1(F0, sp, 336 + 4 * k);
    }
    spa(a0, 336);
    a1 = a0;
    jal(0x2aa0d4, rg::fn_sub_4C69F0_004c69f0);
    mov_s(F20, F0);
    a0 = s1;
    spa(a1, 368);
    jal(0x2aa0e8, rg::fn_sub_27FFB0_0027ffb0);
    lwc1(F1, s1, 140);
    lwc1(F0, s1, 44);
    mul_s(F3, F1, F0);
    lif(v0, 0x3e80, F2);
    lwc1(F1, sp, 372);
    mtc1(zero, F0);
    adda_s(F0, F1);
    madd_s(F0, F2, F3);
    swc1(F0, sp, 372);
    spa(a0, 188);
    spa(a1, 204);
    spa(a2, 368);
    la(a3, 0x69, kVecUpLo);
    jal(0x2aa130, rg::fn_sub_2A4690_002a4690);
    lwc1(F0, gp, -32632);
    mul_s(F2, F0, F20);
    lwc1(F0, sp, 336);
    mul_s(F3, F0, F2);
    swc1(F3, sp, 336);
    lwc1(F0, sp, 340);
    mul_s(F1, F0, F2);
    swc1(F1, sp, 340);
    lwc1(F0, sp, 344);
    mul_s(F2, F0, F2);
    swc1(F2, sp, 344);
    lwc1(F0, sp, 204);
    add_s(F0, F0, F3);
    swc1(F0, sp, 176);
    lwc1(F0, sp, 208);
    add_s(F1, F0, F1);
    swc1(F1, sp, 180);
    lwc1(F0, sp, 212);
    add_s(F0, F0, F2);
    swc1(F0, sp, 184);
    lif(v0, 0x41c8, F0);
    c_lt_s(F1, F0);
    if (cc()) {
        charge(1);
        swc1(F0, sp, 180);
    }
    charge(7);
    min_height_25(208, 2);
    lif(v0, 0x4010, F20);  // 2.25
}

}  // namespace p3fes::game::bcam

namespace p3fes::game {
#define P3FES_BCAM_API_1(name, addr) \
    void name(EEContext& ctx) { bcam::Cpu1(ctx).name(); }
P3FES_BCAM_BODIES_1(P3FES_BCAM_API_1)
#undef P3FES_BCAM_API_1
}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
#define P3FES_BCAM_SHIM_1(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { ::p3fes::game::bcam::Cpu1(ctx).name(); }
P3FES_BCAM_BODIES_1(P3FES_BCAM_SHIM_1)
#undef P3FES_BCAM_SHIM_1
}  // namespace p3fes::recomp_gen
