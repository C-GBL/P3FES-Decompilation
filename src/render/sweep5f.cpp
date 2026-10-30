// Phase 5 slice sweep5f: 80 of the last functions still recompiled (17,168 bytes), hand-written from p3fes_handgen's
// faithful bodies (SLUS_216.21 + symbols/). Every body keeps the recompiled body's registers, frame, spills, $ra links,
// cycle charges and check points (game/include/p3fes/game/hg_cpu.h); the slice adds a role comment per function.
// What is here, by area:
//   - battle / effects: sub_28B800 (an action step), sub_335A70 (a particle emitter);
//   - RenderWare rasters: sub_4D9510, sub_4E96C0 / sub_4E97C0 (pixel pack / unpack by raster format), sub_4E9AA0
//     (image -> raster conversion);
//   - libmpeg: _unknown_extension, _pictureCodingExtension (writes IPU_CTRL through the bus, as the original);
//   - CRI ADX / AIX / AHX: sub_542DC0 .. sub_5540E8, sub_55E978 .. sub_55F4F0 (wrappers inside the CRI / AIXP locks,
//     NULL-pointer error paths, AIXP start / finish);
//   - CRI SRD / DTX / DVCI (the DVD reader under ADX): srd_wait_dvd .. dvci_get_adr_size (sceCdSync / sceCdSeek /
//     sceCdRead / sceCdSearchFile and one sceSifCallRpc, all through their gen:: entry points);
//   - CRI Sofdec / MWPLY: sub_570030 .. sub_5A1380 (demultiplexer step, interface call-throughs, header scans).
// Callees are called through jal(ctx, pc, gen::...) whatever their state; docs/INTEGRATION_LOG.md (sweep5f).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/sweep5f.h"

namespace p3fes::recomp_gen {
void fn_WTLS_get_table_1_005851b0(p3fes::EEContext&);
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegNextBit_004fd658(p3fes::EEContext&);
void fn_asinf_0052ea00(p3fes::EEContext&);
void fn_atanf_0052e408(p3fes::EEContext&);
void fn_btlActionSetState_00299d60(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_dvCiCdSearchFile_00559dd8(p3fes::EEContext&);
void fn_dvCiStopTr_0055a638(p3fes::EEContext&);
void fn_dvci_conv_fname_0055a9b0(p3fes::EEContext&);
void fn_dvci_get_fstate_0055b220(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sceCdGetError_00510ef0(p3fes::EEContext&);
void fn_sceCdRead_00510b80(p3fes::EEContext&);
void fn_sceCdSeek_00510d60(p3fes::EEContext&);
void fn_sceCdSync_00510148(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_19_005851a0(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_strcasecmp_00523dc8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_strtoul_00525e98(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);
void fn_sub_2819D0_002819d0(p3fes::EEContext&);
void fn_sub_29A3E0_0029a3e0(p3fes::EEContext&);
void fn_sub_2D1ED0_002d1ed0(p3fes::EEContext&);
void fn_sub_329740_00329740(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_358030_00358030(p3fes::EEContext&);
void fn_sub_358160_00358160(p3fes::EEContext&);
void fn_sub_358340_00358340(p3fes::EEContext&);
void fn_sub_358380_00358380(p3fes::EEContext&);
void fn_sub_358410_00358410(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE40_004cde40(p3fes::EEContext&);
void fn_sub_4CDF30_004cdf30(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53AE60_0053ae60(p3fes::EEContext&);
void fn_sub_53DD10_0053dd10(p3fes::EEContext&);
void fn_sub_53DEF0_0053def0(p3fes::EEContext&);
void fn_sub_53EC20_0053ec20(p3fes::EEContext&);
void fn_sub_540D40_00540d40(p3fes::EEContext&);
void fn_sub_540D58_00540d58(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_54A6B0_0054a6b0(p3fes::EEContext&);
void fn_sub_54AC40_0054ac40(p3fes::EEContext&);
void fn_sub_54B3F0_0054b3f0(p3fes::EEContext&);
void fn_sub_54F708_0054f708(p3fes::EEContext&);
void fn_sub_551D38_00551d38(p3fes::EEContext&);
void fn_sub_551E30_00551e30(p3fes::EEContext&);
void fn_sub_552480_00552480(p3fes::EEContext&);
void fn_sub_552630_00552630(p3fes::EEContext&);
void fn_sub_552930_00552930(p3fes::EEContext&);
void fn_sub_552BD0_00552bd0(p3fes::EEContext&);
void fn_sub_552D68_00552d68(p3fes::EEContext&);
void fn_sub_5530D0_005530d0(p3fes::EEContext&);
void fn_sub_5535D0_005535d0(p3fes::EEContext&);
void fn_sub_554138_00554138(p3fes::EEContext&);
void fn_sub_5546F0_005546f0(p3fes::EEContext&);
void fn_sub_554708_00554708(p3fes::EEContext&);
void fn_sub_554778_00554778(p3fes::EEContext&);
void fn_sub_554948_00554948(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
void fn_sub_559DA8_00559da8(p3fes::EEContext&);
void fn_sub_55A1D0_0055a1d0(p3fes::EEContext&);
void fn_sub_55A800_0055a800(p3fes::EEContext&);
void fn_sub_55AA58_0055aa58(p3fes::EEContext&);
void fn_sub_55AA90_0055aa90(p3fes::EEContext&);
void fn_sub_55AAE8_0055aae8(p3fes::EEContext&);
void fn_sub_55C9D0_0055c9d0(p3fes::EEContext&);
void fn_sub_55D400_0055d400(p3fes::EEContext&);
void fn_sub_55E1D8_0055e1d8(p3fes::EEContext&);
void fn_sub_55E390_0055e390(p3fes::EEContext&);
void fn_sub_55E3B0_0055e3b0(p3fes::EEContext&);
void fn_sub_55E428_0055e428(p3fes::EEContext&);
void fn_sub_55E940_0055e940(p3fes::EEContext&);
void fn_sub_55F1C8_0055f1c8(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_562E10_00562e10(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564EF8_00564ef8(p3fes::EEContext&);
void fn_sub_5655E8_005655e8(p3fes::EEContext&);
void fn_sub_56DE28_0056de28_at_0056de50(p3fes::EEContext&);
void fn_sub_5703C0_005703c0(p3fes::EEContext&);
void fn_sub_570B98_00570b98(p3fes::EEContext&);
void fn_sub_570CB8_00570cb8(p3fes::EEContext&);
void fn_sub_571088_00571088(p3fes::EEContext&);
void fn_sub_574068_00574068(p3fes::EEContext&);
void fn_sub_5745D0_005745d0(p3fes::EEContext&);
void fn_sub_575410_00575410(p3fes::EEContext&);
void fn_sub_579080_00579080(p3fes::EEContext&);
void fn_sub_57AC68_0057ac68(p3fes::EEContext&);
void fn_sub_581798_00581798(p3fes::EEContext&);
void fn_sub_5851D0_005851d0(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_586628_00586628(p3fes::EEContext&);
void fn_sub_589530_00589530(p3fes::EEContext&);
void fn_sub_589CF0_00589cf0(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58CB00_0058cb00(p3fes::EEContext&);
void fn_sub_58D258_0058d258(p3fes::EEContext&);
void fn_sub_58FC30_0058fc30(p3fes::EEContext&);
void fn_sub_58FE08_0058fe08(p3fes::EEContext&);
void fn_sub_58FEC8_0058fec8(p3fes::EEContext&);
void fn_sub_58FF70_0058ff70(p3fes::EEContext&);
void fn_sub_591C08_00591c08(p3fes::EEContext&);
void fn_sub_595868_00595868(p3fes::EEContext&);
void fn_sub_597168_00597168(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_59B300_0059b300(p3fes::EEContext&);
void fn_sub_59E800_0059e800(p3fes::EEContext&);
void fn_sub_5A0250_005a0250(p3fes::EEContext&);
void fn_sub_5A02C0_005a02c0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0028B800 sub_28B800 -- 448 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// A battle action step: when the global battle flags (*0x7CE3EC +12 bit 0x2000) are set, the actor's word +26 has bit
// 0 and its unit (+48) byte +162 is clear, the action id (+20) becomes 9. If sub_29A3E0 accepts the actor, or the
// distance (sub_2D1ED0) from the unit's position (+4) to the point sub_27F7C0 fills is <= 75.0, it moves to state +20
// (btlActionSetState); otherwise it takes a new object (sub_2819D0), copies the actor's first doubleword to its +96
// and starts it (sub_27ED20(obj, 1)).
void sub_28B800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0028b800
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 48);
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(v0, v0, 12);
    v0 = v0 & 0x2000;
    if (v0 != 0) {
        // 0x0028b82c
        charge(ctx, 4);
        lhu(v0, s1, 26);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x0028b83c
            charge(ctx, 3);
            lbu(v0, s0, 162);
            if (v0 == 0) {
                // 0x0028b848
                charge(ctx, 2);
                v0 = 9;
                sh(v0, s1, 20);
            }
        }
    }
    // 0x0028b850
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x28B854u, gen::fn_sub_29A3E0_0029a3e0);
    if (v0 == 0) {
        // 0x0028b87c
        charge(ctx, 16);
        a0 = s0;
        a1 = addiu(sp, 0x30);
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x28B88Cu, gen::fn_sub_27F7C0_0027f7c0);
        a0 = addiu(s0, 4);
        a1 = addiu(sp, 0x30);
        jal(ctx, 0x28B89Cu, gen::fn_sub_2D1ED0_002d1ed0);
        v0 = 0x42960000;
        mtc1(v0, f1);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0028b998
            charge(ctx, 4);
            a0 = s1;
            lhu(a1, s1, 20);
            jal(ctx, 0x28B9A0u, gen::fn_btlActionSetState_00299d60);
        } else {
            // 0x0028b8bc
            charge(ctx, 21);
            a1 = 2;
            lhu(v1, s1, 110);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, gp, -18680);  // gBtlSkillTbl
            v0 = addu(v0, v1);
            lbu(v0, v0, 0);
            v0 = v0 & 0x2;
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            a3 = v0 & 0xFFFF;
            lw(a0, s1, 48);
            lw(v0, a0, 2604);
            lhu(a2, v0, 2);
            lbu(v1, a0, 162);
            v0 = 1;
            if (v1 == v0) {
                // 0x0028b920
                charge(ctx, 12);
                lw(a1, gp, -18648);  // 0x7CE418
                v1 = a2 & 0xFFFF;
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v1 = addu(v0, a1);
                v0 = a3 & 0xFFFF;
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(a1, v0, 36);
            } else {
                // 0x0028b910
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0028b918
                    charge(ctx, 2);
                }
            }
            // 0x0028b950
            charge(ctx, 18);
            v0 = a1 & 0xFFFF;
            v1 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, 13056);  // &0x693300
            v0 = addu(v0, v1);
            a1 = addiu(sp, 0x30);
            lwc1(f12, v0, 0);
            a2 = 0;
            jal(ctx, 0x28B970u, gen::fn_sub_2819D0_002819d0);
            a0 = v0;
            ld(v1, s1, 0);
            sd(v1, v0, 96);
            a1 = 1;
            jal(ctx, 0x28B988u, gen::fn_sub_27ED20_0027ed20);
        }
    } else {
        // 0x0028b864
        charge(ctx, 6);
        a0 = s1;
        lhu(a1, s1, 20);
        jal(ctx, 0x28B86Cu, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028b9a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00335A70 sub_335A70 -- 2996 bytes; frame 0x1E0: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// A particle emitter update (746 instructions, VU0 macro-mode math): for an emitter ($a0: +40 limit, +48 state, +52
// definition) it spawns particles while the live count is under the limit, drawing random values (sub_357FD0 /
// sub_358030), building directions with sinf / cosf / asinf / atanf, sampling a geometry under geometryLock and
// handing each particle to sub_4933D0. The pseudocode reference reads only part of it (status ok_partial); the body
// is the instruction-faithful one.
void sub_335A70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30};
    // 0x00335a70
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f31, sp, 0x2C);
    swc1(f30, sp, 0x28);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a0, 48);
    lw(s3, a0, 52);
    lw(s1, s0, 0);
    lw(a1, s3, 52);
    lw(v1, a0, 40);
    at = sltu(a1, v1);
    if (at != 0) {
        // 0x00335aec
        charge(ctx, 2);
        if (a1 == 0) {
            goto L_00335af4;
        }
        // 0x003365c0 (the shared epilogue, written out on this path)
        charge(ctx, 25);
        ld(ra, sp, 0xC0);
        lq(fp, sp, 0xB0);
        lq(s7, sp, 0xA0);
        lq(s6, sp, 0x90);
        lq(s5, sp, 0x80);
        lq(s4, sp, 0x70);
        lq(s3, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        lwc1(f31, sp, 0x2C);
        lwc1(f30, sp, 0x28);
        lwc1(f29, sp, 0x24);
        lwc1(f28, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x1E0);
        return;
    }
L_00335af4:
    charge(ctx, 5);
    lw(fp, s3, 56);
    lw(s6, s3, 64);
    lw(v1, s3, 60);
    if (i64(v1) < 0) {
        // 0x00335b1c
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f2, f0);
        add_s(f2, f2, f2);
    } else {
        // 0x00335b08
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f2, f0);
    }
    // 0x00335b38
    charge(ctx, 8);
    lwc1(f0, s3, 132);
    div_s(f31, f0, f2);
    lw(v1, s3, 76);
    if (i64(v1) < 0) {
        // 0x00335b6c
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x00335b58
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x00335b88
    charge(ctx, 14);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    mul_s(f0, f0, f1);
    div_s(f0, f0, f2);
    swc1(f0, sp, 0x114);
    lwc1(f28, s3, 80);
    lwc1(f0, s3, 168);
    swc1(f0, sp, 0x10C);
    lbu(v1, s3, 136);
    sq(v1, sp, 0x120);
    mtc1(zero, f0);
    c_le_s(f31, f0);
    if (!cond(ctx)) {
        // 0x00335bc0
        charge(ctx, 63);
        a0 = addiu(sp, 0x160);
        jal(ctx, 0x335BC4u, gen::fn_sub_329740_00329740);
        lwc1(f25, gp, -32348);  // 0x7CAE94
        v1 = 0x41200000;
        mtc1(v1, f0);
        div_s(f1, f31, f0);
        lwc1(f0, gp, -32524);  // 0x7CADE4
        mul_s(f0, f0, f1);
        neg_s(f0, f0);
        swc1(f0, sp, 0x108);
        mtc1(zero, f23);
        sw(zero, sp, 0x1A0);
        lwc1(f2, s3, 128);
        swc1(f2, sp, 0x1A4);
        lwc1(f1, s3, 124);
        add_s(f0, f2, f1);
        swc1(f0, sp, 0x1A8);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0x1AC);
        add_s(f0, f0, f2);
        swc1(f0, sp, 0x1B0);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xFC);
        sw(v1, sp, 0x19C);
        sw(v1, sp, 0x15C);
        lwc1(f24, s0, 4);
        lwc1(f0, s0, 8);
        add_s(f0, f24, f0);
        swc1(f0, s0, 4);
        s0 = 0;
        v1 = 0x3F000000;
        mtc1(v1, f22);
        v1 = 0x40000000;
        mtc1(v1, f21);
        lwc1(f20, gp, -32408);  // 0x7CAE58
        lwc1(f0, gp, -32556);  // 0x7CADC4
        swc1(f0, sp, 0xF8);
        v1 = lui(0xBF80);
        mtc1(v1, f0);
        swc1(f0, sp, 0xF4);
        lwc1(f0, gp, -32472);  // 0x7CAE18
        swc1(f0, sp, 0xF0);
        lwc1(f0, gp, -32344);  // 0x7CAE98
        swc1(f0, sp, 0xEC);
        lwc1(f0, gp, -32544);  // 0x7CADD0
        swc1(f0, sp, 0xE8);
        lwc1(f0, gp, -32628);  // 0x7CAD7C
        swc1(f0, sp, 0xE4);
        v1 = 0x3F400000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xE0);
        v1 = 0x3E800000;
        mtc1(v1, f0);
        swc1(f0, sp, 0xDC);
        for (;;) {
            // 0x003365b4
            charge(ctx, 3);
            v1 = slt(s0, fp);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00335cbc
            charge(ctx, 4);
            lw(v1, s1, 20);
            a1 = si(-1);
            if (v1 == a1) {
                // 0x00335ccc
                charge(ctx, 18);
                lwc1(f26, s3, 164);
                a0 = 0;
                jal(ctx, 0x335CD4u, gen::fn_sub_358030_00358030);
                lwc1(f1, sp, 0xFC);
                sub_s(f2, f1, f26);
                mtc1(zero, f1);
                adda_s(f1, f2);
                madd_s(f1, f26, f0);
                lwc1(f0, s3, 160);
                mul_s(f0, f0, f1);
                swc1(f0, s1, 36);
                swc1(f23, s1, 40);
                lq(v0, sp, 0x120);
                v0 = v0 & 0xFF;
                if (v0 != 0) {
                    // 0x00335d3c
                    charge(ctx, 14);
                    a0 = 0;
                    jal(ctx, 0x335D40u, gen::fn_sub_358030_00358030);
                    sub_s(f0, f0, f22);
                    mul_s(f1, f21, f0);
                    lwc1(f0, sp, 0xF8);
                    mul_s(f0, f0, f1);
                    swc1(f0, s1, 28);
                    a0 = 0;
                    jal(ctx, 0x335D60u, gen::fn_sub_358030_00358030);
                    lwc1(f1, s3, 156);
                    mul_s(f0, f1, f0);
                    swc1(f0, s1, 44);
                } else {
                    // 0x00335d14
                    charge(ctx, 10);
                    a0 = 0;
                    jal(ctx, 0x335D18u, gen::fn_sub_358030_00358030);
                    sub_s(f0, f0, f22);
                    mul_s(f0, f21, f0);
                    mul_s(f0, f20, f0);
                    swc1(f0, s1, 28);
                    swc1(f23, s1, 44);
                }
                // 0x00335d74
                charge(ctx, 43);
                a0 = 0;
                jal(ctx, 0x335D78u, gen::fn_sub_358030_00358030);
                sub_s(f0, f0, f22);
                mul_s(f0, f21, f0);
                mul_s(f0, f20, f0);
                swc1(f0, s1, 32);
                lwc1(f12, s1, 28);
                jal(ctx, 0x335D94u, gen::fn_sub_358160_00358160);
                lwc1(f12, s1, 32);
                jal(ctx, 0x335DA0u, gen::fn_sub_358380_00358380);
                jal(ctx, 0x335DA8u, gen::fn_sub_358410_00358410);
                lwc1(f26, s1, 40);
                mov_s(f12, f26);
                jal(ctx, 0x335DB8u, gen::fn_cosf_0052e6d8);
                mul_s(f0, f24, f0);
                swc1(f0, sp, 0x150);
                swc1(f23, sp, 0x154);
                mov_s(f12, f26);
                jal(ctx, 0x335DD0u, gen::fn_sinf_0052e878);
                mul_s(f0, f24, f0);
                swc1(f0, sp, 0x158);
                v1 = addiu(sp, 0x150);
                lqc2(vf10, v1, 0);
                vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                sqc2(vf10, v1, 0);
                lwc1(f0, sp, 0x150);
                swc1(f0, s1, 4);
                lwc1(f0, sp, 0x154);
                swc1(f0, s1, 8);
                lwc1(f0, sp, 0x158);
                swc1(f0, s1, 12);
                v1 = si(-1);
                sw(v1, s1, 24);
                goto L_003365a0;
            }
            // 0x00335e20
            charge(ctx, 8);
            lw(a0, s1, 24);
            v1 = lui(0xFF00);
            v1 = a0 & v1;
            at = 0x40000000;
            at = at | 0x1;
            at = sltu(v1, at);
            if (at != 0) {
                // 0x00335e54
                charge(ctx, 3);
                sw(a1, s1, 20);
                if (i64(s6) > 0) {
                    // 0x00335e60
                    charge(ctx, 10);
                    a0 = 0;
                    jal(ctx, 0x335E64u, gen::fn_sub_357FD0_00357fd0);
                    divu(v0, s6);
                    mfhi(a0);
                    lw(v1, s1, 20);
                    v1 = subu(v1, a0);
                    sw(v1, s1, 20);
                }
            } else {
                // 0x00335e40
                charge(ctx, 5);
                v0 = lui(0xC000);
                v0 = addu(a0, v0);
                sw(v0, s1, 24);
                // 0x00335e88
                charge(ctx, 20);
                lw(s2, s1, 0);
                lh(v1, s2, 8);
                v0 = 5;
                div(v1, v0);
                mflo(s7);
                lw(v0, s2, 16);
                lw(a0, v0, 24);
                a1 = 2;
                jal(ctx, 0x335EA8u, gen::fn_geometryLock_00493370);
                lw(v0, s2, 16);
                lw(v0, v0, 24);
                lw(v0, v0, 92);
                lw(s4, v0, 20);
                a0 = 0;
                jal(ctx, 0x335EC4u, gen::fn_sub_357FD0_00357fd0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x00335ed8
                    charge(ctx, 2);
                    lwc1(f0, sp, 0xF4);
                    mul_s(f28, f28, f0);
                }
                // 0x00335ee0
                charge(ctx, 215);
                a0 = 0;
                jal(ctx, 0x335EE4u, gen::fn_sub_358030_00358030);
                mul_s(f30, f20, f0);
                a0 = 0;
                jal(ctx, 0x335EF4u, gen::fn_sub_358030_00358030);
                mtc1(zero, f2);
                lwc1(f1, sp, 0xEC);
                adda_s(f2, f1);
                lwc1(f1, sp, 0xF0);
                madd_s(f0, f1, f0);
                mul_s(f29, f28, f0);
                mov_s(f12, f30);
                jal(ctx, 0x335F18u, gen::fn_sinf_0052e878);
                mul_s(f26, f29, f0);
                lwc1(f0, sp, 0x114);
                add_s(f30, f30, f0);
                mov_s(f12, f30);
                jal(ctx, 0x335F30u, gen::fn_sinf_0052e878);
                mul_s(f27, f29, f0);
                sub_s(f1, f27, f26);
                mula_s(f31, f31);
                madd_s(f0, f1, f1);
                sqrt_s(f0, f0);
                div_s(f12, f1, f0);
                jal(ctx, 0x335F64u, gen::fn_asinf_0052ea00);
                lwc1(f1, s3, 124);
                swc1(f1, sp, 0x118);
                lwc1(f2, s3, 128);
                add_s(f1, f1, f2);
                swc1(f1, sp, 0x11C);
                mov_s(f26, f0);
                a0 = 0;
                jal(ctx, 0x335F88u, gen::fn_sub_358030_00358030);
                mtc1(zero, f3);
                lwc1(f1, sp, 0xE4);
                adda_s(f3, f1);
                lwc1(f1, sp, 0xE8);
                madd_s(f1, f1, f0);
                lwc1(f0, sp, 0x108);
                mul_s(f0, f0, f1);
                swc1(f0, sp, 0x104);
                lw(v0, s1, 20);
                v0 = addiu(v0, 1);
                mtc1(v0, f0);
                cvt_s_w(f2, f0);
                lwc1(f0, sp, 0x10C);
                mul_s(f1, f0, f2);
                lwc1(f0, s1, 36);
                adda_s(f3, f0);
                madd_s(f0, f22, f1);
                mul_s(f1, f2, f0);
                lwc1(f0, s1, 40);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0xD8);
                lwc1(f12, s1, 28);
                jal(ctx, 0x335FECu, gen::fn_sub_358160_00358160);
                lwc1(f12, s1, 32);
                jal(ctx, 0x335FF8u, gen::fn_sub_358380_00358380);
                jal(ctx, 0x336000u, gen::fn_sub_358410_00358410);
                lwc1(f12, sp, 0xD8);
                jal(ctx, 0x33600Cu, gen::fn_cosf_0052e6d8);
                mul_s(f0, f24, f0);
                swc1(f0, sp, 0x150);
                swc1(f23, sp, 0x154);
                lwc1(f12, sp, 0xD8);
                jal(ctx, 0x336024u, gen::fn_sinf_0052e878);
                mul_s(f0, f24, f0);
                swc1(f0, sp, 0x158);
                v1 = addiu(sp, 0x150);
                lqc2(vf10, v1, 0);
                vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                sqc2(vf10, v1, 0);
                v0 = addiu(sp, 0x140);
                sqc2(vf10, v0, 0);
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                a0 = addiu(sp, 0x180);
                sqc2(vf10, a0, 0);
                lwc1(f1, s1, 4);
                lwc1(f0, sp, 0x140);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x190);
                lwc1(f1, s1, 8);
                lwc1(f0, sp, 0x144);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x194);
                lwc1(f1, s1, 12);
                lwc1(f0, sp, 0x148);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x198);
                v0 = addiu(sp, 0x190);
                lqc2(vf10, v0, 0);
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                lqc2(vf11, a0, 0);
                sqc2(vf10, v0, 0);
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                v0 = addiu(sp, 0x170);
                sqc2(vf10, v0, 0);
                v0 = addiu(sp, 0x160);
                lqc2(vf11, v0, 0);
                vmove(0xF, vf10, vf12);  // vmove.xyzw
                vopmula(0xE, vf10, vf11);  // vopmula.xyz
                vopmsub(0xE, vf10, vf11, vf10);  // vopmsub.xyz
                vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                vwaitq(ctx);
                vmulq(0xE, vf10, vf10);  // vmulq.xyz
                vmove(0xF, vf12, vf10);  // vmove.xyzw
                vmove(0xF, vf11, vf10);  // vmove.xyzw
                lwc1(f0, sp, 0x11C);
                mfc1(v0, f0);
                qmtc2(v0, vf2, false);  // qmtc2
                vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                v0 = 0x6A0000;
                v0 = addiu(v0, -15152);  // &0x69C4D0
                sqc2(vf10, v0, 0);  // 0x69C4D0
                a0 = 0x6A0000;
                lwc1(f0, a0, -15152);  // 0x69C4D0
                swc1(f0, s4, 0);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15148);  // 0x69C4D4
                swc1(f0, s4, 4);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15144);  // 0x69C4D8
                swc1(f0, s4, 8);
                vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
                sqc2(vf10, v0, 0);  // 0x69C4D0
                a0 = 0x6A0000;
                lwc1(f0, a0, -15152);  // 0x69C4D0
                swc1(f0, s4, 48);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15148);  // 0x69C4D4
                swc1(f0, s4, 52);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15144);  // 0x69C4D8
                swc1(f0, s4, 56);
                lwc1(f0, sp, 0x118);
                mfc1(a0, f0);
                qmtc2(a0, vf2, false);  // qmtc2
                vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                sqc2(vf11, v0, 0);  // 0x69C4D0
                a0 = 0x6A0000;
                lwc1(f0, a0, -15152);  // 0x69C4D0
                swc1(f0, s4, 12);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15148);  // 0x69C4D4
                swc1(f0, s4, 16);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15144);  // 0x69C4D8
                swc1(f0, s4, 20);
                vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
                sqc2(vf11, v0, 0);  // 0x69C4D0
                a0 = 0x6A0000;
                lwc1(f0, a0, -15152);  // 0x69C4D0
                swc1(f0, s4, 36);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15148);  // 0x69C4D4
                swc1(f0, s4, 40);
                a0 = 0x6A0000;
                lwc1(f0, a0, -15144);  // 0x69C4D8
                swc1(f0, s4, 44);
                swc1(f23, s4, 24);
                swc1(f23, s4, 28);
                swc1(f23, s4, 32);
                lwc1(f1, s1, 44);
                lwc1(f0, sp, 0x154);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x154);
                lqc2(vf11, v1, 0);
                t2 = 0;
                t0 = 0x6A0000;
                a3 = 0x6A0000;
                a2 = 0x6A0000;
                a1 = 0x6A0000;
                a0 = 0x6A0000;
                v1 = 0x6A0000;
                for (;;) {
                    // 0x00336298
                    charge(ctx, 3);
                    t1 = slti(t2, 5);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0033623c
                    charge(ctx, 23);
                    t1 = sll(t2, 1);
                    t1 = addu(t1, t2);
                    t1 = sll(t1, 2);
                    t1 = addu(s4, t1);
                    lwc1(f0, t1, 0);
                    swc1(f0, t0, -15152);
                    lwc1(f0, t1, 4);
                    swc1(f0, a3, -15148);
                    lwc1(f0, t1, 8);
                    swc1(f0, a2, -15144);
                    lqc2(vf10, v0, 0);
                    vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                    sqc2(vf10, v0, 0);
                    lwc1(f0, a1, -15152);
                    swc1(f0, t1, 0);
                    lwc1(f0, a0, -15148);
                    swc1(f0, t1, 4);
                    lwc1(f0, v1, -15144);
                    swc1(f0, t1, 8);
                    t1 = sll(t2, 2);
                    t1 = addu(t1, sp);
                    swc1(f23, t1, 448);
                    t2 = addiu(t2, 1);
                }
                // 0x003362a4
                charge(ctx, 10);
                s4 = addiu(s4, 60);
                lwc1(f0, sp, 0x140);
                swc1(f0, s1, 4);
                lwc1(f0, sp, 0x144);
                swc1(f0, s1, 8);
                lwc1(f0, sp, 0x148);
                swc1(f0, s1, 12);
                s5 = 1;
                for (;;) {
                    // 0x00336564
                    charge(ctx, 3);
                    v0 = slt(s5, s7);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003362cc
                    charge(ctx, 16);
                    a0 = 0;
                    jal(ctx, 0x3362D0u, gen::fn_sub_358030_00358030);
                    mtc1(zero, f2);
                    lwc1(f1, sp, 0xDC);
                    adda_s(f2, f1);
                    lwc1(f1, sp, 0xE0);
                    madd_s(f0, f1, f0);
                    mul_s(f0, f25, f0);
                    swc1(f0, sp, 0x110);
                    a0 = 0;
                    jal(ctx, 0x3362F8u, gen::fn_sub_357FD0_00357fd0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x0033630c
                        charge(ctx, 2);
                        lwc1(f0, sp, 0xF4);
                        mul_s(f25, f25, f0);
                    }
                    // 0x00336314
                    charge(ctx, 5);
                    lwc1(f0, sp, 0x114);
                    add_s(f30, f30, f0);
                    c_lt_s(f30, f20);
                    if (!cond(ctx)) {
                        // 0x00336328
                        charge(ctx, 23);
                        sub_s(f30, f30, f20);
                        lwc1(f0, sp, 0xF4);
                        mul_s(f28, f28, f0);
                        a0 = 0;
                        jal(ctx, 0x336338u, gen::fn_sub_358030_00358030);
                        mtc1(zero, f2);
                        lwc1(f1, sp, 0xEC);
                        adda_s(f2, f1);
                        lwc1(f1, sp, 0xF0);
                        madd_s(f0, f1, f0);
                        mul_s(f29, f28, f0);
                        a0 = 0;
                        jal(ctx, 0x33635Cu, gen::fn_sub_358030_00358030);
                        mtc1(zero, f2);
                        lwc1(f1, sp, 0xE4);
                        adda_s(f2, f1);
                        lwc1(f1, sp, 0xE8);
                        madd_s(f1, f1, f0);
                        lwc1(f0, sp, 0x108);
                        mul_s(f0, f0, f1);
                        swc1(f0, sp, 0x104);
                    }
                    // 0x00336384
                    charge(ctx, 78);
                    mov_s(f12, f30);
                    jal(ctx, 0x336388u, gen::fn_sinf_0052e878);
                    mul_s(f0, f29, f0);
                    swc1(f0, sp, 0xD4);
                    sub_s(f1, f0, f27);
                    mula_s(f31, f31);
                    madd_s(f0, f1, f1);
                    sqrt_s(f0, f0);
                    div_s(f12, f1, f0);
                    jal(ctx, 0x3363C0u, gen::fn_asinf_0052ea00);
                    lwc1(f1, sp, 0x110);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xD0);
                    mov_s(f12, f26);
                    a0 = addiu(sp, 0x180);
                    jal(ctx, 0x3363DCu, gen::fn_sub_358340_00358340);
                    v0 = addiu(sp, 0x190);
                    lqc2(vf10, v0, 0);
                    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                    v0 = addiu(sp, 0x130);
                    sqc2(vf10, v0, 0);
                    lwc1(f12, sp, 0x104);
                    a0 = addiu(sp, 0x170);
                    jal(ctx, 0x336408u, gen::fn_sub_358340_00358340);
                    v0 = addiu(sp, 0x190);
                    lqc2(vf10, v0, 0);
                    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                    sqc2(vf10, v0, 0);
                    v0 = addiu(sp, 0x140);
                    lqc2(vf10, v0, 0);
                    vmove(0xF, vf11, vf10);  // vmove.xyzw
                    vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf30, vf10, 2);  // vmaddz.xyzw
                    sqc2(vf10, v0, 0);
                    vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                    vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
                    vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
                    vsqrt(vf2, 0);  // vsqrt
                    vwaitq(ctx);
                    cfc2(v0, 22, false);  // cfc2
                    mtc1(v0, f0);
                    swc1(f0, sp, 0x100);
                    lwc1(f0, sp, 0xD0);
                    sub_s(f0, f0, f26);
                    mul_s(f12, f22, f0);
                    jal(ctx, 0x336478u, gen::fn_atanf_0052e408);
                    lwc1(f27, sp, 0xD4);
                    lwc1(f26, sp, 0xD0);
                    v0 = addiu(sp, 0x130);
                    lqc2(vf12, v0, 0);
                    v0 = 0;
                    t0 = 0x6A0000;
                    a3 = 0x6A0000;
                    a2 = 0x6A0000;
                    t2 = 0x6A0000;
                    t2 = addiu(t2, -15152);  // &0x69C4D0
                    a1 = 0x6A0000;
                    a0 = 0x6A0000;
                    v1 = 0x6A0000;
                    for (;;) {
                        // 0x00336550
                        charge(ctx, 3);
                        t1 = slti(v0, 5);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003364bc
                        charge(ctx, 37);
                        t1 = sll(v0, 2);
                        t4 = addu(t1, sp);
                        lwc1(f1, t4, 416);
                        mul_s(f3, f0, f1);
                        t3 = addiu(t4, 448);
                        lwc1(f1, t3, 0);
                        add_s(f1, f1, f3);
                        swc1(f1, t3, 0);
                        vmove(0xF, vf11, vf12);  // vmove.xyzw
                        t1 = sll(v0, 1);
                        t1 = addu(t1, v0);
                        t1 = sll(t1, 2);
                        t1 = addu(s4, t1);
                        lwc1(f1, t1, -60);
                        swc1(f1, t0, -15152);
                        lwc1(f1, t1, -56);
                        swc1(f1, a3, -15148);
                        lwc1(f1, t1, -52);
                        swc1(f1, a2, -15144);
                        lqc2(vf10, t2, 0);
                        lwc1(f2, t3, 0);
                        lwc1(f1, sp, 0x100);
                        add_s(f1, f1, f2);
                        mfc1(t3, f1);
                        qmtc2(t3, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        sqc2(vf10, t2, 0);
                        lwc1(f1, a1, -15152);
                        swc1(f1, t1, 0);
                        lwc1(f1, a0, -15148);
                        swc1(f1, t1, 4);
                        lwc1(f1, v1, -15144);
                        swc1(f1, t1, 8);
                        swc1(f3, t4, 448);
                        v0 = addiu(v0, 1);
                    }
                    // 0x0033655c
                    charge(ctx, 2);
                    s5 = addiu(s5, 1);
                    s4 = addiu(s4, 60);
                }
                // 0x00336570
                charge(ctx, 9);
                lw(v0, s2, 16);
                lw(s4, v0, 24);
                a0 = s4;
                jal(ctx, 0x33657Cu, gen::fn_sub_4933D0_004933d0);
                lhu(v1, s2, 0);
                v1 = v1 & 0x4;
                if (v1 != 0) {
                    // 0x00336594
                    charge(ctx, 3);
                    lhu(v1, s4, 12);
                    v1 = v1 | 0x1;
                    sh(v1, s4, 12);
                }
            L_003365a0:
                charge(ctx, 3);
                lw(v1, s1, 20);
                v1 = addiu(v1, 1);
                sw(v1, s1, 20);
            }
            // 0x003365ac
            charge(ctx, 2);
            s0 = addiu(s0, 1);
            s1 = addiu(s1, 48);
        }
    }
    // 0x003365c0 (the shared epilogue, written out on this path)
    charge(ctx, 25);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f31, sp, 0x2C);
    lwc1(f30, sp, 0x28);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x004D9510 sub_4D9510 -- 12 bytes; leaf frame (no stack)
