// Slice battle_camera, part 4 (game/include/p3fes/game/battle_camera_4.h), hand-decompiled from SLUS_216.21: the battle
// camera object and the scene colour fade. battle_camera.cpp has the band's overview, battle_camera_cpu.h the
// register-faithful Cpu view and the cycle model; tests/game/test_battle_camera_4.cpp runs each body against its __recomp
// body.
//
// The battle camera object (the one the game drives is gBtl+32, the camera work record the table rows get in $a0): a ring
// of four keys -- key i at +28i: position (x, y, z) at +4, rotation quaternion (x, y, z, w) at +16 -- with the read head
// +116, the key count +118 and the write index +120 (u16 each; indices wrap at 4), the path parameter +124 (0..1 over
// the keys: 1/3 per segment), the progress +128, the duration +132 (frames), the eased parameter +148 and its RwFrame
// +152. Flags +0: bit 0 the keys are not mirrored into the frame (no sub_48D370 per key, no RW spline: a Bezier of the
// four keys instead), bit 1 a timed curve (sub_2D21E0), bit 2 the eased curve. The game's camera outputs are gBtl+188
// (position) and gBtl+200 (rotation).
#include "battle_camera_cpu.h"
#include "p3fes/game/battle_camera_4.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by other slices: through their generated entry points).
void fn_sub_19F8F0_0019f8f0(p3fes::EEContext&);  // the scene's ambient colour (colour)
void fn_sub_19FD40_0019fd40(p3fes::EEContext&);  // the scene's light A colour (returns its RGBA floats)
void fn_sub_19FD70_0019fd70(p3fes::EEContext&);  // the scene's light B colour (returns its RGBA floats)
void fn_sub_4BE310_004be310(p3fes::EEContext&);  // quaternion slerp setup (q0, q1, out: axis / angle / flags)
void fn_sub_48D370_0048d370(p3fes::EEContext&);  // RwFrame: translate (frame, ..., vector)
void fn_sub_48D480_0048d480(p3fes::EEContext&);  // RwFrame: the key spline at $f12 (frame, 10, out, 0)
void fn_sub_2D21E0_002d21e0(p3fes::EEContext&);  // a timed curve (record; $f12) -> $f0
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

using namespace btl_cam;

namespace btl_cam4 {
// --- the battle camera object -----------------------------------------------------------------------------------------
inline constexpr s32 kCamFlags = 0;        // u16: bit 0 no RwFrame keys, bit 1 timed curve, bit 2 eased curve
inline constexpr s32 kKeyPos = 4;          // f32[3] of key 0 (key i: + 28 i)
inline constexpr s32 kKeyRot = 16;         // f32[4] quaternion of key 0
inline constexpr s32 kCamHead = 116;       // u16: the first key of the path
inline constexpr s32 kCamCount = 118;      // u16: keys in the ring (at most 4)
inline constexpr s32 kCamWrite = 120;      // u16: where the next key goes
inline constexpr s32 kCamT = 124;          // f32: the path parameter (1/3 per segment)
inline constexpr s32 kCamProgress = 128;   // f32: the curve's value last frame
inline constexpr s32 kCamDuration = 132;   // f32: frames (also the timed curve's record)
inline constexpr s32 kCamEase = 148;       // f32: the eased curve's parameter (starts at 0.5)
inline constexpr s32 kCamFrame = 152;      // u32: RwFrame*
// --- gBtl: the scene colours the scene packet fades -------------------------------------------------------------------
inline constexpr s32 kAmbient = 548;       // f32[4]: the ambient colour (sub_19F8F0's)
inline constexpr s32 kLightATarget = 404;  // f32[4]
inline constexpr s32 kLightBTarget = 420;  // f32[4]
inline constexpr s32 kSceneC = 452;        // f32[4]
inline constexpr s32 kSceneD = 468;        // f32[4]
inline constexpr s32 kSceneCTarget = 500;  // f32[4]
inline constexpr s32 kSceneDTarget = 516;  // f32[4]
inline constexpr s32 kGpAmbientTarget = -25472;  // u8[4]: the ambient colour to fade to
inline constexpr s32 kGpThird = -32056;    // f32 1/3 (one segment of the path)
// --- btlUnit ---------------------------------------------------------------------------------------------------------
inline constexpr s32 kUnitModel = 2548;    // u32: the unit's model (+904 fade flags, +924.. the fade)
}  // namespace btl_cam4
using namespace btl_cam4;

