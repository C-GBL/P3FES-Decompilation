// libmpeg's handle layer (0x500AD0-0x5024F0): the sceMpeg accessors and setters over the decoder state that the
// sceMpeg handle's word +64 points at (the record cri2 named, game/include/p3fes/game/cri2.h `cri2::mpeg`), the callback
// dispatchers, the work-area allocator, the field-picture display hand-off and the default error report. Library API
// names are the FLIRT names of symbols/functions.json (ADR-0009); no SDK material was used.
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass (scratch spec.py, checked by check.py) adds the
// role comments and the named offsets of game/include/p3fes/game/libs1_mpeg.h, each equal to the literal it replaces.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs1_mpeg.h"
#include "p3fes/game/cri2.h"

namespace p3fes::recomp_gen {
void fn__ErrMessage_005024f0(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn__clearOnce_004ffda8(p3fes::EEContext&);
void fn__cpr8_00501178(p3fes::EEContext&);
void fn__dispRefImageField_005016c8(p3fes::EEContext&);
void fn__getpic_00500278(p3fes::EEContext&);
void fn__sceMpegAlalcInit_00501068(p3fes::EEContext&);
void fn__sceMpegAlalcReset_00501110(p3fes::EEContext&);
void fn__sceMpegAlalcSetDynamic_00501080(p3fes::EEContext&);
void fn__sceMpegCscStoreRefImage_00501df8(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCallback_00500d10(p3fes::EEContext&);
void fn__sceMpegDispatchMpegCbNodata_00500d88(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegSetBrokenLink_00500f70(p3fes::EEContext&);
void fn__sceMpegSetPtm_00500f80(p3fes::EEContext&);
void fn__sendDataToIPU_005000b0(p3fes::EEContext&);
void fn_sceMpegAddBs_00500ad8(p3fes::EEContext&);
void fn_sceMpegAddCallback_00500c90(p3fes::EEContext&);
void fn_sceMpegClearRefBuff_00500e48(p3fes::EEContext&);
void fn_sceMpegDelete_00500ad0(p3fes::EEContext&);
void fn_sceMpegDispCenterOffX_00500f50(p3fes::EEContext&);
void fn_sceMpegDispCenterOffY_00500f60(p3fes::EEContext&);
void fn_sceMpegDispHeight_00500f40(p3fes::EEContext&);
void fn_sceMpegDispWidth_00500f30(p3fes::EEContext&);
void fn_sceMpegGetBuffType_00500d00(p3fes::EEContext&);
void fn_sceMpegGetDecodeMode_00500c70(p3fes::EEContext&);
void fn_sceMpegGetPictureAbort_00500ba8(p3fes::EEContext&);
void fn_sceMpegGetPictureRAW8_00500b60(p3fes::EEContext&);
void fn_sceMpegGetPictureRAW8xy_00500ea0(p3fes::EEContext&);
void fn_sceMpegGetPicture_00500b18(p3fes::EEContext&);
void fn_sceMpegIsEnd_00500c38(p3fes::EEContext&);
void fn_sceMpegIsRefBuffEmpty_00500c48(p3fes::EEContext&);
void fn_sceMpegResetDefaultPtsGap_00500f08(p3fes::EEContext&);
void fn_sceMpegSetBuffType_00500cc8(p3fes::EEContext&);
void fn_sceMpegSetDecodeMode_00500c58(p3fes::EEContext&);
void fn_sceMpegSetDefaultPtsGap_00500ef0(p3fes::EEContext&);
void fn_sceMpegSetImageBuff_00500f20(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceSnprintf_00505d90(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace mp = ::p3fes::game::cri2::mpeg;

// 0x00500AD0 sceMpegDelete -- 8 bytes; leaf frame (no stack)
// Delete a decoder: nothing to release in this build; returns 1.
void sceMpegDelete(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00500ad0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x00500AD8 sceMpegAddBs -- 60 bytes; frame 0x10: ra sp+0x0
// Feed a bitstream chunk to the IPU: rounds (size + 19) / 16 down to whole quadwords (towards zero for negative sums)
// and hands the state, the data and that length to _sendDataToIPU; returns 1.
void sceMpegAddBs(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500ad8
    enter(ctx, 15);  // entry check point + this block's cycles
    v1 = addiu(a2, 19);
    sp = addiu(sp, -0x10);
    v0 = si(-1);
    sd(ra, sp, 0x0);
    a2 = addiu(a2, 34);
    v0 = slt(v0, v1);
    if (v0 != 0) a2 = v1;
    lw(a0, a0, 64);
    a2 = sra(a2, 4);
    a2 = sll(a2, 4);
    jal(ctx, 0x500AFCu, gen::fn__sendDataToIPU_005000b0);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00500B18 sceMpegGetPicture -- 72 bytes; frame 0x10: ra sp+0x0
// Decode the next picture as RGB32: output format 1 (colour-space converted), the image buffer as an uncached
// (0x20000000) address, the buffer size, no x / y offsets; tail-calls _getpic.
void sceMpegGetPicture(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500b18
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0xFFF0000;
    sd(ra, sp, 0x0);
    v0 = v0 | 0xFFFF;
    a1 = a1 & v0;
    v1 = 0x20000000;
    lw(a3, a0, mp::kInner);
    a1 = a1 | v1;
    v0 = 1;
    sw(v0, a3, libs1::mpeg::kOutCsc);
    sw(a1, a3, mp::kImageBuf);
    sw(a2, a3, libs1::mpeg::kOutSize);
    sw(zero, a3, libs1::mpeg::kOutX);
    link(ctx, 0x500B4Cu);  // $ra first: the delay slot below depends on it
    sw(zero, a3, libs1::mpeg::kOutY);
    call(ctx, gen::fn__getpic_00500278);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00500B60 sceMpegGetPictureRAW8 -- 68 bytes; frame 0x10: ra sp+0x0
// Decode the next picture as raw 8-bit YCbCr macroblocks: the image buffer (uncached, written as a doubleword: +240
// is cleared with it), the buffer size, output format 0, y offset 0; tail-calls _getpic.
void sceMpegGetPictureRAW8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500b60
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0xFFF0000;
    sd(ra, sp, 0x0);
    v0 = v0 | 0xFFFF;
    a1 = a1 & v0;
    v1 = 0x20000000;
    lw(a3, a0, mp::kInner);
    a1 = a1 | v1;
    sw(a2, a3, libs1::mpeg::kOutSize);
    sw(a1, a3, mp::kImageBuf);
    sw(zero, a3, libs1::mpeg::kOutX);
    sw(zero, a3, libs1::mpeg::kOutCsc);
    link(ctx, 0x500B90u);  // $ra first: the delay slot below depends on it
    sw(zero, a3, libs1::mpeg::kOutY);
    call(ctx, gen::fn__getpic_00500278);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00500BA8 sceMpegGetPictureAbort -- 16 bytes; leaf frame (no stack)
// Ask the running _getpic to stop (the abort flag +2168); returns 1.
void sceMpegGetPictureAbort(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500ba8
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    v0 = 1;
    sw(v0, v1, mp::kAbort);
}

// 0x00500C38 sceMpegIsEnd -- 12 bytes; leaf frame (no stack)
// The end-of-stream flag (state +0).
void sceMpegIsEnd(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500c38
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, mp::kEnd);
}

// 0x00500C48 sceMpegIsRefBuffEmpty -- 16 bytes; leaf frame (no stack)
// 1 when no reference picture is held (state +4 == 0).
void sceMpegIsRefBuffEmpty(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500c48
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, mp::kFrameNo);
    v0 = sltiu(v0, 1);
}

// 0x00500C58 sceMpegSetDecodeMode -- 20 bytes; leaf frame (no stack)
// Set the decode-or-skip limits for I / P / B pictures (state +168 / +172 / +176); returns the state pointer.
void sceMpegSetDecodeMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00500c58
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, mp::kInner);
    sw(a3, v0, mp::kSkipB);
    sw(a1, v0, mp::kSkipI);
    sw(a2, v0, mp::kSkipP);
}

// 0x00500C70 sceMpegGetDecodeMode -- 32 bytes; leaf frame (no stack)
// Read the three decode-or-skip limits into *a1 / *a2 / *a3; returns the B limit.
void sceMpegGetDecodeMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00500c70
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(t0, a0, mp::kInner);
    lw(v0, t0, mp::kSkipI);
    sw(v0, a1, 0);
    lw(v1, t0, mp::kSkipP);
    sw(v1, a2, 0);
    lw(v0, t0, mp::kSkipB);
    sw(v0, a3, 0);
}

// 0x00500C90 sceMpegAddCallback -- 52 bytes; leaf frame (no stack)
// Install the callback of a type (12-byte slots from state +12: function, data, the caller's $gp); returns the old
// function.
void sceMpegAddCallback(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x00500c90
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = 12;
    lw(t0, a0, 64);
    mult(a1, a1, v0);
    v1 = addiu(t0, 12);
    v1 = addu(v1, a1);
    a0 = addu(t0, a1);
    lw(v0, v1, 0);
    sw(a2, v1, 0);
    sw(a3, a0, 16);
    v1 = gp;
    t0 = a0;
    sw(v1, t0, 20);
}

// 0x00500CC8 sceMpegSetBuffType -- 52 bytes; frame 0x10: ra sp+0x0
// Set the reference buffers' address space (0 uncached, 1 cached; state +2172) and re-clear them through _clearOnce;
// -1 for any other type, else 1.
void sceMpegSetBuffType(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500cc8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = sltiu(a1, 2);
    sd(ra, sp, 0x0);
    lw(a0, a0, 64);
    if (v0 != 0) {
        // 0x00500ce4
        charge(ctx, 3);
        link(ctx, 0x500CE4u);  // $ra first: the delay slot below depends on it
        sw(a1, a0, 2172);
        call(ctx, gen::fn__clearOnce_004ffda8);
        v0 = 1;
    } else {
        // 0x00500cdc
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00500cf0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00500D00 sceMpegGetBuffType -- 12 bytes; leaf frame (no stack)
// The reference buffers' address space (state +2172).
void sceMpegGetBuffType(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500d00
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, mp::kBufType);
}

// 0x00500D10 _sceMpegDispatchMpegCallback -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// Call the callback installed for the record's type (the record's first word) with (handle, record, its data); 0 when
// the handle, its state or the slot is empty, else the callback's result (a jalr: the frame and $ra as the original).
void _sceMpegDispatchMpegCallback(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00500d10
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t1 = 0;
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x00500d24
        charge(ctx, 3);
        lw(a2, a0, 64);
        t0 = 12;
        if (a2 == 0) {
            goto L_00500d74;
        }
        // 0x00500d30
        charge(ctx, 6);
        lw(v1, a1, 0);
        mult(v1, v1, t0);
        v0 = addu(a2, v1);
        lw(a3, v0, 12);
        ld(ra, sp, 0x10);
        if (a3 != 0) {
            // 0x00500d48
            charge(ctx, 11);
            lw(v1, v0, 20);
            s0 = gp;
            gp = v1;
            lw(v0, a1, 0);
            mult(v1, v0, t0);
            v0 = addu(v1, a2);
            jt = a3.u();  // the target, read before the delay slot
            link(ctx, 0x500D60u);  // $ra = the return address
            lw(a2, v0, 16);
            call_ptr(ctx, jt);
            t1 = v0;
            v0 = gp;
            gp = s0;
            goto L_00500d74;
        }
        // 0x00500d78 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        v0 = t1;
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_00500d74:
    charge(ctx, 1);
    ld(ra, sp, 0x10);
    // 0x00500d78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v0 = t1;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00500D88 _sceMpegDispatchMpegCbNodata -- 116 bytes; frame 0x40: ra sp+0x30, s0 sp+0x20
// Call the NODATA callback (type 1) with a stack record {1} when one is installed; returns 1 either way.
void _sceMpegDispatchMpegCbNodata(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00500d88
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 1;
    sd(ra, sp, 0x30);
    sd(s0, sp, 0x20);
    sw(v0, sp, 0x0);
    if (a0 != 0) {
        // 0x00500da0
        charge(ctx, 3);
        lw(a2, a0, 64);
        ld(ra, sp, 0x30);
        if (a2 == 0) {
        L_00500df0:
            charge(ctx, 1);
            ld(s0, sp, 0x20);
        } else {
            // 0x00500dac
            charge(ctx, 3);
            lw(a3, a2, 24);
            ld(s0, sp, 0x20);
            if (a3 != 0) {
                // 0x00500db8
                charge(ctx, 12);
                lw(v0, a2, 32);
                s0 = gp;
                gp = v0;
                lw(v1, sp, 0x0);
                v0 = 12;
                a1 = sp;
                mult(t0, v1, v0);
                v1 = addu(t0, a2);
                jt = a3.u();  // the target, read before the delay slot
                link(ctx, 0x500DD8u);  // $ra = the return address
                lw(a2, v1, 16);
                call_ptr(ctx, jt);
                v1 = gp;
                gp = s0;
                goto L_00500de8;
            }
        }
        // 0x00500df4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x40);
        return;
    }
L_00500de8:
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    v0 = 1;
    goto L_00500df0;
}

// 0x00500E48 sceMpegClearRefBuff -- 84 bytes; leaf frame (no stack)
// Mark the six reference-picture descriptors (forward / backward, frame and both fields: state +456.. +492) as not
// complete (their word +40 = 0); returns 1.
void sceMpegClearRefBuff(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500e48
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, mp::kRefFwd);
    if (v0 != 0) {
        sw(zero, v0, 40);
    }
    // 0x00500e58
    charge(ctx, 3);
    lw(v0, v1, 472);
    if (v0 != 0) {
        sw(zero, v0, 40);
    }
    // 0x00500e64
    charge(ctx, 3);
    lw(v0, v1, 488);
    if (v0 != 0) {
        sw(zero, v0, 40);
    }
    // 0x00500e70
    charge(ctx, 3);
    lw(v0, v1, mp::kRefBwd);
    if (v0 != 0) {
        sw(zero, v0, 40);
    }
    // 0x00500e7c
    charge(ctx, 3);
    lw(v0, v1, 476);
    if (v0 != 0) {
        sw(zero, v0, 40);
    }
    // 0x00500e88
    charge(ctx, 3);
    lw(v0, v1, 492);
    if (v0 != 0) {
        sw(zero, v0, 40);
    }
    // 0x00500e94
    charge(ctx, 2);
    v0 = 1;
}

// 0x00500EA0 sceMpegGetPictureRAW8xy -- 80 bytes; frame 0x10: ra sp+0x0
// Decode the next picture as raw macroblocks into a buffer of a2 x a3 macroblocks: x / y in pixels (16 x), the
// macroblock count, output format 0; tail-calls _getpic.
void sceMpegGetPictureRAW8xy(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00500ea0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0xFFF0000;
    sd(ra, sp, 0x0);
    mult(t0, a2, a3);
    v0 = v0 | 0xFFFF;
    a2 = sll(a2, 4);
    a1 = a1 & v0;
    lw(v1, a0, mp::kInner);
    v0 = 0x20000000;
    a3 = sll(a3, 4);
    a1 = a1 | v0;
    sw(a3, v1, libs1::mpeg::kOutY);
    sw(a1, v1, mp::kImageBuf);
    sw(t0, v1, libs1::mpeg::kOutSize);
    sw(a2, v1, libs1::mpeg::kOutX);
    link(ctx, 0x500EDCu);  // $ra first: the delay slot below depends on it
    sw(zero, v1, libs1::mpeg::kOutCsc);
    call(ctx, gen::fn__getpic_00500278);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00500EF0 sceMpegSetDefaultPtsGap -- 24 bytes; leaf frame (no stack)
// Set the default PTS gap (u64 at state +144) and its valid flag (+140); returns 1.
void sceMpegSetDefaultPtsGap(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00500ef0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 64);
    v0 = 1;
    a0 = 1;
    sd(a1, v1, 144);
    sw(a0, v1, 140);
}

// 0x00500F08 sceMpegResetDefaultPtsGap -- 20 bytes; leaf frame (no stack)
// Clear the default PTS gap and its flag; returns 1.
void sceMpegResetDefaultPtsGap(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500f08
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    v0 = 1;
    sd(zero, v1, libs1::mpeg::kPtsGap);
    sw(zero, v1, libs1::mpeg::kPtsGapSet);
}

// 0x00500F20 sceMpegSetImageBuff -- 16 bytes; leaf frame (no stack)
// Set the image buffer (state +236); returns 1.
void sceMpegSetImageBuff(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00500f20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    v0 = 1;
    sw(a1, v1, mp::kImageBuf);
}

// 0x00500F30 sceMpegDispWidth -- 12 bytes; leaf frame (no stack)
// The display width (state +224).
void sceMpegDispWidth(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500f30
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, libs1::mpeg::kDispWidth);
}

// 0x00500F40 sceMpegDispHeight -- 12 bytes; leaf frame (no stack)
// The display height (state +228).
void sceMpegDispHeight(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00500f40
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, libs1::mpeg::kDispHeight);
}

// 0x00500F50 sceMpegDispCenterOffX -- 12 bytes; leaf frame (no stack)
// The address of the display-centre record (state + 200). (Both the X and the Y accessor return this same address in
// this build.)
void sceMpegDispCenterOffX(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00500f50
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 64);
    v0 = addiu(v0, 200);
}

// 0x00500F60 sceMpegDispCenterOffY -- 12 bytes; leaf frame (no stack)
// The address of the display-centre record (state + 200), as sceMpegDispCenterOffX.
void sceMpegDispCenterOffY(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00500f60
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 64);
    v0 = addiu(v0, 200);
}

// 0x00500F70 _sceMpegSetBrokenLink -- 16 bytes; leaf frame (no stack)
// Set the pending broken-link flag (state +252); returns the old one.
void _sceMpegSetBrokenLink(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00500f70
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, mp::kInner);
    lw(v0, v1, mp::kBrokenLinkPend);
    sw(a1, v1, mp::kBrokenLinkPend);
}