// A setter: *(u32*)$a0 = $a1, returns 1.
void sub_4D9510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004d9510
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, 0);
    v0 = 1;
}

// 0x004E96C0 sub_4E96C0 -- 248 bytes; leaf frame (no stack)
// Packs one RGBA byte quad ($a1) into a raster pixel ($a0) by the raster format bits ($a2 & 0xF00): 0x600 ->
// 0x80RRGGBB-style 24-bit with the top bit set, 0x500 -> 32-bit with alpha scaled by 0x808081, 0x000 / 0x100 -> 1555
// (5 bits per channel, alpha in bit 15); any other format returns 0, else 1.
void sub_4E96C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004e96c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a2 & 0xF00;
    v0 = 1536;
    if (v1 != v0) {
        // 0x004e96d0
        charge(ctx, 3);
        v0 = 1280;
        if (v1 == v0) {
            // 0x004e9738
            charge(ctx, 19);
            lbu(a3, a1, 2);
            v0 = lui(0xFF00);
            lbu(a2, a1, 1);
            lbu(v1, a1, 0);
            a3 = sll(a3, 16);
            a2 = sll(a2, 8);
            lbu(a1, a1, 3);
            a2 = a3 | a2;
            a2 = v1 | a2;
            v1 = sll(a1, 8);
            v1 = addu(v1, a1);
            v1 = sll(v1, 8);
            v1 = addu(v1, a1);
            v1 = sll(v1, 7);
            v1 = addu(v1, a1);
            v0 = v1 & v0;
            v0 = a2 | v0;
            sw(v0, a0, 0);
            goto L_004e97ac;
        }
        // 0x004e96dc
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x004e96e4
            charge(ctx, 3);
            v0 = 256;
            if (v1 == v0) {
                goto L_004e96f8;
            }
            // 0x004e96f0
            charge(ctx, 2);
            v0 = 0;
            // 0x004e97b0 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_004e96f8:
        charge(ctx, 16);
        lbu(v1, a1, 0);
        lbu(v0, a1, 3);
        lbu(a3, a1, 2);
        lbu(a2, a1, 1);
        v1 = srl(v1, 3);
        v0 = sll(v0, 8);
        v0 = v0 & 0x8000;
        a1 = sll(a3, 7);
        a3 = a1 & 0x7C00;
        a1 = sll(a2, 2);
        a1 = a1 & 0x3E0;
        a1 = a3 | a1;
        v1 = v1 | a1;
        v0 = v0 | v1;
        sw(v0, a0, 0);
        goto L_004e97ac;
    }
    // 0x004e9784
    charge(ctx, 10);
    lbu(v1, a1, 1);
    a2 = lui(0x8000);
    lbu(v0, a1, 2);
    lbu(a3, a1, 0);
    v1 = sll(v1, 8);
    v0 = sll(v0, 16);
    a1 = a3 | a2;
    v1 = a1 | v1;
    v0 = v0 | v1;
    sw(v0, a0, 0);
L_004e97ac:
    charge(ctx, 1);
    v0 = 1;
    // 0x004e97b0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004E97C0 sub_4E97C0 -- 220 bytes; leaf frame (no stack)
// The inverse of sub_4E96C0: unpacks a raster pixel (*$a1) into an RGBA byte quad at $a0 by the same format bits ($a2
// & 0xF00): 0x600 -> alpha 0xFF, 0x500 -> alpha / 0x808080, 0x000 / 0x100 -> 1555 expanded to 8 bits per channel; 0
// for any other format, else 1.
void sub_4E97C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004e97c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = a2 & 0xF00;
    v0 = 1536;
    lw(a3, a1, 0);
    if (v1 != v0) {
        // 0x004e97d0
        charge(ctx, 3);
        v0 = 1280;
        if (v1 == v0) {
            // 0x004e9830
            charge(ctx, 17);
            v0 = srl(a3, 16);
            v1 = srl(a3, 8);
            sb(v0, a0, 2);
            v0 = lui(0xFF00);
            sb(v1, a0, 1);
            a1 = a3 & v0;
            sb(a3, a0, 0);
            v0 = lui(0xFE00);
            v0 = v0 | 0x1FF;
            multu(zero, v0, a1);
            mfhi(v1);
            v0 = subu(a1, v1);
            v0 = srl(v0, 1);
            v0 = addu(v0, v1);
            v0 = srl(v0, 23);
            sb(v0, a0, 3);
            goto L_004e9890;
        }
        // 0x004e97dc
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x004e97e4
            charge(ctx, 3);
            v0 = 256;
            if (v1 == v0) {
                goto L_004e97f8;
            }
            // 0x004e97f0
            charge(ctx, 2);
            v0 = 0;
            // 0x004e9894 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_004e97f8:
        charge(ctx, 14);
        v1 = srl(a3, 7);
        v0 = srl(a3, 2);
        a1 = v1 & 0xF8;
        v1 = v0 & 0xF8;
        sb(a1, a0, 2);
        v0 = sll(a3, 3);
        sb(v1, a0, 1);
        v0 = v0 & 0xF8;
        v1 = a3 & 0x8000;
        sb(v0, a0, 0);
        v0 = 255;
        if (v1 == 0) v0 = 0;
        sb(v0, a0, 3);
        goto L_004e9890;
    }
    // 0x004e9874
    charge(ctx, 7);
    sb(a3, a0, 0);
    v0 = srl(a3, 8);
    sb(v0, a0, 1);
    v0 = srl(a3, 16);
    sb(v0, a0, 2);
    v0 = 255;
    sb(v0, a0, 3);