class Cpu4 final : public Cpu {
public:
    using Cpu::Cpu;
#define P3FES_BCAM_BODY_4(name, addr) void name();
    P3FES_BCAM_BODIES_4(P3FES_BCAM_BODY_4)
#undef P3FES_BCAM_BODY_4

private:
    void epilogue_2A0440();
    void sub_2A0440_final();
    // The key of ring index (u16) `idx`: out = cam + 28 * idx (`t = idx & 0xFFFF; out = (t * 8 - t) * 4 + cam`).
    void key_slot(Gpr& out, Gpr& t, const Gpr& idx, const Gpr& cam) {
        t = idx & 0xffff;
        out = sll(t, 3);
        out = subu(out, t);
        out = sll(out, 2);
        out = addu(out, cam);
    }
    // The write index moves on: +120 = idx + 1 (0 at 4), +118 += 1. p / n are the registers as compiled; `last` the
    // cycles of the closing block (it runs on into the caller's code).
    void key_advance(Gpr& p, Gpr& n, const Gpr& idx, const Gpr& cam, u64 last) {
        charge(5);
        p = addiu(idx, 1);
        n = p & 0xffff;
        p = slti(n, 4);
        if (p == 0) {
            charge(1);
            n = 0;
        }
        charge(last);
        sh(n, cam, kCamWrite);
        lhu(p, cam, kCamCount);
        p = addiu(p, 1);
        sh(p, cam, kCamCount);
    }
    // The inlined key push (sub_2A2050's body) of a key whose position is at `key` and rotation at key + 12 (each
    // skipped when its address is null): the position into the write slot (and the RwFrame through sub_48D370 unless
    // flag bit 0), the rotation, then the index moves on. Two register allocations were compiled: q = false uses
    // $v0 / $a0 / $v1, q = true $v1 / $a1 / $a0. The caller checked +118 < 4.
    void push_key(const Gpr& cam, Gpr& idx, const Gpr& key, u32 link, bool q, u64 last) {
        Gpr& p = q ? v1 : v0;
        Gpr& rot = q ? a1 : a0;
        Gpr& s = q ? a0 : v1;
        charge(3);
        lhu(idx, cam, kCamWrite);
        if (key != 0) {
            charge(15);
            key_slot(p, a1, idx, cam);
            copy_vec3(key, 0, p, kKeyPos);
            lhu(p, cam, kCamFlags);
            p = p & 0x1;
            if (p == 0) {
                charge(4);
                lw(a0, cam, kCamFrame);
                a2 = key;
                jal(link, rg::fn_sub_48D370_0048d370);
            }
        }
        charge(3);
        rot = addiu(key, 12);
        if (rot != 0) {
            charge(13);
            key_slot(p, s, idx, cam);
            copy_vec4(rot, 0, p, kKeyRot);
        }
        key_advance(p, s, idx, cam, last);
    }
    // The same push of a key in the frame at sp+off (position) / sp+off+12 (rotation).
    void push_key_frame(const Gpr& cam, Gpr& idx, s32 off, u32 link, bool q) {
        Gpr& p = q ? v1 : v0;
        Gpr& s = q ? a0 : v1;
        charge(4);
        lhu(idx, cam, kCamWrite);
        a2 = addiu(sp, off);
        if (a2 != 0) {
            charge(15);
            key_slot(p, a1, idx, cam);
            copy_vec3(sp, off, p, kKeyPos);
            lhu(p, cam, kCamFlags);
            p = p & 0x1;
            if (p == 0) {
                charge(3);
                lw(a0, cam, kCamFrame);
                jal(link, rg::fn_sub_48D370_0048d370);
            }
        }
        charge(3);
        p = addiu(sp, off + 12);
        if (p != 0) {
            charge(13);
            key_slot(p, s, idx, cam);
            copy_vec4(sp, off + 12, p, kKeyRot);
        }
        key_advance(p, s, idx, cam, 4);
    }
    // The ring emptied: +0 = flags, +116 = +118 = +120 = 0, +128 = +124 = 0.
    void reset_ring(const Gpr& cam, const Gpr& flags) {
        sh(flags, cam, kCamFlags);
        sh(zero, cam, kCamHead);
        sh(zero, cam, kCamCount);
        sh(zero, cam, kCamWrite);
        sw(zero, cam, kCamProgress);
        sw(zero, cam, kCamT);
    }
    // The segment of path parameter $f12 (`seg` the head +116 on entry): while t >= 1/3: seg++, t -= 1/3 (a test-first
    // loop); then t /= 1/3 and seg / seg + 1 wrapped to the ring (`& 3` when >= 4). $f0 = 1/3 on the way; `ft` is the
    // parameter register; `next` gets seg + 1.
    void segment(Gpr& seg, Gpr& next, Gpr& tmp, unsigned ft, u64 after_wrap) {
        for (;;) {
            charge(4);
            c_lt_s(ft, F0);
            if (cc()) break;
            backedge();
            charge(3);
            tmp = addiu(seg, 1);
            seg = tmp & 0xffff;
            sub_s(ft, ft, F0);
        }
        charge(8);
        div_s(ft, ft, F0);
        tmp = seg & 0xffff;
        tmp = slti(tmp, 4);
        if (tmp == 0) {
            charge(1);
            seg = seg & 0x3;
        }
        charge(6);
        tmp = seg & 0xffff;
        tmp = addiu(tmp, 1);
        next = tmp & 0xffff;
        tmp = slti(next, 4);
        if (tmp == 0) {
            charge(1);
            next = next & 0x3;
        }
        charge(after_wrap);
    }
    // One colour channel of the scene packet: the byte at gp+off as a float * 1/255 into the frame word sp+dst.
    void gp_byte_to_float(s32 off, s32 dst, u64 cycles) {
        lbu(v0, gp, off);
        u2f(F1, F0, v0, v1, v0);
        charge(cycles);
        lwc1(F0, gp, kGpInv255);
        mul_s(F0, F0, F1);
        swc1(F0, sp, dst);
    }
    // dst = src * (1 - t) + target * t for four floats (src at s0 + so, target at gBtl + to; $f20 = 1 - t, $f21 = t),
    // into the frame words sp+80..92, as compiled for the light colours.
    void lerp_light(s32 so, s32 to) {
        lwc1(F0, s0, so);
        mul_s(F7, F0, F20);
        lwc1(F0, s0, so + 4);
        mul_s(F6, F0, F20);
        lwc1(F0, s0, so + 8);
        mul_s(F5, F0, F20);
        lwc1(F0, s0, so + 12);
        mula_s(F0, F20);
        gbtl(v0);
        lwc1(F0, v0, to);
        mul_s(F4, F0, F21);
        lwc1(F0, v0, to + 4);
        mul_s(F3, F0, F21);
        lwc1(F0, v0, to + 8);
        mul_s(F2, F0, F21);
        lwc1(F1, v0, to + 12);
        add_s(F0, F7, F4);
    }
    // ... the same into gBtl + dst (gBtl re-read before each of the last three stores, as compiled)
    void lerp_scene(s32 so, s32 to, s32 dst) {
        lerp_light(so, to);
        swc1(F0, v0, dst);
        add_s(F0, F6, F3);
        gbtl(v0);
        swc1(F0, v0, dst + 4);
        add_s(F0, F5, F2);
        gbtl(v0);
        swc1(F0, v0, dst + 8);
        madd_s(F0, F1, F21);
        gbtl(v0);
        swc1(F0, v0, dst + 12);
    }
    // the light lerp's result into the frame words sp+80..92
    void lerp_light_to_frame(s32 so, s32 to) {
        lerp_light(so, to);
        swc1(F0, sp, 80);
        add_s(F0, F6, F3);
        swc1(F0, sp, 84);
        add_s(F0, F5, F2);
        swc1(F0, sp, 88);
        madd_s(F0, F1, F21);
        swc1(F0, sp, 92);
    }
    // the four lists of btlUnits gBtl+336 + 8k (k = 0..3, along +2612): `k` counts, `unit` walks; body(unit).
    // `tail`: the cycles of the block that loads the next unit when it is a block of its own (1); 0 when the body's
    // last block runs on into that load (the fade and the final colour loops).
    template <typename Body>
    void each_unit(Gpr& k, Gpr& tmp, Gpr& tmp2, Gpr& unit, u64 head, Body body, u64 tail = 1) {
        for (;;) {
            charge(3);
            tmp = sltiu(k, 4);
            if (tmp == 0) break;
            backedge();
            charge(6);
            tmp2 = sll(k, 3);
            gbtl(tmp);
            tmp = addu(tmp, tmp2);
            lw(unit, tmp, kSideListB);
            for (;;) {
                charge(2);
                if (unit == 0) break;
                backedge();
                charge(head);
                body();
                charge(tail);
                lw(unit, unit, kUnitNextB);
            }
            charge(1);
            k = addiu(k, 1);
        }
    }
    // sin(x) by its odd series on the EE (`x2 = x * x; acc = c1 + c0 * x2 ...; out = x + x2 * x * poly`): x = a * b;
    // c[0..5] hold the coefficients (loaded by the caller), zero is $f11.
    void sin_series(unsigned out, unsigned x, unsigned x2, unsigned a, unsigned b, unsigned p, unsigned q,
                    const unsigned (&k)[6]) {
        mul_s(x, a, b);
        mul_s(x2, x, x);
        adda_s(F11, k[1]);
        madd_s(p, k[0], x2);
        adda_s(F11, k[2]);
        madd_s(p, x2, p);
        adda_s(F11, k[3]);
        madd_s(p, x2, p);
        adda_s(F11, k[4]);
        madd_s(p, x2, p);
        adda_s(F11, k[5]);
        madd_s(q, x2, p);
        mul_s(p, x2, x);
        adda_s(F11, x);
        madd_s(out, p, q);
    }
};

