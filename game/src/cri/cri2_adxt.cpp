// Phase 5 slice cri2: ADXT, the ADX stream player (0x547BC0-0x54CA08) -- 16 handles of 200 bytes at 0x787570
// (cri2::adxt). A player owns a decoder (ADXSJD), an output (PS2RNA), a file streamer (ADXSTM) or a memory / caller
// joint as its source, and the joints between them; the server runs its state machine once per call:
//   1 opening -- sub_54BCD8: open the source, wait for the decoder to read the header, set up the output,
//                install the loop trap (or the end trap), go to 2;
//   2 buffering -- sub_54C100: wait until enough PCM is queued (or the decoder ended), start the output, go to 3;
//   3 playing -- sub_54C288: with looping off, stop the decoder at the stop sample; when every output joint is
//                nearly empty after the decoder ended, go to 4;
//   4 decode end -- sub_54C370: pad the output with silence until it has played out, stop the output, go to 5;
//   5 play end -- sub_54C578: nothing; 6 error -- set by the opening state or the error check sub_54C8C0.
// The public entry points are lock wrappers (sub_539848 / sub_539850, empty in retail) around the adxt_* bodies.
// p3fes_handgen bodies with a role comment per function and the handle's fields named (cri2::adxt) where one
// register holds the handle for the whole body; every statement, charge and check point is the generator's.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/cri2.h"