L_004e9890:
    charge(ctx, 1);
    v0 = 1;
    // 0x004e9894 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004E9AA0 sub_4E9AA0 -- 4444 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Converts an image into a raster (RwRaster in $a1) by the raster's format, depth and palette: locks the raster /
// palette (sub_4CDF30, sub_4CDE40), copies or repacks each row and palette entry per format (memcpy for matching
// layouts), then unlocks (sub_4CE200, sub_4CDE00). 1,109 instructions; the body is the instruction-faithful one.
void sub_4E9AA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004e9aa0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = 0;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, a1, 34);
    v0 = v0 & 0x2;
    s1 = 0;
    if (v0 != 0) {
        // 0x004e9ae8
        charge(ctx, 1);
        s1 = 1;
    }
    // 0x004e9aec
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004eab5c
        charge(ctx, 6);
        a0 = s5;
        a1 = 0;
        a2 = 2;
        jal(ctx, 0x4EAB64u, gen::fn_sub_4CE200_004ce200);
        if (v0 != 0) {
            backedge(ctx);
            goto L_004e9af4;
        }
        // 0x004eab74
        charge(ctx, 2);
        v0 = 0;
        // 0x004eabcc (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        sp = addiu(sp, 0xA0);
        return;
    }
L_004e9af4:
    charge(ctx, 4);
    lbu(v0, s5, 35);
    v0 = v0 & 0x60;
    if (v0 != 0) {
        // 0x004e9b04
        charge(ctx, 4);
        lbu(v0, s5, 34);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x004e9b14
            charge(ctx, 1);
            s6 = 1;
        }
        // 0x004e9b18
        charge(ctx, 2);
        if (s6 != 0) {
            goto L_004e9b3c;
        }
        // 0x004e9b20
        charge(ctx, 5);
        a0 = s5;
        a1 = 2;
        jal(ctx, 0x4E9B24u, gen::fn_sub_4CDF30_004cdf30);
        if (v0 != 0) {
            goto L_004e9b3c;
        }
        // 0x004e9b34
        charge(ctx, 2);
        v0 = 0;
        // 0x004eabcc (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        sp = addiu(sp, 0xA0);
        return;
    }
L_004e9b3c:
    charge(ctx, 6);
    lw(a0, s4, 12);
    a1 = 32;
    lw(s2, s4, 20);
    lw(v0, s4, 24);
    lw(s3, s5, 4);
    if (a0 == a1) {
        // 0x004ea650
        charge(ctx, 4);
        lw(v0, s5, 16);
        at = slt(0, v0);
        a2 = 0;
        if (at != 0) {
            // 0x004ea660
            charge(ctx, 11);
            v0 = lui(0xFE00);
            t3 = 0x7C0000;
            t5 = v0 | 0x1FF;
            t7 = 255;
            t6 = lui(0xFF00);
            t3 = addiu(t3, -12448);  // &0x7BCF60
            fp = 0x21;
            s7 = 37;
            v0 = 1;
            v1 = 6;
            a0 = 5;
            for (;;) {
                // 0x004ea68c
                charge(ctx, 4);
                lbu(t2, s5, 35);
                t1 = t2 & 0x6F;
                a3 = s2;
                if (t1 == a0) {
                    // 0x004eaa48
                    charge(ctx, 5);
                    lw(t0, s5, 12);
                    t2 = s3;
                    at = slt(0, t0);
                    t1 = 0;
                    if (at != 0) {
                        for (;;) {
                            // 0x004eaa5c
                            charge(ctx, 20);
                            lw(t0, t2, 0);
                            t4 = srl(t0, 16);
                            s0 = t0 & t6;
                            sb(t4, a3, 2);
                            t2 = addiu(t2, 4);
                            t4 = srl(t0, 8);
                            sb(t4, a3, 1);
                            sb(t0, a3, 0);
                            multu(zero, t5, s0);
                            mfhi(t4);
                            t1 = addiu(t1, 1);
                            t0 = subu(s0, t4);
                            t0 = srl(t0, 1);
                            t0 = addu(t0, t4);
                            t0 = srl(t0, 23);
                            sb(t0, a3, 3);
                            lw(t0, s5, 12);
                            t0 = slt(t1, t0);
                            a3 = addiu(a3, 4);
                            if (t0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004eaaac
                        charge(ctx, 1);
                    }
                L_004eaab0:
                    charge(ctx, 8);
                    lw(a3, s5, 16);
                    lw(t1, s4, 16);
                    a2 = addiu(a2, 1);
                    lw(t0, s5, 24);
                    a3 = slt(a2, a3);
                    s2 = addu(s2, t1);
                    s3 = addu(s3, t0);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                    continue;
                }
                // 0x004ea69c
                charge(ctx, 2);
                if (t1 == v1) {
                    // 0x004ea9e0
                    charge(ctx, 5);
                    lw(t2, s5, 12);
                    t1 = s3;
                    at = slt(0, t2);
                    t0 = 0;
                    if (at != 0) {
                        for (;;) {
                            // 0x004ea9f4
                            charge(ctx, 19);
                            lbu(s0, t1, 1);
                            t0 = addiu(t0, 1);
                            lbu(t2, t1, 2);
                            lbu(t4, t1, 0);
                            s0 = sll(s0, 8);
                            t2 = sll(t2, 16);
                            t4 = t4 | s0;
                            t1 = addiu(t1, 3);
                            t4 = t2 | t4;
                            sb(t4, a3, 0);
                            t2 = srl(t4, 8);
                            sb(t2, a3, 1);
                            t2 = srl(t4, 16);
                            sb(t2, a3, 2);
                            sb(t7, a3, 3);
                            lw(t2, s5, 12);
                            t2 = slt(t0, t2);
                            a3 = addiu(a3, 4);
                            if (t2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004eaa40
                        charge(ctx, 2);
                    }
                    goto L_004eaab0;
                }
                // 0x004ea6a4
                charge(ctx, 2);
                if (t1 != v0) {
                    // 0x004ea6ac
                    charge(ctx, 2);
                    if (t1 == 0) {
                        goto L_004ea974;
                    }
                    // 0x004ea6b4
                    charge(ctx, 2);
                    if (t1 == s7) {
                        // 0x004ea8dc
                        charge(ctx, 6);
                        lw(t0, s5, 12);
                        t4 = s3;
                        lw(t1, s5, 8);
                        at = slt(0, t0);
                        t2 = 0;
                        if (at != 0) {
                            for (;;) {
                                // 0x004ea8f4
                                charge(ctx, 30);
                                lbu(s0, t4, 0);
                                t0 = srl(s0, 3);
                                t4 = addiu(t4, 1);
                                t0 = t0 & 0x3;
                                s0 = s0 & 0xE7;
                                t0 = sll(t0, 2);
                                t0 = addu(t3, t0);
                                lw(t0, t0, 0);
                                t0 = s0 | t0;
                                t0 = sll(t0, 2);
                                t0 = addu(t1, t0);
                                lw(t0, t0, 0);
                                s0 = srl(t0, 16);
                                t8 = srl(t0, 8);
                                sb(s0, a3, 2);
                                sb(t8, a3, 1);
                                s0 = t0 & t6;
                                sb(t0, a3, 0);
                                multu(zero, t5, s0);
                                mfhi(t0);
                                t2 = addiu(t2, 1);
                                s0 = subu(s0, t0);
                                s0 = srl(s0, 1);
                                t0 = addu(s0, t0);
                                t0 = srl(t0, 23);
                                sb(t0, a3, 3);
                                lw(t0, s5, 12);
                                t0 = slt(t2, t0);
                                a3 = addiu(a3, 4);
                                if (t0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004ea96c
                            charge(ctx, 2);
                        }
                        goto L_004eaab0;
                    }
                    // 0x004ea6bc
                    charge(ctx, 2);
                    if (t1 != fp) {
                        // 0x004ea6c4
                        charge(ctx, 2);
                        if (t1 == a1) {
                            goto L_004ea844;
                        }
                        // 0x004ea6cc
                        charge(ctx, 3);
                        t0 = 69;
                        if (t1 == t0) {
                            // 0x004ea7a0
                            charge(ctx, 6);
                            lw(t0, s5, 12);
                            t4 = s3;
                            lw(t1, s5, 8);
                            at = slt(0, t0);
                            t2 = 0;
                            if (at != 0) {
                                for (;;) {
                                    // 0x004ea7b8
                                    charge(ctx, 5);
                                    lh(t0, s5, 28);
                                    t0 = addu(t2, t0);
                                    t0 = t0 & 0x1;
                                    if (t0 == 0) {
                                        // 0x004ea7e0
                                        charge(ctx, 2);
                                        lbu(t0, t4, 0);
                                        t0 = t0 & 0xF;
                                    } else {
                                        // 0x004ea7cc
                                        charge(ctx, 5);
                                        lbu(t0, t4, 0);
                                        t0 = sra(t0, 4);
                                        t4 = addiu(t4, 1);
                                        t0 = t0 & 0xF;
                                    }
                                    // 0x004ea7e8
                                    charge(ctx, 21);
                                    t0 = sll(t0, 2);
                                    t0 = addu(t1, t0);
                                    lw(t0, t0, 0);
                                    s0 = srl(t0, 16);
                                    t8 = srl(t0, 8);
                                    sb(s0, a3, 2);
                                    sb(t8, a3, 1);
                                    s0 = t0 & t6;
                                    sb(t0, a3, 0);
                                    multu(zero, t5, s0);
                                    mfhi(t0);
                                    t2 = addiu(t2, 1);
                                    s0 = subu(s0, t0);
                                    s0 = srl(s0, 1);
                                    t0 = addu(s0, t0);
                                    t0 = srl(t0, 23);
                                    sb(t0, a3, 3);
                                    lw(t0, s5, 12);
                                    t0 = slt(t2, t0);
                                    a3 = addiu(a3, 4);
                                    if (t0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004ea83c
                                charge(ctx, 2);
                            }
                            goto L_004eaab0;
                        }
                        // 0x004ea6d8
                        charge(ctx, 3);
                        t0 = 65;
                        if (t1 != t0) {
                            // 0x004ea6e4
                            charge(ctx, 3);
                            t0 = 64;
                            if (t1 == t0) {
                                goto L_004ea6f8;
                            }
                            goto L_004ea6f0_86;
                        }
                    L_004ea6f8:
                        charge(ctx, 6);
                        lw(t0, s5, 12);
                        t8 = s3;
                        lw(t4, s5, 8);
                        at = slt(0, t0);
                        s0 = 0;
                        if (at != 0) {
                            for (;;) {
                                // 0x004ea710
                                charge(ctx, 5);
                                lh(t0, s5, 28);
                                t0 = addu(s0, t0);
                                t0 = t0 & 0x1;
                                if (t0 == 0) {
                                    // 0x004ea738
                                    charge(ctx, 2);
                                    lbu(t0, t8, 0);
                                    t0 = t0 & 0xF;
                                } else {
                                    // 0x004ea724
                                    charge(ctx, 5);
                                    lbu(t0, t8, 0);
                                    t0 = sra(t0, 4);
                                    t8 = addiu(t8, 1);
                                    t0 = t0 & 0xF;
                                }
                                // 0x004ea740
                                charge(ctx, 22);
                                t0 = t0 & 0xFFFF;
                                t9 = t7;
                                t0 = sll(t0, 1);
                                s0 = addiu(s0, 1);
                                t0 = addu(t4, t0);
                                lhu(t2, t0, 0);
                                t1 = sra(t2, 7);
                                t0 = sra(t2, 2);
                                t1 = t1 & 0xF8;
                                t0 = t0 & 0xF8;
                                sb(t1, a3, 2);
                                t1 = sll(t2, 3);
                                sb(t0, a3, 1);
                                t0 = t1 & 0xF8;
                                sb(t0, a3, 0);
                                t0 = t2 & 0x8000;
                                if (t0 == 0) t9 = 0;
                                sb(t9, a3, 3);
                                lw(t0, s5, 12);
                                t0 = slt(s0, t0);
                                a3 = addiu(a3, 4);
                                if (t0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004ea798
                            charge(ctx, 2);
                        }
                        goto L_004eaab0;
                    }
                L_004ea844:
                    charge(ctx, 6);
                    lw(t0, s5, 12);
                    t8 = s3;
                    lw(t4, s5, 8);
                    at = slt(0, t0);
                    s0 = 0;
                    if (at != 0) {
                        for (;;) {
                            // 0x004ea85c
                            charge(ctx, 30);
                            lbu(t0, t8, 0);
                            t9 = t7;
                            s0 = addiu(s0, 1);
                            t1 = sra(t0, 3);
                            t8 = addiu(t8, 1);
                            t1 = t1 & 0x3;
                            t0 = t0 & 0xE7;
                            t1 = sll(t1, 2);
                            t1 = addu(t3, t1);
                            lw(t1, t1, 0);
                            t0 = t0 | t1;
                            t0 = sll(t0, 1);
                            t0 = addu(t4, t0);
                            lhu(t2, t0, 0);
                            t1 = sra(t2, 7);
                            t0 = sra(t2, 2);
                            t1 = t1 & 0xF8;
                            t0 = t0 & 0xF8;
                            sb(t1, a3, 2);
                            t1 = sll(t2, 3);
                            sb(t0, a3, 1);
                            t0 = t1 & 0xF8;
                            sb(t0, a3, 0);
                            t0 = t2 & 0x8000;
                            if (t0 == 0) t9 = 0;
                            sb(t9, a3, 3);
                            lw(t0, s5, 12);
                            t0 = slt(s0, t0);
                            a3 = addiu(a3, 4);
                            if (t0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ea8d4
                        charge(ctx, 2);
                    }
                    goto L_004eaab0;
                }
            L_004ea974:
                charge(ctx, 5);
                lw(t0, s5, 12);
                t8 = s3;
                at = slt(0, t0);
                s0 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004ea988
                        charge(ctx, 20);
                        lhu(t4, t8, 0);
                        t0 = t7;
                        s0 = addiu(s0, 1);
                        t1 = sra(t4, 7);
                        t8 = addiu(t8, 2);
                        t2 = t1 & 0xF8;
                        t1 = sra(t4, 2);
                        sb(t2, a3, 2);
                        t1 = t1 & 0xF8;
                        t2 = t4 & 0x8000;
                        sb(t1, a3, 1);
                        if (t2 == 0) t0 = 0;
                        t1 = sll(t4, 3);
                        t1 = t1 & 0xF8;
                        sb(t1, a3, 0);
                        sb(t0, a3, 3);
                        lw(t0, s5, 12);
                        t0 = slt(s0, t0);
                        a3 = addiu(a3, 4);
                        if (t0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ea9d8
                    charge(ctx, 2);
                }
                goto L_004eaab0;
            }
            // 0x004eaad0
            charge(ctx, 2);
            goto L_004eab2c;
        }
    L_004eab2c:
        charge(ctx, 1);
        lbu(v0, s5, 35);
    L_004eab30:
        charge(ctx, 3);
        v0 = v0 & 0x60;
        if (v0 != 0) {
            // 0x004eab3c
            charge(ctx, 2);
            if (s6 == 0) {
                // 0x004eab44
                charge(ctx, 2);
                a0 = s5;
                jal(ctx, 0x4EAB44u, gen::fn_sub_4CDE40_004cde40);
            }
        }
        // 0x004eab4c
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x004eabbc
            charge(ctx, 4);
            a0 = s5;
            jal(ctx, 0x4EABBCu, gen::fn_sub_4CDE00_004cde00);
            backedge(ctx);
        }
        // 0x004eab54
        charge(ctx, 2);
        v0 = 1;
    } else {
        // 0x004e9b54
        charge(ctx, 3);
        v1 = 8;
        if (a0 == v1) {
            // 0x004e9ed0
            charge(ctx, 4);
            lbu(a2, s5, 35);
            a0 = a2 & 0x60;
            if (a0 == a1) {
                // 0x004ea208
                charge(ctx, 4);
                a0 = a2 & 0xF;
                v1 = 5;
                if (a0 == v1) {
                    // 0x004ea2b4
                    charge(ctx, 8);
                    lw(a2, s5, 8);
                    a1 = 0x7C0000;
                    v1 = lui(0xFE00);
                    a3 = 0;
                    t0 = 0;
                    a1 = addiu(a1, -12448);  // &0x7BCF60
                    a0 = lui(0xFF00);
                    v1 = v1 | 0x1FF;
                    for (;;) {
                        // 0x004ea2d4
                        charge(ctx, 195);
                        t1 = t0 & 0x3;
                        t2 = a3 & 0xE7;
                        t1 = sll(t1, 2);
                        t1 = addu(a1, t1);
                        lw(t1, t1, 0);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 2);
                        t3 = t4 & a0;
                        sb(t1, v0, 1);
                        sb(t4, v0, 0);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 1);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 3);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 6);
                        t3 = t4 & a0;
                        sb(t1, v0, 5);
                        sb(t4, v0, 4);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 2);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 7);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 10);
                        t3 = t4 & a0;
                        sb(t1, v0, 9);
                        sb(t4, v0, 8);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 3);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 11);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 14);
                        t3 = t4 & a0;
                        sb(t1, v0, 13);
                        sb(t4, v0, 12);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 4);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 15);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 18);
                        t3 = t4 & a0;
                        sb(t1, v0, 17);
                        sb(t4, v0, 16);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 5);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 19);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 22);
                        t3 = t4 & a0;
                        sb(t1, v0, 21);
                        sb(t4, v0, 20);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 6);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 23);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t4, t1, 0);
                        t2 = srl(t4, 16);
                        t1 = srl(t4, 8);
                        sb(t2, v0, 26);
                        t3 = t4 & a0;
                        sb(t1, v0, 25);
                        sb(t4, v0, 24);
                        multu(zero, v1, t3);
                        mfhi(t4);
                        t2 = addiu(a3, 7);
                        t1 = sra(t2, 3);
                        t1 = t1 & 0x3;
                        t2 = t2 & 0xE7;
                        t1 = sll(t1, 2);
                        t3 = subu(t3, t4);
                        t1 = addu(a1, t1);
                        t3 = srl(t3, 1);
                        lw(t1, t1, 0);
                        t3 = addu(t3, t4);
                        t3 = srl(t3, 23);
                        sb(t3, v0, 27);
                        t1 = t2 | t1;
                        t1 = sll(t1, 2);
                        t1 = addu(a2, t1);
                        lw(t3, t1, 0);
                        t2 = srl(t3, 16);
                        t1 = srl(t3, 8);
                        sb(t2, v0, 30);
                        sb(t1, v0, 29);
                        t2 = t3 & a0;
                        sb(t3, v0, 28);
                        multu(zero, v1, t2);
                        mfhi(t3);
                        a3 = addiu(a3, 8);
                        t1 = slti(a3, 256);
                        t0 = addiu(t0, 1);
                        t2 = subu(t2, t3);
                        t2 = srl(t2, 1);
                        t2 = addu(t2, t3);
                        t2 = srl(t2, 23);
                        sb(t2, v0, 31);
                        v0 = addiu(v0, 32);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    // 0x004ea218
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x004ea22c
                        charge(ctx, 5);
                        lw(a0, s5, 8);
                        v1 = 0x7C0000;
                        a1 = 0;
                        v1 = addiu(v1, -12448);  // &0x7BCF60
                        t0 = 255;
                        for (;;) {
                            // 0x004ea240
                            charge(ctx, 27);
                            a2 = sra(a1, 3);
                            t2 = a1 & 0xE7;
                            a2 = a2 & 0x3;
                            a3 = t0;
                            a2 = sll(a2, 2);
                            a1 = addiu(a1, 1);
                            t1 = addu(v1, a2);
                            lw(t1, t1, 0);
                            a2 = slti(a1, 256);
                            t1 = t2 | t1;
                            t1 = sll(t1, 1);
                            t1 = addu(a0, t1);
                            lhu(t4, t1, 0);
                            t2 = sra(t4, 7);
                            t1 = sra(t4, 2);
                            t3 = t2 & 0xF8;
                            t2 = t1 & 0xF8;
                            sb(t3, v0, 2);
                            t1 = sll(t4, 3);
                            sb(t2, v0, 1);
                            t1 = t1 & 0xF8;
                            sb(t1, v0, 0);
                            t1 = t4 & 0x8000;
                            if (t1 == 0) a3 = 0;
                            sb(a3, v0, 3);
                            v0 = addiu(v0, 4);
                            if (a2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ea2ac
                        charge(ctx, 2);
                    } else {
                        // 0x004ea224
                        charge(ctx, 2);
                    }
                }
                // 0x004ea5e0
                charge(ctx, 4);
                lw(v0, s5, 16);
                at = slt(0, v0);
                s0 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004ea5f0
                        charge(ctx, 12);
                        lw(a2, s5, 12);
                        a0 = s2;
                        a1 = s3;
                        jal(ctx, 0x4EA5F8u, gen::fn_memcpy_00521250);
                        lw(v0, s5, 16);
                        s0 = addiu(s0, 1);
                        lw(a0, s4, 16);
                        lw(v1, s5, 24);
                        v0 = slt(s0, v0);
                        s2 = addu(s2, a0);
                        s3 = addu(s3, v1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ea620
                    charge(ctx, 2);
                }
                goto L_004eab2c;
            }
            // 0x004e9ee0
            charge(ctx, 3);
            v1 = 64;
            if (a0 == v1) {
                // 0x004e9ef4
                charge(ctx, 4);
                a0 = a2 & 0xF;
                v1 = 5;
                if (a0 == v1) {
                    // 0x004e9f78
                    charge(ctx, 5);
                    lw(a2, s5, 8);
                    v1 = lui(0xFE00);
                    a1 = 0;
                    a0 = lui(0xFF00);
                    v1 = v1 | 0x1FF;
                    for (;;) {
                        // 0x004e9f8c
                        charge(ctx, 117);
                        lw(t1, a2, 0);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 2);
                        sb(t0, v0, 1);
                        a3 = t1 & a0;
                        sb(t1, v0, 0);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 3);
                        lw(t1, a2, 4);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 6);
                        sb(t0, v0, 5);
                        a3 = t1 & a0;
                        sb(t1, v0, 4);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 7);
                        lw(t1, a2, 8);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 10);
                        sb(t0, v0, 9);
                        a3 = t1 & a0;
                        sb(t1, v0, 8);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 11);
                        lw(t1, a2, 12);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 14);
                        sb(t0, v0, 13);
                        a3 = t1 & a0;
                        sb(t1, v0, 12);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 15);
                        lw(t1, a2, 16);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 18);
                        sb(t0, v0, 17);
                        a3 = t1 & a0;
                        sb(t1, v0, 16);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 19);
                        lw(t1, a2, 20);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 22);
                        sb(t0, v0, 21);
                        a3 = t1 & a0;
                        sb(t1, v0, 20);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 23);
                        lw(t1, a2, 24);
                        a3 = srl(t1, 16);
                        t0 = srl(t1, 8);
                        sb(a3, v0, 26);
                        sb(t0, v0, 25);
                        a3 = t1 & a0;
                        sb(t1, v0, 24);
                        multu(zero, v1, a3);
                        mfhi(t0);
                        a3 = subu(a3, t0);
                        a3 = srl(a3, 1);
                        a3 = addu(a3, t0);
                        a3 = srl(a3, 23);
                        sb(a3, v0, 27);
                        lw(t1, a2, 28);
                        t0 = srl(t1, 16);
                        a3 = srl(t1, 8);
                        sb(t0, v0, 30);
                        sb(a3, v0, 29);
                        t0 = t1 & a0;
                        sb(t1, v0, 28);
                        multu(zero, v1, t0);
                        mfhi(t1);
                        a1 = addiu(a1, 8);
                        a3 = slti(a1, 16);
                        a2 = addiu(a2, 32);
                        t0 = subu(t0, t1);
                        t0 = srl(t0, 1);
                        t0 = addu(t0, t1);
                        t0 = srl(t0, 23);
                        sb(t0, v0, 31);
                        v0 = addiu(v0, 32);
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    // 0x004e9f04
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x004e9f18
                        charge(ctx, 3);
                        lw(t3, s5, 8);
                        t2 = 0;
                        a1 = 255;
                        for (;;) {
                            // 0x004e9f24
                            charge(ctx, 19);
                            lhu(t1, t3, 0);
                            t2 = addiu(t2, 1);
                            a0 = a1;
                            v1 = slti(t2, 16);
                            a3 = sra(t1, 7);
                            a2 = sra(t1, 2);
                            t0 = a3 & 0xF8;
                            t3 = addiu(t3, 2);
                            a3 = a2 & 0xF8;
                            sb(t0, v0, 2);
                            a2 = sll(t1, 3);
                            sb(a3, v0, 1);
                            a2 = a2 & 0xF8;
                            sb(a2, v0, 0);
                            a2 = t1 & 0x8000;
                            if (a2 == 0) a0 = 0;
                            sb(a0, v0, 3);
                            v0 = addiu(v0, 4);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004e9f70
                        charge(ctx, 2);
                    } else {
                        // 0x004e9f10
                        charge(ctx, 2);
                    }
                }
                // 0x004ea160
                charge(ctx, 4);
                lw(v0, s5, 16);
                at = slt(0, v0);
                a1 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004ea170
                        charge(ctx, 6);
                        lw(v0, s5, 12);
                        a2 = s3;
                        a0 = s2;
                        at = slt(0, v0);
                        v1 = 0;
                        if (at != 0) {
                            for (;;) {
                                // 0x004ea188
                                charge(ctx, 5);
                                lh(v0, s5, 28);
                                v0 = addu(v1, v0);
                                v0 = v0 & 0x1;
                                if (v0 == 0) {
                                    // 0x004ea1b8
                                    charge(ctx, 4);
                                    lbu(v0, a2, 0);
                                    v0 = v0 & 0xF;
                                    sb(v0, a0, 0);
                                } else {
                                    // 0x004ea19c
                                    charge(ctx, 6);
                                    lbu(v0, a2, 0);
                                    v0 = sra(v0, 4);
                                    a2 = addiu(a2, 1);
                                    v0 = v0 & 0xF;
                                    sb(v0, a0, 0);
                                }
                                // 0x004ea1c8
                                charge(ctx, 5);
                                lw(v0, s5, 12);
                                v1 = addiu(v1, 1);
                                v0 = slt(v1, v0);
                                a0 = addiu(a0, 1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004ea1dc
                            charge(ctx, 1);
                        }
                        // 0x004ea1e0
                        charge(ctx, 8);
                        lw(v0, s5, 16);
                        lw(a0, s4, 16);
                        a1 = addiu(a1, 1);
                        lw(v1, s5, 24);
                        v0 = slt(a1, v0);
                        s2 = addu(s2, a0);
                        s3 = addu(s3, v1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ea200
                    charge(ctx, 2);
                }
                goto L_004eab2c;
            }
            // 0x004e9eec
            charge(ctx, 2);
            // 0x004ea628
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x004ea630
                charge(ctx, 2);
                if (s6 == 0) {
                    // 0x004ea638
                    charge(ctx, 2);
                    a0 = s5;
                    jal(ctx, 0x4EA638u, gen::fn_sub_4CDE40_004cde40);
                }
            }
            // 0x004ea640
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x004eab8c
                charge(ctx, 4);
                a0 = s5;
                jal(ctx, 0x4EAB8Cu, gen::fn_sub_4CDE00_004cde00);
                backedge(ctx);
            }
            // 0x004ea648
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004e9b60
            charge(ctx, 3);
            v1 = 4;
            if (a0 == v1) {
                // 0x004e9b74
                charge(ctx, 5);
                lbu(a1, s5, 35);
                v1 = 64;
                a0 = a1 & 0x40;
                if (a0 == v1) {
                    // 0x004e9b90
                    charge(ctx, 4);
                    a0 = a1 & 0xF;
                    v1 = 5;
                    if (a0 == v1) {
                        // 0x004e9c14
                        charge(ctx, 5);
                        lw(a2, s5, 8);
                        v1 = lui(0xFE00);
                        a1 = 0;
                        a0 = lui(0xFF00);
                        v1 = v1 | 0x1FF;
                        for (;;) {
                            // 0x004e9c28
                            charge(ctx, 117);
                            lw(t1, a2, 0);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 2);
                            sb(t0, v0, 1);
                            a3 = t1 & a0;
                            sb(t1, v0, 0);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 3);
                            lw(t1, a2, 4);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 6);
                            sb(t0, v0, 5);
                            a3 = t1 & a0;
                            sb(t1, v0, 4);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 7);
                            lw(t1, a2, 8);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 10);
                            sb(t0, v0, 9);
                            a3 = t1 & a0;
                            sb(t1, v0, 8);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 11);
                            lw(t1, a2, 12);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 14);
                            sb(t0, v0, 13);
                            a3 = t1 & a0;
                            sb(t1, v0, 12);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 15);
                            lw(t1, a2, 16);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 18);
                            sb(t0, v0, 17);
                            a3 = t1 & a0;
                            sb(t1, v0, 16);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 19);
                            lw(t1, a2, 20);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 22);
                            sb(t0, v0, 21);
                            a3 = t1 & a0;
                            sb(t1, v0, 20);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 23);
                            lw(t1, a2, 24);
                            a3 = srl(t1, 16);
                            t0 = srl(t1, 8);
                            sb(a3, v0, 26);
                            sb(t0, v0, 25);
                            a3 = t1 & a0;
                            sb(t1, v0, 24);
                            multu(zero, v1, a3);
                            mfhi(t0);
                            a3 = subu(a3, t0);
                            a3 = srl(a3, 1);
                            a3 = addu(a3, t0);
                            a3 = srl(a3, 23);
                            sb(a3, v0, 27);
                            lw(t1, a2, 28);
                            t0 = srl(t1, 16);
                            a3 = srl(t1, 8);
                            sb(t0, v0, 30);
                            sb(a3, v0, 29);
                            t0 = t1 & a0;
                            sb(t1, v0, 28);
                            multu(zero, v1, t0);
                            mfhi(t1);
                            a1 = addiu(a1, 8);
                            a3 = slti(a1, 16);
                            a2 = addiu(a2, 32);
                            t0 = subu(t0, t1);
                            t0 = srl(t0, 1);
                            t0 = addu(t0, t1);
                            t0 = srl(t0, 23);
                            sb(t0, v0, 31);
                            v0 = addiu(v0, 32);
                            if (a3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004e9dfc
                        charge(ctx, 1);
                    } else {
                        // 0x004e9ba0
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x004e9bb4
                            charge(ctx, 3);
                            lw(t2, s5, 8);
                            t3 = 0;
                            a1 = 255;
                            for (;;) {
                                // 0x004e9bc0
                                charge(ctx, 19);
                                lhu(t1, t2, 0);
                                t3 = addiu(t3, 1);
                                a0 = a1;
                                v1 = slti(t3, 16);
                                a3 = sra(t1, 7);
                                a2 = sra(t1, 2);
                                t0 = a3 & 0xF8;
                                t2 = addiu(t2, 2);
                                a3 = a2 & 0xF8;
                                sb(t0, v0, 2);
                                a2 = sll(t1, 3);
                                sb(a3, v0, 1);
                                a2 = a2 & 0xF8;
                                sb(a2, v0, 0);
                                a2 = t1 & 0x8000;
                                if (a2 == 0) a0 = 0;
                                sb(a0, v0, 3);
                                v0 = addiu(v0, 4);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e9c0c
                            charge(ctx, 2);
                        } else {
                            // 0x004e9bac
                            charge(ctx, 2);
                        }
                    }
                    // 0x004e9e00
                    charge(ctx, 4);
                    lw(v1, s5, 16);
                    at = slt(0, v1);
                    v0 = 0;
                    if (at == 0) {
                        goto L_004eab2c;
                    }
                    for (;;) {
                        // 0x004e9e10
                        charge(ctx, 6);
                        lw(v1, s5, 12);
                        a2 = s3;
                        a1 = s2;
                        at = slt(0, v1);
                        a0 = 0;
                        if (at != 0) {
                            for (;;) {
                                // 0x004e9e28
                                charge(ctx, 5);
                                lh(v1, s5, 28);
                                v1 = addu(a0, v1);
                                v1 = v1 & 0x1;
                                if (v1 == 0) {
                                    // 0x004e9e58
                                    charge(ctx, 4);
                                    lbu(v1, a2, 0);
                                    v1 = v1 & 0xF;
                                    sb(v1, a1, 0);
                                } else {
                                    // 0x004e9e3c
                                    charge(ctx, 6);
                                    lbu(v1, a2, 0);
                                    v1 = sra(v1, 4);
                                    a2 = addiu(a2, 1);
                                    v1 = v1 & 0xF;
                                    sb(v1, a1, 0);
                                }
                                // 0x004e9e68
                                charge(ctx, 5);
                                lw(v1, s5, 12);
                                a0 = addiu(a0, 1);
                                v1 = slt(a0, v1);
                                a1 = addiu(a1, 1);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004e9e7c
                            charge(ctx, 1);
                        }
                        // 0x004e9e80
                        charge(ctx, 8);
                        lw(v1, s5, 16);
                        lw(a1, s4, 16);
                        v0 = addiu(v0, 1);
                        lw(a0, s5, 24);
                        v1 = slt(v0, v1);
                        s2 = addu(s2, a1);
                        s3 = addu(s3, a0);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004e9ea0
                    charge(ctx, 2);
                    lbu(v0, s5, 35);
                    goto L_004eab30;
                }
                // 0x004e9b88
                charge(ctx, 2);
                v0 = a1 & 0x60;
                // 0x004e9ea8
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004e9eb0
                    charge(ctx, 2);
                    if (s6 == 0) {
                        // 0x004e9eb8
                        charge(ctx, 2);
                        a0 = s5;
                        jal(ctx, 0x4E9EB8u, gen::fn_sub_4CDE40_004cde40);
                    }
                }
                // 0x004e9ec0
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x004eab7c
                    charge(ctx, 4);
                    a0 = s5;
                    jal(ctx, 0x4EAB7Cu, gen::fn_sub_4CDE00_004cde00);
                    backedge(ctx);
                }
                // 0x004e9ec8
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004e9b6c
                charge(ctx, 2);
                lbu(v0, s5, 35);
                // 0x004eab00
                charge(ctx, 3);
                v0 = v0 & 0x60;
                if (v0 != 0) {
                    // 0x004eab0c
                    charge(ctx, 2);
                    if (s6 == 0) {
                        // 0x004eab14
                        charge(ctx, 2);
                        a0 = s5;
                        jal(ctx, 0x4EAB14u, gen::fn_sub_4CDE40_004cde40);
                    }
                }
                // 0x004eab1c
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x004eabac
                    charge(ctx, 4);
                    a0 = s5;
                    jal(ctx, 0x4EABACu, gen::fn_sub_4CDE00_004cde00);
                    backedge(ctx);
                }
                // 0x004eab24
                charge(ctx, 2);
                v0 = 0;
            }
        }
    }
    // 0x004eabcc (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xA0);
    return;