// 0x00500F80 _sceMpegSetPtm -- 24 bytes; leaf frame (no stack)
// Set the presentation time (u64 at state +256) and its flag (+264); returns 1.
void _sceMpegSetPtm(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00500f80
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a2, a0, mp::kInner);
    v1 = 1;
    v0 = 1;
    sw(v1, a2, libs1::mpeg::kPtmSet);
    sd(a1, a2, libs1::mpeg::kPtm);
}

// 0x00501068 _sceMpegAlalcInit -- 20 bytes; leaf frame (no stack)
// Initialise a work-area allocator {base, size, cursor, dynamic mark}: cursor and mark at the base.
void _sceMpegAlalcInit(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00501068
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(a1, a0, libs1::mpeg::alalc::kMark);
    sw(a2, a0, libs1::mpeg::alalc::kSize);
    sw(a1, a0, libs1::mpeg::alalc::kBase);
    sw(a1, a0, libs1::mpeg::alalc::kCursor);
}

// 0x00501080 _sceMpegAlalcSetDynamic -- 12 bytes; leaf frame (no stack)
// Remember the cursor as the dynamic mark (what _sceMpegAlalcFree rewinds to).
void _sceMpegAlalcSetDynamic(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00501080
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, libs1::mpeg::alalc::kCursor);
    sw(v0, a0, libs1::mpeg::alalc::kMark);
}