namespace p3fes::recomp_gen {
void fn___env_lock_0_0054a630(p3fes::EEContext&);
void fn___env_lock_7_00541cb8(p3fes::EEContext&);
void fn___env_unlock_0_0054a638(p3fes::EEContext&);
void fn__get_peer_or_sock_name_3_0053a358(p3fes::EEContext&);
void fn_coshl_1_00541a90(p3fes::EEContext&);
void fn_cosl_1_00541a78(p3fes::EEContext&);
void fn_get_bufs_2_0054a400(p3fes::EEContext&);
void fn_hypotf_1_00541ac0(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_r_lock_def_free_0_00541cc8(p3fes::EEContext&);
void fn_sceInsockBind_2_00548b38(p3fes::EEContext&);
void fn_sceInsockListen_2_00549160(p3fes::EEContext&);
void fn_sceInsockSetsockopt_2_0054a928(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_535888_00535888(p3fes::EEContext&);
void fn_sub_5358E0_005358e0(p3fes::EEContext&);
void fn_sub_535A80_00535a80(p3fes::EEContext&);
void fn_sub_535DA8_00535da8(p3fes::EEContext&);
void fn_sub_539818_00539818(p3fes::EEContext&);
void fn_sub_539830_00539830(p3fes::EEContext&);
void fn_sub_539848_00539848(p3fes::EEContext&);
void fn_sub_539850_00539850(p3fes::EEContext&);
void fn_sub_5399B8_005399b8(p3fes::EEContext&);
void fn_sub_53AE08_0053ae08(p3fes::EEContext&);
void fn_sub_53AE60_0053ae60(p3fes::EEContext&);
void fn_sub_53AFD8_0053afd8(p3fes::EEContext&);
void fn_sub_53DD10_0053dd10(p3fes::EEContext&);
void fn_sub_5419F8_005419f8(p3fes::EEContext&);
void fn_sub_541A10_00541a10(p3fes::EEContext&);
void fn_sub_541AD8_00541ad8(p3fes::EEContext&);
void fn_sub_541B28_00541b28(p3fes::EEContext&);
void fn_sub_541B58_00541b58(p3fes::EEContext&);
void fn_sub_541B70_00541b70(p3fes::EEContext&);
void fn_sub_541B88_00541b88(p3fes::EEContext&);
void fn_sub_541BA0_00541ba0(p3fes::EEContext&);
void fn_sub_541BD0_00541bd0(p3fes::EEContext&);
void fn_sub_541E28_00541e28(p3fes::EEContext&);
void fn_sub_541FA8_00541fa8(p3fes::EEContext&);
void fn_sub_542008_00542008(p3fes::EEContext&);
void fn_sub_542010_00542010(p3fes::EEContext&);
void fn_sub_542060_00542060(p3fes::EEContext&);
void fn_sub_5420A0_005420a0(p3fes::EEContext&);
void fn_sub_5420D0_005420d0(p3fes::EEContext&);
void fn_sub_542100_00542100(p3fes::EEContext&);
void fn_sub_542BC8_00542bc8(p3fes::EEContext&);
void fn_sub_542F00_00542f00(p3fes::EEContext&);
void fn_sub_542F60_00542f60(p3fes::EEContext&);
void fn_sub_542F68_00542f68(p3fes::EEContext&);
void fn_sub_542F88_00542f88(p3fes::EEContext&);
void fn_sub_5430A8_005430a8(p3fes::EEContext&);
void fn_sub_5430B8_005430b8(p3fes::EEContext&);
void fn_sub_5430C8_005430c8(p3fes::EEContext&);
void fn_sub_5430D8_005430d8(p3fes::EEContext&);
void fn_sub_5430E8_005430e8(p3fes::EEContext&);
void fn_sub_543100_00543100(p3fes::EEContext&);
void fn_sub_543118_00543118(p3fes::EEContext&);
void fn_sub_543130_00543130(p3fes::EEContext&);
void fn_sub_543148_00543148(p3fes::EEContext&);
void fn_sub_543178_00543178(p3fes::EEContext&);
void fn_sub_5431A8_005431a8(p3fes::EEContext&);
void fn_sub_5431D8_005431d8(p3fes::EEContext&);
void fn_sub_5431F0_005431f0(p3fes::EEContext&);
void fn_sub_543220_00543220(p3fes::EEContext&);
void fn_sub_543238_00543238(p3fes::EEContext&);
void fn_sub_543268_00543268(p3fes::EEContext&);
void fn_sub_5432C0_005432c0(p3fes::EEContext&);
void fn_sub_5433A0_005433a0(p3fes::EEContext&);
void fn_sub_5433A8_005433a8(p3fes::EEContext&);
void fn_sub_545FC8_00545fc8(p3fes::EEContext&);
void fn_sub_546058_00546058(p3fes::EEContext&);
void fn_sub_5460E0_005460e0(p3fes::EEContext&);
void fn_sub_546270_00546270(p3fes::EEContext&);
void fn_sub_546368_00546368(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_546498_00546498(p3fes::EEContext&);
void fn_sub_5465A0_005465a0(p3fes::EEContext&);
void fn_sub_5466B8_005466b8(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_546FA0_00546fa0(p3fes::EEContext&);
void fn_sub_547BC0_00547bc0(p3fes::EEContext&);
void fn_sub_547C18_00547c18(p3fes::EEContext&);
void fn_sub_547FD0_00547fd0(p3fes::EEContext&);
void fn_sub_547FF8_00547ff8(p3fes::EEContext&);
void fn_sub_548020_00548020(p3fes::EEContext&);
void fn_sub_548048_00548048(p3fes::EEContext&);
void fn_sub_548078_00548078(p3fes::EEContext&);
void fn_sub_548318_00548318(p3fes::EEContext&);
void fn_sub_548410_00548410(p3fes::EEContext&);
void fn_sub_5484E0_005484e0(p3fes::EEContext&);
void fn_sub_548520_00548520(p3fes::EEContext&);
void fn_sub_5485D8_005485d8(p3fes::EEContext&);
void fn_sub_548678_00548678(p3fes::EEContext&);
void fn_sub_5486A8_005486a8(p3fes::EEContext&);
void fn_sub_548768_00548768(p3fes::EEContext&);
void fn_sub_5487A0_005487a0(p3fes::EEContext&);
void fn_sub_5489A0_005489a0(p3fes::EEContext&);
void fn_sub_548AE8_00548ae8(p3fes::EEContext&);
void fn_sub_548EB8_00548eb8(p3fes::EEContext&);
void fn_sub_548EF0_00548ef0(p3fes::EEContext&);
void fn_sub_548F40_00548f40(p3fes::EEContext&);
void fn_sub_548F78_00548f78(p3fes::EEContext&);
void fn_sub_548FC8_00548fc8(p3fes::EEContext&);
void fn_sub_5491B0_005491b0(p3fes::EEContext&);
void fn_sub_549480_00549480(p3fes::EEContext&);
void fn_sub_5494C0_005494c0(p3fes::EEContext&);
void fn_sub_5497A0_005497a0(p3fes::EEContext&);
void fn_sub_5497B0_005497b0(p3fes::EEContext&);
void fn_sub_5497E0_005497e0(p3fes::EEContext&);
void fn_sub_5497F8_005497f8(p3fes::EEContext&);
void fn_sub_549838_00549838(p3fes::EEContext&);
void fn_sub_549BB0_00549bb0(p3fes::EEContext&);
void fn_sub_549DE8_00549de8(p3fes::EEContext&);
void fn_sub_549E28_00549e28(p3fes::EEContext&);
void fn_sub_549EA0_00549ea0(p3fes::EEContext&);
void fn_sub_549EC8_00549ec8(p3fes::EEContext&);
void fn_sub_549FF8_00549ff8(p3fes::EEContext&);
void fn_sub_54A030_0054a030(p3fes::EEContext&);
void fn_sub_54A138_0054a138(p3fes::EEContext&);
void fn_sub_54A178_0054a178(p3fes::EEContext&);
void fn_sub_54A3C0_0054a3c0(p3fes::EEContext&);
void fn_sub_54A530_0054a530(p3fes::EEContext&);
void fn_sub_54A568_0054a568(p3fes::EEContext&);
void fn_sub_54A968_0054a968(p3fes::EEContext&);
void fn_sub_54B088_0054b088(p3fes::EEContext&);
void fn_sub_54B0D8_0054b0d8(p3fes::EEContext&);
void fn_sub_54B230_0054b230(p3fes::EEContext&);
void fn_sub_54B2E8_0054b2e8(p3fes::EEContext&);
void fn_sub_54B328_0054b328(p3fes::EEContext&);
void fn_sub_54B4D0_0054b4d0(p3fes::EEContext&);
void fn_sub_54B520_0054b520(p3fes::EEContext&);
void fn_sub_54B690_0054b690(p3fes::EEContext&);
void fn_sub_54B988_0054b988(p3fes::EEContext&);
void fn_sub_54B9F0_0054b9f0(p3fes::EEContext&);
void fn_sub_54BCD8_0054bcd8(p3fes::EEContext&);
void fn_sub_54C100_0054c100(p3fes::EEContext&);
void fn_sub_54C288_0054c288(p3fes::EEContext&);
void fn_sub_54C370_0054c370(p3fes::EEContext&);
void fn_sub_54C578_0054c578(p3fes::EEContext&);
void fn_sub_54C8C0_0054c8c0(p3fes::EEContext&);
void fn_sub_54C940_0054c940(p3fes::EEContext&);
void fn_sub_54C9D8_0054c9d8(p3fes::EEContext&);
void fn_sub_54CA08_0054ca08(p3fes::EEContext&);
void fn_sub_55D2A0_0055d2a0(p3fes::EEContext&);
void fn_sub_55D3A8_0055d3a8(p3fes::EEContext&);
void fn_sub_55D3F8_0055d3f8(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_55D790_0055d790(p3fes::EEContext&);
void fn_sub_560DB8_00560db8(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_563C28_00563c28(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace cri2;

// 0x00547BC0 sub_547BC0 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// create (locked). [ADXT_Create]
void sub_547BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547bc0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x547BDCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x547BECu, gen::fn_sub_547C18_00547c18);
    s0 = v0;
    jal(ctx, 0x547BF4u, gen::fn_sub_539850_00539850);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00547C18 sub_547C18 -- 792 bytes; frame 0x30: s0 sp+0x0, s3 sp+0x18, s2 sp+0x10, s1 sp+0x8, ra sp+0x20
// create a player: take a free handle, lay the work area out (PCM buffers, input ring, name buffer), create the ring
//   joint, the streamer, the output joints, the decoder, the output and the list streamer. [adxt_Create]
void sub_547C18(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00547c18
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = addiu(a1, 63);
    v1 = si(-64);
    sd(s0, sp, 0x0);
    s0 = v0 & v1;
    sd(s3, sp, 0x18);
    v0 = subu(s0, a1);
    s3 = a0;
    sd(s2, sp, 0x10);
    s2 = subu(a2, v0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    if (i64(s3) >= 0) {
        // 0x00547c4c
        charge(ctx, 2);
        if (a1 == 0) {
            a0 = 0x7C0000;
        L_00547c60:
            charge(ctx, 2);
            a0 = addiu(a0, 10088);
        L_00547cb0:
            charge(ctx, 4);
            jal(ctx, 0x547CB0u, gen::fn_sub_53AE08_0053ae08);
            v0 = 0;
        } else {
            // 0x00547c54
            charge(ctx, 2);
            a0 = 0;
            if (i64(a2) < 0) {
                goto L_00547c5c;
            }
            for (;;) {
                // 0x00547c68
                charge(ctx, 3);
                v0 = slti(a0, 16);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 16;
                if (cc) {
                    break;
                }
                // 0x00547c74
                charge(ctx, 10);
                v0 = sll(a0, 1);
                v0 = addu(v0, a0);
                v0 = sll(v0, 3);
                v0 = addu(v0, a0);
                v0 = sll(v0, 3);
                v1 = 0x780000;
                v1 = addu(v1, v0);
                lb(v1, v1, 30064);
                if (v1 == 0) {
                    goto L_00547c9c_7;
                }
                a0 = addiu(a0, 1);
                backedge(ctx);
            }
        L_00547ca0:
            charge(ctx, 2);
            cc = a0 != v0;  // the condition, before the delay slot changes it
            v0 = sll(a0, 1);
            if (!cc) {
                // 0x00547ca8
                charge(ctx, 2);
                a0 = 0x7C0000;
                a0 = addiu(a0, 10128);  // "E03100801 adxt_Create: Too many handles.\n"
                goto L_00547cb0;
            }
            // 0x00547cc0
            charge(ctx, 44);
            a1 = 0;
            v0 = addu(v0, a0);
            a2 = 200;
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            v0 = sll(v0, 3);
            s1 = 0x780000;
            s1 = addiu(s1, 30064);  // &0x787570
            s1 = addu(s1, v0);
            a0 = s1;
            jal(ctx, 0x547CE4u, gen::fn_memset_00521408);
            sb(s3, s1, 3);
            v0 = sll(s3, 6);
            t2 = 36;
            v0 = addu(v0, s3);
            t0 = 8192;
            v0 = sll(v0, 2);
            t1 = 8288;
            v0 = subu(v0, s3);
            a2 = 36;
            v0 = sll(v0, 6);
            sw(s0, s1, 44);
            a1 = subu(s2, v0);
            v0 = addu(s0, v0);
            v1 = addiu(a1, -292);
            a1 = addiu(a1, 1755);
            a3 = slti(v1, 0);
            a0 = v0;
            if (a3 != 0) v1 = a1;
            sw(v0, s1, 32);
            v1 = sra(v1, 11);
            sw(t0, s1, 48);
            v1 = sll(v1, 11);
            sw(t1, s1, 52);
            a3 = addu(v1, t2);
            a1 = v1;
            v0 = addu(v0, a3);
            sw(v1, s1, 36);
            sw(v0, s1, 176);
            sw(t2, s1, 40);
            link(ctx, 0x547D60u);  // $ra first: the delay slot below depends on it
            sw(zero, s1, 20);
            call(ctx, gen::fn_sub_562388_00562388);
            sw(v0, s1, 16);
            if (v0 != 0) {
                // 0x00547d70
                charge(ctx, 5);
                a0 = v0;
                a1 = 0;
                jal(ctx, 0x547D74u, gen::fn_sub_545FC8_00545fc8);
                sw(v0, s1, 8);
                if (v0 == 0) {
                    goto L_00547e18;
                }
                // 0x00547d84
                charge(ctx, 2);
                s0 = 0;
                if (i64(s3) > 0) {
                    // 0x00547d8c
                    charge(ctx, 3);
                    s2 = addiu(s1, 24);
                    lw(a2, s1, 52);
                    for (;;) {
                        // 0x00547d98
                        charge(ctx, 14);
                        lw(a1, s1, 48);
                        mult(a0, a2, s0);
                        s0 = addiu(s0, 1);
                        lw(v0, s1, 44);
                        a2 = subu(a2, a1);
                        a2 = sll(a2, 1);
                        a1 = sll(a1, 1);
                        a0 = sll(a0, 1);
                        a0 = addu(v0, a0);
                        jal(ctx, 0x547DB8u, gen::fn_sub_562388_00562388);
                        v1 = slt(s0, s3);
                        sw(v0, s2, 0);
                        s2 = addiu(s2, 4);
                        if (v0 == 0) {
                            goto L_00547e18;
                        }
                        // 0x00547dd0
                        charge(ctx, 2);
                        if (v1 == 0) {
                            break;
                        }
                        lw(a2, s1, 52);
                        backedge(ctx);
                    }
                }
                // 0x00547dd8
                charge(ctx, 7);
                s0 = addiu(s1, 24);
                lw(a0, s1, 16);
                a1 = s3;
                a2 = s0;
                jal(ctx, 0x547DE4u, gen::fn_sub_541E28_00541e28);
                sw(v0, s1, 4);
                if (v0 == 0) {
                    goto L_00547e18;
                }
                // 0x00547df4
                charge(ctx, 5);
                a0 = s0;
                a1 = s3;
                jal(ctx, 0x547DF8u, gen::fn_sub_5419F8_005419f8);
                sw(v0, s1, 12);
                if (v0 == 0) {
                    goto L_00547e18;
                }
                // 0x00547e08
                charge(ctx, 4);
                link(ctx, 0x547E08u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, 16);
                call(ctx, gen::fn_sub_55D2A0_0055d2a0);
                sw(v0, s1, 148);
                if (v0 == 0) {
                    goto L_00547e18;
                }
                // 0x00547e28
                charge(ctx, 27);
                lw(a1, s1, 8);
                a0 = v0;
                jal(ctx, 0x547E2Cu, gen::fn_sub_55D3F8_0055d3f8);
                jal(ctx, 0x547E34u, gen::fn_sub_539818_00539818);
                lw(v0, s1, 36);
                a2 = 0x790000;
                at = 0x3F590000;
                at = at | 0x9999;
                mtc1(at, f1);
                v1 = slti(v0, 0);
                a0 = addiu(v0, 2047);
                if (v1 != 0) v0 = a0;
                lw(a1, a2, 15132);  // 0x793B1C
                v0 = sra(v0, 11);
                sh(zero, s1, 64);
                v1 = sll(v0, 16);
                sh(v0, s1, 60);
                v1 = sra(v1, 16);
                sw(a1, s1, 56);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f1);
                cvt_w_s(f1, f0);
                mfc1(v0, f1);
                sh(v0, s1, 62);
                if (i64(s3) > 0) {
                    // 0x00547e94
                    charge(ctx, 3);
                    s0 = s3;
                    v1 = si(-128);
                    v0 = addiu(s1, 66);
                    for (;;) {
                        // 0x00547ea0
                        charge(ctx, 7);
                        s0 = addiu(s0, -1);
                        sh(v1, v0, 0);
                        v0 = addiu(v0, 2);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00547ebc
                charge(ctx, 22);
                s0 = 1;
                a1 = 0;
                a0 = s1;
                sh(zero, s1, 70);
                sb(s0, s1, 108);
                sw(zero, s1, 84);
                sw(zero, s1, 88);
                sw(zero, s1, 92);
                sh(zero, s1, 96);
                sw(zero, s1, 100);
                sh(zero, s1, 104);
                sh(zero, s1, 106);
                sb(s0, s1, 109);
                sb(zero, s1, 114);
                link(ctx, 0x547EF4u);  // $ra first: the delay slot below depends on it
                sw(zero, s1, 136);
                call(ctx, gen::fn_sub_54A968_0054a968);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x547F00u, gen::fn_sub_5497A0_005497a0);
                link(ctx, 0x547F08u);  // $ra first: the delay slot below depends on it
                sb(s0, s1, 0);
                call(ctx, gen::fn_sub_539830_00539830);
                v0 = s1;
                // 0x00547f14 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(s0, sp, 0x0);
                ld(s1, sp, 0x8);
                ld(s2, sp, 0x10);
                ld(s3, sp, 0x18);
                ld(ra, sp, 0x20);
                sp = addiu(sp, 0x30);
                return;
            }
        L_00547e18:
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x547E18u, gen::fn_sub_548078_00548078);
            v0 = 0;
        }
        // 0x00547f14 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
L_00547c5c:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_00547c60;
L_00547c9c_7:
    charge(ctx, 1);
    v0 = 16;
    goto L_00547ca0;
}

// 0x00547FD0 sub_547FD0 -- 40 bytes; frame 0x10: ra sp+0x0
// call the optional destroy hook 0x793B24. [adxt_CallDestroyHook0]
void sub_547FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547fd0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 15140);  // 0x793B24
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x00547fe4
        charge(ctx, 2);
        jalr(ctx, 0x547FE4u, v0.u());
    }
    // 0x00547fec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00547FF8 sub_547FF8 -- 40 bytes; frame 0x10: ra sp+0x0
// call the optional destroy hook 0x793B28 with the handle. [adxt_CallDestroyHook1]
void sub_547FF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00547ff8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 15144);  // 0x793B28
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0054800c
        charge(ctx, 2);
        jalr(ctx, 0x54800Cu, v0.u());
    }
    // 0x00548014 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00548020 sub_548020 -- 40 bytes; frame 0x10: ra sp+0x0
// call the optional destroy hook 0x793B30 with the handle. [adxt_CallDestroyHook2]
void sub_548020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548020
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x790000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 15152);  // 0x793B30
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x00548034
        charge(ctx, 2);
        jalr(ctx, 0x548034u, v0.u());
    }
    // 0x0054803c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00548048 sub_548048 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// destroy (locked). [ADXT_Destroy]
void sub_548048(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548048
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x548054u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54805Cu, gen::fn_sub_548078_00548078);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00548078 sub_548078 -- 468 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// destroy a player: stop it, release the output, decoder, streamer, list streamer and joints, clear the 200 bytes.
//   [adxt_Destroy]
void sub_548078(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548078
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    if (s1 == 0) {
        // 0x00548098
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 10176);  // "E02080805 adxt_Destroy: parameter error"
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x005480c0
    charge(ctx, 10);
    jal(ctx, 0x5480C0u, gen::fn_sub_547FD0_00547fd0);
    a0 = s1;
    jal(ctx, 0x5480C8u, gen::fn_sub_547FF8_00547ff8);
    a0 = s1;
    jal(ctx, 0x5480D0u, gen::fn_sub_548020_00548020);
    lb(v1, s1, adxt::kUsed);
    v0 = 1;
    if (v1 != v0) {
        lw(a0, s1, adxt::kRna);
    } else {
        // 0x005480e8
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x5480E8u, gen::fn_sub_5486A8_005486a8);
        lw(a0, s1, adxt::kRna);
    }
    // 0x005480f4
    charge(ctx, 2);
    if (a0 == 0) {
        lw(a0, s1, adxt::kSjd);
    } else {
        // 0x005480fc
        charge(ctx, 3);
        link(ctx, 0x5480FCu);  // $ra first: the delay slot below depends on it
        sw(zero, s1, adxt::kRna);
        call(ctx, gen::fn_sub_541A10_00541a10);
        lw(a0, s1, adxt::kSjd);
    }
    // 0x00548108
    charge(ctx, 2);
    if (a0 == 0) {
        lw(s0, s1, adxt::kStm);
    } else {
        // 0x00548110
        charge(ctx, 3);
        link(ctx, 0x548110u);  // $ra first: the delay slot below depends on it
        sw(zero, s1, adxt::kSjd);
        call(ctx, gen::fn_sub_541FA8_00541fa8);
        lw(s0, s1, adxt::kStm);
    }
    // 0x0054811c
    charge(ctx, 2);
    a0 = s0;
    if (s0 != 0) {
        // 0x00548124
        charge(ctx, 6);
        sw(zero, s1, adxt::kStm);
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x54812Cu, gen::fn_sub_5466B8_005466b8);
        a0 = s0;
        jal(ctx, 0x548134u, gen::fn_sub_546058_00546058);
    }
    // 0x0054813c
    charge(ctx, 3);
    lw(a0, s1, adxt::kLsc);
    if (a0 != 0) {
        // 0x00548148
        charge(ctx, 2);
        link(ctx, 0x548148u);  // $ra first: the delay slot below depends on it
        sw(zero, s1, adxt::kLsc);
        call(ctx, gen::fn_sub_55D3A8_0055d3a8);
    }
    // 0x00548150
    charge(ctx, 5);
    jal(ctx, 0x548150u, gen::fn_sub_539818_00539818);
    lw(a0, s1, adxt::kSjf);
    if (a0 == 0) {
        lb(v0, s1, adxt::kMaxCh);
    } else {
        // 0x00548164
        charge(ctx, 6);
        lw(v1, a0, 0);
        sw(zero, s1, adxt::kSjf);
        lw(v0, v1, 12);
        jalr(ctx, 0x548170u, v0.u());
        lb(v0, s1, adxt::kMaxCh);
    }
    // 0x0054817c
    charge(ctx, 2);
    s3 = 0;
    if (i64(v0) > 0) {
        // 0x00548184
        charge(ctx, 3);
        s2 = addiu(s1, 128);
        s0 = addiu(s1, 120);
        for (;;) {
            // 0x00548190
            charge(ctx, 3);
            lw(v1, s0, -96);
            a0 = v1;
            if (v1 != 0) {
                // 0x0054819c
                charge(ctx, 5);
                lw(v1, v1, 0);
                sw(zero, s0, -96);
                lw(v0, v1, 12);
                jalr(ctx, 0x5481A8u, v0.u());
            }
            // 0x005481b0
            charge(ctx, 3);
            lw(a0, s0, 0);
            if (a0 == 0) {
                lw(a0, s2, 0);
            } else {
                // 0x005481bc
                charge(ctx, 6);
                lw(v1, a0, 0);
                sw(zero, s0, 0);
                lw(v0, v1, 12);
                jalr(ctx, 0x5481C8u, v0.u());
                lw(a0, s2, 0);
            }
            // 0x005481d4
            charge(ctx, 2);
            if (a0 == 0) {
                lb(v0, s1, adxt::kMaxCh);
            } else {
                // 0x005481dc
                charge(ctx, 6);
                lw(v1, a0, 0);
                sw(zero, s2, 0);
                lw(v0, v1, 12);
                jalr(ctx, 0x5481E8u, v0.u());
                lb(v0, s1, adxt::kMaxCh);
            }
            // 0x005481f4
            charge(ctx, 5);
            s3 = addiu(s3, 1);
            s2 = addiu(s2, 4);
            v0 = slt(s3, v0);
            s0 = addiu(s0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00548208
    charge(ctx, 3);
    lw(a0, s1, adxt::kAmp);
    if (a0 == 0) {
        a0 = s1;
    } else {
        // 0x00548214
        charge(ctx, 3);
        link(ctx, 0x548214u);  // $ra first: the delay slot below depends on it
        sw(zero, s1, adxt::kAmp);
        call(ctx, gen::fn_sub_535888_00535888);
        a0 = s1;
    }
    // 0x00548220
    charge(ctx, 11);
    a1 = 0;
    a2 = 200;
    jal(ctx, 0x548224u, gen::fn_memset_00521408);
    sb(zero, s1, adxt::kUsed);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00548318 sub_548318 -- 244 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// the common start: reset the output joints, give the decoder its input, start it, state 1. [adxt_StartSj0]
void sub_548318(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548318
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    lb(v0, s0, adxt::kMaxCh);
    s3 = a1;
    if (i64(v0) > 0) {
        // 0x00548344
        charge(ctx, 3);
        s1 = addiu(s0, 24);
        lw(a0, s1, 0);
        for (;;) {
            // 0x00548350
            charge(ctx, 9);
            s1 = addiu(s1, 4);
            lw(v0, a0, 0);
            lw(v1, v0, 20);
            s2 = addiu(s2, 1);
            jalr(ctx, 0x54835Cu, v1.u());
            lb(v0, s0, adxt::kMaxCh);
            v0 = slt(s2, v0);
            if (v0 == 0) {
                break;
            }
            lw(a0, s1, 0);
            backedge(ctx);
        }
    }
    // 0x00548374
    charge(ctx, 23);
    lw(a0, s0, adxt::kSjd);
    a1 = s3;
    jal(ctx, 0x548378u, gen::fn_sub_542010_00542010);
    sw(s3, s0, adxt::kSji);
    link(ctx, 0x548384u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kSjd);
    call(ctx, gen::fn_sub_5420D0_005420d0);
    v1 = 1;
    v0 = 0x7FFF0000;
    a0 = si(-1);
    v0 = v0 | 0xFFFF;
    sb(v1, s0, adxt::kStat);
    sw(a0, s0, adxt::kLoopStartSmp);
    v1 = 0x780000;
    sw(v0, s0, adxt::kReadLimit);
    sw(zero, s0, 76);
    sb(zero, s0, adxt::kStarted);
    sw(zero, s0, adxt::kPauseTime);
    sw(zero, s0, adxt::kTimeSmp);
    lw(a0, s0, adxt::kAmp);
    lw(v0, v1, 30056);  // 0x787568
    sw(zero, s0, adxt::kStopSmp);
    sw(v0, s0, adxt::kVsyncAtPause);
    if (a0 == 0) {
        // 0x005483f0
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x005483d0
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_5358E0_005358e0(ctx);  // tail call
}

// 0x00548410 sub_548410 -- 204 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// open the file stream: buffer limits, stop / seek / start the streamer, then the common start. [adxt_StartStm]
void sub_548410(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548410
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = t0;
    sd(s2, sp, 0x10);
    s2 = a3;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s4, sp, 0x20);
    s4 = a1;
    sd(ra, sp, 0x28);
    lh(a1, s0, adxt::kMinSct);
    lh(a2, s0, adxt::kMaxSct);
    lw(a0, s0, adxt::kStm);
    a1 = sll(a1, 11);
    a2 = sll(a2, 11);
    jal(ctx, 0x548450u, gen::fn_sub_546FA0_00546fa0);
    v1 = 0x790000;
    lw(a1, v1, 15120);  // 0x793B10
    link(ctx, 0x548460u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kStm);
    call(ctx, gen::fn_sub_546718_00546718);
    lw(a0, s0, adxt::kStm);
    a2 = 0;
    a1 = 0;
    jal(ctx, 0x548470u, gen::fn_sub_5466B8_005466b8);
    lw(a0, s0, adxt::kStm);
    a1 = 0;
    jal(ctx, 0x54847Cu, gen::fn_sub_5463A8_005463a8);
    link(ctx, 0x548484u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kStm);
    call(ctx, gen::fn_sub_5465A0_005465a0);
    link(ctx, 0x54848Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kStm);
    call(ctx, gen::fn_sub_546270_00546270);
    lw(a0, s0, adxt::kStm);
    a1 = s4;
    a2 = s3;
    a3 = s2;
    t0 = s1;
    jal(ctx, 0x5484A4u, gen::fn_sub_5460E0_005460e0);
    link(ctx, 0x5484ACu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kStm);
    call(ctx, gen::fn_sub_546498_00546498);
    a0 = s0;
    lw(a1, a0, 16);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_548318_00548318(ctx);  // tail call
}

// 0x005484E0 sub_5484E0 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// start on a caller's joint (locked). [ADXT_StartSj]
void sub_5484E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005484e0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5484F4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x548500u, gen::fn_sub_548520_00548520);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00548520 sub_548520 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// start on a caller's stream joint (source 3). [adxt_StartSj]
void sub_548520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548520
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (s0 != 0) {
        // 0x0054853c
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_00548544;
        }
        // 0x00548560
        charge(ctx, 17);
        jal(ctx, 0x548560u, gen::fn_sub_5486A8_005486a8);
        jal(ctx, 0x548568u, gen::fn_sub_539818_00539818);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x548574u, gen::fn_sub_548318_00548318);
        v0 = 3;
        sb(v0, s0, adxt::kSource);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x548588u, gen::fn_sub_54A968_0054a968);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_539830_00539830(ctx);  // tail call
        return;
    }