L_004ea6f0_86:
    charge(ctx, 2);
    v0 = t2 & 0x60;
    // 0x004eaad8
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004eaae0
        charge(ctx, 2);
        if (s6 == 0) {
            // 0x004eaae8
            charge(ctx, 2);
            a0 = s5;
            jal(ctx, 0x4EAAE8u, gen::fn_sub_4CDE40_004cde40);
        }
    }
    // 0x004eaaf0
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004eab9c
        charge(ctx, 4);
        a0 = s5;
        jal(ctx, 0x4EAB9Cu, gen::fn_sub_4CDE00_004cde00);
        backedge(ctx);
    }
    // 0x004eaaf8
    charge(ctx, 2);
    v0 = 0;
    // 0x004eabcc (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xA0);
}

// 0x004FF5B0 _unknown_extension -- 12 bytes; leaf frame (no stack)
// libmpeg: reports an unknown MPEG extension: _sceMpegError(mpeg, "Unknown Extension") (tail call).
void _unknown_extension(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5};
    // 0x004ff5b0
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    a1 = addiu(a1, -10400);  // "Unknown Extension"
    gen::fn__sceMpegError_00502668(ctx);  // tail call
}

// 0x004FF5C0 _pictureCodingExtension -- 484 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libmpeg: parses the MPEG-2 picture coding extension from the bit stream (_sceMpegNextBit): the four f_codes
// (+372..+384), intra_dc_precision into IPU_CTRL (0x10002010) bits 16-17, picture_structure (+388; also +232 when
// that is 0), top_field_first / frame_pred_frame_dct / concealment_motion_vectors (+392..+400), q_scale_type /
// intra_vlc_format / alternate_scan into IPU_CTRL bits 22 / 21 / 20, repeat_first_field (+404), chroma_420_type
// skipped, progressive_frame (+408), and the composite-display fields when composite_display_flag is set.
void _pictureCodingExtension(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ff5c0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 4;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4FF5D0u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 372);
    a0 = s0;
    a1 = 4;
    jal(ctx, 0x4FF5E0u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 376);
    a0 = s0;
    a1 = 4;
    jal(ctx, 0x4FF5F0u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 380);
    a0 = s0;
    a1 = 4;
    jal(ctx, 0x4FF600u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 384);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x4FF610u, gen::fn__sceMpegNextBit_004fd658);
    a3 = 0x10000000;
    a2 = lui(0xFFFC);
    a3 = a3 | 0x2010;
    a2 = a2 | 0xFFFF;
    lw(v1, a3, 0);  // 0x10002010
    v0 = sll(v0, 16);
    a0 = s0;
    a1 = 2;
    v1 = v1 & a2;
    v1 = v1 | v0;
    link(ctx, 0x4FF640u);  // $ra first: the delay slot below depends on it
    sw(v1, a3, 0);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    v1 = v0;
    lw(v0, s0, 232);
    sw(v1, s0, 388);
    if (v0 == 0) {
        // 0x004ff658
        charge(ctx, 1);
        sw(v1, s0, 232);
    }
    // 0x004ff65c
    charge(ctx, 64);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF660u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 392);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF670u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 396);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF680u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 400);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF690u, gen::fn__sceMpegNextBit_004fd658);
    a2 = 0x10000000;
    lw(a2, a2, 8208);  // 0x10002010
    v1 = lui(0xFFBF);
    v1 = v1 | 0xFFFF;
    v0 = sll(v0, 22);
    a2 = a2 & v1;
    a0 = s0;
    a2 = a2 | v0;
    a1 = 1;
    at = 0x10000000;
    link(ctx, 0x4FF6C0u);  // $ra first: the delay slot below depends on it
    sw(a2, at, 8208);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    a2 = 0x10000000;
    lw(a2, a2, 8208);  // 0x10002010
    v1 = lui(0xFFDF);
    v1 = v1 | 0xFFFF;
    v0 = sll(v0, 21);
    a2 = a2 & v1;
    a0 = s0;
    a2 = a2 | v0;
    a1 = 1;
    at = 0x10000000;
    link(ctx, 0x4FF6F0u);  // $ra first: the delay slot below depends on it
    sw(a2, at, 8208);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    a2 = 0x10000000;
    lw(a2, a2, 8208);  // 0x10002010
    v1 = lui(0xFFEF);
    v1 = v1 | 0xFFFF;
    v0 = sll(v0, 20);
    a2 = a2 & v1;
    a0 = s0;
    a2 = a2 | v0;
    a1 = 1;
    at = 0x10000000;
    link(ctx, 0x4FF720u);  // $ra first: the delay slot below depends on it
    sw(a2, at, 8208);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 404);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF730u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF73Cu, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, 408);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF74Cu, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    if (v0 != 0) {
        // 0x004ff75c
        charge(ctx, 14);
        a1 = 1;
        jal(ctx, 0x4FF75Cu, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        a1 = 3;
        jal(ctx, 0x4FF768u, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x4FF774u, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        a1 = 7;
        jal(ctx, 0x4FF780u, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        a1 = 8;
        jal(ctx, 0x4FF78Cu, gen::fn__sceMpegNextBit_004fd658);
    }
    // 0x004ff794 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00542DC0 sub_542DC0 -- 316 bytes; frame 0x40: s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s0 sp+0x10, s4 sp+0x30, ra sp+0x38
// Consumes data from a multi-channel source ($a0: +2 the channel count, +12 the channel stream-joint pointers, +164
// the pending count): asks every channel for its available amount (vtable +24 / +28), takes the minimum (doubled),
// and when it is positive puts back half of it per channel (vtable +24 / +32) and subtracts it from +164.
void sub_542DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00542dc0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s3, sp, 0x28);
    s3 = 0;
    sd(s0, sp, 0x10);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(v0, s2, 164);
    lb(v1, s2, 2);
    s1 = sll(v0, 1);
    lbu(a0, s2, 2);
    if (i64(v1) > 0) {
        // 0x00542df8
        charge(ctx, 2);
        s0 = addiu(s2, 12);
        for (;;) {
            // 0x00542e00
            charge(ctx, 23);
            lw(a0, s0, 0);
            a2 = 0x7FFF0000;
            a3 = sp;
            a1 = 1;
            lw(v1, a0, 0);
            a2 = a2 | 0xFFFF;
            lw(v0, v1, 24);
            s3 = addiu(s3, 1);
            jalr(ctx, 0x542E1Cu, v0.u());
            lw(a0, s0, 0);
            lw(t0, sp, 0x4);
            a1 = 1;
            lw(a3, a0, 0);
            a2 = sp;
            v0 = slt(s1, t0);
            s0 = addiu(s0, 4);
            lw(v1, a3, 28);
            if (v0 == 0) s1 = t0;
            jalr(ctx, 0x542E44u, v1.u());
            lb(v0, s2, 2);
            v0 = slt(s3, v0);
            lbu(a0, s2, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00542e5c
    charge(ctx, 6);
    v0 = srl(s1, 31);
    v0 = addu(s1, v0);
    s4 = sra(v0, 1);
    s1 = sll(s4, 1);
    ld(s0, sp, 0x10);
    if (i64(s1) > 0) {
        // 0x00542e74
        charge(ctx, 3);
        v0 = sll(a0, 24);
        s3 = 0;
        if (i64(v0) > 0) {
            // 0x00542e80
            charge(ctx, 2);
            s0 = addiu(s2, 12);
            lw(a0, s0, 0);
            for (;;) {
                // 0x00542e88
                charge(ctx, 18);
                a1 = 1;
                a2 = s1;
                a3 = sp;
                lw(v1, a0, 0);
                lw(v0, v1, 24);
                s3 = addiu(s3, 1);
                jalr(ctx, 0x542E9Cu, v0.u());
                lw(a0, s0, 0);
                a1 = 0;
                a2 = sp;
                lw(v0, a0, 0);
                lw(v1, v0, 32);
                s0 = addiu(s0, 4);
                jalr(ctx, 0x542EB8u, v1.u());
                lb(v0, s2, 2);
                v0 = slt(s3, v0);
                if (v0 == 0) {
                    break;
                }
                lw(a0, s0, 0);
                backedge(ctx);
            }
        }
        // 0x00542ed0
        charge(ctx, 4);
        lw(v0, s2, 164);
        v0 = subu(v0, s4);
        sw(v0, s2, 164);
        ld(s0, sp, 0x10);
    }
    // 0x00542ee0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005433A0 sub_5433A0 -- 8 bytes; leaf frame (no stack)
// Returns $a0 + 88 (the address of a handle's embedded sub-object).
void sub_5433A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005433a0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = addiu(a0, 88);
}

// 0x0054A680 sub_54A680 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Calls sub_54A6B0($a0) inside the CRI critical section (sub_539848 enter, sub_539850 leave; the leave is a tail
// call).
void sub_54A680(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a680
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54A68Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54A694u, gen::fn_sub_54A6B0_0054a6b0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054B3A0 sub_54B3A0 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Calls sub_54B3F0($a0, $a1, $a2) inside the CRI critical section (sub_539848 / sub_539850, tail call).
void sub_54B3A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b3a0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x54B3BCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x54B3CCu, gen::fn_sub_54B3F0_0054b3f0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054F5C0 sub_54F5C0 -- 324 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// [proposed name: ADXT_AttachAHX, symbols/deltas/sweep5f.sym] Inside sub_548678 / sub_551D38 ... sub_540D40 / sub_540D58, creates the AHX decoder for an ADXT
// handle ($a0: +4 the stream, +16 the channel count, +24 the work area) with sub_551E30; on failure reports "E1052501
// ADXT_AttachAHX" / "can not attach AHX." through sub_53AE60, else stores it at stream->+4->+180, installs the six
// AHX decode callbacks in the CRI ADX globals (0x793B24, 0x7836B8..0x7836C4, 0x7838D8) and starts it (sub_552480).
void sub_54F5C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054f5c0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = addiu(s0, 24);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    s4 = a2;
    jal(ctx, 0x54F5ECu, gen::fn_sub_548678_00548678);
    a0 = s0;
    jal(ctx, 0x54F5F4u, gen::fn_sub_54F708_0054f708);
    jal(ctx, 0x54F5FCu, gen::fn_sub_551D38_00551d38);
    lw(s1, s0, 16);
    lw(s5, s0, 4);
    link(ctx, 0x54F60Cu);  // $ra first: the delay slot below depends on it
    lw(s0, s5, 4);
    call(ctx, gen::fn_sub_540D40_00540d40);
    a0 = s1;
    a1 = 1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    jal(ctx, 0x54F624u, gen::fn_sub_551E30_00551e30);
    v1 = 0x550000;
    a1 = 0x550000;
    t0 = v0;
    a0 = 0x550000;
    a2 = 0x550000;
    v0 = 0x550000;
    a3 = 0x550000;
    t4 = addiu(a1, -2144);  // &atan2l_6
    a1 = 0x7C0000;
    t3 = addiu(a0, -2120);  // &cosl_6
    a0 = t0;
    t1 = addiu(v0, -2256);  // &sub_54F730
    t2 = addiu(v1, -2096);  // &coshl_6
    a2 = addiu(a2, 8200);  // &sub_552008
    a3 = addiu(a3, 9728);  // &sub_552600
    a1 = addiu(a1, 12632);  // "can not attach AHX."
    if (t0 == 0) {
        // 0x0054f670
        charge(ctx, 11);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 12608);  // "E1052501 ADXT_AttachAHX"
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        gen::fn_sub_53AE60_0053ae60(ctx);  // tail call
        return;
    }
    // 0x0054f6a0
    charge(ctx, 25);
    v0 = 0x790000;
    v1 = 0x780000;
    sw(t0, s0, 180);
    sw(t1, v0, 15140);  // 0x793B24
    v0 = 0x780000;
    sw(t2, v1, 14020);  // 0x7836C4
    v1 = 0x780000;
    sw(t3, v0, 14016);  // 0x7836C0
    v0 = 0x780000;
    sw(t4, v1, 14012);  // 0x7836BC
    v1 = 0x780000;
    sw(a2, v0, 14008);  // 0x7836B8
    sw(a3, v1, 14552);  // 0x7838D8
    lw(a2, s5, 84);
    link(ctx, 0x54F6D8u);  // $ra first: the delay slot below depends on it
    lw(a1, s5, 80);
    call(ctx, gen::fn_sub_552480_00552480);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    gen::fn_sub_540D58_00540d58(ctx);  // tail call
}

// 0x00552760 sub_552760 -- 204 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// AIXP finish: decrements the AIX player init count (0x799964); at 0 it destroys every live player of the four
// 620-byte slots at 0x799978 (state byte 1 -> sub_552BD0), clears the slots (memset 2480), restores two sound
// settings (sub_564EF8(2, 0), sub_564EF8(5, *0x799968)) and finishes the layers below (sub_554778, sub_53EC20, tail
// call).
void sub_552760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552760
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x7A0000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, -26268);  // &0x799964
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v0, v1, 0);  // 0x799964
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x799964
    if (v0 != 0) {
        // 0x00552810
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x00552790
    charge(ctx, 4);
    s3 = 0x7A0000;
    s2 = 1;
    s0 = addiu(s3, -26248);  // &0x799978
    s1 = 3;
    for (;;) {
        // 0x005527a0
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x005527ac
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x5527ACu, gen::fn_sub_552BD0_00552bd0);
            s1 = addiu(s1, -1);
        }
        // 0x005527b8
        charge(ctx, 2);
        s0 = addiu(s0, 620);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005527c0
    charge(ctx, 20);
    a2 = 2480;
    a0 = addiu(s3, -26248);
    a1 = 0;
    jal(ctx, 0x5527C8u, gen::fn_memset_00521408);
    a0 = 2;
    a1 = 0;
    jal(ctx, 0x5527D4u, gen::fn_sub_564EF8_00564ef8);
    v0 = 0x7A0000;
    lw(a1, v0, -26264);  // 0x799968
    a0 = 5;
    jal(ctx, 0x5527E4u, gen::fn_sub_564EF8_00564ef8);
    jal(ctx, 0x5527ECu, gen::fn_sub_554778_00554778);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_53EC20_0053ec20(ctx);  // tail call
}

