// Phase 5 slice finalC: the last kernel / SDK leftovers of the final wave -- the libc stdio IOP file RPCs (sceRead,
// sceWrite, sceIoctl, sceSync, sceLseek64), libkernel syscall wrappers (_sce_SetTLBEntry, _sceSetVTLBRefillHandler,
// _sceSetVCommonHandler, _sce_GetGsDxDyOffset, Exit), the serial kputchar, libmpeg's IPU / scratchpad DMA feeders
// (_sendDataToIPU, _cpr8), libpad's scePadSetButtonInfo, dvCi's cache-file search, the alarm kernel payload body
// sub_77FFA0 and the data-band `break` word sub_7CC670. Written by p3fes_handgen from SLUS_216.21 and symbols/:
// every body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); hardware registers and syscalls go through the bus / the kernel hooks as the
// original. Role comment on top of each; pair tests: tests/game/test_finalC.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/finalC.h"

namespace p3fes::recomp_gen {
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceFlushCache_005033e0(p3fes::EEContext&);
void fn__sceFsSigSema_00508078(p3fes::EEContext&);
void fn__sceFsWaitS_00508048(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn_dvCiCdSearchFile_00559dd8(p3fes::EEContext&);
void fn_dvci_conv_fname_0055a9b0(p3fes::EEContext&);
void fn_get_iob_00507bc8(p3fes::EEContext&);
void fn_sceCdSync_00510148(p3fes::EEContext&);
void fn_sceFsInit_00508170(p3fes::EEContext&);
void fn_sceFsSifCallRpc_00507ad8(p3fes::EEContext&);
void fn_scePadSetReqState_00511b08(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sub_5067F8_005067f8(p3fes::EEContext&);
void fn_sub_50D998_0050d998(p3fes::EEContext&);
void fn_sub_5416E8_005416e8(p3fes::EEContext&);
void fn_sub_541760_00541760(p3fes::EEContext&);
void fn_sub_558988_00558988(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x004F9158 _sce_GetGsDxDyOffset -- 16 bytes; leaf frame (no stack)
// libgraph kernel wrapper (sceGsSetDefDispEnv's helper): one syscall with $v1 = 128, the GS DX / DY offset query;
// the kernel's answer stays in $v0. [proposed name: kept]
void _sce_GetGsDxDyOffset(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x004f9158
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 128;
    syscall(ctx, 0x4F915Cu);
}

// 0x005000B0 _sendDataToIPU -- 256 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// libmpeg: builds the source-chain DMA tag list for the IPU input (sceMpegAddBs) and kicks D4 (to IPU). The tags
// start at ($a0 + 4495) & ~15 (past the 4480-byte header of the stream work); the $a2 bytes at $a1 go out in pieces
// of at most 0xFFF40 bytes: each tag is qwc = (len + 15) >> 4 (len + 30 when the sum is negative), id 3 (ref) while
// more follows else 0 (refe), addr = src & 0x0FFFFFFF. Then FlushCache(0), DIntr, D4_TADR (0x1000B430) = the list
// (& 0x0FFFFFFF), D4_QWC (0x1000B420) = 0, D4_CHCR (0x1000B400) = 0x105 (chain, from memory, start), and EIntr when
// DIntr reported interrupts on. [proposed name: kept]
void _sendDataToIPU(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005000b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = addiu(a0, 4495);
    sd(s0, sp, 0x0);
    a0 = srl(a0, 4);
    s0 = sll(a0, 4);
    sd(ra, sp, 0x10);
    t3 = a1;
    t0 = a2;
    t2 = s0;
    if (i64(t0) > 0) {
        // 0x005000d8
        charge(ctx, 6);
        t1 = 0xF0000;
        t4 = 0xFFF0000;
        t1 = t1 | 0xFF40;
        t4 = t4 | 0xFFFF;
        t6 = 3;
        t5 = si(-1);
        for (;;) {
            // 0x005000f0
            charge(ctx, 23);
            v0 = slt(t1, t0);
            a3 = t1;
            if (v0 == 0) a3 = t0;
            v1 = 0;
            a2 = addiu(a3, 15);
            v0 = addiu(a3, 30);
            a1 = slt(t5, a2);
            t0 = subu(t0, a3);
            if (a1 != 0) v0 = a2;
            a0 = t3 & t4;
            if (t0 != 0) v1 = t6;
            v0 = sra(v0, 4);
            a0 = dsll32(a0, 0);
            v1 = dsll(v1, 28);
            v0 = dsll32(v0, 0);
            a0 = a0 | v1;
            v0 = dsrl32(v0, 0);
            a0 = a0 | v0;
            sd(a0, t2, 0);
            sync(ctx, 0);
            t3 = addu(t3, a3);
            t2 = addiu(t2, 16);
            if (i64(t0) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050014c
    charge(ctx, 19);
    a0 = 0;
    jal(ctx, 0x50014Cu, gen::fn__sceFlushCache_005033e0);
    jal(ctx, 0x500154u, gen::fn_DIntr_0050d3a0);
    v1 = 0xFFF0000;
    a1 = 0x10000000;
    v1 = v1 | 0xFFFF;
    a1 = a1 | 0xB430;
    v1 = s0 & v1;
    a0 = 0x10000000;
    sw(v1, a1, 0);  // 0x1000B430
    a0 = a0 | 0xB420;
    sw(zero, a0, 0);  // 0x1000B420
    v1 = 0x10000000;
    v1 = v1 | 0xB400;
    a0 = 261;
    sw(a0, v1, 0);  // 0x1000B400
    ld(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x005001a4
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00500198
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00501178 _cpr8 -- 656 bytes; frame 0xB0: s6 sp+0x70, s2 sp+0x30, ra sp+0xA0, fp sp+0x90, s7 sp+0x80, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// libmpeg (_dispRefImage / _dispRefImageField): copies a reference picture to the display image through the
// scratchpad. $a0 = the decoder state (+236 the reference plane, +244 the field stride selector, +248 the row step,
// +388 == 3 for a frame picture), $a1 = the destination image (+0 the plane, +12 the block count, +16 the width in
// macroblocks). One pass for a frame (stride s5 = width * 384, fp = the field stride), two for fields (stride halved,
// 192 per block). Per block: interrupts off (DIntr), D9 fromSPR (0x1000D400 .. D480) flushes the previous 16-byte
// chunk run (s2, s4 qwords) to memory with CHCR 0x101, EIntr, poll D9 STR; then D8 toSPR (0x1000D000 .. D080)
// loads the next chunk (s1) with CHCR 0x100, poll D8 STR and D8_QWC. [proposed name: kept]
void _cpr8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00501178
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0xFFF0000;
    sd(s6, sp, 0x70);
    v0 = v0 | 0xFFFF;
    sd(s2, sp, 0x30);
    s6 = a1;
    sw(a0, sp, 0x0);
    sd(ra, sp, 0xA0);
    sd(fp, sp, 0x90);
    sd(s7, sp, 0x80);
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    lw(a2, sp, 0x0);
    lw(v1, s6, 0);
    lw(a0, a0, 236);
    lw(a1, a2, 388);
    s2 = v1 & v0;
    a0 = a0 & v0;
    v1 = 3;
    sw(a0, sp, 0x8);
    if (a1 == v1) {
        // 0x005011ec
        charge(ctx, 3);
        lw(a3, sp, 0x0);
        lw(v1, a3, 244);
        lw(v0, s6, 16);
    L_005011f8:
        charge(ctx, 4);
        a0 = 384;
        mult(s5, v0, a0);
        s4 = sra(s5, 4);
        if (v1 == 0) {
            // 0x00501214
            charge(ctx, 1);
            fp = s5;
        } else {
            // 0x00501208
            charge(ctx, 3);
            v0 = sra(v1, 4);
            mult(fp, v0, a0);
        }
        // 0x00501218
        charge(ctx, 3);
        v0 = 1;
        sw(v0, sp, 0x4);
    } else {
        // 0x005011d8
        charge(ctx, 3);
        lw(a0, a2, 244);
        v1 = a0;
        if (a0 == 0) {
            // 0x005011e4
            charge(ctx, 2);
            lw(v0, s6, 16);
            goto L_005011f8;
        }
        // 0x00501224
        charge(ctx, 10);
        lw(v0, s6, 16);
        a1 = 384;
        v1 = 192;
        a0 = sra(a0, 4);
        v0 = sra(v0, 1);
        mult(fp, a0, v1);
        mult1(s5, v0, a1);
        v1 = 2;
        sw(v1, sp, 0x4);
        s4 = sra(s5, 4);
    }
    // 0x0050124c
    charge(ctx, 3);
    lw(a2, sp, 0x4);
    a1 = 0;
    if (a2 != 0) {
        // 0x00501258
        charge(ctx, 2);
        lw(a2, s6, 12);
        for (;;) {
            // 0x00501260
            charge(ctx, 3);
            lw(s1, sp, 0x8);
            s0 = 0;
            if (i64(a2) <= 0) {
                // 0x005013a4
                charge(ctx, 2);
                s7 = addiu(a1, 1);
                lw(a3, sp, 0x0);
            } else {
                // 0x0050126c
                charge(ctx, 1);
                s7 = addiu(a1, 1);
                for (;;) {
                    // 0x00501270
                    charge(ctx, 17);
                    jal(ctx, 0x501270u, gen::fn_DIntr_0050d3a0);
                    v1 = 0x10000000;
                    a1 = 0x10000000;
                    v1 = v1 | 0xD480;
                    a1 = a1 | 0xD410;
                    sw(zero, v1, 0);  // 0x1000D480
                    a0 = 0x10000000;
                    sw(s2, a1, 0);  // 0x1000D410
                    a0 = a0 | 0xD420;
                    a1 = 0x10000000;
                    sw(s4, a0, 0);  // 0x1000D420
                    a1 = a1 | 0xD400;
                    v1 = 257;
                    sw(v1, a1, 0);  // 0x1000D400
                    v1 = 0x10000000;
                    if (v0 != 0) {
                        // 0x005012b4
                        charge(ctx, 3);
                        jal(ctx, 0x5012B4u, gen::fn_EIntr_0050d3f0);
                        v1 = 0x10000000;
                    }
                    // 0x005012c0
                    charge(ctx, 4);
                    s3 = addu(s2, s5);
                    s0 = addiu(s0, 1);
                    s2 = addu(s1, fp);
                    v1 = v1 | 0xD400;
                    for (;;) {
                        // 0x005012d0
                        charge(ctx, 7);
                        lw(v0, v1, 0);
                        v0 = v0 & 0x100;
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x005012ec
                    charge(ctx, 17);
                    jal(ctx, 0x5012ECu, gen::fn_DIntr_0050d3a0);
                    v1 = 0x10000000;
                    a1 = 0x10000000;
                    v1 = v1 | 0xD080;
                    a1 = a1 | 0xD010;
                    sw(zero, v1, 0);  // 0x1000D080
                    a0 = 0x10000000;
                    sw(s1, a1, 0);  // 0x1000D010
                    a0 = a0 | 0xD020;
                    a1 = 0x10000000;
                    sw(s4, a0, 0);  // 0x1000D020
                    a1 = a1 | 0xD000;
                    v1 = 256;
                    sw(v1, a1, 0);  // 0x1000D000
                    v1 = 0x10000000;
                    if (v0 != 0) {
                        // 0x00501330
                        charge(ctx, 3);
                        jal(ctx, 0x501330u, gen::fn_EIntr_0050d3f0);
                        v1 = 0x10000000;
                    }
                    // 0x0050133c
                    charge(ctx, 3);
                    lw(a2, s6, 12);
                    v1 = v1 | 0xD000;
                    for (;;) {
                        // 0x00501348
                        charge(ctx, 7);
                        lw(v0, v1, 0);
                        v0 = v0 & 0x100;
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00501364
                    charge(ctx, 3);
                    v1 = 0x10000000;
                    v1 = v1 | 0xD020;
                    for (;;) {
                        // 0x00501370
                        charge(ctx, 7);
                        lw(v0, v1, 0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0050138c
                    charge(ctx, 4);
                    s1 = s2;
                    v0 = slt(s0, a2);
                    s2 = s3;
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0050139c
                charge(ctx, 2);
                lw(a3, sp, 0x0);
            }
            // 0x005013ac
            charge(ctx, 11);
            a1 = s7;
            v1 = 192;
            lw(v0, a3, 248);
            lw(a3, sp, 0x4);
            a0 = slt(a1, a3);
            lw(a3, sp, 0x8);
            mtlo(a3);
            madd(zero, v0, v1);
            mflo(a3);
            sw(a3, sp, 0x8);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x005013d8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xA0);
    ld(fp, sp, 0x90);
    ld(s7, sp, 0x80);
    ld(s6, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xB0);
}

// 0x00502E10 _sceSetVTLBRefillHandler -- 16 bytes; leaf frame (no stack)
// libkernel wrapper: syscall 13 (SetVTLBRefillHandler) with $a0 / $a1 as the kernel takes them; SetTLBHandler /
// SetDebugHandler call it. [proposed name: kept]
void _sceSetVTLBRefillHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e10
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 13;
    syscall(ctx, 0x502E14u);
}

// 0x00502E20 _sceSetVCommonHandler -- 16 bytes; leaf frame (no stack)
// libkernel wrapper: syscall 14 (SetVCommonHandler); SetDebugHandler calls it. [proposed name: kept]
void _sceSetVCommonHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e20
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 14;
    syscall(ctx, 0x502E24u);
}

// 0x00504BC0 kputchar -- 56 bytes; leaf frame (no stack)
// Kernel-side serial output (serialPutchar -> kprintf): spins while SIO_ISR (0x1000F130) bit 15 (TX FIFO full) is
// set, then writes the byte $a0 to SIO_TXFIFO (0x1000F180); $v0 = the byte. [proposed name: kept]
void kputchar(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00504bc0
    enter(ctx, 2);  // entry check point + this block's cycles
    v1 = 0x10000000;
    v1 = v1 | 0xF130;
    for (;;) {
        // 0x00504bc8
        charge(ctx, 7);
        lw(v0, v1, 0);
        v0 = v0 & 0x8000;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00504be4
    charge(ctx, 5);
    v1 = 0x10000000;
    v0 = a0;
    v1 = v1 | 0xF180;
    sb(a0, v1, 0);  // 0x1000F180
}

// 0x00508CB8 sceRead -- 620 bytes; frame 0xE0: fp sp+0xC0, s7 sp+0xB0, s5 sp+0x90, s1 sp+0x50, s0 sp+0x40, ra sp+0xD0, s6 sp+0xA0, s4 sp+0x80, s3 sp+0x70, s2 sp+0x60
// libc stdio (IOP file service RPC command 2): read $a2 bytes into $a1 from the descriptor $a0. Under the stdio lock
// (_sceFsWaitS 2) the iob of $a0 (get_iob; flags at +4) must exist and sceFsInit must have run (0x77F53C), else -9.
// The request packet at 0x968500: +0xC the IOP fd, +0x1C the iob index, +0x10 / +0x14 buffer and size, +4 the result
// slot, +8 = 4, +0 the "SceStdioReadSema" it creates. A non-blocking iob (flag 0x8000) registers that semaphore in the
// first free slot of the 32 at 0x77F4B8 under the lock 0x77F54C and sends its negative. The buffer is written back
// (sub_5067F8) unless flag 0x20000000, then the packet; sceFsSifCallRpc(0x969C00, 2, 32-byte packet, 4-byte reply at
// 0x969140): a failed call or a zero reply -> -11 after _sceFsSigSema; else the lock is released, the semaphore waited
// (blocking) and deleted, $v0 = the byte count the IOP stored at sp + 0x30 (or 0 for a non-blocking read).
// [proposed name: kept]
void sceRead(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508cb8
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(fp, sp, 0xC0);
    sd(s7, sp, 0xB0);
    fp = a2;
    sd(s5, sp, 0x90);
    s7 = a1;
    sd(s1, sp, 0x50);
    s5 = 0x970000;
    sd(s0, sp, 0x40);
    s1 = addiu(s5, -31488);  // &0x968500
    sd(ra, sp, 0xD0);
    sd(s6, sp, 0xA0);
    sd(s4, sp, 0x80);
    sd(s3, sp, 0x70);
    link(ctx, 0x508CF0u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x60);
    call(ctx, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 2;
    jal(ctx, 0x508CFCu, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        // 0x00508d14
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00508d28;
        }
        // 0x00508d1c
        charge(ctx, 3);
        lw(s4, s0, 4);
        v0 = 0x970000;
        if (s4 == 0) {
            goto L_00508d28;
        }
        // 0x00508d38
        charge(ctx, 24);
        lw(a0, s0, 0);
        v0 = addiu(v0, -26112);
        v1 = 0x7C0000;
        v0 = subu(s0, v0);
        sw(a0, s1, 12);
        v0 = sra(v0, 4);
        v1 = addiu(v1, -8664);  // "SceStdioReadSema"
        sw(v0, s1, 28);
        a1 = 1;
        sw(a1, sp, 0x14);
        a0 = addiu(sp, 0x10);
        sw(v1, sp, 0x24);
        s0 = s4 & 0x8000;
        sw(s7, s1, 16);
        sw(fp, s1, 20);
        link(ctx, 0x508D74u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s3 = v0;
        v1 = 4;
        v0 = addiu(sp, 0x30);
        sw(v1, s1, 8);
        sw(v0, s1, 4);
        sw(s3, s5, -31488);
        if (s0 == 0) {
            // 0x00508e24
            charge(ctx, 3);
            s0 = 0x970000;
            s2 = 0;
            s6 = 0x20000000;
        } else {
            // 0x00508d98
            charge(ctx, 9);
            s6 = 0x780000;
            link(ctx, 0x508D9Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s6, -2740);  // 0x77F54C
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a3 = 0x780000;
            a2 = 0;
            lw(v1, a3, -2888);  // 0x77F4B8
            v0 = si(-1);
            s2 = s0;
            if (v1 != v0) {
                // 0x00508dd8
                charge(ctx, 2);
                s0 = 0x970000;
                a2 = addiu(a2, 1);
                for (;;) {
                    // 0x00508de0
                    charge(ctx, 3);
                    v0 = slti(a2, 32);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = sll(a2, 2);
                    if (cc) {
                        break;
                    }
                    // 0x00508dec
                    charge(ctx, 6);
                    v1 = addiu(a3, -2888);
                    a1 = addu(v0, v1);
                    a0 = si(-1);
                    lw(v0, a1, 0);
                    a2 = addiu(a2, 1);
                    if (v0 == a0) {
                        goto L_00508e04_10;
                    }
                    backedge(ctx);
                }
            } else {
                // 0x00508dbc
                charge(ctx, 6);
                lw(v1, s5, -31488);
                s0 = 0x970000;
                v0 = subu(0, v1);
                sw(v1, a3, -2888);
                sw(v0, s5, -31488);
            }
        L_00508e14:
            charge(ctx, 4);
            link(ctx, 0x508E14u);  // $ra first: the delay slot below depends on it
            lw(a0, s6, -2740);
            call(ctx, gen::fn__sceSignalSema_00503180);
            s6 = 0x20000000;
        }
        // 0x00508e30
        charge(ctx, 3);
        v0 = s4 & s6;
        a0 = s1;
        if (v0 == 0) {
            // 0x00508e3c
            charge(ctx, 4);
            a0 = s7;
            a1 = fp;
            jal(ctx, 0x508E40u, gen::fn_sub_5067F8_005067f8);
            a0 = s1;
        }
        // 0x00508e4c
        charge(ctx, 17);
        a1 = 32;
        jal(ctx, 0x508E4Cu, gen::fn_sub_5067F8_005067f8);
        s0 = addiu(s0, -28352);
        v0 = 0x970000;
        a3 = addiu(s5, -31488);
        a0 = addiu(v0, -25600);  // &0x969C00
        sw(zero, sp, 0x0);
        a1 = 2;
        sw(s2, sp, 0x8);
        a2 = 0;
        t0 = 32;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x508E80u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = s6 | s0;
        if (cc) {
            // 0x00508ea8
            charge(ctx, 4);
            link(ctx, 0x508EA8u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x00508ec8
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x00508ee0
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x508EE0u, gen::fn__sceWaitSema_005031a0);
                    a0 = s3;
                    jal(ctx, 0x508EE8u, gen::fn__sceDeleteSema_00503170);
                    lw(v0, sp, 0x30);
                } else {
                    // 0x00508ed0
                    charge(ctx, 4);
                    a0 = s3;
                    jal(ctx, 0x508ED0u, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                }
            } else {
                // 0x00508eb8
                charge(ctx, 4);
                a0 = s3;
                jal(ctx, 0x508EB8u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x00508e90
            charge(ctx, 6);
            a0 = s3;
            jal(ctx, 0x508E90u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x508E98u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x00508ef4 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0xD0);
        ld(fp, sp, 0xC0);
        ld(s7, sp, 0xB0);
        ld(s6, sp, 0xA0);
        ld(s5, sp, 0x90);
        ld(s4, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0xE0);
        return;
    }
L_00508d28:
    charge(ctx, 4);
    jal(ctx, 0x508D28u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x00508ef4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xD0);
    ld(fp, sp, 0xC0);
    ld(s7, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xE0);
    return;
L_00508e04_10:
    charge(ctx, 4);
    lw(v0, s1, 0);
    v1 = subu(0, v0);
    sw(v0, a1, 0);
    sw(v1, s1, 0);
    goto L_00508e14;
}

// 0x00508F28 sceWrite -- 704 bytes; frame 0xE0: s6 sp+0xA0, s1 sp+0x50, fp sp+0xC0, s2 sp+0x60, s0 sp+0x40, ra sp+0xD0, s7 sp+0xB0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70
// libc stdio (IOP file service RPC command 3): write $a2 bytes from $a1 to the descriptor $a0. The same shape as
// sceRead with a 48-byte packet and the "SceStdioWriteSema": -9 without an iob or before sceFsInit, -11 on a failed
// call or an empty reply, else the IOP's byte count (0 for a non-blocking iob). [proposed name: kept]
void sceWrite(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508f28
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(s6, sp, 0xA0);
    sd(s1, sp, 0x50);
    s6 = a2;
    sd(fp, sp, 0xC0);
    s1 = a1;
    sd(s2, sp, 0x60);
    fp = 0x970000;
    sd(s0, sp, 0x40);
    s2 = addiu(fp, -0x7B00);
    sd(ra, sp, 0xD0);
    sd(s7, sp, 0xB0);
    sd(s5, sp, 0x90);
    sd(s4, sp, 0x80);
    link(ctx, 0x508F60u);  // $ra first: the delay slot below depends on it
    sd(s3, sp, 0x70);
    call(ctx, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 3;
    jal(ctx, 0x508F6Cu, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        // 0x00508f84
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00508f98;
        }
        // 0x00508f8c
        charge(ctx, 3);
        lw(s7, s0, 4);
        v0 = 0x970000;
        if (s7 == 0) {
            goto L_00508f98;
        }
        // 0x00508fa8
        charge(ctx, 24);
        lw(a0, s0, 0);
        v0 = addiu(v0, -26112);
        v1 = 0x7C0000;
        v0 = subu(s0, v0);
        sw(a0, s2, 12);
        v0 = sra(v0, 4);
        v1 = addiu(v1, -8640);  // "SceStdioWriteSema"
        sw(v0, s2, 44);
        a1 = 1;
        sw(a1, sp, 0x14);
        a0 = addiu(sp, 0x10);
        sw(v1, sp, 0x24);
        s0 = s7 & 0x8000;
        sw(s6, s2, 20);
        sw(s1, s2, 16);
        link(ctx, 0x508FE4u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s5 = v0;
        v1 = 4;
        v0 = addiu(sp, 0x30);
        sw(v1, s2, 8);
        sw(v0, s2, 4);
        sw(s5, fp, -0x7B00);
        if (s0 == 0) {
            // 0x00509094
            charge(ctx, 2);
            s0 = s1 & 0xF;
            s4 = 0;
        } else {
            // 0x00509008
            charge(ctx, 9);
            s3 = 0x780000;
            link(ctx, 0x50900Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s3, -2740);  // 0x77F54C
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a3 = 0x780000;
            a2 = 0;
            lw(v1, a3, -2888);  // 0x77F4B8
            v0 = si(-1);
            s4 = s0;
            if (v1 != v0) {
                // 0x00509048
                charge(ctx, 2);
                s0 = s1 & 0xF;
                a2 = addiu(a2, 1);
                for (;;) {
                    // 0x00509050
                    charge(ctx, 3);
                    v0 = slti(a2, 32);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = sll(a2, 2);
                    if (cc) {
                        break;
                    }
                    // 0x0050905c
                    charge(ctx, 6);
                    v1 = addiu(a3, -2888);
                    a1 = addu(v0, v1);
                    a0 = si(-1);
                    lw(v0, a1, 0);
                    a2 = addiu(a2, 1);
                    if (v0 == a0) {
                        goto L_00509074_10;
                    }
                    backedge(ctx);
                }
            } else {
                // 0x0050902c
                charge(ctx, 6);
                lw(v1, fp, -0x7B00);
                s0 = s1 & 0xF;
                v0 = subu(0, v1);
                sw(v1, a3, -2888);
                sw(v0, fp, -0x7B00);
            }
        L_00509084:
            charge(ctx, 4);
            link(ctx, 0x509084u);  // $ra first: the delay slot below depends on it
            lw(a0, s3, -2740);
            call(ctx, gen::fn__sceSignalSema_00503180);
        }
        // 0x0050909c
        charge(ctx, 2);
        v0 = srl(s1, 4);
        if (s0 != 0) {
            // 0x005090ac
            charge(ctx, 3);
            v1 = addiu(s1, -16);
            v0 = sll(v0, 4);
            s0 = subu(v0, v1);
        } else {
            // 0x005090a4
            charge(ctx, 2);
            s0 = 0;
        }
        // 0x005090b8
        charge(ctx, 5);
        v1 = slt(s6, s0);
        s3 = 0x20000000;
        v0 = s7 & s3;
        if (v1 != 0) s0 = s6;
        if (v0 == 0) {
            // 0x005090cc
            charge(ctx, 3);
            a1 = s6;
            a0 = s1;
            jal(ctx, 0x5090D0u, gen::fn_sub_5067F8_005067f8);
        }
        // 0x005090d8
        charge(ctx, 4);
        s1 = s1 | s3;
        sw(s0, s2, 24);
        a1 = 0;
        if (i64(s0) > 0) {
            // 0x005090e8
            charge(ctx, 2);
            a2 = addiu(s2, 28);
            for (;;) {
                // 0x005090f0
                charge(ctx, 8);
                v0 = addu(s1, a1);
                a0 = addu(a2, a1);
                lbu(v1, v0, 0);
                a1 = addiu(a1, 1);
                v0 = slt(a1, s0);
                sb(v1, a0, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00509110
        charge(ctx, 16);
        v0 = 0x970000;
        a3 = addiu(fp, -0x7B00);
        s0 = addiu(v0, -28352);  // &0x969140
        sw(zero, sp, 0x0);
        v0 = 0x970000;
        sw(s4, sp, 0x8);
        a0 = addiu(v0, -25600);  // &0x969C00
        a1 = 3;
        a2 = 0;
        t0 = 48;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x509140u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x00509168
            charge(ctx, 5);
            v0 = s0 | v0;
            link(ctx, 0x50916Cu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x0050918c
                charge(ctx, 2);
                if (s4 == 0) {
                    // 0x005091a4
                    charge(ctx, 5);
                    a0 = s5;
                    jal(ctx, 0x5091A4u, gen::fn__sceWaitSema_005031a0);
                    a0 = s5;
                    jal(ctx, 0x5091ACu, gen::fn__sceDeleteSema_00503170);
                    lw(v0, sp, 0x30);
                } else {
                    // 0x00509194
                    charge(ctx, 4);
                    a0 = s5;
                    jal(ctx, 0x509194u, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                }
            } else {
                // 0x0050917c
                charge(ctx, 4);
                a0 = s5;
                jal(ctx, 0x50917Cu, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x00509150
            charge(ctx, 6);
            a0 = s5;
            jal(ctx, 0x509150u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x509158u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x005091b8 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0xD0);
        ld(fp, sp, 0xC0);
        ld(s7, sp, 0xB0);
        ld(s6, sp, 0xA0);
        ld(s5, sp, 0x90);
        ld(s4, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0xE0);
        return;
    }
L_00508f98:
    charge(ctx, 4);
    jal(ctx, 0x508F98u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x005091b8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0xD0);
    ld(fp, sp, 0xC0);
    ld(s7, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xE0);
    return;
L_00509074_10:
    charge(ctx, 4);
    lw(v0, s2, 0);
    v1 = subu(0, v0);
    sw(v0, a1, 0);
    sw(v1, s2, 0);
    goto L_00509084;
}

// 0x005091E8 sceIoctl -- 904 bytes; frame 0xC0: s2 sp+0x60, s1 sp+0x50, s6 sp+0xA0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70, s0 sp+0x40, ra sp+0xB0
// libc stdio (IOP file service RPC command 5): ioctl request $a1 (packet +0x10) on the descriptor $a0 with the
// 1024-byte argument at $a2 (copied to packet +0x14, zeros for a null argument), the "SceStdioIoctlSema", a 1056-byte
// packet.
// -9 without an iob or before sceFsInit, -11 on a failed call or an empty reply, else the IOP's result.
// [proposed name: kept]
void sceIoctl(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005091e8
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s2, sp, 0x60);
    sd(s1, sp, 0x50);
    s2 = a2;
    sd(s6, sp, 0xA0);
    s1 = a1;
    sd(s5, sp, 0x90);
    s6 = 0x970000;
    sd(s4, sp, 0x80);
    s5 = 1;
    sd(s3, sp, 0x70);
    s4 = 0x970000;
    sd(s0, sp, 0x40);
    sd(ra, sp, 0xB0);
    s3 = addiu(s6, -31488);  // &0x968500
    jal(ctx, 0x509220u, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 5;
    jal(ctx, 0x50922Cu, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    sw(s2, s4, -31544);  // 0x9684C8
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 == 0) {
        // 0x00509248
        charge(ctx, 2);
        jal(ctx, 0x509248u, gen::fn_sceFsInit_00508170);
    }
    // 0x00509250
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00509258
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 == 0) {
            goto L_00509264;
        }
        sw(zero, s3, 1044);
        // 0x00509274
        charge(ctx, 3);
        v0 = 2;
        sw(zero, s3, 1048);
        if (s1 == v0) {
            // 0x00509320
            charge(ctx, 12);
            a0 = 0x780000;
            a1 = 1088;
            lw(v0, a0, -2760);  // 0x77F538
            v1 = 0x970000;
            v1 = addiu(v1, -28272);  // &0x969190
            a0 = 0x20000000;
            mult(v0, v0, a1);
            v0 = addu(v0, v1);
            v0 = v0 | a0;
            lw(v1, v0, 0);
            sw(v1, s2, 0);
        L_00509378:
            charge(ctx, 4);
            jal(ctx, 0x509378u, gen::fn__sceFsSigSema_00508078);
            v0 = 0;
        } else {
            // 0x00509280
            charge(ctx, 3);
            v0 = slti(s1, 3);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 3;
            if (!cc) {
                // 0x0050928c
                charge(ctx, 2);
                if (s1 != s5) {
                    // 0x00509294
                    charge(ctx, 2);
                    lw(v0, s0, 0);
                    goto L_00509388;
                }
                s0 = 0x780000;
                // 0x005092ac
                charge(ctx, 8);
                link(ctx, 0x5092ACu);  // $ra first: the delay slot below depends on it
                lw(a0, s0, -2740);
                call(ctx, gen::fn__sceWaitSema_005031a0);
                a1 = 0x780000;
                a0 = 0;
                lw(v1, a1, -2888);  // 0x77F4B8
                v0 = si(-1);
                cc = v1 != v0;  // the condition, before the delay slot changes it
                v0 = 32;
                if (!cc) {
                    // 0x005092cc
                    charge(ctx, 3);
                    v1 = addiu(a1, -2888);
                    a1 = si(-1);
                    a0 = addiu(a0, 1);
                    for (;;) {
                        // 0x005092d8
                        charge(ctx, 3);
                        v0 = slti(a0, 32);
                        v1 = addiu(v1, 4);
                        if (v0 != 0) {
                            // 0x005092e4
                            charge(ctx, 3);
                            lw(v0, v1, 0);
                            if (v0 == a1) {
                                a0 = addiu(a0, 1);
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                    // 0x005092f0
                    charge(ctx, 1);
                    v0 = 32;
                }
                // 0x005092f4
                charge(ctx, 2);
                lw(v1, s4, -31544);
                if (a0 != v0) {
                    // 0x00509308
                    charge(ctx, 2);
                    v0 = 1;
                    sw(v0, v1, 0);
                } else {
                    // 0x005092fc
                    charge(ctx, 3);
                    lw(v0, s4, -31544);
                    sw(zero, v0, 0);
                }
                // 0x00509310
                charge(ctx, 4);
                link(ctx, 0x509310u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, -2740);
                call(ctx, gen::fn__sceSignalSema_00503180);
                goto L_00509378;
            }
            // 0x0050929c
            charge(ctx, 2);
            a0 = 0x780000;
            if (s1 == v0) {
                // 0x00509350
                charge(ctx, 10);
                a1 = 1088;
                lw(v0, a0, -2760);
                v1 = 0x970000;
                v1 = addiu(v1, -28272);  // &0x969190
                a0 = 0x20000000;
                mult(v0, v0, a1);
                v0 = addu(v0, v1);
                v0 = v0 | a0;
                ld(v1, v0, 0);
                sd(v1, s2, 0);
                goto L_00509378;
            }
            // 0x005092a4
            charge(ctx, 2);
            lw(v0, s0, 0);
        L_00509388:
            charge(ctx, 3);
            sw(s1, s3, 16);
            sw(v0, s3, 12);
            if (s2 == 0) {
                // 0x00509394
                charge(ctx, 6);
                sw(zero, s3, 1052);
                v1 = 0x7C0000;
                s2 = addiu(sp, 0x30);
                s5 = 0x970000;
                s1 = 0x970000;
                goto L_00509480;
            }
            // 0x005093ac
            charge(ctx, 7);
            a2 = s2;
            a0 = addiu(s3, 20);
            v1 = 1024;
            v0 = a2 | a0;
            v0 = v0 & 0x7;
            sw(v1, s3, 1052);
            if (v0 == 0) {
                // 0x00509438
                charge(ctx, 5);
                v0 = addiu(a2, 1024);
                v1 = 0x7C0000;
                s2 = addiu(sp, 0x30);
                s5 = 0x970000;
                s1 = 0x970000;
                for (;;) {
                    // 0x0050944c
                    charge(ctx, 13);
                    ld(a1, a2, 0);
                    ld(a3, a2, 8);
                    ld(t0, a2, 16);
                    ld(t1, a2, 24);
                    sd(a1, a0, 0);
                    sd(a3, a0, 8);
                    sd(t0, a0, 16);
                    sd(t1, a0, 24);
                    a2 = addiu(a2, 32);
                    a0 = addiu(a0, 32);
                    if (a2 == v0) {
                        break;
                    }
                    backedge(ctx);
                }
            L_00509480:
                charge(ctx, 1);
                v1 = addiu(v1, -8616);
            } else {
                // 0x005093c8
                charge(ctx, 5);
                v0 = addiu(a2, 1024);
                v1 = 0x7C0000;
                s2 = addiu(sp, 0x30);
                s5 = 0x970000;
                s1 = 0x970000;
                for (;;) {
                    // 0x005093dc
                    charge(ctx, 21);
                    ldl(a1, a2, 7);
                    ldr(a1, a2, 0);
                    ldl(a3, a2, 15);
                    ldr(a3, a2, 8);
                    ldl(t0, a2, 23);
                    ldr(t0, a2, 16);
                    ldl(t1, a2, 31);
                    ldr(t1, a2, 24);
                    sdl(a1, a0, 7);
                    sdr(a1, a0, 0);
                    sdl(a3, a0, 15);
                    sdr(a3, a0, 8);
                    sdl(t0, a0, 23);
                    sdr(t0, a0, 16);
                    sdl(t1, a0, 31);
                    sdr(t1, a0, 24);
                    a2 = addiu(a2, 32);
                    a0 = addiu(a0, 32);
                    if (a2 == v0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00509430
                charge(ctx, 2);
                v1 = addiu(v1, -8616);
            }
            // 0x00509484
            charge(ctx, 29);
            v0 = 1;
            sw(v0, sp, 0x14);
            a0 = addiu(sp, 0x10);
            sw(v1, sp, 0x24);
            s4 = addiu(s1, -28352);
            sw(zero, sp, 0x18);
            s0 = addiu(s6, -31488);
            jal(ctx, 0x50949Cu, gen::fn__sceCreateSema_00503160);
            s1 = v0;
            a0 = s0;
            v0 = 4;
            sw(s2, s3, 4);
            sw(v0, s3, 8);
            a1 = 1056;
            link(ctx, 0x5094BCu);  // $ra first: the delay slot below depends on it
            sw(s1, s3, 0);
            call(ctx, gen::fn_sub_5067F8_005067f8);
            a0 = addiu(s5, -25600);
            a3 = s0;
            sw(zero, sp, 0x0);
            a1 = 5;
            sw(zero, sp, 0x8);
            a2 = 0;
            t0 = 1056;
            t1 = s4;
            t2 = 4;
            t3 = 0;
            jal(ctx, 0x5094E8u, gen::fn_sceFsSifCallRpc_00507ad8);
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 0x20000000;
            if (cc) {
                // 0x00509510
                charge(ctx, 5);
                v0 = s4 | v0;
                link(ctx, 0x509514u);  // $ra first: the delay slot below depends on it
                lw(s0, v0, 0);
                call(ctx, gen::fn__sceFsSigSema_00508078);
                if (s0 != 0) {
                    // 0x00509534
                    charge(ctx, 5);
                    a0 = s1;
                    jal(ctx, 0x509534u, gen::fn__sceWaitSema_005031a0);
                    a0 = s1;
                    jal(ctx, 0x50953Cu, gen::fn__sceDeleteSema_00503170);
                    lw(v0, sp, 0x30);
                } else {
                    // 0x00509524
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x509524u, gen::fn__sceDeleteSema_00503170);
                    v0 = si(-11);
                }
            } else {
                // 0x005094f8
                charge(ctx, 6);
                a0 = s1;
                jal(ctx, 0x5094F8u, gen::fn__sceDeleteSema_00503170);
                jal(ctx, 0x509500u, gen::fn__sceFsSigSema_00508078);
                v0 = si(-11);
            }
        }
        // 0x00509548 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0xB0);
        ld(s6, sp, 0xA0);
        ld(s5, sp, 0x90);
        ld(s4, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0xC0);
        return;
    }
L_00509264:
    charge(ctx, 4);
    jal(ctx, 0x509264u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x00509548 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xC0);
}

// 0x0050A888 sceSync -- 428 bytes; frame 0xC0: s1 sp+0x50, s5 sp+0x90, s6 sp+0xA0, s0 sp+0x40, ra sp+0xB0, s4 sp+0x80, s3 sp+0x70, s2 sp+0x60
// libc stdio (IOP file service RPC command 19): sync the device named at $a0 with the mode $a1. Runs sceFsInit when
// it has not run; copies the name (up to 1024 bytes, the terminator cleared at 1024) into the packet at 0x968514,
// creates the "SceStdioSyncSema", 1044-byte packet; -11 on a failed call or an empty reply, else the IOP's result.
// [proposed name: kept]
void sceSync(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050a888
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s1, sp, 0x50);
    sd(s5, sp, 0x90);
    s1 = a0;
    sd(s6, sp, 0xA0);
    s5 = a1;
    sd(s0, sp, 0x40);
    a0 = 19;
    sd(ra, sp, 0xB0);
    s6 = 0x970000;
    sd(s4, sp, 0x80);
    s0 = addiu(s6, -31488);  // &0x968500
    sd(s3, sp, 0x70);
    link(ctx, 0x50A8BCu);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x60);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s1, 0);
    } else {
        // 0x0050a8d4
        charge(ctx, 3);
        jal(ctx, 0x50A8D4u, gen::fn_sceFsInit_00508170);
        lbu(v0, s1, 0);
    }
    // 0x0050a8e0
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s0, 20);
    if (v1 == 0) {
        // 0x0050a934
        charge(ctx, 4);
        a2 = 0x7C0000;
        s2 = addiu(sp, 0x30);
        s4 = 0x970000;
        s3 = 0x970000;
    L_0050a944:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050a8f0
        charge(ctx, 6);
        a2 = 0x7C0000;
        s2 = addiu(sp, 0x30);
        s4 = 0x970000;
        s3 = 0x970000;
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050a908
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, a1);
            if (cc) {
                goto L_0050a944;
            }
            // 0x0050a914
            charge(ctx, 6);
            a0 = addu(s0, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 20);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x0050a92c
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050a948
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s0, 1043);
    }
    // 0x0050a950
    charge(ctx, 27);
    sw(s5, s0, 16);
    v1 = addiu(a2, -8352);
    v0 = 1;
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x14);
    s3 = addiu(s3, -28352);
    sw(v1, sp, 0x24);
    link(ctx, 0x50A96Cu);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    sw(s2, s0, 4);
    v0 = 4;
    sw(s1, s0, 0);
    sw(v0, s0, 8);
    a0 = addiu(s4, -25600);
    a3 = addiu(s6, -31488);
    a1 = 19;
    sw(zero, sp, 0x0);
    a2 = 0;
    sw(zero, sp, 0x8);
    t0 = 1044;
    t1 = s3;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50A9ACu, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x0050a9d4
        charge(ctx, 5);
        v0 = s3 | v0;
        link(ctx, 0x50A9D8u);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x0050a9f8
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x50A9F8u, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x50AA00u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x0050a9e8
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x50A9E8u, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050a9bc
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x50A9BCu, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x50A9C4u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x0050aa0c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xC0);
}

// 0x0050ACD8 sceLseek64 -- 572 bytes; frame 0xC0: s5 sp+0x90, s3 sp+0x70, s4 sp+0x80, s1 sp+0x50, s0 sp+0x40, ra sp+0xB0, s6 sp+0xA0, s2 sp+0x60
// libc stdio (IOP file service RPC command 22): 64-bit seek on the descriptor $a0 to the offset $a1 (low / high at
// +0x10 / +0x14) with the whence $a2 (+0x18); the "SceStdioLseek64Sema", 32-byte packet, the 8-byte reply in $v0.
// -9 without an iob or before sceFsInit, -11 on a failed call or an empty reply. [proposed name: kept]
void sceLseek64(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050acd8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s5, sp, 0x90);
    sd(s3, sp, 0x70);
    s5 = a2;
    sd(s4, sp, 0x80);
    s3 = a1;
    sd(s1, sp, 0x50);
    s4 = 0x970000;
    sd(s0, sp, 0x40);
    s1 = addiu(s4, -31488);  // &0x968500
    sd(ra, sp, 0xB0);
    sd(s6, sp, 0xA0);
    link(ctx, 0x50AD08u);  // $ra first: the delay slot below depends on it
    sd(s2, sp, 0x60);
    call(ctx, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 22;
    jal(ctx, 0x50AD14u, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        // 0x0050ad2c
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_0050ad40;
        }
        // 0x0050ad34
        charge(ctx, 3);
        lw(s2, s0, 4);
        v0 = 0x970000;
        if (s2 == 0) {
            goto L_0050ad40;
        }
        // 0x0050ad50
        charge(ctx, 24);
        lw(a0, s0, 0);
        v0 = addiu(v0, -26112);
        v1 = 0x7C0000;
        v0 = subu(s0, v0);
        sw(a0, s1, 12);
        v0 = sra(v0, 4);
        sd(s3, s1, 16);
        sw(s5, s1, 24);
        v1 = addiu(v1, -8304);  // "SceStdioLseek64Sema"
        sw(v0, s1, 28);
        a1 = 1;
        a0 = addiu(sp, 0x10);
        sw(a1, sp, 0x14);
        sw(v1, sp, 0x24);
        s0 = s2 & 0x8000;
        link(ctx, 0x50AD8Cu);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s3 = v0;
        v1 = 8;
        v0 = addiu(sp, 0x30);
        sw(v1, s1, 8);
        sw(v0, s1, 4);
        sw(s3, s4, -31488);
        if (s0 == 0) {
            // 0x0050ae40
            charge(ctx, 4);
            s6 = 0x970000;
            s0 = 0x970000;
            s2 = 0;
            s0 = addiu(s0, -28352);  // &0x969140
        } else {
            // 0x0050adb0
            charge(ctx, 9);
            s5 = 0x780000;
            link(ctx, 0x50ADB4u);  // $ra first: the delay slot below depends on it
            lw(a0, s5, -2740);  // 0x77F54C
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a3 = 0x780000;
            a2 = 0;
            lw(v1, a3, -2888);  // 0x77F4B8
            v0 = si(-1);
            s2 = s0;
            if (v1 != v0) {
                // 0x0050adf0
                charge(ctx, 3);
                s6 = 0x970000;
                s0 = 0x970000;
                a2 = addiu(a2, 1);
                for (;;) {
                    // 0x0050adfc
                    charge(ctx, 3);
                    v0 = slti(a2, 32);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = sll(a2, 2);
                    if (cc) {
                        break;
                    }
                    // 0x0050ae08
                    charge(ctx, 6);
                    v1 = addiu(a3, -2888);
                    a1 = addu(v0, v1);
                    a0 = si(-1);
                    lw(v0, a1, 0);
                    a2 = addiu(a2, 1);
                    if (v0 == a0) {
                        goto L_0050ae20_10;
                    }
                    backedge(ctx);
                }
            } else {
                // 0x0050add4
                charge(ctx, 7);
                lw(v1, s4, -31488);
                s6 = 0x970000;
                s0 = 0x970000;
                v0 = subu(0, v1);
                sw(v1, a3, -2888);
                sw(v0, s4, -31488);
            }
        L_0050ae30:
            charge(ctx, 4);
            link(ctx, 0x50AE30u);  // $ra first: the delay slot below depends on it
            lw(a0, s5, -2740);
            call(ctx, gen::fn__sceSignalSema_00503180);
            s0 = addiu(s0, -28352);
        }
        // 0x0050ae50
        charge(ctx, 13);
        a0 = addiu(s6, -25600);
        a3 = addiu(s4, -31488);
        sw(zero, sp, 0x0);
        sw(s2, sp, 0x8);
        a1 = 22;
        a2 = 0;
        t0 = 32;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50AE74u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x0050ae9c
            charge(ctx, 5);
            v0 = s0 | v0;
            link(ctx, 0x50AEA0u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x0050aec0
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x0050aed8
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x50AED8u, gen::fn__sceWaitSema_005031a0);
                    a0 = s3;
                    jal(ctx, 0x50AEE0u, gen::fn__sceDeleteSema_00503170);
                    ld(v0, sp, 0x30);
                } else {
                    // 0x0050aec8
                    charge(ctx, 4);
                    a0 = s3;
                    jal(ctx, 0x50AEC8u, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                }
            } else {
                // 0x0050aeb0
                charge(ctx, 4);
                a0 = s3;
                jal(ctx, 0x50AEB0u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x0050ae84
            charge(ctx, 6);
            a0 = s3;
            jal(ctx, 0x50AE84u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x50AE8Cu, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x0050aeec (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0xB0);
        ld(s6, sp, 0xA0);
        ld(s5, sp, 0x90);
        ld(s4, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0xC0);
        return;
    }
L_0050ad40:
    charge(ctx, 4);
    jal(ctx, 0x50AD40u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x0050aeec (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xC0);
    return;
L_0050ae20_10:
    charge(ctx, 4);
    lw(v0, s1, 0);
    v1 = subu(0, v0);
    sw(v0, a1, 0);
    sw(v1, s1, 0);
    goto L_0050ae30;
}

// 0x0050CD60 _sce_SetTLBEntry -- 16 bytes; leaf frame (no stack)
// libkernel wrapper: syscall 86 (the TLB entry set-up SetTLBEntry / InitTLB32MB use). [proposed name: kept]
void _sce_SetTLBEntry(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050cd60
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 86;
    syscall(ctx, 0x50CD64u);
}

// 0x0050DA58 Exit -- 56 bytes, 2 chunks; frame 0x20: s0 sp+0x0, ra sp+0x10
// libkernel Exit: runs the exit hook sub_50D998 first (with $a0 kept in $s0 and restored), then its second chunk at
// 0x502D80 issues syscall 4 (Exit) with the status in $a0. Two chunks: 0x50DA58 and 0x502D80. [proposed name: kept]
void Exit(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050da58
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x50DA64u, gen::fn_sub_50D998_0050d998);
    a0 = s0;
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    backedge(ctx);
    // 0x00502d80
    charge(ctx, 4);
    v1 = 4;
    syscall(ctx, 0x502D84u);
}

// 0x005122C0 scePadSetButtonInfo -- 176 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x30, s1 sp+0x20, ra sp+0x40
// libpad (scePadEnterPressMode / scePadExitPressMode): RPC command 10 for the port $a0, slot $a1 and the mode $a2 in
// the pad request buffer 0x96DF00 (+0 func, +4 port, +8 slot, +0xC param) through sceSifCallRpc on the pad client
// 0x96DCC0 (128 bytes each way): a failed call -> 0; a reply (+0x10) of 1 also sets the request state 2
// (scePadSetReqState); $v0 = the reply. [proposed name: kept]
void scePadSetButtonInfo(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005122c0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x970000;
    sd(s0, sp, 0x10);
    v1 = 10;
    s0 = addiu(v0, -8448);  // &pad_rpc_buf
    sd(s2, sp, 0x30);
    sd(s1, sp, 0x20);
    s2 = a0;
    sd(ra, sp, 0x40);
    s1 = a1;
    sw(a2, s0, 12);  // pad_rpc_buf+0xC
    a0 = 0x970000;
    sw(v1, v0, -8448);  // pad_rpc_buf
    a0 = addiu(a0, -9024);  // &pad_rpc_cd0
    sw(s2, s0, 4);  // pad_rpc_buf+0x4
    a1 = 1;
    sw(s1, s0, 8);  // pad_rpc_buf+0x8
    a2 = 0;
    sw(zero, sp, 0x0);
    a3 = s0;
    t0 = 128;
    t1 = s0;
    t2 = 128;
    t3 = 0;
    jal(ctx, 0x51231Cu, gen::fn_sceSifCallRpc_00507230);
    if (i64(v0) >= 0) {
        lw(v1, s0, 16);  // pad_rpc_buf+0x10
        // 0x00512334
        charge(ctx, 3);
        v0 = 1;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = v1;
        if (!cc) {
            // 0x00512340
            charge(ctx, 6);
            a0 = s2;
            a1 = s1;
            a2 = 2;
            jal(ctx, 0x512348u, gen::fn_scePadSetReqState_00511b08);
            lw(v1, s0, 16);
            v0 = v1;
        }
    } else {
        // 0x0051232c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00512358 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x0055AEA0 dvci_search_fstate -- 400 bytes; frame 0x90: s6 sp+0x70, s4 sp+0x60, s5 sp+0x68, s7 sp+0x78, s0 sp+0x40, s1 sp+0x48, s2 sp+0x50, s3 sp+0x58, fp sp+0x80, ra sp+0x88
// dvCi (dvCiLoadFcache): resolves the $a1 cache-file entries of the table $a0 on the disc. The table holds $a1
// (sector, size) pairs, then the names, each 0x7A2A6C + 1 bytes after the 8 * 0x7A2A68 pair bytes. For each non-empty
// name: dvci_conv_fname into 0x7A2B88, trace mark 37888, wait while sceCdSync(1) == 1, marks 37889 / 38144,
// dvCiCdSearchFile(out[2], name) == 1 stores the pair into the entry and prints "DVCI: \"%s\" found." (sub_5416E8),
// else counts a miss (sp + 0x30) and prints "Not found.". Then "DVCI: Total %d files." and, with misses, the
// "Can't load all cache file" warning (sub_541760); $v0 = the found count. [proposed name: kept]
void dvci_search_fstate(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0055aea0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s6, sp, 0x70);
    s6 = a1;
    sd(s4, sp, 0x60);
    s4 = 0;
    sd(s5, sp, 0x68);
    s5 = a0;
    sd(s7, sp, 0x78);
    s7 = 0;
    sd(s0, sp, 0x40);
    sd(s1, sp, 0x48);
    sd(s2, sp, 0x50);
    sd(s3, sp, 0x58);
    sd(fp, sp, 0x80);
    sd(ra, sp, 0x88);
    sw(zero, sp, 0x30);
    if (i64(s6) > 0) {
        // 0x0055aee4
        charge(ctx, 3);
        v0 = 0x7A0000;
        s2 = s5;
        fp = addiu(v0, 0x2A60);  // &0x7A2A60
        for (;;) {
            // 0x0055aef0
            charge(ctx, 10);
            lw(v0, fp, 0xC);
            lw(v1, fp, 0x8);
            mult(a0, v0, s4);
            v1 = sll(v1, 3);
            v0 = addu(a0, s4);
            v1 = addu(v1, v0);
            s1 = addu(s5, v1);
            lb(v0, s1, 0);
            s3 = 0x7A0000;
            if (v0 != 0) {
                // 0x0055af18
                charge(ctx, 6);
                a0 = s1;
                a1 = addiu(s3, 11144);
                jal(ctx, 0x55AF1Cu, gen::fn_dvci_conv_fname_0055a9b0);
                a0 = 0x9400;
                jal(ctx, 0x55AF24u, gen::fn_sub_558988_00558988);
                s0 = 1;
                for (;;) {
                    // 0x0055af30
                    charge(ctx, 4);
                    a0 = 1;
                    jal(ctx, 0x55AF30u, gen::fn_sceCdSync_00510148);
                    if (v0 != s0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0055af40
                charge(ctx, 10);
                a0 = 0x9401;
                jal(ctx, 0x55AF40u, gen::fn_sub_558988_00558988);
                a0 = 0x9500;
                jal(ctx, 0x55AF48u, gen::fn_sub_558988_00558988);
                a1 = addiu(s3, 11144);
                a0 = sp;
                jal(ctx, 0x55AF54u, gen::fn_dvCiCdSearchFile_00559dd8);
                v1 = 1;
                if (v0 != v1) {
                    lw(v1, sp, 0x30);
                    // 0x0055afa0
                    charge(ctx, 8);
                    a0 = 0x9502;
                    v1 = addiu(v1, 1);
                    link(ctx, 0x55AFA8u);  // $ra first: the delay slot below depends on it
                    sw(v1, sp, 0x30);
                    call(ctx, gen::fn_sub_558988_00558988);
                    v0 = 0x7C0000;
                    a1 = s1;
                    a0 = addiu(v0, 20064);  // "DVCI: \"%s\" Not found.\n"
                    jal(ctx, 0x55AFB8u, gen::fn_sub_5416E8_005416e8);
                    goto L_0055afc0;
                }
                // 0x0055af68
                charge(ctx, 13);
                a0 = 0x9501;
                s7 = addiu(s7, 1);
                jal(ctx, 0x55AF6Cu, gen::fn_sub_558988_00558988);
                v0 = 0x7C0000;
                lw(v1, sp, 0x0);
                a0 = addiu(v0, 20040);  // "DVCI: \"%s\" found.\n"
                lw(v0, sp, 0x4);
                a1 = s1;
                sw(v1, s2, 0);
                link(ctx, 0x55AF8Cu);  // $ra first: the delay slot below depends on it
                sw(v0, s2, 4);
                call(ctx, gen::fn_sub_5416E8_005416e8);
                s4 = addiu(s4, 1);
                goto L_0055afc4;
            }
        L_0055afc0:
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        L_0055afc4:
            charge(ctx, 3);
            v0 = slt(s4, s6);
            s2 = addiu(s2, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0055afd0
    charge(ctx, 7);
    a0 = 0x7C0000;
    a1 = s7;
    a0 = addiu(a0, 20088);  // "DVCI: Total %d files.\n"
    jal(ctx, 0x55AFD8u, gen::fn_sub_5416E8_005416e8);
    lw(v1, sp, 0x30);
    v0 = s7;
    if (i64(v1) > 0) {
        // 0x0055afec
        charge(ctx, 5);
        a0 = 0x7C0000;
        a1 = 10;
        a0 = addiu(a0, 20112);  // "DVCI: Warning, Can't load all cache file.%c"
        jal(ctx, 0x55AFF4u, gen::fn_sub_541760_00541760);
        v0 = s7;
    }
    // 0x0055b000 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x40);
    ld(s1, sp, 0x48);
    ld(s2, sp, 0x50);
    ld(s3, sp, 0x58);
    ld(s4, sp, 0x60);
    ld(s5, sp, 0x68);
    ld(s6, sp, 0x70);
    ld(s7, sp, 0x78);
    ld(fp, sp, 0x80);
    ld(ra, sp, 0x88);
    sp = addiu(sp, 0x90);
}

// 0x0077FFA0 sub_77FFA0 -- 208 bytes; frame 0x10: ra sp+0x0
// What it is: the alarm kernel payload's body (kpayload_alarm, docs/ANALYSIS/06_ghidra_crosscheck.md): it lies past
// the main game text and has 0 callers at its file address because the blob is copied to 0x80074000.. and run in
// kernel mode; its seven calls go through the payload's own pointer table at 0x8007474C..0x80074764. Acknowledges
// INTC_STAT (0x1000F000) bit 2, spins until the bit is set, acknowledges again, then calls +0x4760 (), +0x4764
// (1, 2, 1), +0x474C (0xDFFD), +0x4750 (), +0x475C (127), +0x4754 () and +0x4758 (), whose result it returns.
// [proposed name: kpayload_alarm_body]
void sub_77FFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0077ffa0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x10000000;
    sd(ra, sp, 0x0);
    v1 = 4;
    v0 = v0 | 0xF000;
    a0 = 0x10000000;
    sw(v1, v0, 0);  // 0x1000F000
    a0 = a0 | 0xF000;
    for (;;) {
        // 0x0077ffc0
        charge(ctx, 7);
        lw(v0, a0, 0);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0077ffdc
    charge(ctx, 37);
    v0 = 0x10000000;
    a0 = 4;
    v0 = v0 | 0xF000;
    v1 = lui(0x8007);
    sw(a0, v0, 0);  // 0x1000F000
    lw(v0, v1, 18272);  // 0x80074760
    jalr(ctx, 0x77FFF4u, v0.u());
    v0 = lui(0x8007);
    a1 = 2;
    lw(v1, v0, 18276);  // 0x80074764
    a2 = 1;
    a0 = 1;
    jalr(ctx, 0x78000Cu, v1.u());
    v0 = lui(0x8007);
    lw(v1, v0, 18252);  // 0x8007474C
    a0 = 0xDFFD;
    jalr(ctx, 0x78001Cu, v1.u());
    v0 = lui(0x8007);
    lw(v1, v0, 18256);  // 0x80074750
    jalr(ctx, 0x78002Cu, v1.u());
    v0 = lui(0x8007);
    lw(v1, v0, 18268);  // 0x8007475C
    a0 = 127;
    jalr(ctx, 0x78003Cu, v1.u());
    v0 = lui(0x8007);
    lw(v1, v0, 18260);  // 0x80074754
    jalr(ctx, 0x78004Cu, v1.u());
    v0 = lui(0x8007);
    lw(v1, v0, 18264);  // 0x80074758
    jalr(ctx, 0x78005Cu, v1.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x007CC670 sub_7CC670 -- 4 bytes; leaf frame (no stack)
// What it is: not code. One `break 0x10D` word inside the data band (IDA artefact: 0 callers, 1 data reference,
// docs/ANALYSIS/00_elf_layout.md); the body is that trap, reached only if something jumps into the data.
// [proposed name: kept]
void sub_7CC670(EEContext& ctx) {
    using namespace hg;
    // 0x007cc670
    enter(ctx, 1);  // entry check point + this block's cycles
    brk(ctx, 0x7CC670u, 0x10Du);
    rt::unreachable(0x7CC674u);
}

}  // namespace p3fes::game

// The recompiled program's entry points fn_<name>_<addr8> are generated from game/replaced.txt (game/forwarders.cmake).