L_00548544:
    charge(ctx, 7);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 10216);  // "E02080812 adxt_StartSj: parameter error"
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x005485D8 sub_5485D8 -- 160 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the common stop: output off, decoder stop, release a memory source's joint, state 0. [adxt_StopWithoutLsc]
void sub_5485D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005485d8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5485E4u, gen::fn_sub_539818_00539818);
    lw(a0, s0, adxt::kRna);
    a1 = 0;
    jal(ctx, 0x5485F0u, gen::fn_cosl_1_00541a78);
    lw(a0, s0, adxt::kRna);
    a1 = 0;
    jal(ctx, 0x5485FCu, gen::fn_coshl_1_00541a90);
    lw(a0, s0, adxt::kRna);
    a1 = 1;
    jal(ctx, 0x548608u, gen::fn_sub_560DB8_00560db8);
    link(ctx, 0x548610u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kSjd);
    call(ctx, gen::fn_sub_542100_00542100);
    lb(v1, s0, adxt::kSource);
    v0 = 2;
    if (v1 != v0) {
        lw(a0, s0, adxt::kAmp);
    } else {
        // 0x00548628
        charge(ctx, 3);
        lw(a0, s0, adxt::kSji);
        if (a0 == 0) {
            lw(a0, s0, adxt::kAmp);
        } else {
            // 0x00548634
            charge(ctx, 6);
            lw(v1, a0, 0);
            sw(zero, s0, adxt::kSji);
            lw(v0, v1, 12);
            jalr(ctx, 0x548640u, v0.u());
            lw(a0, s0, adxt::kAmp);
        }
    }
    // 0x0054864c
    charge(ctx, 2);
    if (a0 == 0) {
        sb(zero, s0, adxt::kOpenReq);
    } else {
        // 0x00548654
        charge(ctx, 3);
        jal(ctx, 0x548654u, gen::fn_sub_535A80_00535a80);
        sb(zero, s0, adxt::kOpenReq);
    }
    // 0x00548660
    charge(ctx, 6);
    sw(zero, s0, adxt::kSji);
    sb(zero, s0, adxt::kStat);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00548678 sub_548678 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// stop (locked). [ADXT_Stop]
void sub_548678(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548678
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x548684u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54868Cu, gen::fn_sub_5486A8_005486a8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x005486A8 sub_5486A8 -- 192 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// stop: the stop hook, the streamer, the list streamer for source 4, then the common stop. [adxt_Stop]
void sub_5486A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005486a8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x005486c0
        charge(ctx, 7);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 10256);  // "E02080813 adxt_Stop: parameter error"
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x005486e0
    charge(ctx, 5);
    v0 = 0x790000;
    s1 = addiu(v0, 15148);  // &0x793B2C
    lw(v1, s1, 0);  // 0x793B2C
    if (v1 == 0) {
        lw(a0, s0, adxt::kStm);
    } else {
        // 0x005486f4
        charge(ctx, 6);
        link(ctx, 0x5486F4u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxt::kSjd);
        call(ctx, gen::fn_sub_542100_00542100);
        lw(v0, s1, 0);
        a0 = s0;
        jalr(ctx, 0x548700u, v0.u());
        lw(a0, s0, adxt::kStm);
    }
    // 0x0054870c
    charge(ctx, 2);
    if (a0 == 0) {
        lb(v1, s0, adxt::kSource);
    } else {
        // 0x00548714
        charge(ctx, 3);
        jal(ctx, 0x548714u, gen::fn_sub_546270_00546270);
        lb(v1, s0, adxt::kSource);
    }
    // 0x00548720
    charge(ctx, 3);
    v0 = 4;
    if (v1 != v0) {
        a0 = s0;
    } else {
        // 0x0054872c
        charge(ctx, 5);
        link(ctx, 0x54872Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxt::kLsc);
        call(ctx, gen::fn_sub_55D668_0055d668);
        lw(v0, s0, adxt::kSji);
        a0 = v0;
        if (v0 != 0) {
            // 0x00548740
            charge(ctx, 4);
            lw(v0, v0, 0);
            lw(v1, v0, 20);
            jalr(ctx, 0x548748u, v1.u());
        }
        // 0x00548750
        charge(ctx, 1);
        a0 = s0;
    }
    // 0x00548754
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5485D8_005485d8(ctx);  // tail call
}

// 0x00548768 sub_548768 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// status (locked). [ADXT_GetStat (one of the copies)]
void sub_548768(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548768
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x548774u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54877Cu, gen::fn_sub_5487A0_005487a0);
    s0 = v0;
    jal(ctx, 0x548784u, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005487A0 sub_5487A0 -- 48 bytes; frame 0x10: ra sp+0x0
// a player's state (-1 for a null handle). [adxt_GetStat]
void sub_5487A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005487a0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005487c0
        charge(ctx, 1);
        lb(v0, a0, adxt::kStat);
    } else {
        // 0x005487ac
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10296);  // "E02080814 adxt_GetStat: parameter error"
        jal(ctx, 0x5487B0u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x005487c4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005489A0 sub_5489A0 -- 300 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// the play time as (samples, rate): from the output while playing, the total at the end. [adxt_GetTimeSfreq]
void sub_5489A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005489a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    lbu(v0, s2, adxt::kStat);
    v1 = sll(v0, 24);
    v0 = addiu(v0, -3);
    v0 = sltiu(v0, 2);
    v1 = sra(v1, 24);
    if (v0 == 0) {
        // 0x00548a30
        charge(ctx, 3);
        v0 = 5;
        if (v1 != v0) {
            v0 = 1;
            // 0x00548a90
            charge(ctx, 2);
            sw(zero, s3, 0);
            sw(v0, s0, 0);
        } else {
            // 0x00548a3c
            charge(ctx, 12);
            link(ctx, 0x548A3Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s2, adxt::kSjd);
            call(ctx, gen::fn_sub_543178_00543178);
            lw(a0, s2, adxt::kSjd);
            link(ctx, 0x548A48u);  // $ra first: the delay slot below depends on it
            sw(v0, s3, 0);
            call(ctx, gen::fn_sub_543100_00543100);
            lw(a0, s2, adxt::kSjd);
            link(ctx, 0x548A54u);  // $ra first: the delay slot below depends on it
            sw(v0, s0, 0);
            call(ctx, gen::fn_sub_543130_00543130);
            v1 = 16;
            div(v1, v0);
            if (v0 == 0) {
                brk(ctx, 0x548A68u, 0x7u);
            }
            // 0x00548a6c
            charge(ctx, 8);
            lw(v0, s3, 0);
            mflo(v1);
            mult(v0, v0, v1);
            sw(v0, s3, 0);
            lw(v1, s2, adxt::kTimeSmp);
            v0 = addu(v0, v1);
            sw(v0, s3, 0);
        }
    } else {
        // 0x005489dc
        charge(ctx, 20);
        link(ctx, 0x5489DCu);  // $ra first: the delay slot below depends on it
        lw(a0, s2, adxt::kSjd);
        call(ctx, gen::fn_sub_543100_00543100);
        lw(a0, s2, adxt::kSjd);
        link(ctx, 0x5489E8u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 0);
        call(ctx, gen::fn_sub_542F68_00542f68);
        lw(a0, s2, adxt::kRna);
        s1 = v0;
        jal(ctx, 0x5489F4u, gen::fn_hypotf_1_00541ac0);
        a0 = s2;
        a1 = 0;
        s0 = v0;
        jal(ctx, 0x548A04u, gen::fn_sub_549BB0_00549bb0);
        lw(v1, s2, adxt::kFlushedSmp);
        lw(a0, s2, adxt::kTimeSmp);
        s0 = subu(s0, v1);
        s0 = addu(s0, v0);
        s1 = subu(s1, s0);
        s1 = addu(s1, a0);
        sw(s1, s3, 0);
    }
    // 0x00548a98 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    lw(v0, s2, adxt::kTimeOfs);
    lw(v1, s3, 0);
    ld(s0, sp, 0x0);
    v1 = addu(v1, v0);
    ld(s1, sp, 0x8);
    a0 = slti(v1, 0);
    ld(s2, sp, 0x10);
    if (a0 != 0) v1 = 0;
    ld(ra, sp, 0x20);
    sw(v1, s3, 0);
    ld(s3, sp, 0x18);
    sp = addiu(sp, 0x30);
}