// =====================================================================================================================
// The scene colour fade
// =====================================================================================================================

// 0x2A0440 sub_2A0440(data): the per-frame callback of the scene packet (sub_2A1080; data +80 the frames, +84 the frame
// counter, +88 flags: bit 1 leave the units' colours, bit 2 leave their model fades). Returns 1 at once unless gBtl+12
// has both bit 1 and bit 25. The first frame keeps the start: the ambient colour gBtl+548 (data +0), the two light
// colours sub_19FD40() / sub_19FD70() (+16 / +32), gBtl+452 / +468 (+48 / +64), and for every btlUnit of the four lists
// its colour +60 -> +56 and +112 -> +96, and, unless flag bit 2, for one with a model (+152 bit 1) the model's fade
// (+904 |= 2, &= ~0x14, +937 = 0, +938 = +936 / frames when frames != 0). While frame < frames (t = frame / frames) every
// colour goes from its start towards its target (the ambient to the bytes at gp-25472 through sub_19F8F0, the lights to
// gBtl+404 / +420, gBtl+452 / +468 to gBtl+500 / +516, the units' RGBA bytes +60.. and +112.. towards the ambient
// target, unless flag bit 1), frame++ and 0. Then everything is set to its target (the units' colours to the base
// screen colour gp-18424 unless flag bit 1, their models to the default fade unless flag bit 2) and 1.
void Cpu4::sub_2A0440() {
    enter(12);
    sp = addiu(sp, -96);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    gbtl(a0);
    lw(v1, a0, btl_task::kFlags);
    v0 = v1 & 0x2;
    if (v0 == 0) {
        charge(3);
        v0 = li(1);
        return epilogue_2A0440();
    }
    charge(4);
    v0 = lui(0x200);
    v0 = v1 & v0;
    if (v0 == 0) {
        charge(3);
        v0 = li(1);
        return epilogue_2A0440();
    }
    charge(3);
    lw(v0, s0, 84);
    if (v0 == 0) {
        // the first frame: the starting colours
        charge(47);
        copy_vec4(a0, kAmbient, s0, 0);
        copy_vec4(a0, kSceneC, s0, 48);
        copy_vec4(a0, kSceneD, s0, 64);
        jal(0x2a0504, rg::fn_sub_19FD40_0019fd40);
        copy_vec4(v0, 0, s0, 16);
        jal(0x2a052c, rg::fn_sub_19FD70_0019fd70);
        copy_vec4(v0, 0, s0, 32);
        v0 = 0;
        each_unit(v0, v1, a0, v1, 20, [&] {
            lbu(a3, v1, 60);
            lbu(a2, v1, 61);
            lbu(a1, v1, 62);
            lbu(a0, v1, 63);
            sb(a3, v1, 56);
            sb(a2, v1, 57);
            sb(a1, v1, 58);
            sb(a0, v1, 59);
            copy_vec4(v1, 112, v1, 96);
            lhu(a0, s0, 88);
            a0 = a0 & 0x4;
            if (a0 != 0) return;
            charge(4);
            lw(a0, v1, 152);
            a0 = a0 & 0x2;
            if (a0 == 0) return;
            charge(16);
            lw(a1, v1, kUnitModel);
            lbu(a0, a1, 904);
            a0 = a0 | 0x2;
            sb(a0, a1, 904);
            lw(a1, v1, kUnitModel);
            lbu(a0, a1, 904);
            a0 = a0 & 0xeb;
            sb(a0, a1, 904);
            lw(a0, v1, kUnitModel);
            sb(zero, a0, 937);
            lw(a1, v1, kUnitModel);
            lbu(a0, a1, 936);
            sb(a0, a1, 938);
            lw(a2, s0, 80);
            if (a2 == 0) return;
            charge(5);
            lw(a1, v1, kUnitModel);
            lbu(a0, a1, 938);
            divu(a0, a2);
            mflo(a0);
            sb(a0, a1, 938);
        });
    }
    // the ambient target (the bytes at gp-25472) into sp+64..76
    charge(3);
    gp_byte_to_float(kGpAmbientTarget, 64, 6);
    gp_byte_to_float(kGpAmbientTarget + 1, 68, 6);
    gp_byte_to_float(kGpAmbientTarget + 2, 72, 6);
    gp_byte_to_float(kGpAmbientTarget + 3, 76, 8);
    lw(a0, s0, 80);
    lw(v0, s0, 84);
    at = sltu(v0, a0);
    if (at == 0) {
        sub_2A0440_final();
        return epilogue_2A0440();
    }
    charge(2);
    u2f(F1, F0, v0, v1, v0);
    charge(2);
    u2f(F0, F0, a0, v1, v0);
    // t = frame / frames ($f21), 1 - t ($f20)
    charge(163);
    div_s(F21, F1, F0);
    lif(v0, 0x3f80, F0);
    sub_s(F20, F0, F21);
    // the ambient colour (alpha 1.0) through sub_19F8F0 and gBtl+548
    lwc1(F0, s0, 0);
    mul_s(F5, F0, F20);
    lwc1(F0, s0, 4);
    mul_s(F4, F0, F20);
    lwc1(F0, s0, 8);
    mula_s(F0, F20);
    lwc1(F0, sp, 64);
    mul_s(F3, F0, F21);
    lwc1(F0, sp, 68);
    mul_s(F2, F0, F21);
    lwc1(F1, sp, 72);
    add_s(F0, F5, F3);
    swc1(F0, sp, 80);
    add_s(F0, F4, F2);
    swc1(F0, sp, 84);
    madd_s(F0, F1, F21);
    swc1(F0, sp, 88);
    sw(v0, sp, 92);
    gbtl(v0);
    a0 = addiu(sp, 80);
    copy_vec4(sp, 80, v0, kAmbient);
    jal(0x2a0878, rg::fn_sub_19F8F0_0019f8f0);
    // the two lights, gBtl+452 and +468
    lerp_light_to_frame(16, kLightATarget);
    jal(0x2a08e0, rg::fn_sub_19FD40_0019fd40);
    copy_vec4(sp, 80, v0, 0);
    lerp_light_to_frame(32, kLightBTarget);
    jal(0x2a0968, rg::fn_sub_19FD70_0019fd70);
    copy_vec4(sp, 80, v0, 0);
    lerp_scene(48, kSceneCTarget, kSceneC);
    lerp_scene(64, kSceneDTarget, kSceneD);
    lhu(v0, s0, 88);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // the units' colours: RGBA bytes +56.. (start) towards the ambient target into +60..; +96.. * (1 - t) -> +112..
        charge(9);
        v0 = 0;
        lwc1(F0, gp, kGpInv255);
        lif(v1, 0x437f, F4);  // 255
        lif(v1, 0x3f00, F3);  // 0.5
        mtc1(zero, F2);
        each_unit(v0, v1, a0, a1, 3, [&] {
            static constexpr unsigned kChan[3] = {F11, F10, F9};
            for (int k = 0; k < 3; ++k) {
                lbu(v1, a1, 56 + k);
                u2f(F1, F1, v1, a0, v1);
                charge(5);
                mul_s(F1, F0, F1);
                mul_s(kChan[k], F1, F20);
            }
            lbu(v1, a1, 59);
            u2f(F1, F1, v1, a0, v1);
            charge(57);
            mul_s(F1, F0, F1);
            mula_s(F1, F20);
            lwc1(F1, sp, 64);
            mul_s(F5, F1, F21);
            lwc1(F1, sp, 68);
            mul_s(F8, F1, F21);
            lwc1(F1, sp, 72);
            mul_s(F7, F1, F21);
            lwc1(F6, sp, 76);
            add_s(F5, F11, F5);
            swc1(F5, sp, 80);
            add_s(F1, F10, F8);
            swc1(F1, sp, 84);
            add_s(F1, F9, F7);
            swc1(F1, sp, 88);
            madd_s(F1, F6, F21);
            swc1(F1, sp, 92);
            // each channel back to a byte: (int)(c * 255 + 0.5)
            for (int k = 0; k < 4; ++k) {
                if (k > 0) lwc1(F1, sp, 80 + 4 * k);
                adda_s(F2, F3);
                madd_s(F1, F4, k == 0 ? F5 : F1);
                cvt_w_s(F1, F1);
                mfc1(v1, F1);
                sb(v1, a1, 60 + k);
            }
            for (int k = 0; k < 4; ++k) {
                lwc1(F1, a1, 96 + 4 * k);
                mul_s(F1, F1, F20);
                swc1(F1, a1, 112 + 4 * k);
            }
        }, 0);
        charge(2);
    }
    charge(4);
    lw(v0, s0, 84);
    v0 = addiu(v0, 1);
    sw(v0, s0, 84);
    v0 = 0;
    epilogue_2A0440();
}
void Cpu4::epilogue_2A0440() {
    charge(8);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 96);
}
// sub_2A0440's last frame: every colour to its target; v0 = 1.
void Cpu4::sub_2A0440_final() {
    charge(54);
    a0 = addiu(sp, 64);
    jal(0x2a0cc4, rg::fn_sub_19F8F0_0019f8f0);
    gbtl(s1);
    copy_vec4(sp, 64, s1, kAmbient);
    jal(0x2a0cf0, rg::fn_sub_19FD40_0019fd40);
    copy_vec4(s1, kLightATarget, v0, 0);
    gbtl(s1);
    jal(0x2a0d1c, rg::fn_sub_19FD70_0019fd70);
    copy_vec4(s1, kLightBTarget, v0, 0);
    gbtl(v0);
    copy_vec4(v0, kSceneCTarget, v0, kSceneC);
    copy_vec4(v0, kSceneDTarget, v0, kSceneD);
    lhu(v0, s0, 88);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // the units' colours to the ambient target bytes, +112.. to the base screen colour
        charge(3);
        gp_byte_to_float(kGpBaseColour, 80, 6);
        gp_byte_to_float(kGpBaseColour + 1, 84, 6);
        gp_byte_to_float(kGpBaseColour + 2, 88, 6);
        gp_byte_to_float(kGpBaseColour + 3, 92, 6);
        a3 = 0;
        each_unit(a3, v0, v1, a2, 17, [&] {
            lbu(a1, gp, kGpAmbientTarget);
            lbu(a0, gp, kGpAmbientTarget + 1);
            lbu(v1, gp, kGpAmbientTarget + 2);
            lbu(v0, gp, kGpAmbientTarget + 3);
            sb(a1, a2, 60);
            sb(a0, a2, 61);
            sb(v1, a2, 62);
            sb(v0, a2, 63);
            copy_vec4(sp, 80, a2, 112);
        }, 0);
    }
    charge(4);
    lhu(v0, s0, 88);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // the units' models: the default fade (+904 &= 0xFA then |= 2, +924 = +928 * 1.25 capped at 1.0, +932 =
        // gp-32104, +936 = 0, +937 = 160, +938 = 6, +940 = 1.0f, +944 = gp-32264) unless +904 bit 4
        charge(11);
        v1 = 0;
        lif(v0, 0x3fa0, F4);  // 1.25
        lwc1(F3, gp, -32104);
        t0 = li(160);
        a3 = li(6);
        a2 = lui(0x3f80);
        mtc1(a2, F2);
        lwc1(F1, gp, -32264);
        each_unit(v1, v0, a0, v0, 4, [&] {
            lw(a0, v0, 152);
            a0 = a0 & 0x2;
            if (a0 == 0) return;
            charge(6);
            lw(a0, v0, kUnitModel);
            t1 = addiu(a0, 904);
            lbu(a1, a0, 904);
            a0 = a1 & 0x10;
            if (a0 != 0) return;
            charge(28);
            a0 = a1 & 0xfa;
            sb(a0, t1, 0);
            lw(a1, v0, kUnitModel);
            lbu(a0, a1, 904);
            a0 = a0 | 0x2;
            sb(a0, a1, 904);
            lw(a0, v0, kUnitModel);
            lwc1(F0, a0, 928);
            mul_s(F0, F4, F0);
            swc1(F0, a0, 924);
            lw(a0, v0, kUnitModel);
            swc1(F3, a0, 932);
            lw(a0, v0, kUnitModel);
            sb(zero, a0, 936);
            lw(a0, v0, kUnitModel);
            sb(t0, a0, 937);
            lw(a0, v0, kUnitModel);
            sb(a3, a0, 938);
            lw(a0, v0, kUnitModel);
            sw(a2, a0, 940);
            lw(a0, v0, kUnitModel);
            swc1(F1, a0, 944);
            lw(a1, v0, kUnitModel);
            a0 = addiu(a1, 924);
            lwc1(F0, a1, 924);
            c_le_s(F0, F2);
            if (cc()) return;
            charge(1);
            swc1(F2, a0, 0);
        });
    }
    charge(3);
    v0 = li(1);
}