// 0x00501110 _sceMpegAlalcReset -- 24 bytes; leaf frame (no stack)
// Bytes left in the allocator: base + size - cursor.
void _sceMpegAlalcReset(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00501110
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, libs1::mpeg::alalc::kBase);
    lw(v1, a0, libs1::mpeg::alalc::kSize);
    lw(a1, a0, libs1::mpeg::alalc::kCursor);
    v0 = addu(v0, v1);
    v0 = subu(v0, a1);
}

// 0x005016C8 _dispRefImageField -- 1056 bytes; frame 0x1B0: fp sp+0x190, s4 sp+0x150, s2 sp+0x130, ra sp+0x1A0, s7 sp+0x180, s6 sp+0x170, s5 sp+0x160, s3 sp+0x140, s1 sp+0x120, s0 sp+0x110
// Hand a decoded field pair to the display (a0 = the decoder state, a1 / a2 = the two field descriptors, top first
// unless the picture structure +388 is 2): fills the output-info record (+2152) with each field's PTS (its own, else
// extrapolated from the default PTS gap, or a pending PTM) and DTS and its coded flags, sets the display size (+224 /
// +228) and centre (+200 / +204), checks the image buffer is large enough ("Too small buffer ... for %dx%d picture"
// through sceSnprintf and _sceMpegError otherwise), then converts with _sceMpegCscStoreRefImage (RGB32) or copies
// with _cpr8 (raw), by the output format.
void _dispRefImageField(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x005016c8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    v0 = 2;
    sd(fp, sp, 0x190);
    sd(s4, sp, 0x150);
    fp = a2;
    sd(s2, sp, 0x130);
    s4 = a1;
    sd(ra, sp, 0x1A0);
    s2 = a0;
    sd(s7, sp, 0x180);
    sd(s6, sp, 0x170);
    sd(s5, sp, 0x160);
    sd(s3, sp, 0x140);
    sd(s1, sp, 0x120);
    sd(s0, sp, 0x110);
    lw(v1, s2, 388);
    sw(zero, sp, 0x100);
    if (v1 != v0) {
        // 0x00501724
        charge(ctx, 2);
        s5 = fp;
        s6 = s4;
    } else {
        // 0x00501710
        charge(ctx, 5);
        v0 = 64;
        s5 = s4;
        s6 = fp;
        sw(v0, sp, 0x100);
    }
    // 0x0050172c
    charge(ctx, 8);
    lw(s3, s2, 2152);
    lw(t1, s2, 140);
    v1 = addiu(s3, 24);
    v0 = addiu(s3, 32);
    s7 = addiu(s3, 16);
    sw(v1, sp, 0x104);
    sw(v0, sp, 0x108);
    if (t1 == 0) {
        // 0x005017d8
        charge(ctx, 3);
        ld(v1, s5, 24);
        sd(v1, s7, 0);
    } else {
        // 0x0050174c
        charge(ctx, 3);
        ld(v1, s5, 24);
        if (i64(v1) >= 0) {
            sd(v1, s7, 0);
        } else {
            // 0x00501758
            charge(ctx, 3);
            lw(v0, s2, 152);
            if (i64(v0) < 0) {
                sd(v1, s7, 0);
            } else {
                // 0x00501764
                charge(ctx, 24);
                ld(a1, s2, 160);
                lw(s0, s2, 156);
                a1 = dsll32(a1, 0);
                a1 = dsra32(a1, 0);
                ld(a0, s2, 144);
                s1 = a1 & 0x1;
                s0 = s0 & 0x1;
                s0 = s1 & s0;
                v0 = a0 & 0x1;
                s0 = s0 & v0;
                s0 = dsll32(s0, 0);
                s0 = dsra32(s0, 0);
                // daddu a1: a 64-bit move to itself (no effect)
                jal(ctx, 0x501794u, gen::fn___muldi3_0052ea78);
                v0 = dsll(v0, 31);
                v0 = dsra32(v0, 0);
                lw(v1, s2, 152);
                v0 = addu(v0, s0);
                v1 = addu(v1, v0);
                sd(v1, s3, 16);
                ld(v0, s2, 144);
                s1 = s1 & v0;
                lw(s3, s2, 2152);
                if (s1 == 0) {
                    // 0x005017e4
                    charge(ctx, 1);
                    lw(t1, s2, 140);
                } else {
                    // 0x005017c4
                    charge(ctx, 5);
                    lw(v0, s2, 156);
                    v0 = addiu(v0, 1);
                    lw(t1, s2, 140);
                    sw(v0, s2, 156);
                }
            }
        }
    }
    // 0x005017e8
    charge(ctx, 4);
    lw(v1, s2, 264);
    v0 = 2;
    if (v1 != v0) {
        lw(a2, s5, 64);
    } else {
        // 0x005017f8
        charge(ctx, 3);
        ld(v0, s2, 256);
        if (i64(v0) < 0) {
            lw(a2, s5, 64);
        } else {
            // 0x00501804
            charge(ctx, 5);
            sd(v0, s7, 0);
            v0 = si(-1);
            sw(zero, s2, 264);
            sd(v0, s2, 256);
            lw(a2, s5, 64);
        }
    }
    // 0x00501818
    charge(ctx, 28);
    t0 = 1;
    lw(a1, s5, 60);
    t2 = addiu(s3, 40);
    lw(a0, s5, 56);
    a2 = dsll(a2, 5);
    lw(v1, s5, 48);
    a1 = dsll(a1, 6);
    a0 = dsll(a0, 7);
    lw(v0, s5, 52);
    v1 = dsll(v1, 3);
    a2 = a2 | a1;
    a0 = a0 | v1;
    ld(a1, s5, 32);
    lw(v1, sp, 0x104);
    v0 = dsll(v0, 8);
    lw(a3, s5, 44);
    t3 = addiu(s3, 48);
    sd(a1, v1, 0);
    t4 = addiu(s3, 56);
    v0 = v0 | a3;
    lw(v1, sp, 0x108);
    v0 = v0 | a2;
    v0 = v0 | a0;
    sd(v0, v1, 0);
    lw(v1, s3, 16);
    sd(t0, s2, 160);
    sw(v1, s2, 152);
    if (t1 == 0) {
        // 0x005018e4
        charge(ctx, 2);
        ld(v0, s6, 24);
        sd(v0, t2, 0);
    } else {
        // 0x00501888
        charge(ctx, 3);
        ld(v0, s6, 24);
        if (i64(v0) >= 0) {
            sd(v0, t2, 0);
        } else {
            // 0x00501894
            charge(ctx, 2);
            if (i64(v1) < 0) {
                sd(v0, t2, 0);
            } else {
                // 0x0050189c
                charge(ctx, 14);
                ld(a0, s2, 144);
                lw(v0, s2, 156);
                a1 = a0 & 0x1;
                v0 = v0 & 0x1;
                a0 = dsll(a0, 31);
                a0 = dsra32(a0, 0);
                v0 = v0 & a1;
                v0 = addu(v0, a0);
                v1 = addu(v1, v0);
                sd(v1, s3, 40);
                ld(v0, s2, 144);
                v0 = v0 & 0x1;
                lw(s3, s2, 2152);
                if (v0 != 0) {
                    // 0x005018d4
                    charge(ctx, 4);
                    lw(v0, s2, 156);
                    v0 = addiu(v0, 1);
                    sw(v0, s2, 156);
                }
            }
        }
    }
    // 0x005018ec
    charge(ctx, 4);
    lw(v1, s2, 264);
    v0 = 2;
    if (v1 != v0) {
        lw(a2, s6, 64);
    } else {
        // 0x005018fc
        charge(ctx, 3);
        ld(v0, s2, 256);
        if (i64(v0) < 0) {
            lw(a2, s6, 64);
        } else {
            // 0x00501908
            charge(ctx, 5);
            sd(v0, t2, 0);
            v0 = si(-1);
            sw(zero, s2, 264);
            sd(v0, s2, 256);
            lw(a2, s6, 64);
        }
    }
    // 0x0050191c
    charge(ctx, 43);
    t1 = 1;
    lw(a1, s6, 60);
    lw(v0, s6, 52);
    a2 = dsll(a2, 5);
    lw(a3, s6, 44);
    a1 = dsll(a1, 6);
    lw(a0, s6, 56);
    a2 = a2 | a1;
    lw(v1, s6, 48);
    v0 = dsll(v0, 8);
    ld(a1, s6, 32);
    v0 = v0 | a3;
    v1 = dsll(v1, 3);
    a0 = dsll(a0, 7);
    lw(t0, sp, 0x100);
    a0 = a0 | v1;
    v0 = v0 | a2;
    sd(a1, t3, 0);
    v0 = v0 | a0;
    lw(a1, s2, 244);
    sd(v0, t4, 0);
    lw(v1, s3, 40);
    sd(t1, s2, 160);
    sw(v1, s2, 152);
    ld(v0, s3, 32);
    lw(a0, s5, 92);
    v0 = v0 | t0;
    ld(v1, s3, 56);
    sw(a0, s2, 224);
    sd(v0, s3, 32);
    v1 = v1 | t0;
    lw(a0, s5, 96);
    sd(v1, s3, 56);
    sw(a0, s2, 228);
    lw(v0, s5, 68);
    sw(v0, s2, 200);
    lw(v1, s6, 72);
    sw(v1, s2, 204);
    lw(v0, s5, 80);
    sw(v0, s2, 212);
    lw(v1, s6, 84);
    sw(v1, s2, 216);
    if (a1 == 0) {
        // 0x005019ec
        charge(ctx, 6);
        lw(v1, s4, 12);
        lw(a0, s4, 16);
        lw(v0, s2, 248);
        mult(v1, v1, a0);
        v0 = slt(v0, v1);
        s0 = v0 ^ 0x1;
    } else {
        // 0x005019c8
        charge(ctx, 5);
        lw(v0, s2, 240);
        lw(v1, s4, 4);
        v0 = slt(v0, v1);
        s0 = 0;
        if (v0 == 0) {
            // 0x005019dc
            charge(ctx, 4);
            lw(v0, s4, 8);
            v0 = slt(a1, v0);
            s0 = v0 ^ 0x1;
        }
    }
    // 0x00501a04
    charge(ctx, 2);
    if (s0 != 0) {
        lw(v1, s4, 40);
    } else {
        // 0x00501a0c
        charge(ctx, 12);
        a2 = 0x7C0000;
        lw(a3, s4, 4);
        lw(t0, s4, 8);
        a2 = addiu(a2, -9784);  // "Too small buffer size for %dx%d picture\n"
        a0 = sp;
        a1 = 256;
        jal(ctx, 0x501A20u, gen::fn_sceSnprintf_00505d90);
        a0 = s2;
        a1 = sp;
        jal(ctx, 0x501A2Cu, gen::fn__sceMpegError_00502668);
        ld(ra, sp, 0x1A0);
        if (s0 != 0) {
            // 0x00501a3c
            charge(ctx, 1);
            lw(v1, s4, 40);
            goto L_00501a40;
        }
    L_00501abc:
        charge(ctx, 1);
        ld(fp, sp, 0x190);
        // 0x00501ac0 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s7, sp, 0x180);
        ld(s6, sp, 0x170);
        ld(s5, sp, 0x160);
        ld(s4, sp, 0x150);
        ld(s3, sp, 0x140);
        ld(s2, sp, 0x130);
        ld(s1, sp, 0x120);
        ld(s0, sp, 0x110);
        sp = addiu(sp, 0x1B0);
        return;
    }
L_00501a40:
    charge(ctx, 3);
    v0 = 1;
    ld(ra, sp, 0x1A0);
    if (v1 != v0) {
        goto L_00501abc;
    }
    // 0x00501a4c
    charge(ctx, 3);
    lw(v0, fp, 0x28);
    if (v0 == v1) {
        // 0x00501a58
        charge(ctx, 6);
        lw(v0, s4, 16);
        v0 = sll(v0, 1);
        sw(v0, s4, 16);
        lw(v1, s2, 196);
        a0 = s2;
        if (v1 == 0) {
            // 0x00501a80
            charge(ctx, 3);
            a1 = s4;
            jal(ctx, 0x501A80u, gen::fn__cpr8_00501178);
            lw(v0, s4, 16);
        } else {
            // 0x00501a70
            charge(ctx, 4);
            a1 = s4;
            jal(ctx, 0x501A70u, gen::fn__sceMpegCscStoreRefImage_00501df8);
            lw(v0, s4, 16);
        }
        // 0x00501a8c
        charge(ctx, 6);
        a0 = 2;
        v0 = sra(v0, 1);
        sw(v0, s4, 16);
        lw(v1, s2, 8);
        v0 = 1;
        if (v1 != a0) {
            // 0x00501aa4
            charge(ctx, 4);
            lw(v0, s2, 296);
            sw(a0, s2, 8);
            sw(v0, s2, 192);
            v0 = 1;
        }
        // 0x00501ab4
        charge(ctx, 2);
        sw(v0, s2, 2100);
        ld(ra, sp, 0x1A0);
        goto L_00501abc;
    }
    ld(fp, sp, 0x190);
    // 0x00501ac0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s7, sp, 0x180);
    ld(s6, sp, 0x170);
    ld(s5, sp, 0x160);
    ld(s4, sp, 0x150);
    ld(s3, sp, 0x140);
    ld(s2, sp, 0x130);
    ld(s1, sp, 0x120);
    ld(s0, sp, 0x110);
    sp = addiu(sp, 0x1B0);
}

// 0x005024F0 _ErrMessage -- 16 bytes; leaf frame (no stack)
// The default error report: scePrintf("[MPEG ERROR]%s\n", text) (a tail call).
void _ErrMessage(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x005024f0
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = a0;
    a0 = 0x7C0000;
    a0 = addiu(a0, -9648);  // "[MPEG ERROR]%s\n"
    gen::fn_scePrintf_00505e48(ctx);  // tail call
}

}  // namespace p3fes::game