// 0x00548AE8 sub_548AE8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// the play time (locked; the body is sceInsockBind_2, a FLIRT name). [ADXT_GetTime]
void sub_548AE8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548ae8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x548B04u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x548B14u, gen::fn_sceInsockBind_2_00548b38);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00548EB8 sub_548EB8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// total samples (locked). [ADXT_GetNumSmpl]
void sub_548EB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548eb8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x548EC4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x548ECCu, gen::fn_sub_548EF0_00548ef0);
    s0 = v0;
    jal(ctx, 0x548ED4u, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00548EF0 sub_548EF0 -- 76 bytes; frame 0x10: ra sp+0x0
// the stream's total samples once the header is known. [adxt_GetNumSmpl]
void sub_548EF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548ef0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00548efc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10376);  // "E02080817 adxt_GetNumSmpl: parameter error"
        jal(ctx, 0x548F00u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
        // 0x00548f30 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00548f10
    charge(ctx, 4);
    lb(v0, a0, adxt::kStat);
    v0 = slti(v0, 2);
    if (v0 != 0) {
        v0 = 0;
        // 0x00548f30 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00548f20
    charge(ctx, 4);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543178_00543178(ctx);  // tail call
}

// 0x00548F40 sub_548F40 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sample rate (locked). [ADXT_GetSfreq]
void sub_548F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548f40
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x548F4Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x548F54u, gen::fn_sub_548F78_00548f78);
    s0 = v0;
    jal(ctx, 0x548F5Cu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00548F78 sub_548F78 -- 76 bytes; frame 0x10: ra sp+0x0
// the stream's sample rate once the header is known. [adxt_GetSfreq]
void sub_548F78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00548f78
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x00548f84
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 10424);  // "E02080819 adxt_GetSfreq: parameter error"
        jal(ctx, 0x548F88u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
        // 0x00548fb8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00548f98
    charge(ctx, 4);
    lb(v0, a0, adxt::kStat);
    v0 = slti(v0, 2);
    if (v0 != 0) {
        v0 = 0;
        // 0x00548fb8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00548fa8
    charge(ctx, 4);
    lw(a0, a0, adxt::kSjd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_543100_00543100(ctx);  // tail call
}

// 0x005491B0 sub_5491B0 -- 276 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s1 sp+0x8, ra sp+0x20
// set a channel's pan (the header's pan added; -128 = automatic: +-15 for stereo). [adxt_SetOutPan]
void sub_5491B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005491b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    s3 = a2;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x20);
    if (s0 == 0) {
        // 0x005491d8
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 10616);  // "E02080825 adxt_SetOutPan: parameter error"
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x00549200
    charge(ctx, 4);
    lb(v1, s0, adxt::kPanMode);
    v0 = 1;
    s1 = 0;
    if (v1 == v0) {
        // 0x00549210
        charge(ctx, 6);
        link(ctx, 0x549210u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxt::kSjd);
        call(ctx, gen::fn_sub_5432C0_005432c0);
        s1 = v0;
        v0 = si(-128);
        v1 = 0x780000;
        if (s1 == v0) {
            // 0x00549228
            charge(ctx, 1);
            s1 = 0;
            goto L_0054922c;
        }
        goto L_00549230;
    }
L_0054922c:
    charge(ctx, 1);
    v1 = 0x780000;
L_00549230:
    charge(ctx, 3);
    lw(v0, v1, 30048);
    a2 = 0;
    if (v0 == 0) {
        // 0x0054923c
        charge(ctx, 3);
        v0 = si(-128);
        if (s3 != v0) {
            a2 = addu(s3, s1);
        } else {
            // 0x00549248
            charge(ctx, 5);
            link(ctx, 0x549248u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, adxt::kSjd);
            call(ctx, gen::fn_sub_543118_00543118);
            v1 = 2;
            if (v0 != v1) {
                a2 = 0;
            } else {
                // 0x0054925c
                charge(ctx, 3);
                v0 = 15;
                a2 = si(-15);
                if (s2 != 0) a2 = v0;
            }
            // 0x00549268
            charge(ctx, 1);
            a2 = addu(a2, s1);
        }
    }
    // 0x0054926c
    charge(ctx, 7);
    v0 = sll(s2, 1);
    v0 = addu(v0, s0);
    sh(s3, v0, 66);
    lb(v1, s0, adxt::kMaxCh);
    v1 = slt(s2, v1);
    a0 = 0x7C0000;
    if (v1 == 0) {
        // 0x005492a0
        charge(ctx, 3);
        a0 = addiu(a0, 10664);
        jal(ctx, 0x5492A0u, gen::fn_sub_53AE08_0053ae08);
        ld(s0, sp, 0x0);
    } else {
        // 0x00549288
        charge(ctx, 5);
        lw(a0, s0, adxt::kRna);
        a1 = s2;
        jal(ctx, 0x54928Cu, gen::fn_sub_541BA0_00541ba0);
        ld(s0, sp, 0x0);
    }
    // 0x005492ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00549480 sub_549480 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// set the volume (locked). [ADXT_SetOutVol]
void sub_549480(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549480
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x549494u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x5494A0u, gen::fn_sub_5494C0_005494c0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x005494C0 sub_5494C0 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// set the volume (the header's volume added). [adxt_SetOutVol]
void sub_5494C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005494c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x005494d4
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 10856);  // "E02080823 adxt_SetOutVol: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x005494f0
    charge(ctx, 4);
    lb(v1, s0, adxt::kPanMode);
    v0 = 1;
    sh(a1, s0, adxt::kOutVol);
    if (v1 != v0) {
        // 0x00549510
        charge(ctx, 2);
        v0 = 0;
        lh(a1, s0, adxt::kOutVol);
    } else {
        // 0x00549500
        charge(ctx, 4);
        link(ctx, 0x549500u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxt::kSjd);
        call(ctx, gen::fn_sub_543268_00543268);
        lh(a1, s0, adxt::kOutVol);
    }
    // 0x00549518
    charge(ctx, 6);
    lw(a0, s0, adxt::kRna);
    ld(ra, sp, 0x8);
    a1 = addu(a1, v0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_541B88_00541b88(ctx);  // tail call
}

// 0x005497A0 sub_5497A0 -- 8 bytes; leaf frame (no stack)
// store the pan mode byte (+173). [adxt_SetPanMode]
void sub_5497A0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x005497a0
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, adxt::kPanMode);
}

// 0x005497B0 sub_5497B0 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// set the default server frequency (locked). [ADXT_SetDefSvrFreq]
void sub_5497B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005497b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5497BCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x5497C4u, gen::fn_sub_5497E0_005497e0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x005497E0 sub_5497E0 -- 20 bytes; leaf frame (no stack)
// set the default and current server frequency. [adxt_SetDefSvrFreq]
void sub_5497E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x005497e0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x790000;
    v1 = 0x790000;
    sw(a0, v0, 15132);  // 0x793B1C
    sw(a0, v1, 15136);  // 0x793B20
}

// 0x005497F8 sub_5497F8 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// set a player's server frequency (locked). [ADXT_SetSvrFreq]
void sub_5497F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005497f8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54980Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x549818u, gen::fn_sub_549838_00549838);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00549838 sub_549838 -- 56 bytes; frame 0x10: ra sp+0x0
// set a player's server frequency (and the current one). [adxt_SetSvrFreq]
void sub_549838(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549838
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549858
        charge(ctx, 6);
        ld(ra, sp, 0x0);
        v0 = 0x790000;
        sw(a1, a0, adxt::kSvrFreq);
        sw(a1, v0, 15136);  // 0x793B20
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00549844
    charge(ctx, 5);
    a0 = 0x7C0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, 10952);  // "E02080840 adxt_SetSvrFreq: parameter error"
    sp = addiu(sp, 0x10);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x00549BB0 sub_549BB0 -- 104 bytes; frame 0x10: ra sp+0x0
// samples waiting in a channel's output joint. [adxt_GetNumSmplObuf]
void sub_549BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549bb0
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x00549bbc
        charge(ctx, 2);
        v0 = sll(a1, 2);
        if (i64(a1) < 0) {
            goto L_00549bc4;
        }
        // 0x00549bd8
        charge(ctx, 4);
        v0 = addu(v0, a0);
        lw(v0, v0, 24);
        a0 = v0;
        if (v0 == 0) {
            // 0x00549c08
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00549be8
            charge(ctx, 8);
            lw(v1, v0, 0);
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x549BF0u, v0.u());
            v1 = srl(v0, 31);
            v1 = addu(v1, v0);
            v0 = sra(v1, 1);
        }
        // 0x00549c0c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00549bc4:
    charge(ctx, 5);
    a0 = 0x7C0000;
    a0 = addiu(a0, 11192);  // "E02080837 adxt_GetNumSmplObuf: parameter error"
    jal(ctx, 0x549BC8u, gen::fn_sub_53AE08_0053ae08);
    v0 = si(-1);
    // 0x00549c0c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00549DE8 sub_549DE8 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// store byte +109 (locked). [ADXT_SetFlag6D]
void sub_549DE8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549de8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x549DFCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x549E08u, gen::fn_sub_549E28_00549e28);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00549E28 sub_549E28 -- 8 bytes; leaf frame (no stack)
// store byte +109. [adxt_SetFlag6D]
void sub_549E28(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00549e28
    enter(ctx, 2);  // entry check point + this block's cycles
    sb(a1, a0, adxt::kFlag6D);
}

// 0x00549EA0 sub_549EA0 -- 36 bytes; frame 0x10: ra sp+0x0
// the server (locked). [ADXT_ExecServer]
void sub_549EA0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00549ea0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x549EA8u, gen::fn_sub_539848_00539848);
    jal(ctx, 0x549EB0u, gen::fn_sub_549EC8_00549ec8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x00549EC8 sub_549EC8 -- 236 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// the server: once (re-entry guarded), run the decoders, every used player, then the output twice at low frequencies.
//   [adxt_ExecServer]
void sub_549EC8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549ec8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    s3 = 0x790000;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = addiu(s3, 15128);  // &0x793B18
    jal(ctx, 0x549EE4u, gen::fn_sub_539818_00539818);
    lw(v0, s0, 0);  // 0x793B18
    ld(s2, sp, 0x10);
    if (v0 != 0) {
        // 0x00549ef8
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_539830_00539830(ctx);  // tail call
        return;
    }
    // 0x00549f10
    charge(ctx, 14);
    v0 = 1;
    s2 = 1;
    sw(v0, s0, 0);
    s1 = 15;
    jal(ctx, 0x549F1Cu, gen::fn_sub_539830_00539830);
    jal(ctx, 0x549F24u, gen::fn_sub_539818_00539818);
    jal(ctx, 0x549F2Cu, gen::fn_sub_542F00_00542f00);
    v0 = 2;
    v1 = 0x780000;
    sw(v0, s0, 0);
    s0 = addiu(v1, 30064);  // &0x787570
    for (;;) {
        // 0x00549f48
        charge(ctx, 3);
        lb(v0, s0, 0);
        if (v0 != s2) {
            s1 = addiu(s1, -1);
        } else {
            // 0x00549f54
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x549F54u, gen::fn_sub_54C9D8_0054c9d8);
            s1 = addiu(s1, -1);
        }
        // 0x00549f60
        charge(ctx, 2);
        s0 = addiu(s0, 200);
        if (i64(s1) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00549f68
    charge(ctx, 9);
    v0 = 3;
    s0 = addiu(s3, 15128);
    link(ctx, 0x549F70u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, 0);
    call(ctx, gen::fn_sub_541B28_00541b28);
    v1 = 0x790000;
    lw(v0, v1, 15136);  // 0x793B20
    v0 = slti(v0, 51);
    if (v0 != 0) {
        // 0x00549f8c
        charge(ctx, 2);
        jal(ctx, 0x549F8Cu, gen::fn_sub_541B28_00541b28);
    }
    // 0x00549f94
    charge(ctx, 8);
    sw(zero, s0, 0);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_539830_00539830(ctx);  // tail call
}

// 0x00549FF8 sub_549FF8 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the error code (locked). [ADXT_GetErrCode]
void sub_549FF8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00549ff8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54A004u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54A00Cu, gen::fn_sub_54A030_0054a030);
    s0 = v0;
    jal(ctx, 0x54A014u, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A030 sub_54A030 -- 48 bytes; frame 0x10: ra sp+0x0
// a player's error code (+96). [adxt_GetErrCode]
void sub_54A030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a030
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054a050
        charge(ctx, 1);
        lh(v0, a0, adxt::kErrCode);
    } else {
        // 0x0054a03c
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11392);  // "E02080843 adxt_GetErrCode: parameter error"
        jal(ctx, 0x54A040u, gen::fn_sub_53AE08_0053ae08);
        v0 = si(-1);
    }
    // 0x0054a054 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A138 sub_54A138 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// set the loop flag (locked). [ADXT_SetLpFlg]
void sub_54A138(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a138
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54A14Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54A158u, gen::fn_sub_54A178_0054a178);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054A178 sub_54A178 -- 260 bytes; frame 0x20: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, ra sp+0x18
// set the loop flag; the stop sample becomes the end of the current loop pass. [adxt_SetLpFlg]
void sub_54A178(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a178
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    if (s2 == 0) {
        // 0x0054a194
        charge(ctx, 8);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 11536);  // "E02080828 adxt_SetLpFlg: parameter error"
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0054a1b8
    charge(ctx, 5);
    lw(v1, s2, adxt::kSji);
    s0 = 0;
    sb(a1, s2, adxt::kLoopFlag);
    a0 = v1;
    if (v1 != 0) {
        // 0x0054a1cc
        charge(ctx, 5);
        lw(v1, v1, 0);
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x54A1D4u, v0.u());
        s0 = v0;
    }
    // 0x0054a1e0
    charge(ctx, 23);
    link(ctx, 0x54A1E0u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, adxt::kSjd);
    call(ctx, gen::fn_sub_542F60_00542f60);
    lw(a0, s2, adxt::kSjd);
    s0 = addu(v0, s0);
    jal(ctx, 0x54A1ECu, gen::fn_sub_5431F0_005431f0);
    lw(a0, s2, adxt::kSjd);
    s1 = v0;
    v0 = addiu(s1, 2047);
    a1 = addiu(s1, 4094);
    v1 = slti(v0, 0);
    if (v1 != 0) v0 = a1;
    v0 = sra(v0, 11);
    s1 = sll(v0, 11);
    jal(ctx, 0x54A210u, gen::fn_sub_543238_00543238);
    v1 = addiu(v0, 2047);
    v0 = addiu(v0, 4094);
    a0 = slti(v1, 0);
    if (a0 != 0) v1 = v0;
    v1 = sra(v1, 11);
    v1 = sll(v1, 11);
    v1 = subu(v1, s1);
    s0 = subu(s0, s1);
    if (i64(v1) > 0) {
        // 0x0054a248
        charge(ctx, 3);
        div(s0, v1);
        if (v1 == 0) {
            brk(ctx, 0x54A250u, 0x7u);
        }
        // 0x0054a254
        charge(ctx, 4);
        mflo(v0);
        mult(a0, v0, v1);
        v0 = addu(a0, s1);
        sw(v0, s2, adxt::kStopSmp);
    } else {
        // 0x0054a23c
        charge(ctx, 2);
        sw(zero, s2, adxt::kStopSmp);
    }
    // 0x0054a264 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0054A3C0 sub_54A3C0 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// pause / resume (locked). [ADXT_Pause]