// =====================================================================================================================
// The camera object: interpolation and the key ring
// =====================================================================================================================

// 0x2A1E00 sub_2A1E00(out, a, b; $f12 = t): one camera key between the keys a and b: position = a * (1 - t) + b * t;
// rotation (+12) = a's for t <= 0, b's for t >= 1, else the slerp sub_4BE310(a + 12, b + 12, sp+80) gives (axis
// sp+80.., sp+96.., angle sp+112, flag sp+116: no sine weights when set): weights sin((1 - t) angle) and sin(t angle) by
// the sine series (unless the flag), rotation xyz = sp+80.. * w0 + sp+96.. * w1, w = sp+92 * w0 + sp+108 * w1.
void Cpu4::sub_2A1E00() {
    enter(42);
    sp = addiu(sp, -128);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s0 = a0;
    s2 = a1;
    s1 = a2;
    mov_s(F21, F12);
    lif(v0, 0x3f80, F0);
    sub_s(F20, F0, F21);
    lwc1(F0, a1, 4);
    mul_s(F5, F0, F20);
    lwc1(F0, a1, 8);
    mul_s(F4, F0, F20);
    lwc1(F0, a2, 4);
    mul_s(F3, F0, F21);
    lwc1(F0, a2, 8);
    mul_s(F2, F0, F21);
    lwc1(F1, a1, 0);
    lwc1(F0, a2, 0);
    mula_s(F0, F21);
    madd_s(F0, F1, F20);
    swc1(F0, a0, 0);
    add_s(F0, F5, F3);
    swc1(F0, a0, 4);
    add_s(F0, F4, F2);
    swc1(F0, a0, 8);
    a0 = addiu(s2, 12);
    a1 = addiu(s1, 12);
    a2 = addiu(sp, 80);
    jal(0x2a1e8c, rg::fn_sub_4BE310_004be310);
    mtc1(zero, F11);
    c_le_s(F21, F11);
    if (cc()) {
        charge(10);
        copy_vec4(s2, 12, s0, 12);
    } else {
        charge(6);
        lif(v1, 0x3f80, F0);
        c_le_s(F0, F21);
        if (cc()) {
            charge(10);
            copy_vec4(s1, 12, s0, 12);
        } else {
            charge(3);
            lw(v1, sp, 116);
            if (v1 == 0) {
                charge(37);
                lwc1(F10, sp, 112);
                // the coefficients (gp-32700..-32680) load between the first series' steps, as compiled
                mul_s(F3, F20, F10);
                mul_s(F2, F3, F3);
                lwc1(F9, gp, -32700);
                lwc1(F8, gp, -32696);
                adda_s(F11, F8);
                madd_s(F0, F9, F2);
                lwc1(F7, gp, -32692);
                adda_s(F11, F7);
                madd_s(F0, F2, F0);
                lwc1(F6, gp, -32688);
                adda_s(F11, F6);
                madd_s(F0, F2, F0);
                lwc1(F5, gp, -32684);
                adda_s(F11, F5);
                madd_s(F0, F2, F0);
                lwc1(F4, gp, -32680);
                adda_s(F11, F4);
                madd_s(F1, F2, F0);
                mul_s(F0, F2, F3);
                adda_s(F11, F3);
                madd_s(F20, F0, F1);
                sin_series(F21, F3, F2, F21, F10, F0, F1, {F9, F8, F7, F6, F5, F4});
            }
            charge(31);
            for (int k = 0; k < 3; ++k) {
                lwc1(F0, sp, 80 + 4 * k);
                mul_s(F0, F0, F20);
                swc1(F0, s0, 12 + 4 * k);
            }
            lwc1(F1, sp, 96);
            lwc1(F0, s0, 12);
            mtc1(zero, F2);
            adda_s(F2, F0);
            madd_s(F0, F1, F21);
            swc1(F0, s0, 12);
            for (int k = 1; k < 3; ++k) {
                lwc1(F1, sp, 96 + 4 * k);
                lwc1(F0, s0, 12 + 4 * k);
                adda_s(F2, F0);
                madd_s(F0, F1, F21);
                swc1(F0, s0, 12 + 4 * k);
            }
            lwc1(F1, sp, 92);
            lwc1(F0, sp, 108);
            mula_s(F0, F21);
            madd_s(F0, F1, F20);
            swc1(F0, s0, 24);
        }
    }
    charge(9);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 128);
}