// 0x00552830 sub_552830 -- 128 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s2 sp+0x20, ra sp+0x30, s1 sp+0x0, s0 sp+0x4
// AIXP create with a caller-given work area: builds a 12-byte create parameter on the stack {$a0, $a1, 0} and calls
// sub_552930(&param, $a2, $a3) inside the AIXP lock (sub_5546F0 / sub_554708); returns its handle.
void sub_552830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552830
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s3, sp, 0x28);
    s3 = a2;
    a0 = sp;
    a1 = 0;
    a2 = 12;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x30);
    s2 = a3;
    jal(ctx, 0x552860u, gen::fn_memset_00521408);
    sw(s1, sp, 0x0);
    sw(s0, sp, 0x4);
    link(ctx, 0x552870u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x8);
    call(ctx, gen::fn_sub_5546F0_005546f0);
    a0 = sp;
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x552880u, gen::fn_sub_552930_00552930);
    s0 = v0;
    jal(ctx, 0x552888u, gen::fn_sub_554708_00554708);
    ld(s1, sp, 0x18);
    v0 = s0;
    ld(s2, sp, 0x20);
    ld(s0, sp, 0x10);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005528B0 sub_5528B0 -- 124 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28, s0 sp+0x0
// AIXP create with fixed parameters: the stack parameter {$a0, 2, 1}, then sub_552930(&param, $a1, $a2) inside the
// AIXP lock; returns the handle.
void sub_5528B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005528b0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = a1;
    a0 = sp;
    a2 = 12;
    sd(ra, sp, 0x28);
    a1 = 0;
    jal(ctx, 0x5528D8u, gen::fn_memset_00521408);
    v1 = 2;
    v0 = 1;
    sw(s0, sp, 0x0);
    sw(v1, sp, 0x4);
    link(ctx, 0x5528F0u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x8);
    call(ctx, gen::fn_sub_5546F0_005546f0);
    a0 = sp;
    a1 = s2;
    a2 = s1;
    jal(ctx, 0x552900u, gen::fn_sub_552930_00552930);
    s0 = v0;
    jal(ctx, 0x552908u, gen::fn_sub_554708_00554708);
    ld(s1, sp, 0x18);
    v0 = s0;
    ld(s2, sp, 0x20);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00552EA8 sub_552EA8 -- 32 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_552D68($a0, $a1, $a2, 0, 0xFFFFF) (a start with the default range).
void sub_552EA8(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552ea8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0xF0000;
    sd(ra, sp, 0x0);
    a3 = 0;
    t0 = t0 | 0xFFFF;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_552D68_00552d68(ctx);  // tail call
}

// 0x00552EC8 sub_552EC8 -- 212 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// AIXP start by file name ($a0 the player, $a1 the file system / directory, $a2 the name): NULL player ->
// "E2003050205 : NULL pointer is specified." (sub_552630). Otherwise stops it (sub_5530D0) and, inside the AIXP lock,
// looks the file up (sub_53DD10, results on the stack); when found it records the file size (sub_53DEF0) and range
// (+460..+472), sets the stream (+144 from +140), starts the reader (sub_554948) and marks the player playing (+1 =
// 1, +476 = 1, +434 = 1).
void sub_552EC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00552ec8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(ra, sp, 0x28);
    if (s0 != 0) {
        // 0x00552f00
        charge(ctx, 14);
        jal(ctx, 0x552F00u, gen::fn_sub_5530D0_005530d0);
        jal(ctx, 0x552F08u, gen::fn_sub_5546F0_005546f0);
        a2 = 0x990000;
        a3 = sp;
        a0 = s2;
        a1 = s1;
        a2 = addiu(a2, 29448);  // &0x997308
        t0 = addiu(sp, 0x4);
        t1 = addiu(sp, 0x8);
        jal(ctx, 0x552F28u, gen::fn_sub_53DD10_0053dd10);
        a0 = s2;
        if (v0 == 0) {
            // 0x00552f38
            charge(ctx, 17);
            jal(ctx, 0x552F38u, gen::fn_sub_53DEF0_0053def0);
            lw(a1, s0, 140);
            sw(v0, s0, 460);
            sw(a1, s0, 144);
            lw(a0, s0, 4);
            lw(v0, sp, 0x0);
            lw(v1, sp, 0x4);
            lw(a2, sp, 0x8);
            sw(v0, s0, 464);
            sw(v1, s0, 468);
            link(ctx, 0x552F64u);  // $ra first: the delay slot below depends on it
            sw(a2, s0, 472);
            call(ctx, gen::fn_sub_554948_00554948);
            v0 = 1;
            sb(v0, s0, 1);
            sw(v0, s0, 476);
            sb(v0, s0, 434);
        }
        // 0x00552f7c
        charge(ctx, 3);
        jal(ctx, 0x552F7Cu, gen::fn_sub_554708_00554708);
        ld(s0, sp, 0x10);
    } else {
        // 0x00552eec
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13032);  // "E2003050205 : NULL pointer is specified."
        jal(ctx, 0x552EF0u, gen::fn_sub_552630_00552630);
        ld(s0, sp, 0x10);
    }
    // 0x00552f88 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00553028 sub_553028 -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// AIXP start from memory ($a0 the player, $a1 the data, $a2 its size): NULL -> "E2003050207 : NULL pointer is
// specified."; else stops it (sub_5530D0) and, inside the AIXP lock, opens a memory stream (sub_561970) at +144,
// starts the reader (sub_554948) and sets +476 = 2, +1 = 1.
void sub_553028(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553028
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 != 0) {
        // 0x0055304c
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_00553054;
        }
        // 0x00553078
        charge(ctx, 21);
        jal(ctx, 0x553078u, gen::fn_sub_5530D0_005530d0);
        jal(ctx, 0x553080u, gen::fn_sub_5546F0_005546f0);
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x55308Cu, gen::fn_sub_561970_00561970);
        lw(a0, s0, 4);
        sw(v0, s0, 144);
        a1 = v0;
        jal(ctx, 0x55309Cu, gen::fn_sub_554948_00554948);
        v0 = 2;
        v1 = 1;
        sw(v0, s0, 476);
        sb(v1, s0, 1);
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_554708_00554708(ctx);  // tail call
        return;
    }
L_00553054:
    charge(ctx, 8);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 13128);  // "E2003050207 : NULL pointer is specified."
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_552630_00552630(ctx);  // tail call
}

// 0x005533D8 sub_5533D8 -- 48 bytes; frame 0x10: ra sp+0x0
// AIXP set a flag byte: $a0 NULL -> "E2003050211 : NULL pointer is specified."; else *(u8*)($a0 + 432) = $a1.
void sub_5533D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005533d8
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005533f8
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sb(a1, a0, 432);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005533e4
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 13424);  // "E2003050211 : NULL pointer is specified."
    sp = addiu(sp, 0x10);
    gen::fn_sub_552630_00552630(ctx);  // tail call
}

// 0x00553590 sub_553590 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Calls sub_5535D0($a0, $a1) inside the AIXP lock (sub_5546F0 / sub_554708).
void sub_553590(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553590
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5535A4u, gen::fn_sub_5546F0_005546f0);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x5535B0u, gen::fn_sub_5535D0_005535d0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00553658 sub_553658 -- 48 bytes; frame 0x10: ra sp+0x0
// [proposed name: AIXP_GetStatPause, symbols/deltas/sweep5f.sym] $a0 NULL -> "E2003062000 AIXP_GetStatPause: parameter AIXP_CREATE_ERROR" and 0; else the pause
// state word +424.
void sub_553658(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00553658
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00553678
        charge(ctx, 1);
        lw(v0, a0, 424);
    } else {
        // 0x00553664
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 13808);  // "E2003062000 AIXP_GetStatPause: parameter AIXP_CREATE_ERROR"
        jal(ctx, 0x553668u, gen::fn_sub_552630_00552630);
        v0 = 0;
    }
    // 0x0055367c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005540E8 sub_5540E8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Calls sub_554138($a0, $a1, $a2) inside the AIXP lock (sub_5546F0 / sub_554708).
void sub_5540E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005540e8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x554104u, gen::fn_sub_5546F0_005546f0);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x554114u, gen::fn_sub_554138_00554138);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_554708_00554708(ctx);  // tail call
}

// 0x00555F90 sceLibgcc32GetErxEntries_5 -- 12 bytes; leaf frame (no stack)
// Returns the address 0x997858 (a CRI file-system device-name table; the symbol name is the importer's
// library-signature match).
void sceLibgcc32GetErxEntries_5(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00555f90
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x990000;
    v0 = addiu(v0, 30808);  // &0x997858
}

// 0x00557D58 srd_wait_dvd -- 40 bytes; frame 0x10: ra sp+0x0
// SRD (CRI stream reader) DVD wait: sceCdSync(0) between the trace marks sub_558988(0x1300) / sub_558988(0x1301).
void srd_wait_dvd(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00557d58
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 4864;
    jal(ctx, 0x557D60u, gen::fn_sub_558988_00558988);
    a0 = 0;
    jal(ctx, 0x557D68u, gen::fn_sceCdSync_00510148);
    a0 = 4865;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_558988_00558988(ctx);  // tail call
}

// 0x00558768 SRD_GetReadStatusDvd -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Returns sceCdSync(1) (the non-blocking read status) between the trace marks 0x2300 / 0x2301.
void SRD_GetReadStatusDvd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558768
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    a0 = 8960;
    jal(ctx, 0x558774u, gen::fn_sub_558988_00558988);
    a0 = 1;
    jal(ctx, 0x55877Cu, gen::fn_sceCdSync_00510148);
    a0 = 8961;
    s0 = v0;
    jal(ctx, 0x558788u, gen::fn_sub_558988_00558988);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00558AE0 SRD_SetDvdSeekPos -- 132 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// If sub_5655E8 takes the seek request flag (0x7A08EC), seeks with sceCdSeek($a0) between the trace marks 0x9600 /