void sub_54A3C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a3c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54A3D4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54A3E0u, gen::fn_get_bufs_2_0054a400);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054A400 get_bufs_2 -- 300 bytes; frame 0x30: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, ra sp+0x28
// pause / resume: the output's pause and the play time at the pause (a FLIRT name). [adxt_Pause]
void get_bufs_2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0054a400
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x28);
    if (s2 != 0) {
        // 0x0054a438
        charge(ctx, 3);
        lb(v0, s2, adxt::kPause);
        lb(s1, s2, adxt::kStat);
        if (s0 != v0) {
            // 0x0054a444
            charge(ctx, 6);
            jal(ctx, 0x54A444u, gen::fn_sub_539818_00539818);
            v0 = addiu(s1, -3);
            v0 = sltiu(v0, 2);
            sb(s0, s2, adxt::kPause);
            if (v0 != 0) {
                // 0x0054a45c
                charge(ctx, 3);
                v0 = 1;
                lw(a0, s2, adxt::kRna);
                if (s0 != v0) {
                    // 0x0054a478
                    charge(ctx, 6);
                    a1 = 1;
                    jal(ctx, 0x54A478u, gen::fn_coshl_1_00541a90);
                    v0 = 0x780000;
                    lw(v1, v0, 30056);  // 0x787568
                    sw(v1, s2, adxt::kVsyncAtPause);
                    s0 = 0x790000;
                } else {
                    // 0x0054a468
                    charge(ctx, 4);
                    a1 = 0;
                    jal(ctx, 0x54A468u, gen::fn_coshl_1_00541a90);
                    s0 = 0x790000;
                }
                // 0x0054a490
                charge(ctx, 25);
                a0 = s2;
                s0 = addiu(s0, 15124);
                a1 = sp;
                lw(s1, s0, 0);
                a2 = addiu(sp, 0x4);
                link(ctx, 0x54A4A4u);  // $ra first: the delay slot below depends on it
                sw(zero, s0, 0);
                call(ctx, gen::fn_sceInsockBind_2_00548b38);
                v0 = 0x790000;
                lwc1(f0, sp, 0x0);
                cvt_s_w(f0, f0);
                at = 0x4F000000;
                mtc1(at, f3);
                lwc1(f2, sp, 0x4);
                cvt_s_w(f2, f2);
                lwc1(f1, v0, 15200);  // 0x793B60
                cvt_s_w(f1, f1);
                div_s(f0, f0, f2);
                mul_s(f0, f0, f1);
                c_le_s(f3, f0);
                cvt_w_s(f1, f0);
                mfc1(v1, f1);
                sw(s1, s0, 0);
                if (cond(ctx)) {
                    // 0x0054a4f4
                    charge(ctx, 5);
                    sub_s(f0, f0, f3);
                    v0 = lui(0x8000);
                    cvt_w_s(f1, f0);
                    mfc1(v1, f1);
                    v1 = v1 | v0;
                }
                // 0x0054a508
                charge(ctx, 1);
                sw(v1, s2, adxt::kPauseTime);
            }
            // 0x0054a50c
            charge(ctx, 2);
            jal(ctx, 0x54A50Cu, gen::fn_sub_539830_00539830);
        }
        // 0x0054a514
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x0054a420
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11744);  // "E02080846 adxt_Pause: parameter error"
        jal(ctx, 0x54A424u, gen::fn_sub_53AE08_0053ae08);
        ld(s0, sp, 0x10);
    }
    // 0x0054a518 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0054A530 sub_54A530 -- 56 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the pause state (locked). [ADXT_GetStatPause]
void sub_54A530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a530
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54A53Cu, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54A544u, gen::fn_sub_54A568_0054a568);
    s0 = v0;
    jal(ctx, 0x54A54Cu, gen::fn_sub_539850_00539850);
    ld(ra, sp, 0x8);
    v0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A568 sub_54A568 -- 48 bytes; frame 0x10: ra sp+0x0
// a player's pause state (+114). [adxt_GetStatPause]
void sub_54A568(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a568
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0054a588
        charge(ctx, 1);
        lb(v0, a0, adxt::kPause);
    } else {
        // 0x0054a574
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 11784);  // "E02080847 adxt_GetStatPause: parameter error"
        jal(ctx, 0x54A578u, gen::fn_sub_53AE08_0053ae08);
        v0 = 0;
    }
    // 0x0054a58c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0054A638 __env_unlock_0 -- 8 bytes; leaf frame (no stack)
// an empty stub the opening state calls (`jr $ra`; a FLIRT name). [adxt_GetHdrPan (stub)]
void __env_unlock_0(EEContext& ctx) {
    using namespace hg;
    // 0x0054a638
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0054A968 sub_54A968 -- 60 bytes, 2 chunks; frame 0x10: ra sp+0x0
// set the trap flag (+152, and into the decoder). [adxt_SetTrapFlag]
void sub_54A968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054a968
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sb(a1, a0, adxt::kTrapFlag);
    lw(v0, a0, 4);
    a0 = v0;
    if (v0 == 0) {
        // 0x0054a990
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0054a980
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00542f98
    charge(ctx, 2);
    sw(a1, a0, adxsjd::kTrapFlag);
}

// 0x0054B088 sub_54B088 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// start a partition file (locked). [ADXT_StartAfs]
void sub_54B088(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b088
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x54B0A4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x54B0B4u, gen::fn_sub_54B0D8_0054b0d8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054B0D8 sub_54B0D8 -- 248 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, ra sp+0x38
// start file N of a partition (source 1): the file's range from ADXF, else error state 6. [adxt_StartAfs]
void sub_54B0D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b0d8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(s2, sp, 0x30);
    s2 = a2;
    sd(ra, sp, 0x38);
    if (s0 != 0) {
        // 0x0054b110
        charge(ctx, 11);
        jal(ctx, 0x54B110u, gen::fn_sub_548678_00548678);
        a0 = s1;
        lw(a2, s0, adxt::kFnameBuf);
        a1 = s2;
        a3 = addiu(sp, 0x10);
        t0 = addiu(sp, 0x14);
        t1 = addiu(sp, 0x18);
        jal(ctx, 0x54B12Cu, gen::fn_sub_53DD10_0053dd10);
        if (v0 != 0) {
            ld(s0, sp, 0x20);
        } else {
            // 0x0054b13c
            charge(ctx, 3);
            lw(v0, s0, adxt::kStm);
            if (v0 != 0) {
                lw(a3, sp, 0x10);
                // 0x0054b180
                charge(ctx, 14);
                v0 = 1;
                lw(a2, sp, 0x14);
                a0 = s0;
                lw(v1, sp, 0x18);
                a1 = 0;
                lw(t0, s0, adxt::kFnameBuf);
                sw(a3, s0, adxt::kReqPtid);
                sw(t0, s0, adxt::kReqFname);
                sw(a2, s0, adxt::kReqOfst);
                sw(v1, s0, adxt::kReqNsct);
                sb(v0, s0, adxt::kSource);
                sb(v0, s0, adxt::kStat);
                link(ctx, 0x54B1B0u);  // $ra first: the delay slot below depends on it
                sb(v0, s0, adxt::kOpenReq);
                call(ctx, gen::fn_sceInsockSetsockopt_2_0054a928);
            } else {
                // 0x0054b148
                charge(ctx, 14);
                a0 = s1;
                a1 = s2;
                a2 = sp;
                a3 = 16;
                jal(ctx, 0x54B154u, gen::fn_sub_53AFD8_0053afd8);
                a0 = 0x7C0000;
                a0 = addiu(a0, 12072);  // "E8101202 adxt_StartAfs: can't open "
                a1 = sp;
                jal(ctx, 0x54B164u, gen::fn_sub_53AE60_0053ae60);
                v0 = si(-1);
                v1 = 6;
                sh(v0, s0, adxt::kErrCode);
                sb(v1, s0, adxt::kStat);
            }
            // 0x0054b1b8
            charge(ctx, 1);
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x0054b0fc
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, 12024);  // "E02080811 adxt_StartAfs: parameter error"
        jal(ctx, 0x54B100u, gen::fn_sub_53AE08_0053ae08);
        ld(s0, sp, 0x20);
    }
    // 0x0054b1bc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0054B230 sub_54B230 -- 180 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// start a named file range (source 0): copy the name, request the open. [adxt_StartFnameRange]
void sub_54B230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b230
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(ra, sp, 0x20);
    if (s0 != 0) {
        // 0x0054b25c
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_0054b264;
        }
        // 0x0054b288
        charge(ctx, 23);
        jal(ctx, 0x54B288u, gen::fn_sub_548678_00548678);
        lw(a0, s0, adxt::kFnameBuf);
        a1 = s1;
        jal(ctx, 0x54B294u, gen::fn_strcpy_00524270);
        lw(v1, s0, adxt::kFnameBuf);
        v0 = 1;
        sw(s2, s0, adxt::kReqOfst);
        sw(s3, s0, adxt::kReqNsct);
        a0 = s0;
        sw(v1, s0, adxt::kReqFname);
        a1 = 0;
        sb(v0, s0, adxt::kOpenReq);
        sw(zero, s0, adxt::kReqPtid);
        sb(v0, s0, adxt::kStat);
        sb(zero, s0, adxt::kSource);
        ld(s1, sp, 0x8);
        ld(s0, sp, 0x0);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sceInsockSetsockopt_2_0054a928(ctx);  // tail call
        return;
    }
L_0054b264:
    charge(ctx, 9);
    a0 = 0x7C0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a0 = addiu(a0, 12112);  // "E02080807 adxt_StartFnameRange: parameter error"
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
}

// 0x0054B2E8 sub_54B2E8 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// start a named file (locked). [ADXT_StartFname]
void sub_54B2E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b2e8
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x54B2FCu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x54B308u, gen::fn_sub_54B328_0054b328);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054B328 sub_54B328 -- 32 bytes; frame 0x10: ra sp+0x0
// start a named file: the whole range (0, 0xFFFFF sectors). [adxt_StartFname]
void sub_54B328(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b328
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0xF0000;
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = a3 | 0xFFFF;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54B230_0054b230(ctx);  // tail call
}

// 0x0054B4D0 sub_54B4D0 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// start a memory index entry (locked). [ADXT_StartMemIdx]
void sub_54B4D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b4d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x54B4ECu, gen::fn_sub_539848_00539848);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    jal(ctx, 0x54B4FCu, gen::fn_sub_54B520_0054b520);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054B520 sub_54B520 -- 368 bytes; frame 0x30: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, ra sp+0x20
// start entry N of a memory index (big-endian count and offsets): an SJMEM joint over it (source 2). [adxt_StartMemIdx]
void sub_54B520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b520
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    if (s2 != 0) {
        // 0x0054b548
        charge(ctx, 2);
        if (s1 == 0) {
            a0 = 0x7C0000;
        L_0054b55c:
            charge(ctx, 8);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            a0 = addiu(a0, 12256);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
            return;
        }
        // 0x0054b550
        charge(ctx, 2);
        if (i64(s0) < 0) {
            goto L_0054b558;
        }
        // 0x0054b580
        charge(ctx, 15);
        s3 = 0xFF0000;
        jal(ctx, 0x54B580u, gen::fn_sub_548678_00548678);
        lw(v1, s1, 4);
        a1 = sra(v1, 8);
        a0 = sll(v1, 8);
        v0 = srl(v1, 24);
        v1 = sll(v1, 24);
        a0 = a0 & s3;
        a1 = a1 & 0xFF00;
        v0 = v0 | v1;
        a0 = a0 | a1;
        v0 = v0 | a0;
        v0 = slt(s0, v0);
        if (v0 == 0) {
            ld(s0, sp, 0x0);
            // 0x0054b678 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x0054b5bc
        charge(ctx, 2);
        if (i64(s0) < 0) {
            ld(s0, sp, 0x0);
            // 0x0054b678 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x0054b5c4
        charge(ctx, 20);
        jal(ctx, 0x54B5C4u, gen::fn_sub_539818_00539818);
        a1 = 0x40000000;
        v0 = sll(s0, 3);
        v0 = addu(v0, s1);
        lw(v1, v0, 8);
        a2 = sra(v1, 8);
        v0 = sll(v1, 8);
        a2 = a2 & 0xFF00;
        a0 = srl(v1, 24);
        v0 = v0 & s3;
        v1 = sll(v1, 24);
        a0 = a0 | v1;
        v0 = v0 | a2;
        a0 = a0 | v0;
        a0 = addu(s1, a0);
        jal(ctx, 0x54B600u, gen::fn_sub_561970_00561970);
        a0 = s2;
        a1 = v0;
        if (v0 == 0) {
            // 0x0054b614
            charge(ctx, 11);
            jal(ctx, 0x54B614u, gen::fn_sub_539830_00539830);
            a0 = 0x7C0000;
            ld(s0, sp, 0x0);
            a0 = addiu(a0, 12304);  // "E8101207: can't create sj (adxt_StartMemIdx)"
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
            return;
        }
        // 0x0054b640
        charge(ctx, 14);
        jal(ctx, 0x54B640u, gen::fn_sub_548318_00548318);
        v0 = 2;
        sb(v0, s2, adxt::kSource);
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x54B654u, gen::fn_sceInsockSetsockopt_2_0054a928);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_539830_00539830(ctx);  // tail call
        return;
    }
L_0054b558:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_0054b55c;
}

// 0x0054B690 sub_54B690 -- 184 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28, s1 sp+0x8
// the loop trap installer: decode up to the loop end, trap there into sub_54B748. [adxt_SetLoopTrap]
void sub_54B690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b690
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    sd(s1, sp, 0x8);
    lw(s1, s2, adxt::kSjd);
    a0 = s1;
    jal(ctx, 0x54B6B4u, gen::fn_sub_5431D8_005431d8);
    a0 = s1;
    s3 = v0;
    jal(ctx, 0x54B6C0u, gen::fn_sub_5431F0_005431f0);
    a0 = s1;
    s4 = v0;
    jal(ctx, 0x54B6CCu, gen::fn_sub_543220_00543220);
    a0 = s1;
    s0 = v0;
    jal(ctx, 0x54B6D8u, gen::fn_sub_5433A8_005433a8);
    s0 = subu(s0, s3);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x54B6E8u, gen::fn_sub_5430C8_005430c8);
    sw(s0, s2, adxt::kLoopStartSmp);
    a1 = s0;
    a0 = s1;
    jal(ctx, 0x54B6F8u, gen::fn_sub_5430B8_005430b8);
    a0 = s1;
    a1 = s4;
    jal(ctx, 0x54B704u, gen::fn_sub_5430D8_005430d8);
    a0 = s1;
    a1 = s3;
    jal(ctx, 0x54B710u, gen::fn_sub_542F88_00542f88);
    a1 = 0x550000;
    a0 = s1;
    ld(s1, sp, 0x8);
    a2 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    a1 = addiu(a1, -18616);  // &sub_54B748
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    gen::fn_sub_5430A8_005430a8(ctx);  // tail call
}