// 0x2A2050 sub_2A2050(cam, pos, rot): pushes a key (pos / rot each skipped when null) into the ring at the write index
// (the position also into the RwFrame through sub_48D370 unless flag bit 0); returns 0 when the ring already holds four
// keys, else 1.
void Cpu4::sub_2A2050() {
    enter(12);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    v1 = a1;
    s1 = a2;
    lhu(v0, a0, kCamCount);
    v0 = slti(v0, 4);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        lhu(s0, s2, kCamWrite);
        if (v1 != 0) {
            charge(15);
            key_slot(v0, a1, s0, s2);
            copy_vec3(v1, 0, v0, kKeyPos);
            lhu(v0, s2, kCamFlags);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                charge(4);
                lw(a0, s2, kCamFrame);
                a2 = v1;
                jal(0x2a20dc, rg::fn_sub_48D370_0048d370);
            }
        }
        charge(2);
        if (s1 != 0) {
            charge(13);
            key_slot(v0, v1, s0, s2);
            copy_vec4(s1, 0, v0, kKeyRot);
        }
        key_advance(v0, v1, s0, s2, 5);
        v0 = li(1);
    }
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2A2170 sub_2A2170(cam, key): empties the ring (flags 0) and pushes `key` (position +0, rotation +12): a camera
// standing at one key.
void Cpu4::sub_2A2170() {
    enter(17);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    reset_ring(a0, zero);
    lhu(v1, a0, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key(s2, s0, s1, 0x2a2204, true, 4);
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// 0x2A2290 sub_2A2290(cam, a, b, flags): empties the ring (flags a3) and fills it with four keys: a, the two keys at
// t = 1/3 and 2/3 between a and b (sub_2A1E00 into the frame at sp+80), b.
void Cpu4::sub_2A2290() {
    enter(19);
    sp = addiu(sp, -112);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s3 = a1;
    s0 = a2;
    reset_ring(a0, a3);
    lhu(v0, a0, kCamCount);
    at = slti(v0, 4);
    if (at != 0) push_key(s1, s2, s3, 0x2a232c, false, 4);
    charge(10);
    a0 = addiu(sp, 80);
    a1 = s3;
    a2 = s0;
    lwc1(F12, gp, -32704);  // 1/3
    jal(0x2a23ac, rg::fn_sub_2A1E00_002a1e00);
    lhu(v0, s1, kCamCount);
    at = slti(v0, 4);
    if (at != 0) push_key_frame(s1, s2, 80, 0x2a2414, false);
    charge(10);
    a0 = addiu(sp, 80);
    a1 = s3;
    a2 = s0;
    lwc1(F12, gp, -32676);  // 2/3
    jal(0x2a2494, rg::fn_sub_2A1E00_002a1e00);
    lhu(v1, s1, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key_frame(s1, s2, 80, 0x2a24fc, true);
    charge(4);
    lhu(v1, s1, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key(s1, s2, s0, 0x2a25cc, true, 4);
    charge(8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
}

// 0x2A2660 sub_2A2660(cam, k0, k1, k2, t0 = k3, t1 = flags): empties the ring (flags t1) and pushes the four keys k0..k3
// (a four-key path: the Bezier / RW spline of sub_2A2ED0).
void Cpu4::sub_2A2660() {
    enter(23);
    sp = addiu(sp, -112);
    sd(ra, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    s5 = a1;
    s4 = a2;
    s3 = a3;
    s2 = t0;
    reset_ring(a0, t1);
    lhu(v1, a0, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key(s0, s1, s5, 0x2a270c, true, 4);
    charge(4);
    lhu(v1, s0, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key(s0, s1, s4, 0x2a27dc, true, 4);
    charge(4);
    lhu(v1, s0, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key(s0, s1, s3, 0x2a28ac, true, 4);
    charge(4);
    lhu(v1, s0, kCamCount);
    at = slti(v1, 4);
    if (at != 0) push_key(s0, s1, s2, 0x2a297c, true, 4);
    charge(10);
    ld(ra, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
}

// 0x2A2A20 sub_2A2A20(cam, out; $f12 = t): the cubic Bezier of the four keys from the head: out = sum over i of
// B_i(t) * key(head + i).position with B = ((1-t)^3, 3t(1-t)^2, 3t^2(1-t), t^3) (the weights in a 16-byte frame),
// starting from the vector at 0x957180.
void Cpu4::sub_2A2A20() {
    enter(34);
    sp = addiu(sp, -16);
    lif(v1, 0x3f80, F0);
    sub_s(F3, F0, F12);
    mul_s(F1, F3, F3);
    mul_s(F0, F3, F1);
    swc1(F0, sp, 0);
    mul_s(F0, F12, F1);
    lif(v1, 0x4040, F2);  // 3
    mul_s(F0, F2, F0);
    swc1(F0, sp, 4);
    mul_s(F1, F12, F12);
    mul_s(F0, F3, F1);
    mul_s(F0, F2, F0);
    swc1(F0, sp, 8);
    mul_s(F0, F12, F1);
    swc1(F0, sp, 12);
    lhu(a3, a0, kCamHead);
    v1 = lui(0x95);
    lwc1(F2, v1, 29056);
    v1 = lui(0x95);
    lwc1(F1, v1, 29060);
    v1 = lui(0x95);
    lwc1(F0, v1, 29064);
    swc1(F2, a1, 0);
    swc1(F1, a1, 4);
    swc1(F0, a1, 8);
    t0 = 0;
    mtc1(zero, F1);
    for (;;) {
        charge(4);
        v1 = t0 & 0xffff;
        v1 = slti(v1, 4);
        if (v1 == 0) break;
        backedge();
        charge(30);
        v1 = t0 & 0xffff;
        v1 = sll(v1, 2);
        v1 = addu(v1, sp);
        v1 = addiu(v1, 0);
        lwc1(F5, v1, 0);
        key_slot(v1, a2, a3, a0);
        lwc1(F0, v1, 8);
        mul_s(F4, F0, F5);
        lwc1(F0, v1, 12);
        mul_s(F3, F0, F5);
        lwc1(F2, v1, 4);
        lwc1(F0, a1, 0);
        adda_s(F1, F0);
        madd_s(F0, F2, F5);
        swc1(F0, a1, 0);
        lwc1(F0, a1, 4);
        add_s(F0, F0, F4);
        swc1(F0, a1, 4);
        lwc1(F0, a1, 8);
        add_s(F0, F0, F3);
        swc1(F0, a1, 8);
        v1 = addiu(a3, 1);
        a3 = v1 & 0xffff;
        v1 = slti(a3, 4);
        if (v1 == 0) {
            charge(1);
            a3 = 0;
        }
        charge(2);
        v1 = addiu(t0, 1);
        t0 = v1 & 0xffff;
    }
    charge(3);
    sp = addiu(sp, 16);
}

// 0x2A2B50 sub_2A2B50(cam, out; $f12 = t): the position on the straight path: the segment of t (1/3 each from the
// head), out = key(seg).position * (1 - u) + key(seg + 1).position * u.
void Cpu4::sub_2A2B50() {
    enter(4);
    lhu(a2, a0, kCamHead);
    lwc1(F0, gp, kGpThird);
    segment(a2, t0, v1, F12, 33);
    lif(v1, 0x3f80, F0);
    sub_s(F6, F0, F12);
    a2 = a2 & 0xffff;
    v1 = sll(a2, 3);
    v1 = subu(v1, a2);
    v1 = sll(v1, 2);
    a3 = addu(v1, a0);
    lwc1(F0, a3, 8);
    mul_s(F5, F0, F6);
    lwc1(F0, a3, 12);
    mul_s(F4, F0, F6);
    key_slot(v1, a2, t0, a0);
    lwc1(F0, v1, 8);
    mul_s(F3, F0, F12);
    lwc1(F0, v1, 12);
    mul_s(F2, F0, F12);
    lwc1(F1, a3, 4);
    lwc1(F0, v1, 4);
    mula_s(F0, F12);
    madd_s(F0, F1, F6);
    swc1(F0, a1, 0);
    add_s(F0, F5, F3);
    swc1(F0, a1, 4);
    add_s(F0, F4, F2);
    swc1(F0, a1, 8);
}

// 0x2A2C40 sub_2A2C40(cam, out; $f12 = t): the rotation on the path: the segment of t, then the slerp of key(seg) and
// key(seg + 1) rotations (sub_4BE310, the sine series with the gp-31788.. coefficients) at the local parameter, as
// sub_2A1E00 does for one pair of keys.
void Cpu4::sub_2A2C40() {
    enter(12);
    sp = addiu(sp, -128);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s1 = a1;
    mov_s(F20, F12);
    lhu(a1, a0, kCamHead);
    lwc1(F0, gp, kGpThird);
    segment(a1, v1, v0, F20, 22);
    v1 = v1 & 0xffff;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(a0, v0);
    s0 = addiu(v0, kKeyRot);
    v1 = a1 & 0xffff;
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(a0, v0);
    s2 = addiu(v0, kKeyRot);
    a0 = s2;
    a1 = s0;
    a2 = addiu(sp, 80);
    jal(0x2a2d08, rg::fn_sub_4BE310_004be310);
    mtc1(zero, F11);
    c_le_s(F20, F11);
    if (cc()) {
        charge(10);
        copy_vec4(s2, 0, s1, 0);
    } else {
        charge(6);
        lif(v1, 0x3f80, F0);
        c_le_s(F0, F20);
        if (cc()) {
            charge(10);
            copy_vec4(s0, 0, s1, 0);
        } else {
            charge(4);
            sub_s(F0, F0, F20);
            lw(v1, sp, 116);
            if (v1 == 0) {
                charge(37);
                lwc1(F10, sp, 112);
                mul_s(F4, F0, F10);
                mul_s(F3, F4, F4);
                lwc1(F9, gp, -31788);
                lwc1(F8, gp, -32696);
                adda_s(F11, F8);
                madd_s(F0, F9, F3);
                lwc1(F7, gp, -32488);
                adda_s(F11, F7);
                madd_s(F0, F3, F0);
                lwc1(F6, gp, -32688);
                adda_s(F11, F6);
                madd_s(F0, F3, F0);
                lwc1(F5, gp, -32684);
                adda_s(F11, F5);
                madd_s(F0, F3, F0);
                lwc1(F2, gp, -31784);
                adda_s(F11, F2);
                madd_s(F1, F3, F0);
                mul_s(F0, F3, F4);
                adda_s(F11, F4);
                madd_s(F0, F0, F1);
                sin_series(F20, F4, F3, F20, F10, F1, F2, {F9, F8, F7, F6, F5, F2});
            }
            charge(31);
            for (int k = 0; k < 3; ++k) {
                lwc1(F1, sp, 80 + 4 * k);
                mul_s(F1, F1, F0);
                swc1(F1, s1, 4 * k);
            }
            lwc1(F2, sp, 96);
            lwc1(F1, s1, 0);
            mtc1(zero, F3);
            adda_s(F3, F1);
            madd_s(F1, F2, F20);
            swc1(F1, s1, 0);
            for (int k = 1; k < 3; ++k) {
                lwc1(F2, sp, 96 + 4 * k);
                lwc1(F1, s1, 4 * k);
                adda_s(F3, F1);
                madd_s(F1, F2, F20);
                swc1(F1, s1, 4 * k);
            }
            lwc1(F2, sp, 92);
            lwc1(F1, sp, 108);
            mula_s(F1, F20);
            madd_s(F0, F2, F0);
            swc1(F0, s1, 12);
        }
    }
    charge(8);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 128);
}

// 0x2A2ED0 sub_2A2ED0(cam, pos, rot): the camera's current position and rotation from the ring at +124: no key -> 0;
// one key -> the head key as it is, 0; two or three keys -> the straight path (sub_2A2B50); four -> the Bezier
// (sub_2A2A20) with flag bit 0, else the RwFrame spline sub_48D480(frame, 10, pos, 0); then the rotation sub_2A2C40;
// returns 1.
void Cpu4::sub_2A2ED0() {
    enter(10);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    a3 = a1;
    s0 = a2;
    lhu(v0, a0, kCamCount);
    if (!gtz(v0)) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        at = slti(v0, 2);
        if (at != 0) {
            charge(27);
            lhu(v1, s1, kCamHead);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, s1);
            copy_vec3(v0, kKeyPos, a3, 0);
            lhu(v1, s1, kCamHead);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, s1);
            copy_vec4(v0, kKeyRot, s0, 0);
            v0 = 0;
        } else {
            charge(3);
            at = slti(v0, 4);
            if (at != 0) {
                charge(5);
                lwc1(F12, s1, kCamT);
                jal(0x2a2f8c, rg::fn_sub_2A2B50_002a2b50);
            } else {
                charge(4);
                lhu(v0, s1, kCamFlags);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    charge(5);
                    lwc1(F12, s1, kCamT);
                    jal(0x2a2fb0, rg::fn_sub_2A2A20_002a2a20);
                } else {
                    charge(7);
                    lw(a0, s1, kCamFrame);
                    a1 = li(10);
                    lwc1(F12, s1, kCamT);
                    a2 = a3;
                    a3 = 0;
                    jal(0x2a2fd4, rg::fn_sub_48D480_0048d480);
                }
            }
            charge(6);
            a0 = s1;
            a1 = s0;
            lwc1(F12, s1, kCamT);
            jal(0x2a2fe8, rg::fn_sub_2A2C40_002a2c40);
            v0 = li(1);
        }
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// 0x2A3010 sub_2A3010(cam; $f12 = step): moves the path parameter on. Fewer than two keys: +124 = 0, returns 0.
// Otherwise t = +124 + step; with 2 keys, t >= 1/3 drops one key (head + 1, count - 1, t = 0); with 3, t >= 2/3 drops
// two (t = 0); with 4, t >= 0.9999 drops three (t -= 1); the head wraps (& 3 at 4), +124 = t, returns 1.
void Cpu4::sub_2A3010() {
    enter(4);
    lhu(v1, a0, kCamCount);
    at = slti(v1, 2);
    if (at != 0) {
        charge(4);
        sw(zero, a0, kCamT);
        v0 = 0;
    } else {
        charge(5);
        lwc1(F0, a0, kCamT);
        add_s(F1, F0, F12);
        at = slti(v1, 3);
        if (at != 0) {
            charge(4);
            lwc1(F0, gp, kGpThird);
            c_lt_s(F1, F0);
            if (!cc()) {
                charge(8);
                mtc1(zero, F1);
                v0 = addiu(v1, -1);
                sh(v0, a0, kCamCount);
                lhu(v0, a0, kCamHead);
                v0 = addiu(v0, 1);
                sh(v0, a0, kCamHead);
            }
        } else {
            charge(3);
            at = slti(v1, 4);
            if (at != 0) {
                charge(4);
                lwc1(F0, gp, -32676);  // 2/3
                c_lt_s(F1, F0);
                if (!cc()) {
                    charge(8);
                    mtc1(zero, F1);
                    v0 = addiu(v1, -2);
                    sh(v0, a0, kCamCount);
                    lhu(v0, a0, kCamHead);
                    v0 = addiu(v0, 2);
                    sh(v0, a0, kCamHead);
                }
            } else {
                charge(4);
                lwc1(F0, gp, -31792);  // 0.9999
                c_lt_s(F1, F0);
                if (!cc()) {
                    charge(9);
                    lif(v0, 0x3f80, F0);
                    sub_s(F1, F1, F0);
                    v0 = addiu(v1, -3);
                    sh(v0, a0, kCamCount);
                    lhu(v0, a0, kCamHead);
                    v0 = addiu(v0, 3);
                    sh(v0, a0, kCamHead);
                }
            }
        }
        charge(4);
        lhu(v1, a0, kCamHead);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            charge(2);
            v0 = v1 & 0x3;
            sh(v0, a0, kCamHead);
        }
        charge(2);
        swc1(F1, a0, kCamT);
        v0 = li(1);
    }
    charge(2);
}

// 0x2A3110 sub_2A3110(cam; $f12 = seconds): the eased curve over seconds: +132 = 60 * seconds frames (computed as
// 2 * s * 60 / 2), +148 = 0.5, flag bit 1 off, bit 2 on.
void Cpu4::sub_2A3110() {
    enter(19);
    lif(v1, 0x4270, F2);  // 60
    lif(v1, 0x4000, F1);  // 2
    mul_s(F0, F1, F12);
    mul_s(F0, F2, F0);
    div_s(F0, F0, F1);
    swc1(F0, a0, kCamDuration);
    v1 = lui(0x3f00);
    sw(v1, a0, kCamEase);
    lhu(v1, a0, kCamFlags);
    v1 = v1 & 0xfffd;
    sh(v1, a0, kCamFlags);
    lhu(v1, a0, kCamFlags);
    v1 = v1 | 0x4;
    sh(v1, a0, kCamFlags);
}

// 0x2A3160 sub_2A3160(cam; $f12 = seconds): the linear curve: +132 = 60 * seconds / 2 frames (computed as s * 60 / 2),
// flag bits 1 and 2 off.
void Cpu4::sub_2A3160() {
    enter(17);
    lif(v1, 0x4270, F0);  // 60
    mul_s(F1, F0, F12);
    lif(v1, 0x4000, F0);  // 2
    div_s(F0, F1, F0);
    swc1(F0, a0, kCamDuration);
    lhu(v1, a0, kCamFlags);
    v1 = v1 & 0xfffd;
    sh(v1, a0, kCamFlags);
    lhu(v1, a0, kCamFlags);
    v1 = v1 & 0xfffb;
    sh(v1, a0, kCamFlags);
}

// 0x2A31B0 sub_2A31B0(cam): one frame of the camera's motion. The step: flag bit 1 -> sub_2D21E0(cam + 132; $f12 = 1)
// - +128; bit 2 -> while +148 < 0.99999: +148 += 1 / +132, the eased value 2 * ((-1 - 2e^2 + 4e) - 0.5) - +128 (else 0);
// neither -> 1 / +132. +128 += step, the path moves on (sub_2A3010) and the game camera gBtl+32 writes its position and
// rotation to gBtl+188 / +200 (sub_2A2ED0).
void Cpu4::sub_2A31B0() {
    enter(8);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lhu(v1, a0, kCamFlags);
    v0 = v1 & 0x2;
    if (v0 != 0) {
        charge(9);
        lif(v0, 0x3f80, F12);
        a0 = addiu(s0, kCamDuration);
        jal(0x2a31dc, rg::fn_sub_2D21E0_002d21e0);
        lwc1(F1, s0, kCamProgress);
        sub_s(F12, F0, F1);
    } else {
        charge(3);
        v0 = v1 & 0x4;
        if (v0 != 0) {
            charge(5);
            lwc1(F2, s0, kCamEase);
            lwc1(F0, gp, -31796);  // 0.99999
            c_lt_s(F2, F0);
            if (cc()) {
                charge(30);
                lif(v0, 0x3f80, F1);
                lwc1(F0, s0, kCamDuration);
                div_s(F0, F1, F0);
                add_s(F4, F2, F0);
                swc1(F4, s0, kCamEase);
                lif(v0, 0x4080, F3);  // 4
                lif(v0, 0xc000, F0);  // -2
                mul_s(F2, F0, F4);
                lif(v0, 0xbf80, F1);  // -1
                mtc1(zero, F0);
                adda_s(F0, F1);
                madda_s(F2, F4);
                madd_s(F2, F3, F4);
                lif(v0, 0x4000, F1);  // 2
                lif(v0, 0x3f00, F0);  // 0.5
                sub_s(F0, F2, F0);
                mul_s(F1, F1, F0);
                lwc1(F0, s0, kCamProgress);
                sub_s(F12, F1, F0);
            } else {
                charge(3);
                mtc1(zero, F12);
            }
        } else {
            charge(4);
            lif(v0, 0x3f80, F1);
            lwc1(F0, s0, kCamDuration);
            div_s(F12, F1, F0);
        }
    }
    charge(17);
    lwc1(F0, s0, kCamProgress);
    add_s(F0, F0, F12);
    swc1(F0, s0, kCamProgress);
    a0 = s0;
    jal(0x2a32b8, rg::fn_sub_2A3010_002a3010);
    gbtl(v0);
    a0 = addiu(v0, 32);
    a1 = addiu(v0, 188);
    a2 = addiu(v0, 200);
    jal(0x2a32d0, rg::fn_sub_2A2ED0_002a2ed0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

}  // namespace p3fes::game::bcam

namespace p3fes::game {
#define P3FES_BCAM_API_4(name, addr) \
    void name(EEContext& ctx) { bcam::Cpu4(ctx).name(); }
P3FES_BCAM_BODIES_4(P3FES_BCAM_API_4)
#undef P3FES_BCAM_API_4
}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {
#define P3FES_BCAM_SHIM_4(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { ::p3fes::game::bcam::Cpu4(ctx).name(); }
P3FES_BCAM_BODIES_4(P3FES_BCAM_SHIM_4)
#undef P3FES_BCAM_SHIM_4
}  // namespace p3fes::recomp_gen