// 0x9601, returns sceCdGetError() when the seek is refused (else 0) and clears the flag; returns sub_5655E8's 0
// otherwise.
void SRD_SetDvdSeekPos(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00558ae0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7A0000;
    sd(s2, sp, 0x10);
    s2 = addiu(v0, 2284);  // &0x7A08EC
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    a0 = s2;
    jal(ctx, 0x558B00u, gen::fn_sub_5655E8_005655e8);
    s1 = 0;
    a0 = 0x9600;
    if (v0 != 0) {
        // 0x00558b14
        charge(ctx, 9);
        jal(ctx, 0x558B14u, gen::fn_sub_558988_00558988);
        a0 = s0;
        jal(ctx, 0x558B1Cu, gen::fn_sceCdSeek_00510d60);
        a0 = 0x9601;
        s0 = v0;
        jal(ctx, 0x558B28u, gen::fn_sub_558988_00558988);
        if (s0 != 0) {
            sw(zero, s2, 0);
        } else {
            // 0x00558b38
            charge(ctx, 4);
            jal(ctx, 0x558B38u, gen::fn_sceCdGetError_00510ef0);
            s1 = v0;
            sw(zero, s2, 0);
        }
        // 0x00558b48
        charge(ctx, 1);
        v0 = s1;
    }
    // 0x00558b4c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005595F8 dtx_destroy_rmt -- 76 bytes; frame 0x20: ra sp+0x10
// DTX: destroys the IOP-side remote object $a0 with sceSifCallRpc(client 0x7A19E0, function 3, mode 0, send 0x9979C0
// (4 bytes, holds $a0), receive 0x997AC0, 0 bytes, no callback).
void dtx_destroy_rmt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005595f8
    enter(ctx, 19);  // entry check point + this block's cycles
    a3 = 0x990000;
    sp = addiu(sp, -0x20);
    a3 = addiu(a3, 31168);  // &0x9979C0
    sd(ra, sp, 0x10);
    v0 = 0x7A0000;
    t1 = 0x990000;
    sw(a0, a3, 0);  // 0x9979C0
    a0 = addiu(v0, 6624);  // &0x7A19E0
    t1 = addiu(t1, 31424);  // &0x997AC0
    a1 = 3;
    a2 = 0;
    t0 = 4;
    t2 = 0;
    t3 = 0;
    link(ctx, 0x559630u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x0);
    call(ctx, gen::fn_sceSifCallRpc_00507230);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055A050 dvCiIsExistFile -- 136 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// CRI DVD file interface: is the file $a0 known? NULL -> 0. A cache hit (dvci_get_fstate, stack record +4 != 0) -> 1;
// else converts the name (dvci_conv_fname into 0x7A2930), waits for the drive (sceCdSync(0), trace marks 0x8100 /
// 0x8101) and returns 1 when dvCiCdSearchFile finds it, else 0.
void dvCiIsExistFile(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a050
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0;
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    sd(ra, sp, 0x40);
    if (s0 != 0) {
        // 0x0055a06c
        charge(ctx, 8);
        a1 = sp;
        jal(ctx, 0x55A06Cu, gen::fn_dvci_get_fstate_0055b220);
        v1 = 0x7A0000;
        lw(v0, sp, 0x4);
        s1 = addiu(v1, 10544);  // &0x7A2930
        a0 = s0;
        a1 = s1;
        if (v0 == 0) {
            // 0x0055a08c
            charge(ctx, 13);
            jal(ctx, 0x55A08Cu, gen::fn_dvci_conv_fname_0055a9b0);
            a0 = 0x8100;
            jal(ctx, 0x55A094u, gen::fn_sub_558988_00558988);
            a0 = 0;
            jal(ctx, 0x55A09Cu, gen::fn_sceCdSync_00510148);
            a0 = 0x8101;
            jal(ctx, 0x55A0A4u, gen::fn_sub_558988_00558988);
            a1 = s1;
            a0 = sp;
            jal(ctx, 0x55A0B0u, gen::fn_dvCiCdSearchFile_00559dd8);
            ld(s0, sp, 0x30);
            if (v0 != 0) {
                goto L_0055a0c0;
            }
            // 0x0055a0c8 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x38);
            ld(ra, sp, 0x40);
            sp = addiu(sp, 0x50);
            return;
        }
    L_0055a0c0:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x0055a0c4
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x0055a0c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0055A0D8 dvCiGetFileSize -- 192 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// CRI DVD file interface: the size of file $a0. NULL -> "E0092901:fname is null.(dvCiGetFileSize)" (sub_559DA8) and
// 0; a cache hit returns its size; else searches the disc as dvCiIsExistFile does (trace marks 0x8200 / 0x8201) and
// returns the found size, or prints "DVCI: sceCdSearchFile failed." (sub_541760), reports E0092902 and returns 0.
void dvCiGetFileSize(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a0d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x38);
    sd(ra, sp, 0x40);
    if (s0 == 0) {
        // 0x0055a0f0
        charge(ctx, 3);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19528);  // "E0092901:fname is null.(dvCiGetFileSize)"
        goto L_0055a170;
    }
    // 0x0055a100
    charge(ctx, 8);
    a1 = sp;
    jal(ctx, 0x55A100u, gen::fn_dvci_get_fstate_0055b220);
    v1 = 0x7A0000;
    lw(v0, sp, 0x4);
    s1 = addiu(v1, 10544);  // &0x7A2930
    a0 = s0;
    a1 = s1;
    if (v0 == 0) {
        // 0x0055a120
        charge(ctx, 15);
        jal(ctx, 0x55A120u, gen::fn_dvci_conv_fname_0055a9b0);
        a0 = 0x8200;
        jal(ctx, 0x55A128u, gen::fn_sub_558988_00558988);
        a0 = 0;
        jal(ctx, 0x55A130u, gen::fn_sceCdSync_00510148);
        a0 = 0x8201;
        jal(ctx, 0x55A138u, gen::fn_sub_558988_00558988);
        a1 = s1;
        a0 = sp;
        jal(ctx, 0x55A144u, gen::fn_dvCiCdSearchFile_00559dd8);
        a0 = 0x7C0000;
        a0 = addiu(a0, 19576);  // "DVCI: sceCdSearchFile failed. \"%s\"\n"
        a1 = s1;
        if (v0 != 0) {
            // 0x0055a180
            charge(ctx, 1);
            lw(v0, sp, 0x4);
        } else {
            // 0x0055a15c
            charge(ctx, 5);
            jal(ctx, 0x55A15Cu, gen::fn_sub_541760_00541760);
            a1 = 0x7C0000;
            a1 = addiu(a1, 19616);  // "E0092902:can't find file.(dvCiGetFileSize)"
            a0 = 0;
        L_0055a170:
            charge(ctx, 4);
            jal(ctx, 0x55A170u, gen::fn_sub_559DA8_00559da8);
            v0 = 0;
        }
    }
    // 0x0055a184 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0055A368 dvCiClose -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// CRI DVD file interface: closes handle $a0 (NULL: nothing): stops a running transfer first when the state byte +2 is
// >= 2 (dvCiStopTr), clears the used byte +0 and frees it (sub_55A1D0, tail call).
void dvCiClose(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a368
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x0055a3b0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0055a37c
    charge(ctx, 4);
    lbu(v0, s0, 2);
    v0 = sltiu(v0, 2);
    if (v0 != 0) {
        sb(zero, s0, 0);
    } else {
        // 0x0055a38c
        charge(ctx, 3);
        jal(ctx, 0x55A38Cu, gen::fn_dvCiStopTr_0055a638);
        sb(zero, s0, 0);
    }
    // 0x0055a398
    charge(ctx, 5);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55A1D0_0055a1d0(ctx);  // tail call
}

// 0x0055A458 sub_55A458 -- 56 bytes; frame 0x10: ra sp+0x0
// CRI DVD file interface: the file size field (+12) of handle $a0; NULL -> "E0092912:handl is null." and 0.
void sub_55A458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a458
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a0;
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0055a480
        charge(ctx, 1);
        lw(v0, v0, 12);
    } else {
        // 0x0055a468
        charge(ctx, 5);
        a1 = 0x7C0000;
        a1 = addiu(a1, 19880);  // "E0092912:handl is null."
        jal(ctx, 0x55A46Cu, gen::fn_sub_559DA8_00559da8);
        v0 = 0;
    }
    // 0x0055a484 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0055A7C0 sceInsockGetErrnoMode_3 -- 12 bytes; leaf frame (no stack)
// Returns the word at 0x7A2A78 (a dvci setting; the symbol name is the importer's library-signature match).
void sceInsockGetErrnoMode_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0055a7c0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7A0000;
    lw(v0, v1, 10872);  // 0x7A2A78
}

// 0x0055A800 sub_55A800 -- 152 bytes; frame 0x50: s0 sp+0x30, s1 sp+0x38, ra sp+0x40
// CRI DVD file interface: the size of file $a0 without a NULL check: a cache hit returns its size; else searches the
// disc (trace marks 0x8400 / 0x8401) and returns the found size, or prints "DVCI: sceCdSearchFile failed." and
// returns 0.
void sub_55A800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a800
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a1 = sp;
    sd(s0, sp, 0x30);
    sd(s1, sp, 0x38);
    sd(ra, sp, 0x40);
    s0 = a0;
    jal(ctx, 0x55A814u, gen::fn_dvci_get_fstate_0055b220);
    lw(v0, sp, 0x4);
    v1 = 0x7A0000;
    s1 = addiu(v1, 10544);  // &0x7A2930
    a0 = s0;
    a1 = s1;
    if (v0 == 0) {
        // 0x0055a834
        charge(ctx, 15);
        jal(ctx, 0x55A834u, gen::fn_dvci_conv_fname_0055a9b0);
        a0 = 0x8400;
        jal(ctx, 0x55A83Cu, gen::fn_sub_558988_00558988);
        a0 = 0;
        jal(ctx, 0x55A844u, gen::fn_sceCdSync_00510148);
        a0 = 0x8401;
        jal(ctx, 0x55A84Cu, gen::fn_sub_558988_00558988);
        a1 = s1;
        a0 = sp;
        jal(ctx, 0x55A858u, gen::fn_dvCiCdSearchFile_00559dd8);
        a0 = 0x7C0000;
        a0 = addiu(a0, 19576);  // "DVCI: sceCdSearchFile failed. \"%s\"\n"
        a1 = s1;
        if (v0 != 0) {
            // 0x0055a880
            charge(ctx, 1);
            lw(v0, sp, 0x4);
        } else {
            // 0x0055a870
            charge(ctx, 4);
            jal(ctx, 0x55A870u, gen::fn_sub_541760_00541760);
            v0 = 0;
        }
    }
    // 0x0055a884 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x30);
    ld(s1, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0055A8C8 sub_55A8C8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (a stub interface entry).
void sub_55A8C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0055a8c8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0055A8D0 sub_55A8D0 -- 20 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_55A800 (the interface entry for the file size).
void sub_55A8D0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0055a8d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55A800_0055a800(ctx);  // tail call
}

// 0x0055AA58 sub_55AA58 -- 52 bytes; leaf frame (no stack)
// Normalises one path character ($a0, sign-extended byte): lower case -> upper case, '\\' -> '/'.
void sub_55AA58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0055aa58
    enter(ctx, 8);  // entry check point + this block's cycles
    a0 = sll(a0, 24);
    a0 = sra(a0, 24);
    v0 = addiu(a0, -97);
    v1 = addiu(a0, -32);
    v0 = sltiu(v0, 26);
    a1 = sll(v1, 24);
    v1 = a0;
    if (v0 != 0) {
        // 0x0055aa78
        charge(ctx, 1);
        a0 = sra(a1, 24);
    }
    // 0x0055aa7c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v1 = v1 ^ 0x5C;
    v0 = 47;
    if (v1 != 0) v0 = a0;
}

// 0x0055AA90 sub_55AA90 -- 84 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Compares two path characters after sub_55AA58: 0 when equal, -1 otherwise.
void sub_55AA90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055aa90
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = sll(a0, 24);
    sd(s1, sp, 0x8);
    s1 = sll(a1, 24);
    s1 = sra(s1, 24);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    a0 = sra(a0, 24);
    jal(ctx, 0x55AAACu, gen::fn_sub_55AA58_0055aa58);
    a0 = s1;
    s0 = v0;
    jal(ctx, 0x55AAB8u, gen::fn_sub_55AA58_0055aa58);
    v1 = si(-1);
    s0 = s0 ^ v0;
    v0 = 0;
    if (s0 != 0) v0 = v1;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0055AAE8 sub_55AAE8 -- 148 bytes; frame 0x30: s2 sp+0x10, s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Compares two path names ($a0, $a1) case-insensitively with '\\' == '/' (sub_55AA90 per character): 0 when equal, -1