// 0x0054B988 sub_54B988 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// apply the pans (one or both channels). [adxt_SetOutPanAll]
void sub_54B988(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b988
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x54B998u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, adxt::kSjd);
    call(ctx, gen::fn_sub_543118_00543118);
    a0 = s0;
    v1 = 1;
    a1 = 0;
    if (v0 == v1) {
        // 0x0054b9b0
        charge(ctx, 5);
        lh(a2, a0, 66);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sceInsockListen_2_00549160(ctx);  // tail call
        return;
    }
    // 0x0054b9c8
    charge(ctx, 10);
    lh(a2, s0, adxt::kOutPan);
    a0 = s0;
    jal(ctx, 0x54B9CCu, gen::fn_sceInsockListen_2_00549160);
    a0 = s0;
    lh(a2, a0, 68);
    a1 = 1;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sceInsockListen_2_00549160(ctx);  // tail call
}

// 0x0054B9F0 sub_54B9F0 -- 740 bytes; frame 0x90: s4 sp+0x70, s0 sp+0x50, s1 sp+0x58, s2 sp+0x60, s3 sp+0x68, s5 sp+0x78, s6 sp+0x80, ra sp+0x88
// the trap at the end of a stream with a trailer: resync on the next header (AHX) and restart the decoder seamlessly.
//   [adxt_TrapEntry]
void sub_54B9F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054b9f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s4, sp, 0x70);
    s4 = a0;
    sd(s0, sp, 0x50);
    sd(s1, sp, 0x58);
    sd(s2, sp, 0x60);
    sd(s3, sp, 0x68);
    sd(s5, sp, 0x78);
    sd(s6, sp, 0x80);
    sd(ra, sp, 0x88);
    lb(v0, s4, adxt::kTrapFlag);
    lw(s2, s4, adxt::kSjd);
    lw(s1, s4, adxt::kSji);
    if (v0 != 0) {
        // 0x0054ba28
        charge(ctx, 25);
        lw(v0, s1, 0);
        a2 = 0x7FFF0000;
        sh(zero, sp, 0x42);
        a3 = sp;
        lw(v1, v0, 24);
        a0 = s1;
        a1 = 1;
        a2 = a2 | 0xFFFF;
        jalr(ctx, 0x54BA44u, v1.u());
        lw(v0, s1, 0);
        s5 = addiu(sp, 0x20);
        a2 = 0x7FFF0000;
        lw(v1, v0, 24);
        a0 = s1;
        a1 = 1;
        a2 = a2 | 0xFFFF;
        a3 = s5;
        jalr(ctx, 0x54BA68u, v1.u());
        s3 = addiu(sp, 0x40);
        lw(a0, sp, 0x0);
        lw(a1, sp, 0x4);
        a2 = s3;
        jal(ctx, 0x54BA7Cu, gen::fn__get_peer_or_sock_name_3_0053a358);
        a0 = s4;
        if (v0 == 0) {
            // 0x0054bad0
            charge(ctx, 10);
            lh(s0, sp, 0x40);
            a2 = s3;
            lw(a0, sp, 0x0);
            lw(a1, sp, 0x4);
            a0 = addu(a0, s0);
            a1 = subu(a1, s0);
            jal(ctx, 0x54BAE4u, gen::fn_sub_5399B8_005399b8);
            s3 = v0;
            v1 = si(-1);
            if (s3 != 0) {
                // 0x0054baf8
                charge(ctx, 5);
                lw(a0, sp, 0x20);
                a2 = addiu(sp, 0x42);
                link(ctx, 0x54BB00u);  // $ra first: the delay slot below depends on it
                lw(a1, sp, 0x24);
                call(ctx, gen::fn_sub_5399B8_005399b8);
                v1 = v0;
            }
            // 0x0054bb0c
            charge(ctx, 4);
            lh(v0, sp, 0x40);
            lh(s6, sp, 0x42);
            s0 = addu(s0, v0);
            if (s3 != 0) {
                // 0x0054bb1c
                charge(ctx, 2);
                a2 = s5;
                if (v1 != 0) {
                    // 0x0054bb24
                    charge(ctx, 13);
                    lw(v1, s1, 0);
                    a0 = s1;
                    lw(v0, v1, 28);
                    a1 = 1;
                    jalr(ctx, 0x54BB30u, v0.u());
                    lw(v1, s1, 0);
                    a0 = s1;
                    a1 = 1;
                    lw(v0, v1, 28);
                    a2 = sp;
                    jalr(ctx, 0x54BB48u, v0.u());
                    a0 = s4;
                    goto L_0054bc64;
                }
                // 0x0054bbc0
                charge(ctx, 24);
                lw(v1, s1, 0);
                a2 = sp;
                a0 = s1;
                lw(v0, v1, 32);
                a1 = 0;
                jalr(ctx, 0x54BBD0u, v0.u());
                a0 = s5;
                s0 = addiu(sp, 0x30);
                a1 = s6;
                a2 = s5;
                a3 = s0;
                jal(ctx, 0x54BBE8u, gen::fn_sub_563C28_00563c28);
                lw(v1, s1, 0);
                a2 = s5;
                a0 = s1;
                lw(v0, v1, 32);
                a1 = 0;
                jalr(ctx, 0x54BC00u, v0.u());
                lw(v1, s1, 0);
                a0 = s1;
                a2 = s0;
                lw(v0, v1, 28);
                a1 = 1;
                jalr(ctx, 0x54BC18u, v0.u());
                goto L_0054bc20;
            }
            // 0x0054bb58
            charge(ctx, 26);
            lw(v1, s1, 0);
            a2 = s5;
            a0 = s1;
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x54BB68u, v0.u());
            a1 = s0;
            s0 = addiu(sp, 0x10);
            a0 = sp;
            a2 = sp;
            a3 = s0;
            jal(ctx, 0x54BB80u, gen::fn_sub_563C28_00563c28);
            lw(v1, s1, 0);
            a0 = s1;
            a1 = 0;
            lw(v0, v1, 32);
            a2 = sp;
            jalr(ctx, 0x54BB98u, v0.u());
            lw(v1, s1, 0);
            a0 = s1;
            a2 = s0;
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x54BBB0u, v0.u());
        L_0054bc20:
            charge(ctx, 16);
            a0 = s2;
            jal(ctx, 0x54BC20u, gen::fn_sub_542F68_00542f68);
            lw(v1, s4, adxt::kTimeSmp);
            a0 = s2;
            v1 = addu(v1, v0);
            link(ctx, 0x54BC34u);  // $ra first: the delay slot below depends on it
            sw(v1, s4, adxt::kTimeSmp);
            call(ctx, gen::fn_sub_542100_00542100);
            a0 = s2;
            jal(ctx, 0x54BC3Cu, gen::fn_sub_5420D0_005420d0);
            a0 = s2;
            jal(ctx, 0x54BC44u, gen::fn_sub_542BC8_00542bc8);
            a0 = s2;
            jal(ctx, 0x54BC4Cu, gen::fn_sub_542008_00542008);
            v1 = 2;
            if (v0 == v1) {
                lw(a1, s4, adxt::kMaxDec);
                // 0x0054bc78
                charge(ctx, 13);
                a0 = s2;
                jal(ctx, 0x54BC78u, gen::fn_sub_542060_00542060);
                a0 = s2;
                jal(ctx, 0x54BC80u, gen::fn_sub_543178_00543178);
                a0 = s2;
                a1 = v0;
                jal(ctx, 0x54BC8Cu, gen::fn_sub_5430B8_005430b8);
                a0 = s2;
                a1 = 0;
                jal(ctx, 0x54BC98u, gen::fn_sub_5430D8_005430d8);
                a0 = s2;
                a1 = 0;
                jal(ctx, 0x54BCA4u, gen::fn_sub_5430C8_005430c8);
                goto L_0054bcac;
            }
            // 0x0054bc60
            charge(ctx, 1);
            a0 = s4;
        L_0054bc64:
            charge(ctx, 4);
            a1 = 0;
            jal(ctx, 0x54BC64u, gen::fn_sceInsockSetsockopt_2_0054a928);
            ld(s0, sp, 0x50);
        } else {
            // 0x0054ba8c
            charge(ctx, 16);
            a1 = 0;
            jal(ctx, 0x54BA8Cu, gen::fn_sceInsockSetsockopt_2_0054a928);
            lw(v1, s1, 0);
            a2 = s5;
            a0 = s1;
            lw(v0, v1, 28);
            a1 = 1;
            jalr(ctx, 0x54BAA4u, v0.u());
            lw(v1, s1, 0);
            a0 = s1;
            a1 = 1;
            lw(v0, v1, 28);
            a2 = sp;
            jalr(ctx, 0x54BABCu, v0.u());
            ld(s0, sp, 0x50);
        }
        // 0x0054bcb0 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s1, sp, 0x58);
        ld(s2, sp, 0x60);
        ld(s3, sp, 0x68);
        ld(s4, sp, 0x70);
        ld(s5, sp, 0x78);
        ld(s6, sp, 0x80);
        ld(ra, sp, 0x88);
        sp = addiu(sp, 0x90);
        return;
    }
L_0054bcac:
    charge(ctx, 1);
    ld(s0, sp, 0x50);
    // 0x0054bcb0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(s6, sp, 0x80);
    ld(ra, sp, 0x88);
    sp = addiu(sp, 0x90);
}

// 0x0054BCD8 sub_54BCD8 -- 1036 bytes; frame 0x70: s0 sp+0x30, s3 sp+0x48, s1 sp+0x38, s2 sp+0x40, s4 sp+0x50, s5 sp+0x58, ra sp+0x60
// state 1: open the source, wait for the header, set the output (rate, channels, volume, pans), install the loop or end
//   trap, state 2. [adxt_ExecPrep]
void sub_54BCD8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054bcd8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s0, sp, 0x30);
    s0 = a0;
    sd(s3, sp, 0x48);
    s3 = 2048;
    sd(s1, sp, 0x38);
    sd(s2, sp, 0x40);
    sd(s4, sp, 0x50);
    sd(s5, sp, 0x58);
    sd(ra, sp, 0x60);
    sw(zero, sp, 0x20);
    lw(s1, s0, adxt::kSjd);
    lbu(v0, s0, adxt::kSource);
    sw(zero, sp, 0x24);
    v0 = sltiu(v0, 2);
    sw(zero, s0, adxt::kFlushedSmp);
    if (v0 != 0) {
        // 0x0054bd1c
        charge(ctx, 4);
        lb(v1, s0, adxt::kOpenReq);
        v0 = 1;
        if (v1 != v0) {
            goto L_0054bd78;
        }
        // 0x0054bd2c
        charge(ctx, 5);
        link(ctx, 0x54BD2Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, adxt::kStm);
        call(ctx, gen::fn_sub_546368_00546368);
        v1 = 2;
        if (v0 != v1) {
            // 0x0054bd40
            charge(ctx, 3);
            lw(a0, s0, adxt::kSjf);
            if (a0 == 0) {
                lw(a1, s0, adxt::kReqFname);
            } else {
                // 0x0054bd4c
                charge(ctx, 5);
                lw(v1, a0, 0);
                lw(v0, v1, 20);
                jalr(ctx, 0x54BD54u, v0.u());
                lw(a1, s0, adxt::kReqFname);
            }
            // 0x0054bd60
            charge(ctx, 6);
            a0 = s0;
            lw(a2, s0, adxt::kReqPtid);
            lw(a3, s0, adxt::kReqOfst);
            link(ctx, 0x54BD6Cu);  // $ra first: the delay slot below depends on it
            lw(t0, s0, adxt::kReqNsct);
            call(ctx, gen::fn_sub_548410_00548410);
            sb(zero, s0, adxt::kOpenReq);
            goto L_0054bd78;
        }
        ld(s0, sp, 0x30);
        // 0x0054c0c4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x38);
        ld(s2, sp, 0x40);
        ld(s3, sp, 0x48);
        ld(s4, sp, 0x50);
        ld(s5, sp, 0x58);
        ld(ra, sp, 0x60);
        sp = addiu(sp, 0x70);
        return;
    }
L_0054bd78:
    charge(ctx, 6);
    a0 = s1;
    jal(ctx, 0x54BD78u, gen::fn_sub_542008_00542008);
    v1 = v0;
    v0 = 2;
    if (v1 != v0) {
        v0 = 4;
        // 0x0054c0b0
        charge(ctx, 2);
        if (v1 != v0) {
            ld(s0, sp, 0x30);
        } else {
            // 0x0054c0b8
            charge(ctx, 2);
            v0 = 6;
            sb(v0, s0, adxt::kStat);
        L_0054c0c0:
            charge(ctx, 1);
            ld(s0, sp, 0x30);
        }
    } else {
        // 0x0054bd90
        charge(ctx, 7);
        a0 = s1;
        jal(ctx, 0x54BD90u, gen::fn_sub_543118_00543118);
        lb(a1, s0, adxt::kMaxCh);
        s4 = v0;
        v0 = slt(a1, s4);
        a2 = sp;
        if (v0 == 0) {
            // 0x0054bdd8
            charge(ctx, 8);
            a0 = s1;
            jal(ctx, 0x54BDD8u, gen::fn_sub_543100_00543100);
            a0 = s1;
            s2 = v0;
            jal(ctx, 0x54BDE4u, gen::fn_sub_5431A8_005431a8);
            s4 = v0;
            if (i64(s4) <= 0) {
                lw(v1, s0, adxt::kSvrFreq);
                // 0x0054be20
                charge(ctx, 3);
                div(s2, v1);
                if (v1 == 0) {
                    brk(ctx, 0x54BE28u, 0x7u);
                }
                // 0x0054be2c
                charge(ctx, 7);
                mflo(a0);
                v0 = sll(a0, 1);
                v0 = addu(v0, a0);
                v1 = srl(v0, 31);
                v0 = addu(v0, v1);
                v0 = sra(v0, 1);
                sw(v0, s0, adxt::kMaxDec);
            } else {
                // 0x0054bdf8
                charge(ctx, 4);
                lw(v0, s0, adxt::kSvrFreq);
                div(s2, v0);
                if (v0 == 0) {
                    brk(ctx, 0x54BE04u, 0x7u);
                }
                // 0x0054be08
                charge(ctx, 5);
                mflo(a0);
                v1 = sll(a0, 1);
                v1 = addu(v1, a0);
                sw(v1, s0, adxt::kMaxDec);
            }
            // 0x0054be48
            charge(ctx, 8);
            a0 = s1;
            jal(ctx, 0x54BE48u, gen::fn_sub_543148_00543148);
            lw(a1, s0, adxt::kMaxDec);
            v0 = sll(v0, 1);
            a0 = s1;
            a1 = addu(a1, v0);
            if (v0 == 0) {
                brk(ctx, 0x54BE64u, 0x7u);
            }
            // 0x0054be68
            charge(ctx, 7);
            div(a1, v0);
            mflo(a1);
            mult(a1, a1, v0);
            link(ctx, 0x54BE74u);  // $ra first: the delay slot below depends on it
            sw(a1, s0, adxt::kMaxDec);
            call(ctx, gen::fn_sub_542060_00542060);
            if (i64(s4) <= 0) {
                lw(a0, s0, adxt::kStm);
                // 0x0054bf50
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x0054bf58
                    charge(ctx, 3);
                    a1 = 0x7FFF0000;
                    a1 = a1 | 0xFFFF;
                    jal(ctx, 0x54BF5Cu, gen::fn_sub_546718_00546718);
                }
                // 0x0054bf64
                charge(ctx, 16);
                a0 = s1;
                jal(ctx, 0x54BF64u, gen::fn_sub_543178_00543178);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x54BF70u, gen::fn_sub_5430B8_005430b8);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x54BF7Cu, gen::fn_sub_5430D8_005430d8);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x54BF88u, gen::fn_sub_5430C8_005430c8);
                a1 = 0x550000;
                a1 = addiu(a1, -17936);  // &sub_54B9F0
                a0 = s1;
                a2 = s0;
                jal(ctx, 0x54BF9Cu, gen::fn_sub_5430A8_005430a8);
            } else {
                // 0x0054be84
                charge(ctx, 4);
                lb(v1, s0, adxt::kSource);
                v0 = 2;
                if (v1 != v0) {
                    // 0x0054bea0
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x54BEA0u, gen::fn_sub_543238_00543238);
                    if (s3 == 0) {
                        brk(ctx, 0x54BEACu, 0x7u);
                    }
                    // 0x0054beb0
                    charge(ctx, 19);
                    div(v0, s3);
                    v0 = addiu(v0, 2047);
                    mfhi(v1);
                    div(v0, s3);
                    v1 = subu(s3, v1);
                    sw(v1, s0, adxt::kLoopSkip);
                    mflo(v0);
                    div(v1, s3);
                    a1 = v0;
                    mfhi(a0);
                    sw(a0, s0, adxt::kLoopSkip);
                    lw(a0, s0, adxt::kStm);
                    link(ctx, 0x54BEE0u);  // $ra first: the delay slot below depends on it
                    sw(v0, s0, adxt::kReadLimit);
                    call(ctx, gen::fn_sub_546718_00546718);
                    a1 = 0x550000;
                    lw(a0, s0, adxt::kStm);
                    a1 = addiu(a1, -18208);  // &sub_54B8E0
                    a2 = s0;
                    jal(ctx, 0x54BEF4u, gen::fn_sub_5466B8_005466b8);
                } else {
                    // 0x0054be94
                    charge(ctx, 2);
                    sw(zero, s0, adxt::kLoopSkip);
                }
                // 0x0054befc
                charge(ctx, 21);
                a0 = s1;
                jal(ctx, 0x54BEFCu, gen::fn_sub_543220_00543220);
                a0 = s1;
                jal(ctx, 0x54BF04u, gen::fn_sub_5431D8_005431d8);
                a0 = s1;
                sw(v0, s0, adxt::kLoopStartSmp);
                a1 = v0;
                jal(ctx, 0x54BF14u, gen::fn_sub_5430B8_005430b8);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x54BF20u, gen::fn_sub_5430D8_005430d8);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x54BF2Cu, gen::fn_sub_5430C8_005430c8);
                a1 = 0x550000;
                a1 = addiu(a1, -18800);  // &sub_54B690
                a0 = s1;
                a2 = s0;
                jal(ctx, 0x54BF40u, gen::fn_sub_5430A8_005430a8);
            }
            // 0x0054bfa4
            charge(ctx, 33);
            a0 = s1;
            jal(ctx, 0x54BFA4u, gen::fn_sub_543100_00543100);
            a0 = s1;
            s2 = v0;
            jal(ctx, 0x54BFB0u, gen::fn_sub_543118_00543118);
            a0 = s1;
            s4 = v0;
            jal(ctx, 0x54BFBCu, gen::fn_sub_543178_00543178);
            a0 = s1;
            s5 = v0;
            jal(ctx, 0x54BFC8u, gen::fn_sub_543130_00543130);
            lw(a0, s0, adxt::kRna);
            a1 = v0;
            jal(ctx, 0x54BFD4u, gen::fn_sub_541BD0_00541bd0);
            lw(a0, s0, adxt::kRna);
            a1 = s2;
            jal(ctx, 0x54BFE0u, gen::fn_sub_541B70_00541b70);
            lw(a0, s0, adxt::kRna);
            a1 = s4;
            jal(ctx, 0x54BFECu, gen::fn_sub_541B58_00541b58);
            lw(a0, s0, adxt::kRna);
            a1 = s5;
            jal(ctx, 0x54BFF8u, gen::fn___env_lock_7_00541cb8);
            a0 = s0;
            link(ctx, 0x54C004u);  // $ra first: the delay slot below depends on it
            lh(a1, s0, adxt::kOutVol);
            call(ctx, gen::fn_sub_549480_00549480);
            a0 = s0;
            a1 = addiu(sp, 0x20);
            a2 = addiu(sp, 0x24);
            jal(ctx, 0x54C014u, gen::fn___env_unlock_0_0054a638);
            lw(a1, sp, 0x20);
            lw(a2, sp, 0x24);
            if (a1 == 0) {
                // 0x0054c028
                charge(ctx, 2);
                if (a2 != 0) {
                    goto L_0054c030;
                }
                goto L_0054c038;
            }
        L_0054c030:
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x54C030u, gen::fn___env_lock_0_0054a630);
        L_0054c038:
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x54C038u, gen::fn_sub_54B988_0054b988);
            lw(a0, s0, adxt::kAmp);
            if (a0 == 0) {
                a0 = s1;
            } else {
                // 0x0054c04c
                charge(ctx, 3);
                a1 = s2;
                jal(ctx, 0x54C04Cu, gen::fn_sub_535DA8_00535da8);
                a0 = s1;
            }
            // 0x0054c058
            charge(ctx, 4);
            s3 = 2;
            jal(ctx, 0x54C058u, gen::fn_sub_5430E8_005430e8);
            if (v0 != s3) {
                lw(a0, s0, adxt::kRna);
            } else {
                // 0x0054c068
                charge(ctx, 6);
                a0 = s1;
                jal(ctx, 0x54C068u, gen::fn_sub_5433A0_005433a0);
                lw(a0, s0, adxt::kRna);
                a1 = v0;
                jal(ctx, 0x54C074u, gen::fn_r_lock_def_free_0_00541cc8);
                lw(a0, s0, adxt::kRna);
            }
            // 0x0054c080
            charge(ctx, 6);
            a1 = 1;
            jal(ctx, 0x54C080u, gen::fn_cosl_1_00541a78);
            v0 = 0x790000;
            lw(v0, v0, 15208);  // 0x793B68
            a1 = s2;
            if (v0 != 0) {
                // 0x0054c098
                charge(ctx, 4);
                a2 = s4;
                a3 = s5;
                a0 = s0;
                jalr(ctx, 0x54C0A0u, v0.u());
            }
            // 0x0054c0a8
            charge(ctx, 2);
            sb(s3, s0, adxt::kStat);
            goto L_0054c0c0;
        }
        // 0x0054bdac
        charge(ctx, 11);
        a0 = s4;
        a3 = 16;
        jal(ctx, 0x54BDB0u, gen::fn_sub_53AFD8_0053afd8);
        a0 = 0x7C0000;
        a0 = addiu(a0, 12400);  // "E9081001 adxt_stat_decinfo: can't play this number of channels"
        a1 = sp;
        jal(ctx, 0x54BDC0u, gen::fn_sub_53AE60_0053ae60);
        a0 = s0;
        jal(ctx, 0x54BDC8u, gen::fn_sub_548678_00548678);
        ld(s0, sp, 0x30);
    }
    // 0x0054c0c4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x0054C100 sub_54C100 -- 388 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s2 sp+0x20, s4 sp+0x30, ra sp+0x38
// state 2: wait until enough PCM is queued, start the output (unless held), state 3. [adxt_ExecBuffering]
void sub_54C100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054c100
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s3, sp, 0x28);
    sd(s2, sp, 0x20);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(s2, s1, 12);
    lw(s4, s1, 4);
    a0 = s2;
    jal(ctx, 0x54C128u, gen::fn_hypotf_1_00541ac0);
    a0 = s2;
    s0 = v0;
    jal(ctx, 0x54C134u, gen::fn_sub_541AD8_00541ad8);
    s3 = v0;
    lw(v0, s1, 72);
    v1 = 16384;
    v0 = sll(v0, 1);
    a0 = slti(v0, 16385);
    if (a0 != 0) v1 = v0;
    s0 = slt(s0, v1);
    if (s0 == 0) {
        lb(v0, s1, 112);
    } else {
        // 0x0054c160
        charge(ctx, 5);
        a0 = s4;
        jal(ctx, 0x54C160u, gen::fn_sub_543148_00543148);
        v0 = slt(v0, s3);
        if (v0 == 0) {
            lb(v0, s1, 112);
            goto L_0054c18c;
        }
        // 0x0054c174
        charge(ctx, 5);
        link(ctx, 0x54C174u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 4);
        call(ctx, gen::fn_sub_542008_00542008);
        v1 = 3;
        if (v0 == v1) {
            // 0x0054c188
            charge(ctx, 1);
            lb(v0, s1, 112);
            goto L_0054c18c;
        }
        goto L_0054c1d0;
    }
L_0054c18c:
    charge(ctx, 2);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (!cc) {
        // 0x0054c194
        charge(ctx, 3);
        lb(v0, s1, 114);
        if (v0 != 0) {
            v0 = 3;
        } else {
            // 0x0054c1a0
            charge(ctx, 9);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x54C1A4u, gen::fn_coshl_1_00541a90);
            sw(zero, s1, 156);
            v0 = 0x780000;
            v0 = addiu(v0, 30056);  // &0x787568
            lw(v1, v0, 0);  // 0x787568
            sw(v1, s1, 160);
            v0 = 3;
        }
        // 0x0054c1c4
        charge(ctx, 2);
        sb(v0, s1, 1);
        v0 = 1;
    }
    // 0x0054c1cc
    charge(ctx, 1);
    sb(v0, s1, 113);
L_0054c1d0:
    charge(ctx, 5);
    link(ctx, 0x54C1D0u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 4);
    call(ctx, gen::fn_sub_542008_00542008);
    v1 = 3;
    ld(s0, sp, 0x10);
    if (v0 == v1) {
        // 0x0054c1e4
        charge(ctx, 7);
        a0 = s1;
        jal(ctx, 0x54C1E4u, gen::fn_sub_548FC8_00548fc8);
        v1 = v0;
        lw(v0, s1, 72);
        mult(v0, v0, v1);
        s3 = sll(v0, 1);
        if (i64(v1) > 0) {
            // 0x0054c200
            charge(ctx, 4);
            s2 = addiu(s1, 24);
            s1 = v1;
            lw(s0, s2, 0);
            for (;;) {
                // 0x0054c210
                charge(ctx, 21);
                s2 = addiu(s2, 4);
                a3 = sp;
                a1 = 0;
                lw(v1, s0, 0);
                a0 = s0;
                a2 = s3;
                lw(v0, v1, 24);
                s1 = addiu(s1, -1);
                jalr(ctx, 0x54C22Cu, v0.u());
                a1 = 0;
                lw(a0, sp, 0x0);
                link(ctx, 0x54C23Cu);  // $ra first: the delay slot below depends on it
                lw(a2, sp, 0x4);
                call(ctx, gen::fn_memset_00521408);
                lw(v1, s0, 0);
                a0 = s0;
                a1 = 1;
                lw(v0, v1, 32);
                a2 = sp;
                jalr(ctx, 0x54C254u, v0.u());
                if (s1 == 0) {
                    break;
                }
                lw(s0, s2, 0);
                backedge(ctx);
            }
        }
        // 0x0054c264
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0054c268 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0054C288 sub_54C288 -- 232 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// state 3: the loop-off stop sample, then the decode end once every output joint is nearly empty, state 4.
//   [adxt_ExecPlaying]
void sub_54C288(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054c288
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    lb(v0, s1, adxt::kLoopFlag);
    if (v0 == 0) {
        // 0x0054c2b4
        charge(ctx, 6);
        link(ctx, 0x54C2B4u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, adxt::kSjd);
        call(ctx, gen::fn_sub_542F60_00542f60);
        lw(v1, s1, adxt::kStopSmp);
        v0 = slt(v0, v1);
        if (v0 == 0) {
            // 0x0054c2cc
            charge(ctx, 3);
            lw(a0, s1, adxt::kSjd);
            a1 = si(-1);
            jal(ctx, 0x54C2D0u, gen::fn_sub_5430B8_005430b8);
        }
    }
    // 0x0054c2d8
    charge(ctx, 5);
    link(ctx, 0x54C2D8u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, adxt::kSjd);
    call(ctx, gen::fn_sub_542008_00542008);
    v1 = 3;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0054c2ec
        charge(ctx, 9);
        lw(a0, s1, adxt::kSjd);
        s3 = 0;
        s4 = 0x790000;
        s0 = addiu(s1, 24);
        jal(ctx, 0x54C2F8u, gen::fn_sub_543118_00543118);
        s2 = v0;
        v0 = 0x790000;
        sw(s2, v0, 15212);  // 0x793B6C
        for (;;) {
            // 0x0054c314
            charge(ctx, 3);
            v0 = slt(s3, s2);
            if (v0 != 0) {
                // 0x0054c320
                charge(ctx, 9);
                lw(a0, s0, 0);
                s0 = addiu(s0, 4);
                lw(v1, a0, 0);
                lw(v0, v1, 36);
                a1 = 1;
                jalr(ctx, 0x54C330u, v0.u());
                v1 = slti(v0, 64);
                sw(v0, s4, 15216);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x0054c310
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                    continue;
                }
            }
            break;
        }
        // 0x0054c344
        charge(ctx, 2);
        ld(s0, sp, 0x0);
        if (s3 == s2) {
            // 0x0054c34c
            charge(ctx, 2);
            v0 = 4;
            sb(v0, s1, adxt::kStat);
        }
    }
    // 0x0054c354 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0054C370 sub_54C370 -- 516 bytes; frame 0x70: s4 sp+0x40, s5 sp+0x48, s6 sp+0x50, s7 sp+0x58, s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, fp sp+0x60, ra sp+0x68