// when the lengths (strlen) or any character differ.
void sub_55AAE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055aae8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x55AB04u, gen::fn_strlen_00524388);
    a0 = s2;
    s1 = v0;
    jal(ctx, 0x55AB10u, gen::fn_strlen_00524388);
    if (s1 == v0) {
        // 0x0055ab28
        charge(ctx, 2);
        s0 = 0;
        if (i64(s1) > 0) {
            // 0x0055ab30
            charge(ctx, 2);
            v1 = addu(s2, s0);
            for (;;) {
                // 0x0055ab38
                charge(ctx, 7);
                v0 = addu(s3, s0);
                lb(a1, v1, 0);
                s0 = addiu(s0, 1);
                link(ctx, 0x55AB44u);  // $ra first: the delay slot below depends on it
                lb(a0, v0, 0);
                call(ctx, gen::fn_sub_55AA90_0055aa90);
                v1 = slt(s0, s1);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_0055ab20;
                }
                // 0x0055ab54
                charge(ctx, 2);
                cc = v1 != 0;  // the condition, before the delay slot changes it
                v1 = addu(s2, s0);
                if (!cc) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0055ab5c
        charge(ctx, 1);
        v0 = 0;
        // 0x0055ab60 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_0055ab20:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x0055ab60 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0055AD18 dvci_load_flist -- 392 bytes; frame 0x80: s1 sp+0x58, s2 sp+0x60, s0 sp+0x50, s3 sp+0x68, ra sp+0x70
// CRI DVD file interface: loads a file list ($a0 the name, $a1 the buffer). A "HST:" prefix goes to the host loader
// (sub_55C9D0). Otherwise converts the name into 0x7A2B88, waits for the drive, searches the file (dvCiCdSearchFile)
// and reads 2 sectors from its LSN into $a1 (sceCdRead, read mode {1 retry, 0, 0, 0} on the stack), waiting for
// completion; trace marks 0x9000..0x9301 around each step. Returns 1, or 0 when the search or the read fails.
void dvci_load_flist(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055ad18
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v1 = 0x7C0000;
    sd(s1, sp, 0x58);
    s1 = a0;
    sd(s2, sp, 0x60);
    s2 = a1;
    sd(s0, sp, 0x50);
    v0 = addiu(sp, 0x40);
    sd(s3, sp, 0x68);
    a1 = addiu(v1, 20032);  // "HST:"
    sd(ra, sp, 0x70);
    a0 = v0;
    lwl(v1, s1, 3);
    lwr(v1, s1, 0);
    lb(a2, s1, 4);
    swl(v1, v0, 3);
    swr(v1, v0, 0);
    sb(a2, v0, 4);
    link(ctx, 0x55AD60u);  // $ra first: the delay slot below depends on it
    sb(zero, sp, 0x44);
    call(ctx, gen::fn_strcasecmp_00523dc8);
    if (v0 != 0) {
        s3 = 0x7A0000;
        // 0x0055ad88
        charge(ctx, 12);
        a2 = 128;
        s0 = addiu(s3, 11144);
        a1 = 0;
        a0 = s0;
        jal(ctx, 0x55AD94u, gen::fn_memset_00521408);
        a0 = s1;
        a1 = s0;
        s0 = 1;
        jal(ctx, 0x55ADA4u, gen::fn_dvci_conv_fname_0055a9b0);
        a0 = 0x9000;
        jal(ctx, 0x55ADACu, gen::fn_sub_558988_00558988);
        for (;;) {
            // 0x0055adb8
            charge(ctx, 4);
            a0 = 1;
            jal(ctx, 0x55ADB8u, gen::fn_sceCdSync_00510148);
            if (v0 != s0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0055adc8
        charge(ctx, 9);
        a0 = 0x9001;
        jal(ctx, 0x55ADC8u, gen::fn_sub_558988_00558988);
        a0 = 0x9100;
        jal(ctx, 0x55ADD0u, gen::fn_sub_558988_00558988);
        a1 = addiu(s3, 11144);
        a0 = sp;
        jal(ctx, 0x55ADDCu, gen::fn_dvCiCdSearchFile_00559dd8);
        if (v0 == 0) {
            // 0x0055adec
            charge(ctx, 2);
            a0 = 0x9101;
            goto L_0055ae3c;
        }
        // 0x0055adf8
        charge(ctx, 16);
        a0 = 0x9102;
        jal(ctx, 0x55ADF8u, gen::fn_sub_558988_00558988);
        v0 = 1;
        a0 = 0x9200;
        sb(v0, sp, 0x31);
        sb(zero, sp, 0x30);
        sb(zero, sp, 0x32);
        link(ctx, 0x55AE14u);  // $ra first: the delay slot below depends on it
        sb(zero, sp, 0x33);
        call(ctx, gen::fn_sub_558988_00558988);
        lw(a0, sp, 0x0);
        a3 = addiu(sp, 0x30);
        a2 = s2;
        a1 = 2;
        jal(ctx, 0x55AE28u, gen::fn_sceCdRead_00510b80);
        if (v0 != 0) {
            // 0x0055ae50
            charge(ctx, 6);
            a0 = 0x9202;
            jal(ctx, 0x55AE50u, gen::fn_sub_558988_00558988);
            a0 = 0x9300;
            jal(ctx, 0x55AE58u, gen::fn_sub_558988_00558988);
            s0 = 1;
            for (;;) {
                // 0x0055ae68
                charge(ctx, 4);
                a0 = 1;
                jal(ctx, 0x55AE68u, gen::fn_sceCdSync_00510148);
                if (v0 != s0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0055ae78
            charge(ctx, 3);
            a0 = 0x9301;
            jal(ctx, 0x55AE78u, gen::fn_sub_558988_00558988);
            v0 = 1;
        } else {
            // 0x0055ae38
            charge(ctx, 1);
            a0 = 0x9201;
        L_0055ae3c:
            charge(ctx, 4);
            jal(ctx, 0x55AE3Cu, gen::fn_sub_558988_00558988);
            v0 = 0;
        }
        // 0x0055ae84
        charge(ctx, 1);
        ld(s0, sp, 0x50);
    } else {
        // 0x0055ad70
        charge(ctx, 5);
        a0 = addiu(s1, 4);
        a1 = s2;
        jal(ctx, 0x55AD74u, gen::fn_sub_55C9D0_0055c9d0);
        ld(s0, sp, 0x50);
    }
    // 0x0055ae88 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(ra, sp, 0x70);
    sp = addiu(sp, 0x80);
}

// 0x0055B030 dvci_get_fp_from_fname -- 200 bytes; frame 0x40: s4 sp+0x20, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s6 sp+0x30, s1 sp+0x8, s5 sp+0x28, ra sp+0x38
// CRI DVD file interface: finds name $a1 in the file cache ($a2 the table of {LSN, size} pairs, $a3 the count; the
// names follow the pairs, *0x7A2A68 pairs in, with a stride of *0x7A2A6C + 1) using sub_55AAE8, and stores the found
// pair at $a0 ({0, 0} when absent).
void dvci_get_fp_from_fname(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b030
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s4, sp, 0x20);
    s4 = a3;
    sd(s0, sp, 0x0);
    s0 = 0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(s6, sp, 0x30);
    s6 = a1;
    sd(s1, sp, 0x8);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    if (i64(s4) > 0) {
        // 0x0055b06c
        charge(ctx, 3);
        v0 = 0x7A0000;
        s1 = s2;
        s5 = addiu(v0, 10848);  // &0x7A2A60
        for (;;) {
            // 0x0055b078
            charge(ctx, 12);
            lw(v0, s5, 12);
            a0 = s6;
            lw(a1, s5, 8);
            mult(v1, v0, s0);
            a1 = sll(a1, 3);
            v0 = addu(v1, s0);
            s0 = addiu(s0, 1);
            a1 = addu(a1, v0);
            a1 = addu(s2, a1);
            jal(ctx, 0x55B098u, gen::fn_sub_55AAE8_0055aae8);
            v1 = slt(s0, s4);
            if (v0 == 0) {
                goto L_0055b0a8_3;
            }
            // 0x0055b0c0
            charge(ctx, 2);
            s1 = addiu(s1, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055b0c8
    charge(ctx, 2);
    sw(zero, s3, 4);
    sw(zero, s3, 0);
    // 0x0055b0d0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
    return;
L_0055b0a8_3:
    charge(ctx, 5);
    lw(v0, s1, 0);
    sw(v0, s3, 0);
    lw(v1, s1, 4);
    sw(v1, s3, 4);
    // 0x0055b0d0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0055B160 dvci_get_adr_size -- 192 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28, s1 sp+0x0
// CRI DVD file interface: parses "<LSN>,<size>" ($a0, base-16 strtoul; the separator is skipped) into *$a1 and *$a2,
// prints "DVCI: \"%s\" opened. LSN=%d, Size=%d[sector]" (sub_5416E8) and returns 1.
void dvci_get_adr_size(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055b160
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = a1;
    a2 = 16;
    a1 = sp;
    sd(ra, sp, 0x28);
    link(ctx, 0x55B188u);  // $ra first: the delay slot below depends on it
    sw(s1, sp, 0x0);
    call(ctx, gen::fn_strtoul_00525e98);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    a1 = sp;
    sw(v0, s2, 0);
    a2 = 16;
    lw(v0, sp, 0x0);
    lb(v1, v0, 0);
    v0 = addiu(v0, 1);
    if (v1 != 0) {
        // 0x0055b1b4
        charge(ctx, 1);
        sw(v0, sp, 0x0);
    }
    // 0x0055b1b8
    charge(ctx, 2);
    if (s0 == 0) {
        a0 = 0x7C0000;
    } else {
        // 0x0055b1c0
        charge(ctx, 6);
        link(ctx, 0x55B1C0u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x0);
        call(ctx, gen::fn_strtoul_00525e98);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        sw(v0, s0, 0);
        a0 = 0x7C0000;
    }
    // 0x0055b1d8
    charge(ctx, 18);
    a1 = s1;
    a0 = addiu(a0, 20160);
    jal(ctx, 0x55B1DCu, gen::fn_sub_5416E8_005416e8);
    a0 = 0x7C0000;
    lw(a1, s2, 0);
    a0 = addiu(a0, 20184);  // "LSN=%d, "
    jal(ctx, 0x55B1ECu, gen::fn_sub_5416E8_005416e8);
    a0 = 0x7C0000;
    lw(a1, s0, 0);
    a0 = addiu(a0, 20200);  // "Size=%d[sector]\n"
    jal(ctx, 0x55B1FCu, gen::fn_sub_5416E8_005416e8);
    v0 = 1;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0055E978 sub_55E978 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Opens an entry of a file group: entry $a0 <= 0 -> "E1041001:invalid entry number." and 0; $a2 != 0 -> "E1041002:rw
// is illigal." and 0; else takes a free handle (sub_55E3B0; none -> "E1041002:not enough handle resource." and 0),
// initialises it (sub_55E428) and returns it. Errors go through sub_55E1D8.
void sub_55E978(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055e978
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    if (i64(a0) <= 0) {
        // 0x0055e988
        charge(ctx, 4);
        a1 = 0x7C0000;
        a0 = 0;
        a1 = addiu(a1, 23504);  // "E1041001:invalid entry number.(mfCiOpenEntry)"
        goto L_0055e9cc;
    }
    // 0x0055e998
    charge(ctx, 2);
    a1 = 0x7C0000;
    if (a2 != 0) {
        // 0x0055e9a0
        charge(ctx, 3);
        a0 = 0;
        a1 = addiu(a1, 23552);
        goto L_0055e9cc;
    }
    // 0x0055e9b0
    charge(ctx, 7);
    jal(ctx, 0x55E9B0u, gen::fn_sub_55E3B0_0055e3b0);
    a1 = 0x7C0000;
    s0 = v0;
    a1 = addiu(a1, 23592);  // "E1041002:not enough handle resource.(mfCiOpenEntry)"
    a0 = 0;
    if (s0 != 0) {
        // 0x0055e9e0
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x55E9E0u, gen::fn_sub_55E428_0055e428);
        v0 = s0;
    } else {
    L_0055e9cc:
        charge(ctx, 4);
        jal(ctx, 0x55E9CCu, gen::fn_sub_55E1D8_0055e1d8);
        v0 = 0;
    }
    // 0x0055e9ec (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0055EA00 sub_55EA00 -- 124 bytes; frame 0x10: ra sp+0x0
// An interface query by id ($a1) for handle $a0: 201 -> sub_55E940, 203 / 205 -> sub_55E390 (tail calls), anything
// else (or a NULL handle) -> 0.
void sub_55EA00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0055ea00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0;
    sd(ra, sp, 0x0);
    v0 = 0;
    if (a0 != 0) {
        // 0x0055ea14
        charge(ctx, 3);
        v0 = 203;
        cc = a1 == v0;  // the condition, before the delay slot changes it
        v0 = slti(a1, 204);
        if (!cc) {
            // 0x0055ea20
            charge(ctx, 2);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 205;
            if (cc) {
                // 0x0055ea40
                charge(ctx, 2);
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = v1;
                if (cc) {
                    goto L_0055ea60;
                }
                // 0x0055ea48
                charge(ctx, 2);
                ld(ra, sp, 0x0);
            } else {
                // 0x0055ea28
                charge(ctx, 3);
                v0 = 201;
                cc = a1 == v0;  // the condition, before the delay slot changes it
                v0 = v1;
                if (cc) {
                    // 0x0055ea50
                    charge(ctx, 4);
                    jal(ctx, 0x55EA50u, gen::fn_sub_55E940_0055e940);
                    v1 = v0;
                L_0055ea6c:
                    charge(ctx, 1);
                    v0 = v1;
                    goto L_0055ea70;
                }
                // 0x0055ea34
                charge(ctx, 2);
                ld(ra, sp, 0x0);
            }
            // 0x0055ea74 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0055ea60:
        charge(ctx, 3);
        jal(ctx, 0x55EA60u, gen::fn_sub_55E390_0055e390);
        v1 = v0;
        goto L_0055ea6c;
    }
L_0055ea70:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0055ea74 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0055F4F0 sub_55F4F0 -- 168 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// ADXT 3D sound parameter set: $a0 NULL -> "E2003091605 : NULL pointer is specified."; a handle with fewer than 2
// channels (+3) or no 3D object (stream +4 -> +232) -> "E2003091606 : ADXT handle must be created for 3D sound."
// (sub_53AE08); else updates it (sub_55F1C8) and stores $a1 / $a2 at +236 / +240.
void sub_55F4F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055f4f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    if (a0 == 0) {
        // 0x0055f510
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 25088);  // "E2003091605 : NULL pointer is specified."
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0055f530
    charge(ctx, 6);
    lw(v1, a0, 4);
    lb(v0, a0, 3);
    lw(s0, v1, 4);
    v0 = slti(v0, 2);
    lw(a0, s0, 232);
    if (v0 == 0) {
        // 0x0055f548
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_0055f550;
        }
        // 0x0055f570
        charge(ctx, 10);
        jal(ctx, 0x55F570u, gen::fn_sub_55F1C8_0055f1c8);
        sw(s1, s0, 240);
        sw(s2, s0, 236);
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0055f550:
    charge(ctx, 8);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 25136);  // "E2003091606 : ADXT handle must be created for 3D sound."
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x00570030 sub_570030 -- 524 bytes; frame 0x50: s2 sp+0x30, s1 sp+0x28, s3 sp+0x38, s4 sp+0x40, s0 sp+0x20, ra sp+0x48
// Sofdec demultiplexer step: clears the counters (+1624, +1628, +1128, +1132), then for each chunk type sub_57AC68
// reports on stream joint $a1 (4, 8, 16, 32, 64, 128) gets the chunk (vtable +24) and hands it to its parser
// (sub_5745D0, sub_574068, sub_571088, sub_570CB8, sub_5703C0, sub_570B98). A parser that consumes nothing returns
// the chunk (vtable +28) and stops; otherwise the consumed part is split off (sub_563C28) and put back (+32), the
// rest returned (+28). It stops when a parser sets +1624; then adds +1624 / +1628 to the totals +1632 / +1636 and
// returns -2 when +1624 is set, else 0.
void sub_570030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00570030
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(s3, sp, 0x38);
    s3 = addiu(s2, 352);
    sd(s4, sp, 0x40);
    s4 = addiu(sp, 0x10);
    sd(s0, sp, 0x20);
    sd(ra, sp, 0x48);
    sw(zero, s3, 1272);
    sw(zero, s3, 1276);
    sw(zero, s3, 776);
    sw(zero, s3, 780);
    for (;;) {
        // 0x005701e0
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x5701E0u, gen::fn_sub_57AC68_0057ac68);
        s0 = v0;
        if (s0 == 0) {
            goto L_005701f4_22;
        }
        lw(v1, s1, 0);
        backedge(ctx);
        // 0x00570070
        charge(ctx, 10);
        a2 = 0x7FFF0000;
        a0 = s1;
        a1 = 1;
        lw(v0, v1, 24);
        a2 = a2 | 0xFFFF;
        a3 = sp;
        jalr(ctx, 0x570084u, v0.u());
        v0 = 16;
        v1 = 0;
        if (s0 == v0) {
            // 0x00570130
            charge(ctx, 5);
            lw(a1, sp, 0x0);
            a0 = s2;
            jal(ctx, 0x570134u, gen::fn_sub_571088_00571088);
            v1 = v0;
        } else {
            // 0x00570098
            charge(ctx, 3);
            v0 = slti(s0, 17);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 64;
            if (cc) {
                // 0x005700c0
                charge(ctx, 2);
                cc = s0 == v0;  // the condition, before the delay slot changes it
                v0 = slti(s0, 65);
                if (cc) {
                    // 0x005700f8
                    charge(ctx, 5);
                    lw(a1, sp, 0x0);
                    a0 = s2;
                    jal(ctx, 0x5700FCu, gen::fn_sub_5703C0_005703c0);
                    v1 = v0;
                } else {
                    // 0x005700c8
                    charge(ctx, 2);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 128;
                    if (cc) {
                        // 0x005700e8
                        charge(ctx, 2);
                        lw(a1, sp, 0x0);
                        if (s0 == v0) {
                            // 0x00570110
                            charge(ctx, 4);
                            a0 = s2;
                            jal(ctx, 0x570110u, gen::fn_sub_570B98_00570b98);
                            v1 = v0;
                        } else {
                            // 0x005700f0
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x005700d0
                        charge(ctx, 3);
                        v0 = 32;
                        lw(a1, sp, 0x0);
                        if (s0 == v0) {
                            // 0x00570120
                            charge(ctx, 4);
                            a0 = s2;
                            jal(ctx, 0x570120u, gen::fn_sub_570CB8_00570cb8);
                            v1 = v0;
                        } else {
                            // 0x005700dc
                            charge(ctx, 2);
                        }
                    }
                }
            } else {
                // 0x005700a4
                charge(ctx, 3);
                v0 = 4;
                cc = s0 == v0;  // the condition, before the delay slot changes it
                v0 = 8;
                if (cc) {
                    // 0x00570158
                    charge(ctx, 4);
                    lw(a1, sp, 0x0);
                    a0 = s2;
                    jal(ctx, 0x57015Cu, gen::fn_sub_5745D0_005745d0);
                    v1 = v0;
                } else {
                    // 0x005700b0
                    charge(ctx, 2);
                    lw(a1, sp, 0x0);
                    if (s0 == v0) {
                        // 0x00570148
                        charge(ctx, 4);
                        a0 = s2;
                        jal(ctx, 0x570148u, gen::fn_sub_574068_00574068);
                        v1 = v0;
                    } else {
                        // 0x005700b8
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x00570168
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00570170_19;
        }
        lw(a1, sp, 0x0);
        // 0x00570190
        charge(ctx, 20);
        a0 = sp;
        a2 = sp;
        a3 = s4;
        a1 = subu(v1, a1);
        jal(ctx, 0x57019Cu, gen::fn_sub_563C28_00563c28);
        lw(v1, s1, 0);
        a2 = sp;
        a0 = s1;
        lw(v0, v1, 32);
        a1 = 0;
        jalr(ctx, 0x5701B4u, v0.u());
        lw(v1, s1, 0);
        a2 = s4;
        a0 = s1;
        lw(v0, v1, 28);
        a1 = 1;
        jalr(ctx, 0x5701CCu, v0.u());
        lw(a2, s3, 1272);
        if (a2 == 0) {
            continue;
        }
        lw(v1, s3, 1280);
        break;
    }
    // 0x005701fc (the shared epilogue, written out on this path)
    charge(ctx, 16);
    v0 = si(-2);
    lw(a0, s3, 1284);
    if (a2 == 0) v0 = 0;
    lw(a1, s3, 1276);
    v1 = addu(v1, a2);
    sw(v1, s3, 1280);
    a0 = addu(a0, a1);
    ld(s0, sp, 0x20);
    sw(a0, s3, 1284);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_00570170_19:
    charge(ctx, 8);
    lw(v1, s1, 0);
    a2 = sp;
    a0 = s1;
    lw(v0, v1, 28);
    a1 = 1;
    jalr(ctx, 0x570180u, v0.u());
    lw(a2, s3, 1272);
L_005701f8:
    charge(ctx, 1);
    lw(v1, s3, 1280);
    // 0x005701fc (the shared epilogue, written out on this path)
    charge(ctx, 16);
    v0 = si(-2);
    lw(a0, s3, 1284);
    if (a2 == 0) v0 = 0;
    lw(a1, s3, 1276);
    v1 = addu(v1, a2);
    sw(v1, s3, 1280);
    a0 = addu(a0, a1);
    ld(s0, sp, 0x20);
    sw(a0, s3, 1284);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_005701f4_22:
    charge(ctx, 1);
    lw(a2, s3, 1272);
    goto L_005701f8;
}

// 0x0057FA98 sub_57FA98 -- 32 bytes; frame 0x10: ra sp+0x0
// Returns the word +60 of the current thread-key block (__gthread_get_ee_key_use).
void sub_57FA98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0057fa98
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x57FAA0u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, v0, 60);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00580ED8 sub_580ED8 -- 52 bytes; frame 0x10: ra sp+0x0
// Copies $a1 bytes from the scratchpad (0x70000000 + $a0) to $a2 (memcpy); returns 0.
void sub_580ED8(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580ed8
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = a1;
    at = 0x70000000;
    a0 = addu(at, a0);
    sp = addiu(sp, -0x10);
    a1 = a0;
    a0 = a2;
    sd(ra, sp, 0x0);
    a2 = v0;
    jal(ctx, 0x580EF4u, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00580FB8 sub_580FB8 -- 48 bytes; frame 0x10: ra sp+0x0
// Copies $a1 bytes from $a0 to the scratchpad (0x70000000 + $a2) (memcpy); returns 0.
void sub_580FB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580fb8
    enter(ctx, 12);  // entry check point + this block's cycles
    v0 = a0;
    a0 = 0x70000000;
    a0 = addu(a0, a2);
    sp = addiu(sp, -0x10);
    a2 = a1;
    sd(ra, sp, 0x0);
    a1 = v0;
    jal(ctx, 0x580FD0u, gen::fn_memcpy_00521250);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005827C0 sub_5827C0 -- 24 bytes; frame 0x10: ra sp+0x0
// An error callback: tail-calls sub_585590($a1).
void sub_5827C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005827c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = a1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x005840D0 sub_5840D0 -- 192 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MWPLY entry of a file name ($a0 the player, $a1 the name): an invalid handle (sub_581798 != 1) -> "E1122633 ...
// handle is invalid."; NULL name -> "E10915B ... fname is NULL."; else enters it into the player's file list (+72,
// sub_55D400): on failure sets +4 = 4 and reports "E204021 ... Can't entry file '%s'" (sub_585590), on success
// increments the entry count +116.
void sub_5840D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005840d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5840E4u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -26536);  // "E1122633: mwPlyEntryFname: handle is invalid."
    if (v0 != v1) {
        // 0x005840fc
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00584110
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00584118
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -26488);  // "E10915B: mwPlyEntryFname: fname is NULL."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    lw(a0, s1, 72);
    // 0x00584138
    charge(ctx, 6);
    a1 = s0;
    jal(ctx, 0x584138u, gen::fn_sub_55D400_0055d400);
    a0 = 0x7D0000;
    a1 = s0;
    a0 = addiu(a0, -26440);  // "E204021: mwPlyEntryFname: Can't entry file'%s'"
    if (i64(v0) >= 0) {
        // 0x00584170
        charge(ctx, 8);
        lw(v0, s1, 116);
        ld(s0, sp, 0x0);
        v0 = addiu(v0, 1);
        ld(ra, sp, 0x10);
        sw(v0, s1, 116);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00584150
    charge(ctx, 7);
    v0 = 4;
    ld(s0, sp, 0x0);
    sw(v0, s1, 4);
    ld(ra, sp, 0x10);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x00584B18 sub_584B18 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Releases one reference of the thread-local work (sceLibgcc32GetErxEntries_19 +4); on the last one calls the table's
// release hook (WTLS_get_table_1 +4) when it is set.
void sub_584B18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584b18
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x584B24u, gen::fn_sceLibgcc32GetErxEntries_19_005851a0);
    s0 = v0;
    jal(ctx, 0x584B2Cu, gen::fn_WTLS_get_table_1_005851b0);
    a0 = v0;
    if (a0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584b40
        charge(ctx, 3);
        lw(v0, s0, 4);
        v1 = addiu(v0, -1);
        if (v0 != 0) {
            // 0x00584b4c
            charge(ctx, 2);
            sw(v1, s0, 4);
            if (v1 != 0) {
                goto L_00584b68;
            }
            // 0x00584b54
            charge(ctx, 3);
            lw(v0, a0, 4);
            if (v0 != 0) {
                // 0x00584b60
                charge(ctx, 2);
                jalr(ctx, 0x584B60u, v0.u());
                goto L_00584b68;
            }
            ld(s0, sp, 0x0);
            // 0x00584b6c (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_00584b68:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00584b6c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00584C38 sub_584C38 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Calls the thread table's hook +16 with $a0 when $a0 and the table (WTLS_get_table_1) and the hook are all non-zero.
void sub_584C38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584c38
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x584C44u, gen::fn_WTLS_get_table_1_005851b0);
    if (s0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584c54
        charge(ctx, 2);
        if (v0 == 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00584c5c
            charge(ctx, 3);
            lw(v0, v0, 16);
            if (v0 == 0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x00584c68
                charge(ctx, 3);
                a0 = s0;
                jalr(ctx, 0x584C68u, v0.u());
                ld(s0, sp, 0x0);
            }
        }
    }
    // 0x00584c74 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00584D30 sub_584D30 -- 104 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// When the library is initialised (sub_5851D0 == 1) and the thread table exists, returns its hook +28 called with
// *($a0 + 20) (0 when the hook is not set); else 0.
void sub_584D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00584d30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = 0;
    jal(ctx, 0x584D44u, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    cc = v0 != v1;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x00584d58
        charge(ctx, 4);
        jal(ctx, 0x584D58u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a0, s0, 20);
        if (v0 != 0) {
            // 0x00584d68
            charge(ctx, 3);
            lw(v0, v0, 28);
            if (v0 != 0) {
                // 0x00584d74
                charge(ctx, 3);
                jalr(ctx, 0x584D74u, v0.u());
                s1 = v0;
                goto L_00584d80;
            }
            v0 = s1;
            // 0x00584d84 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00584d80:
        charge(ctx, 1);
        v0 = s1;
    }
    // 0x00584d84 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00586FE0 sub_586FE0 -- 284 bytes; frame 0x60: s4 sp+0x30, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s5 sp+0x38, s6 sp+0x40, fp sp+0x50, s0 sp+0x10, s7 sp+0x48, ra sp+0x58
// Scans the buffer $a1 .. $a1 + $a2 in 18-byte steps for a byte with bit 7 set and checks the 18 bytes there with
// sub_54AC40, for the start offsets $a1, $a1 + 2, .. below $a1 + 36 (while each pass finds a candidate): returns the
// start whose valid candidate lies highest; when candidates were seen but none was valid, reports error 0xFF000C0A
// (sub_58BE40) and returns $a1; a pass without a candidate returns its start.
void sub_586FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00586fe0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s4, sp, 0x30);
    s4 = a1;
    sd(s1, sp, 0x18);
    s1 = s4;
    v1 = addiu(s1, 36);
    sd(s2, sp, 0x20);
    v0 = sltu(s1, v1);
    sd(s3, sp, 0x28);
    sd(s5, sp, 0x38);
    s5 = 0;
    sd(s6, sp, 0x40);
    s6 = 0;
    sd(fp, sp, 0x50);
    fp = a0;
    sd(s0, sp, 0x10);
    s2 = addu(s4, a2);
    sd(s7, sp, 0x48);
    s3 = 0;
    sd(ra, sp, 0x58);
    if (v0 != 0) {
        // 0x00587034
        charge(ctx, 3);
        s7 = v1;
        s3 = 0;
        for (;;) {
            // 0x00587040
            charge(ctx, 1);
            s0 = s1;
            for (;;) {
                // 0x00587044
                charge(ctx, 3);
                v0 = sltu(s0, s2);
                if (v0 == 0) {
                    break;
                }
                // 0x00587050
                charge(ctx, 3);
                lb(v0, s0, 0);
                if (i64(v0) < 0) {
                    goto L_0058705c_5;
                }
                s0 = addiu(s0, 18);
                backedge(ctx);
            }
        L_00587088:
            charge(ctx, 2);
            v0 = s1;
            if (s3 != 0) {
                // 0x00587090
                charge(ctx, 4);
                s1 = addiu(s1, 2);
                v0 = sltu(s1, s7);
                if (v0 == 0) {
                    break;
                }
                s3 = 0;
                backedge(ctx);
                continue;
            }
            // 0x005870cc (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(s0, sp, 0x10);
            ld(s1, sp, 0x18);
            ld(s2, sp, 0x20);
            ld(s3, sp, 0x28);
            ld(s4, sp, 0x30);
            ld(s5, sp, 0x38);
            ld(s6, sp, 0x40);
            ld(s7, sp, 0x48);
            ld(fp, sp, 0x50);
            ld(ra, sp, 0x58);
            sp = addiu(sp, 0x60);
            return;
        }
    }
    // 0x005870a0
    charge(ctx, 2);
    v0 = s1;
    if (s3 != 0) {
        // 0x005870a8
        charge(ctx, 2);
        if (s6 != 0) {
            s1 = s6;
            // 0x005870c8
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x005870b0
            charge(ctx, 6);
            a1 = lui(0xFF00);
            a0 = fp;
            a1 = a1 | 0xC0A;
            jal(ctx, 0x5870B8u, gen::fn_sub_58BE40_0058be40);
            v0 = s4;
        }
    }
    // 0x005870cc (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
    return;
L_0058705c_5:
    charge(ctx, 7);
    a0 = s0;
    a1 = 18;
    a2 = sp;
    s3 = 1;
    jal(ctx, 0x587068u, gen::fn_sub_54AC40_0054ac40);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = sltu(s5, s0);
    if (!cc) {
        // 0x00587078
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x00587080
            charge(ctx, 2);
            s5 = s0;
            s6 = s1;
        }
    }
    goto L_00587088;
}

// 0x00587618 sub_587618 -- 28 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_589CF0($a0, *($a0 + 8208), $a1).
void sub_587618(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587618
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a1;
    sd(ra, sp, 0x0);
    lw(a1, a0, 8208);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589CF0_00589cf0(ctx);  // tail call
}

// 0x00588168 sub_588168 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// MWPLY call-through 1: refuses with error 0xFF0001A1 (sub_58BE40) while the library is busy (sub_58C060); else, when
// the player passes the state check sub_599408($a0, 6), calls its interface's entry +4 (*($a0 + 8468)) with ($a0,
// $a1, $a2).
void sub_588168(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588168
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x588184u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    a1 = a1 | 0x1A1;
    if (v0 != 0) {
        // 0x0058819c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005881b8
    charge(ctx, 6);
    a1 = 6;
    jal(ctx, 0x5881B8u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    if (v0 != 0) {
        // 0x005881d0
        charge(ctx, 4);
        lw(v0, s0, 8468);
        lw(v1, v0, 4);
        jalr(ctx, 0x5881D8u, v1.u());
    }
    // 0x005881e0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005881F8 sub_5881F8 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MWPLY call-through 2: busy -> error 0xFF0001A2 and 0; else the interface entry +8 with ($a0, $a1) after the state
// check.
void sub_5881F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005881f8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x58820Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = s0;
    if (v0 == 0) {
        // 0x00588238
        charge(ctx, 5);
        a1 = 6;
        jal(ctx, 0x588238u, gen::fn_sub_599408_00599408);
        a0 = s0;
        a1 = s1;
        if (v0 != 0) {
            // 0x0058824c
            charge(ctx, 4);
            lw(v1, s0, 8468);
            lw(v0, v1, 8);
            jalr(ctx, 0x588254u, v0.u());
        }
    } else {
        // 0x00588220
        charge(ctx, 5);
        a0 = 0;
        a1 = a1 | 0x1A2;
        jal(ctx, 0x588224u, gen::fn_sub_58BE40_0058be40);
        v0 = 0;
    }
    // 0x0058825c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00588270 sub_588270 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MWPLY call-through 3: busy -> error 0xFF0001A3; else the interface entry +12 with ($a0, $a1) after the state check.
void sub_588270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588270
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x588284u, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00588298
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x1A3;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005882b0
    charge(ctx, 6);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x5882B4u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = s1;
    if (v0 != 0) {
        // 0x005882c8
        charge(ctx, 4);
        lw(v0, s0, 8468);
        lw(v1, v0, 12);
        jalr(ctx, 0x5882D0u, v1.u());
    }
    // 0x005882d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005882F0 sub_5882F0 -- 108 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// MWPLY call-through 4: busy -> error 0xFF0001A4 and 0; else the interface entry +16 with $a0 after the state check.
void sub_5882F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005882f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5882FCu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x1A4;
    if (v0 == 0) {
        // 0x00588328
        charge(ctx, 5);
        a0 = s0;
        a1 = 6;
        jal(ctx, 0x58832Cu, gen::fn_sub_599408_00599408);
        a0 = s0;
        if (v0 != 0) {
            // 0x0058833c
            charge(ctx, 4);
            lw(v1, s0, 8468);
            lw(v0, v1, 16);
            jalr(ctx, 0x588344u, v0.u());
        }
    } else {
        // 0x00588314
        charge(ctx, 4);
        jal(ctx, 0x588314u, gen::fn_sub_58BE40_0058be40);
        v0 = 0;
    }
    // 0x0058834c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058ABA0 sub_58ABA0 -- 216 bytes; frame 0x40: s0 sp+0x10, s2 sp+0x20, s1 sp+0x18, s3 sp+0x28, ra sp+0x30
// Copies up to 2048 bytes of $a0 into the work buffer at 0x9A6EF8 and scans it at each 4-byte step for a header
// (sub_586628); when one is found it fills the info record $a2 (+12 the handler table 0x7C9D78, +40 the header byte
// +7, +44 the big-endian word +8) and returns 1; else 0.
void sub_58ABA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058aba0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x9A0000;
    sd(s0, sp, 0x10);
    s0 = a1;
    v1 = slti(s0, 2049);
    a1 = 2048;
    if (v1 == 0) s0 = a1;
    a1 = a0;
    v0 = addiu(v0, 28408);  // &0x9A6EF8
    sd(s2, sp, 0x20);
    a0 = v0;
    s2 = a2;
    a2 = s0;
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    s1 = v0;
    jal(ctx, 0x58ABE0u, gen::fn_memcpy_00521250);
    v0 = 0;
    if (i64(s0) > 0) {
        // 0x0058abf0
        charge(ctx, 2);
        v0 = 0x7D0000;
        s3 = addiu(v0, -25224);  // "XhX"
        for (;;) {
            // 0x0058abf8
            charge(ctx, 7);
            a1 = s0;
            s0 = addiu(s0, -4);
            a0 = s1;
            a2 = sp;
            jal(ctx, 0x58AC04u, gen::fn_sub_586628_00586628);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (!cc) {
                goto L_0058ac14_3;
            }
            // 0x0058ac50
            charge(ctx, 2);
            s1 = addiu(s1, 4);
            if (i64(s0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0058ac58
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0058ac5c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    return;
L_0058ac14_3:
    charge(ctx, 15);
    sw(s3, s2, 12);
    lbu(v1, s1, 7);
    sb(v1, s2, 40);
    lbu(a1, s1, 9);
    lbu(v1, s1, 8);
    lbu(a0, s1, 10);
    a1 = sll(a1, 16);
    lbu(a2, s1, 11);
    v1 = sll(v1, 24);
    a0 = sll(a0, 8);
    v1 = v1 | a2;
    a0 = a0 | a1;
    v1 = v1 | a0;
    sw(v1, s2, 44);
    // 0x0058ac5c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0058AF20 sub_58AF20 -- 128 bytes; leaf frame (no stack)
// Unpacks the flag bytes 1..3 of a header ($a1) into eleven byte fields of $a0 (2-, 1- and 4-bit fields).
void sub_58AF20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0058af20
    enter(ctx, 32);  // entry check point + this block's cycles
    lbu(v0, a1, 3);
    lbu(a2, a1, 2);
    lbu(a3, a1, 1);
    t4 = srl(v0, 4);
    t0 = srl(a2, 2);
    t1 = srl(a2, 1);
    a1 = srl(a3, 1);
    a3 = a3 & 0x1;
    t2 = srl(v0, 3);
    t3 = srl(v0, 2);
    t5 = a2 & 0x1;
    a2 = srl(a2, 4);
    v1 = v0 & 0x3;
    v0 = srl(v0, 6);
    a1 = a1 & 0x3;
    t0 = t0 & 0x3;
    t1 = t1 & 0x1;
    t4 = t4 & 0x3;
    t2 = t2 & 0x1;
    t3 = t3 & 0x1;
    sb(v1, a0, 10);
    sb(a1, a0, 0);
    sb(a3, a0, 1);
    sb(a2, a0, 2);
    sb(t0, a0, 3);
    sb(t1, a0, 4);
    sb(t5, a0, 5);
    sb(v0, a0, 6);
    sb(t4, a0, 7);
    sb(t2, a0, 8);
    sb(t3, a0, 9);
}

// 0x0058CA60 sub_58CA60 -- 64 bytes; leaf frame (no stack)
// Returns 1 when the $a1 bytes at $a0 are all zero, else 0.
void sub_58CA60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0058ca60
    enter(ctx, 2);  // entry check point + this block's cycles
    a2 = 0;
    if (i64(a1) > 0) {
        // 0x0058ca68
        charge(ctx, 2);
        lbu(v1, a0, 0);
        for (;;) {
            // 0x0058ca70
            charge(ctx, 3);
            a0 = addiu(a0, 1);
            v0 = 0;
            if (v1 != 0) {
                break;
            }
            // 0x0058ca7c
            charge(ctx, 6);
            a2 = addiu(a2, 1);
            v0 = slt(a2, a1);
            if (v0 == 0) {
                goto L_0058ca94;
            }
            lbu(v1, a0, 0);
            backedge(ctx);
        }
        // 0x0058ca98 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0058ca94:
    charge(ctx, 1);
    v0 = 1;
    // 0x0058ca98 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0058CAA0 sub_58CAA0 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Checks a position against the current buffer (sub_58CB00): when the buffer is active (+0), or idle (+16 and +20
// both 0), returns $a1 == +8 + +12; else 0.
void sub_58CAA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058caa0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x58CAACu, gen::fn_sub_58CB00_0058cb00);
    a0 = v0;
    lw(v0, a0, 0);
    if (v0 != 0) {
        lw(v1, a0, 12);
    } else {
        // 0x0058cac4
        charge(ctx, 3);
        lw(v0, a0, 16);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0058cad0
            charge(ctx, 3);
            lw(v0, a0, 20);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x0058cadc
                charge(ctx, 1);
                lw(v1, a0, 12);
                goto L_0058cae0;
            }
        }
        // 0x0058caf0 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058cae0:
    charge(ctx, 4);
    lw(v0, a0, 8);
    v0 = addu(v0, v1);
    v0 = s0 ^ v0;
    v0 = sltiu(v0, 1);
    // 0x0058caf0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058CCA0 sub_58CCA0 -- 112 bytes; frame 0x30: s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, ra sp+0x20
// Runs sub_58D258($a0, $a4, $a5); when it returns 1 and the callback $a1 is set, calls $a1($a2, $a3) and returns 1;
// otherwise returns sub_58D258's result.
void sub_58CCA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058cca0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    a1 = t0;
    a2 = t1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    s1 = a3;
    jal(ctx, 0x58CCC8u, gen::fn_sub_58D258_0058d258);
    s0 = v0;
    v0 = 1;
    if (s0 != v0) {
        v0 = s0;
    } else {
        // 0x0058cce0
        charge(ctx, 2);
        a0 = s3;
        if (s2 != 0) {
            // 0x0058cce8
            charge(ctx, 2);
            a1 = s1;
            jalr(ctx, 0x58CCE8u, s2.u());
        }
        // 0x0058ccf0
        charge(ctx, 1);
        v0 = s0;
    }
    // 0x0058ccf4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058D300 sub_58D300 -- 108 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Reads through a stream joint ($a0): gets a chunk of up to $a2 bytes (vtable +24), copies it to $a1 (sub_575410),
// puts it back as consumed (vtable +32) and returns the chunk size.
void sub_58D300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d300
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(ra, sp, 0x20);
    a3 = sp;
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a1 = 0;
    jalr(ctx, 0x58D324u, v0.u());
    a1 = s1;
    lw(a0, sp, 0x0);
    link(ctx, 0x58D334u);  // $ra first: the delay slot below depends on it
    lw(a2, sp, 0x4);
    call(ctx, gen::fn_sub_575410_00575410);
    lw(v1, s0, 0);
    a0 = s0;
    a1 = 1;
    lw(v0, v1, 32);
    a2 = sp;
    jalr(ctx, 0x58D34Cu, v0.u());
    lw(v0, sp, 0x4);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058D5E8 sub_58D5E8 -- 20 bytes; leaf frame (no stack)
// Increments the counter +32 of the object at *($a0 + 8060).
void sub_58D5E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0058d5e8
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, 8060);
    lw(v0, v1, 32);
    v0 = addiu(v0, 1);
    sw(v0, v1, 32);
}

// 0x0058EFB8 sub_58EFB8 -- 28 bytes; frame 0x10: ra sp+0x0
// Tail-calls sub_589CF0($a0, *($a0 + 8140), $a1).
void sub_58EFB8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058efb8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a1;
    sd(ra, sp, 0x0);
    lw(a1, a0, 8140);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589CF0_00589cf0(ctx);  // tail call
}

// 0x0058FB28 sub_58FB28 -- 180 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Lazily computes a player offset (+8152 = sub_589530($a0, +8136) + 4 when negative) and, when the record at +3524 is
// unset (+3560 < 0), copies the 44-byte record at +3480 into it.
void sub_58FB28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fb28
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = addiu(s1, 3524);
    sd(ra, sp, 0x18);
    s0 = addiu(s1, 8120);
    lw(v0, s0, 32);
    lw(a1, s0, 16);
    if (i64(v0) < 0) {
        // 0x0058fb54
        charge(ctx, 4);
        jal(ctx, 0x58FB54u, gen::fn_sub_589530_00589530);
        v0 = addiu(v0, 4);
        sw(v0, s0, 32);
    }
    // 0x0058fb64
    charge(ctx, 3);
    lw(v0, s2, 36);
    ld(s0, sp, 0x0);
    if (i64(v0) < 0) {
        // 0x0058fb70
        charge(ctx, 22);
        ldl(v0, s1, 3487);
        ldr(v0, s1, 3480);
        ldl(v1, s1, 3495);
        ldr(v1, s1, 3488);
        ldl(a0, s1, 3503);
        ldr(a0, s1, 3496);
        ldl(a1, s1, 3511);
        ldr(a1, s1, 3504);
        sdl(v0, s2, 7);
        sdr(v0, s2, 0);
        sdl(v1, s2, 15);
        sdr(v1, s2, 8);
        sdl(a0, s2, 23);
        sdr(a0, s2, 16);
        sdl(a1, s2, 31);
        sdr(a1, s2, 24);
        ldl(v0, s1, 3519);
        ldr(v0, s1, 3512);
        lw(v1, s1, 3520);
        sdl(v0, s2, 39);
        sdr(v0, s2, 32);
        sw(v1, s2, 40);
    }
    // 0x0058fbc8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058FBE0 sub_58FBE0 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// When sub_58FC30 does not return -1, calls sub_58FE08($a0, $a1) and returns 0; else -1.
void sub_58FBE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fbe0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x58FBF4u, gen::fn_sub_58FC30_0058fc30);
    v1 = si(-1);
    a0 = s0;
    a1 = s1;
    if (v0 != v1) {
        // 0x0058fc0c
        charge(ctx, 3);
        jal(ctx, 0x58FC0Cu, gen::fn_sub_58FE08_0058fe08);
        v0 = 0;
    }
    // 0x0058fc18 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00591B18 sub_591B18 -- 240 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s6 sp+0x30, s1 sp+0x8, s5 sp+0x28, ra sp+0x38
// Decodes one unit from the input buffer of a player ($a0: +8128 the decoder): measures the bytes the decoder
// (sub_579080) consumes from stream $a1 (sub_562E10 before and after), commits them (sub_58FF70, sub_58FEC8); on
// success marks the decoder (+364 = 1 when byte +228 is 0) and advances (sub_597168($a0, 1, +164)), returning 0; else
// the error.
void sub_591B18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00591b18
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    sd(s1, sp, 0x8);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    lw(s5, s2, 8128);
    link(ctx, 0x591B48u);  // $ra first: the delay slot below depends on it
    lw(s1, s5, 0);
    call(ctx, gen::fn_sub_591C08_00591c08);
    a0 = s0;
    a2 = 1;
    a1 = 0;
    s6 = addiu(s5, 140);
    jal(ctx, 0x591B5Cu, gen::fn_sub_562E10_00562e10);
    a0 = s1;
    a1 = s0;
    s4 = v0;
    jal(ctx, 0x591B6Cu, gen::fn_sub_579080_00579080);
    a0 = s0;
    a1 = 0;
    a2 = 1;
    s3 = v0;
    jal(ctx, 0x591B80u, gen::fn_sub_562E10_00562e10);
    s1 = subu(v0, s4);
    a3 = lui(0xFF00);
    a0 = s2;
    a1 = s3;
    a2 = s1;
    a3 = a3 | 0xF07;
    jal(ctx, 0x591B9Cu, gen::fn_sub_58FF70_0058ff70);
    a0 = s2;
    s0 = v0;
    a1 = s1;
    jal(ctx, 0x591BACu, gen::fn_sub_58FEC8_0058fec8);
    v0 = s0;
    a0 = s2;
    a1 = 1;
    if (s0 == 0) {
        // 0x00591bc4
        charge(ctx, 3);
        lb(v0, s6, 88);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            // 0x00591bd0
            charge(ctx, 1);
            sw(v0, s5, 364);
        }
        // 0x00591bd4
        charge(ctx, 3);
        link(ctx, 0x591BD4u);  // $ra first: the delay slot below depends on it
        lw(a2, s6, 24);
        call(ctx, gen::fn_sub_597168_00597168);
        v0 = 0;
    }
    // 0x00591be0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x005957D8 sub_5957D8 -- 140 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MWPLY set a mode word +80 ($a1): busy -> error 0xFF000142; else, when $a1 or the old value is non-zero, stores it,
// applies it (sub_595868($a0, 0 / 1 / 2)) and sets +68 = 1.
void sub_5957D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005957d8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5957ECu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0x142;
    a2 = 1;
    if (v0 != 0) {
        // 0x00595808
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00595820
    charge(ctx, 4);
    lw(a0, s0, 80);
    v1 = 2;
    if (a0 != 0) a2 = v1;
    if (s1 == 0) {
        // 0x00595830
        charge(ctx, 2);
        a2 = 0;
        if (a0 != 0) {
            goto L_00595838;
        }
        // 0x00595850 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_00595838:
    charge(ctx, 6);
    sw(s1, s0, 80);
    a1 = a2;
    a0 = s0;
    jal(ctx, 0x595840u, gen::fn_sub_595868_00595868);
    v1 = 1;
    sw(v1, s0, 68);
    // 0x00595850 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00599418 sub_599418 -- 212 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// MWPLY get a 64-byte info block: busy -> error 0xFF000114; else copies $a0 + 2316 .. + 2380 to $a1.
void sub_599418(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599418
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x59942Cu, gen::fn_sub_58C060_0058c060);
    a1 = lui(0xFF00);
    a0 = 0;
    if (v0 != 0) {
        // 0x00599440
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x114;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00599458
    charge(ctx, 37);
    ldl(v1, s0, 2323);
    ldr(v1, s0, 2316);
    ldl(a0, s0, 2331);
    ldr(a0, s0, 2324);
    ldl(a1, s0, 2339);
    ldr(a1, s0, 2332);
    ldl(a2, s0, 2347);
    ldr(a2, s0, 2340);
    sdl(v1, s1, 7);
    sdr(v1, s1, 0);
    sdl(a0, s1, 15);
    sdr(a0, s1, 8);
    sdl(a1, s1, 23);
    sdr(a1, s1, 16);
    sdl(a2, s1, 31);
    sdr(a2, s1, 24);
    ldl(v1, s0, 2355);
    ldr(v1, s0, 2348);
    ldl(a0, s0, 2363);
    ldr(a0, s0, 2356);
    ldl(a1, s0, 2371);
    ldr(a1, s0, 2364);
    ldl(a2, s0, 2379);
    ldr(a2, s0, 2372);
    sdl(v1, s1, 39);
    sdr(v1, s1, 32);
    sdl(a0, s1, 47);
    sdr(a0, s1, 40);
    sdl(a1, s1, 55);
    sdr(a1, s1, 48);
    sdl(a2, s1, 63);
    sdr(a2, s1, 56);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00599D70 sub_599D70 -- 148 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Fills the time / position pair ($a2, $a3) from the record $a1 by the player state (sub_599408($a0, 71)): state 71
// -> (+680 - +720, *0x7B4728); else (+732 - +720, +736).
void sub_599D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00599d70
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = a1;
    a1 = 71;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = addiu(v0, 18208);  // &0x7B4720
    sd(ra, sp, 0x20);
    s1 = a2;
    jal(ctx, 0x599D9Cu, gen::fn_sub_599408_00599408);
    v1 = 1;
    if (v0 != v1) {
        // 0x00599dd0
        charge(ctx, 6);
        lw(v0, s0, 732);
        lw(v1, s0, 720);
        v0 = subu(v0, v1);
        sw(v0, s1, 0);
        lw(v1, s0, 736);
        sw(v1, s2, 0);
    } else {
        // 0x00599db0
        charge(ctx, 7);
        lw(v0, s0, 720);
        lw(v1, s0, 680);
        v1 = subu(v1, v0);
        sw(v1, s1, 0);
        lw(v0, s3, 8);
        sw(v0, s2, 0);
    }
    // 0x00599de8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0059BE90 sub_59BE90 -- 8 bytes; leaf frame (no stack)
// A setter: *($a0 + 12) = $a1.
void sub_59BE90(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0059be90
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, 12);
}

// 0x0059CAC8 sub_59CAC8 -- 8 bytes; leaf frame (no stack)
// Returns 1 (a stub interface entry).
void sub_59CAC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0059cac8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0059CDE0 sub_59CDE0 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Returns 1 when the player is not in state 15 (sub_599408) or sub_59B300 reports true, else 0.
void sub_59CDE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059cde0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 15;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x59CDF0u, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 != 0) {
        // 0x0059ce08
        charge(ctx, 3);
        jal(ctx, 0x59CE08u, gen::fn_sub_59B300_0059b300);
        v0 = sltu(0, v0);
    } else {
        // 0x0059ce00
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0059ce14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059FA38 sub_59FA38 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Library finish: while the init count (0x7B4918) is positive, finishes the layers (sub_5A02C0, sub_59E800,
// sub_5A0250 and the entry 0x56DE50 inside sub_56DE28) and decrements it.
void sub_59FA38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0059fa38
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 18712);  // &0x7B4918
    lw(v1, s0, 0);  // 0x7B4918
    sd(ra, sp, 0x8);
    if (i64(v1) > 0) {
        // 0x0059fa54
        charge(ctx, 11);
        jal(ctx, 0x59FA54u, gen::fn_sub_5A02C0_005a02c0);
        jal(ctx, 0x59FA5Cu, gen::fn_sub_59E800_0059e800);
        jal(ctx, 0x59FA64u, gen::fn_sub_5A0250_005a0250);
        link(ctx, 0x59FA6Cu);
        gen::fn_sub_56DE28_0056de28_at_0056de50(ctx);
        lw(v0, s0, 0);
        v0 = addiu(v0, -1);
        sw(v0, s0, 0);
    }
    // 0x0059fa80 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0059FDB8 sub_59FDB8 -- 8 bytes; leaf frame (no stack)
// Returns the word +4 of $a0.
void sub_59FDB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0059fdb8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 4);
}

// 0x005A1380 sub_5A1380 -- 64 bytes; frame 0x10: ra sp+0x0
// Returns 1 when $a0 is non-NULL, $a1 >= 0 and the byte $a0 + 19 matches the one-character tag at 0x7CABF0
// (strncmp(.., .., 1) == 0), else 0.
void sub_5A1380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005a1380
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005a138c
        charge(ctx, 2);
        cc = i64(a1) >= 0;  // the condition, before the delay slot changes it
        a1 = 0x7D0000;
        if (!cc) {
            goto L_005a1394;
        }
        // 0x005a13a0
        charge(ctx, 5);
        a0 = addiu(a0, 19);
        a1 = addiu(a1, -21520);
        a2 = 1;
        jal(ctx, 0x5A13A8u, gen::fn_strncmp_00524670);
        v0 = sltiu(v0, 1);
        // 0x005a13b4 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_005a1394:
    charge(ctx, 2);
    v0 = 0;
    // 0x005a13b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game

// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).