// state 4: pad the output with silence until it has played out, then stop the output, state 5. [adxt_ExecDecEnd]
void sub_54C370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0054c370
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s4, sp, 0x40);
    s4 = 0;
    sd(s5, sp, 0x48);
    sd(s6, sp, 0x50);
    s6 = a0;
    sd(s7, sp, 0x58);
    sd(s0, sp, 0x20);
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(s3, sp, 0x38);
    sd(fp, sp, 0x60);
    sd(ra, sp, 0x68);
    link(ctx, 0x54C3A4u);  // $ra first: the delay slot below depends on it
    lw(a0, s6, adxt::kRna);
    call(ctx, gen::fn_hypotf_1_00541ac0);
    v1 = 0x790000;
    sw(v0, v1, 15220);  // 0x793B74
    link(ctx, 0x54C3B4u);  // $ra first: the delay slot below depends on it
    lw(a0, s6, adxt::kSjd);
    call(ctx, gen::fn_sub_543118_00543118);
    s7 = v0;
    jal(ctx, 0x54C3BCu, gen::fn_sub_539818_00539818);
    lw(s5, s6, adxt::kMaxDec);
    if (i64(s7) > 0) {
        // 0x0054c3cc
        charge(ctx, 1);
        s1 = addiu(s6, 24);
        for (;;) {
            // 0x0054c3d0
            charge(ctx, 18);
            lw(a0, s1, 0);
            s1 = addiu(s1, 4);
            s0 = sll(s4, 3);
            s4 = addiu(s4, 1);
            lw(v1, a0, 0);
            a2 = sll(s5, 1);
            a3 = addu(sp, s0);
            lw(v0, v1, 24);
            a1 = 0;
            jalr(ctx, 0x54C3F0u, v0.u());
            a0 = slt(s4, s7);
            v0 = addiu(sp, 0x4);
            s0 = addu(v0, s0);
            lw(v1, s0, 0);
            v1 = srl(v1, 1);
            v0 = sltu(v1, s5);
            if (v0 != 0) s5 = v1;
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054c418
    charge(ctx, 2);
    s4 = 0;
    if (i64(s7) > 0) {
        // 0x0054c420
        charge(ctx, 4);
        fp = sll(s5, 1);
        s3 = addiu(s6, 24);
        v0 = addiu(sp, 0x10);
        for (;;) {
            // 0x0054c430
            charge(ctx, 31);
            s0 = sll(s4, 3);
            s1 = addu(sp, s0);
            s2 = addu(v0, s0);
            a3 = s2;
            a0 = s1;
            a1 = fp;
            a2 = s1;
            jal(ctx, 0x54C448u, gen::fn_sub_563C28_00563c28);
            a1 = 0;
            v0 = addiu(sp, 0x4);
            lw(a0, s1, 0);
            s0 = addu(v0, s0);
            s4 = addiu(s4, 1);
            link(ctx, 0x54C464u);  // $ra first: the delay slot below depends on it
            lw(a2, s0, 0);
            call(ctx, gen::fn_memset_00521408);
            lw(a0, s3, 0);
            a2 = s1;
            lw(v1, a0, 0);
            lw(v0, v1, 32);
            a1 = 1;
            jalr(ctx, 0x54C47Cu, v0.u());
            lw(a0, s3, 0);
            a2 = s2;
            a1 = 0;
            lw(v1, a0, 0);
            lw(v0, v1, 28);
            s3 = addiu(s3, 4);
            jalr(ctx, 0x54C498u, v0.u());
            v1 = slt(s4, s7);
            v0 = addiu(sp, 0x10);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054c4ac
    charge(ctx, 7);
    lw(v0, s6, adxt::kFlushedSmp);
    s1 = 0;
    v0 = addu(v0, s5);
    link(ctx, 0x54C4B8u);  // $ra first: the delay slot below depends on it
    sw(v0, s6, adxt::kFlushedSmp);
    call(ctx, gen::fn_sub_539830_00539830);
    if (i64(s7) > 0) {
        // 0x0054c4c8
        charge(ctx, 2);
        s4 = s7;
        s0 = addiu(s6, 24);
        for (;;) {
            // 0x0054c4d0
            charge(ctx, 11);
            lw(a0, s0, 0);
            s0 = addiu(s0, 4);
            a1 = 1;
            lw(v1, a0, 0);
            lw(v0, v1, 36);
            s4 = addiu(s4, -1);
            jalr(ctx, 0x54C4E4u, v0.u());
            v0 = srl(v0, 1);
            v1 = slt(v0, s1);
            if (v1 == 0) s1 = v0;
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0054c4fc
    charge(ctx, 7);
    link(ctx, 0x54C4FCu);  // $ra first: the delay slot below depends on it
    lw(a0, s6, adxt::kRna);
    call(ctx, gen::fn_hypotf_1_00541ac0);
    lw(v1, s6, adxt::kFlushedSmp);
    v0 = addu(s1, v0);
    v0 = subu(v0, v1);
    if (i64(v0) > 0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x0054c518
        charge(ctx, 12);
        lw(a0, s6, adxt::kRna);
        a1 = 0;
        jal(ctx, 0x54C51Cu, gen::fn_cosl_1_00541a78);
        lw(a0, s6, adxt::kRna);
        a1 = 0;
        jal(ctx, 0x54C528u, gen::fn_coshl_1_00541a90);
        lw(a0, s6, adxt::kRna);
        a1 = 1;
        jal(ctx, 0x54C534u, gen::fn_sub_560DB8_00560db8);
        v0 = 5;
        sb(v0, s6, adxt::kStat);
        ld(s0, sp, 0x20);
    }
    // 0x0054c548 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
}

// 0x0054C578 sub_54C578 -- 8 bytes; leaf frame (no stack)
// state 5: nothing (`jr $ra`). [adxt_ExecPlayEnd]
void sub_54C578(EEContext& ctx) {
    using namespace hg;
    // 0x0054c578
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0054C8C0 sub_54C8C0 -- 128 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the error check: a failed streamer or list streamer puts the player in state 6 (error -1). [adxt_ExecErrChk]
void sub_54C8C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054c8c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, adxt::kStm);
    a0 = v0;
    if (v0 != 0) {
        // 0x0054c8dc
        charge(ctx, 5);
        jal(ctx, 0x54C8DCu, gen::fn_sub_546368_00546368);
        v1 = 4;
        if (v0 == v1) {
            // 0x0054c8f0
            charge(ctx, 4);
            v0 = si(-1);
            v1 = 6;
            sh(v0, s0, adxt::kErrCode);
            sb(v1, s0, adxt::kStat);
            goto L_0054c900;
        }
        lw(a0, s0, adxt::kLsc);
        goto L_0054c904;
    }
L_0054c900:
    charge(ctx, 1);
    lw(a0, s0, adxt::kLsc);
L_0054c904:
    charge(ctx, 2);
    if (a0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0054c90c
        charge(ctx, 5);
        jal(ctx, 0x54C90Cu, gen::fn_sub_55D790_0055d790);
        v1 = 3;
        if (v0 != v1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0054c920
            charge(ctx, 5);
            v0 = 6;
            v1 = si(-1);
            sb(v0, s0, adxt::kStat);
            sh(v1, s0, adxt::kErrCode);
            ld(s0, sp, 0x0);
        }
    }
    // 0x0054c934 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0054C940 sub_54C940 -- 152 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// the end-of-input check: tell the decoder when a file / memory source has delivered everything. [adxt_ExecTermSupply]
void sub_54C940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054c940
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, adxt::kStm);
    if (v0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0054c95c
        charge(ctx, 4);
        jal(ctx, 0x54C95Cu, gen::fn_sub_548768_00548768);
        if (v0 == 0) {
            ld(s0, sp, 0x0);
        } else {
            // 0x0054c96c
            charge(ctx, 4);
            lb(v1, s0, adxt::kSource);
            v0 = sltiu(v1, 5);
            if (v0 == 0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x0054c97c
                charge(ctx, 6);
                v0 = sll(v1, 2);
                v1 = 0x7C0000;
                v1 = addu(v1, v0);
                lw(v1, v1, 12464);
                switch (v1.u()) {
                case 0x54C998u:  // table[0, 1]
                    // 0x0054c998
                    charge(ctx, 5);
                    link(ctx, 0x54C998u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, adxt::kStm);
                    call(ctx, gen::fn_sub_546368_00546368);
                    v1 = 3;
                    if (v0 != v1) {
                        ld(s0, sp, 0x0);
                    } else {
                        // 0x0054c9ac
                        charge(ctx, 4);
                        link(ctx, 0x54C9ACu);  // $ra first: the delay slot below depends on it
                        lw(a0, s0, adxt::kSjd);
                        call(ctx, gen::fn_sub_5420A0_005420a0);
                        ld(s0, sp, 0x0);
                    }
                    break;
                case 0x54C9C0u:  // table[2]
                    // 0x0054c9c0
                    charge(ctx, 2);
                    link(ctx, 0x54C9C0u);  // $ra first: the delay slot below depends on it
                    lw(a0, s0, adxt::kSjd);
                    call(ctx, gen::fn_sub_5420A0_005420a0);
                L_0054c9c8:
                    charge(ctx, 1);
                    ld(s0, sp, 0x0);
                    break;
                case 0x54C9C8u:  // table[3, 4]
                    goto L_0054c9c8;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
        }
    }
    // 0x0054c9cc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0054C9D8 sub_54C9D8 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// run one player (locked). [ADXT_ExecHndl]
void sub_54C9D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0054c9d8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x54C9E4u, gen::fn_sub_539848_00539848);
    a0 = s0;
    jal(ctx, 0x54C9ECu, gen::fn_sub_54CA08_0054ca08);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_539850_00539850(ctx);  // tail call
}

// 0x0054CA08 sub_54CA08 -- 196 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// run one player: its state's step, then the end-of-input and error checks. [adxt_ExecHndl]
void sub_54CA08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0054ca08
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (s0 == 0) {
        // 0x0054ca1c
        charge(ctx, 6);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, 12488);  // "E02080842 adxt_ExecHndl: parameter error"
        sp = addiu(sp, 0x10);
        gen::fn_sub_53AE08_0053ae08(ctx);  // tail call
        return;
    }
    // 0x0054ca38
    charge(ctx, 4);
    lb(v1, s0, adxt::kStat);
    v0 = 3;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 1;
    if (cc) {
        // 0x0054ca58
        charge(ctx, 2);
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = 2;
        if (cc) {
            // 0x0054ca70
            charge(ctx, 2);
            cc = v1 != v0;  // the condition, before the delay slot changes it
            v0 = 4;
            if (cc) {
                // 0x0054ca88
                charge(ctx, 2);
                cc = v1 != v0;  // the condition, before the delay slot changes it
                v0 = 5;
                if (cc) {
                    // 0x0054caa0
                    charge(ctx, 2);
                    if (v1 == v0) {
                        // 0x0054caa8 -- state 5, play end: nothing
                        charge(ctx, 2);
                        jal(ctx, 0x54CAA8u, gen::fn_sub_54C578_0054c578);
                    }
                } else {
                    // 0x0054ca90 -- state 4, decode end: pad with silence until the output has played out
                    charge(ctx, 4);
                    jal(ctx, 0x54CA90u, gen::fn_sub_54C370_0054c370);
                }
            } else {
                // 0x0054ca78 -- state 2, buffering: start the output once enough PCM is queued
                charge(ctx, 4);
                jal(ctx, 0x54CA78u, gen::fn_sub_54C100_0054c100);
            }
        } else {
            // 0x0054ca60 -- state 1, opening: the source, the header, the output set-up
            charge(ctx, 4);
            jal(ctx, 0x54CA60u, gen::fn_sub_54BCD8_0054bcd8);
        }
    } else {
        // 0x0054ca48 -- state 3, playing
        charge(ctx, 4);
        jal(ctx, 0x54CA48u, gen::fn_sub_54C288_0054c288);
    }
    // 0x0054cab0 -- every state: the end-of-input check, then the error check (tail call)
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x54CAB0u, gen::fn_sub_54C940_0054c940);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_54C8C0_0054c8c0(ctx);  // tail call
}

// 0x00539818 sub_539818 -- 20 bytes; frame 0x10: ra sp+0x0
// the ADX libraries' SVM lock (type 1 through sub_564978). [adxcrs_Lock]
void sub_539818(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00539818
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564978_00564978(ctx);  // tail call
}

// 0x00539830 sub_539830 -- 20 bytes; frame 0x10: ra sp+0x0
// the matching unlock (sub_564990). [adxcrs_Unlock]
void sub_539830(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00539830
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

}  // namespace p3fes::game
