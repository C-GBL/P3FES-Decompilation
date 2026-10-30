/* Phase 2 topic 10 (frame_loop_gs) — type layouts recovered from SkyStart 0x4E1060, sceGsSetDefDispEnv 0x4F9168,
 * sceGsSetDefDrawEnv 0x4F9668 / Env2 0x4FA558, sceGsSwapDBuffDc 0x4FA738, _rwDMAVSYNCHandler 0x4D47F0, SkyUseMode 0x4DFF20.
 * Not defined inside the IDA copy; derived from the instructions (offsets cited in docs/ANALYSIS/10_frame_loop_gs.md §2).
 * Parseable with ida_typeinf.parse_decls. Field names follow the SCE libgraph headers where the semantics match.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* one 128-bit quadword (GIF tag / DMA tag / A+D pair) */
struct qword128 { u64 lo; u64 hi; };

/* libgraph: display environment, written to the GS privileged registers by sceGsPutDispEnv 0x4F94E0 (size 0x28) */
struct sceGsDispEnv {
    u64 pmode;    /* -> 0x12000000 */
    u64 smode2;   /* -> 0x12000020 */
    u64 dispfb;   /* -> 0x12000090 (DISPFB2) */
    u64 display;  /* -> 0x120000A0 (DISPLAY2) */
    u64 bgcolor;  /* -> 0x120000E0 */
};

/* libgraph: context-1 drawing environment, 8 A+D pairs, giftag kept separately (size 0x80) */
struct sceGsDrawEnv1 {
    u64 frame1;      u64 frame1addr;      /* 0x4C */
    u64 zbuf1;       u64 zbuf1addr;       /* 0x4E */
    u64 xyoffset1;   u64 xyoffset1addr;   /* 0x18 */
    u64 scissor1;    u64 scissor1addr;    /* 0x40 */
    u64 prmodecont;  u64 prmodecontaddr;  /* 0x1A */
    u64 colclamp;    u64 colclampaddr;    /* 0x46 */
    u64 dthe;        u64 dtheaddr;        /* 0x45 */
    u64 test1;       u64 test1addr;       /* 0x47 */
};

/* libgraph: context-2 drawing environment, 5 A+D pairs (size 0x50) */
struct sceGsDrawEnv2 {
    u64 frame2;      u64 frame2addr;      /* 0x4D */
    u64 zbuf2;       u64 zbuf2addr;       /* 0x4F */
    u64 xyoffset2;   u64 xyoffset2addr;   /* 0x19 */
    u64 scissor2;    u64 scissor2addr;    /* 0x41 */
    u64 test2;       u64 test2addr;       /* 0x48 */
};

/* libgraph: clear packet tail of the sceGsDBuffDc block (size 0x90 observed: 0x964AC0..0x964B50). Field order unverified. */
struct sceGsClear {
    u64 regs[18];
};

/* libgraph SDK 3.x double-buffer block (size 0x330 observed at rwDMAFlipData 0x964990) */
struct sceGsDBuffDc {
    struct sceGsDispEnv  disp[2];   /* 0x000 disp[0]=FBP 0, disp[1]=FBP 140 */
    struct qword128      giftag0;   /* 0x050 NLOOP=16 EOP A+D */
    struct sceGsDrawEnv1 draw0;     /* 0x060 FBP 140 */
    struct sceGsDrawEnv2 draw02;    /* 0x0E0 */
    struct sceGsClear    clear0;    /* 0x130 */
    struct qword128      giftag1;   /* 0x1C0 */
    struct sceGsDrawEnv1 draw1;     /* 0x1D0 FBP 0 */
    struct sceGsDrawEnv2 draw12;    /* 0x250 */
    struct sceGsClear    clear1;    /* 0x2A0 */
};

/* RenderWare sky driver flip block = sceGsDBuffDc plus the driver's own tail (size 0x450: 0x964990..0x964DE0) */
struct RwSkyFlipData {
    struct sceGsDBuffDc dbuff;          /* 0x000 */
    u64 circ1_dispfb[2];                /* 0x330 DISPFB1 values for buf 0/1 (written to 0x12000070 by _rwDMAVSYNCHandler) */
    u64 circ1_display[2];               /* 0x340 DISPLAY1 values for buf 0/1 (-> 0x12000080) */
    u32 unpacked[28];                   /* 0x350 bit-field copies of disp/draw regs (0x964CE0..0x964D50) */
    u32 postFlipChain[4];               /* 0x3C0 D2 TADR kicked after flip, index buf|field; all 0 in this game */
    struct qword128 tagTemplate[4];     /* 0x3D0 DMA tag templates written by _rwDMADmaOpen (0x964D60..0x964DA0) */
    u8  tail[0x40];                     /* 0x410 ..0x450 */
};

/* RenderWare RwVideoMode as laid out in videoModes 0x77E710 (90 entries, 24 bytes each) and customMode 0x965730 */
struct RwVideoMode {
    int width;
    int height;
    int depth;
    int flags;      /* 1 EXCLUSIVE, 2 INTERLACE, 4 FSAA(?), 0x100 half-height/field buffer, 0x200 flicker-free interlace */
    int refRate;    /* 50 / 60 */
    int format;     /* 0x100 = 16-bit (PSMCT16S), 0x500 = 32-bit (PSMCT32) raster format */
};

/* libgraph private state returned by sceGsGetGParam 0x4F9040 (fields read in sceGsResetGraph/sceGsSyncV/sceGsSyncVCallback) */
struct sceGsGParam {
    u16 sceGsInterMode;   /* +0 interlace flag */
    u16 sceGsOutMode;     /* +2 2=NTSC 3=PAL 0x50=VESA/480p */
    u16 sceGsFFMode;      /* +4 0=FIELD 1=FRAME */
    u16 sceGsVersion;     /* +6 GS_CSR byte 2 */
    u32 vsyncCallback;    /* +8 handler fn registered by sceGsSyncVCallback */
    u32 vsyncHandlerId;   /* +12 id from sceAddIntcHandler(2,...) */
};

/* RenderWare DMA queue entry consumed by _rwDMAHandler 0x4D4350 */
struct RwDMAQueueEntry {
    u32 hdr;    /* bits 0-7 type: 1 VIF1, 2 GIF, 0x21 VIF1+GIF image, 64/65 flip buf0/1, 66 dec-counter, 67 nop, 79 callback, 127 wrap;
                   bits 8-9 (0x300) -> chain mode, bits 12-27 QWC for normal mode */
    u32 addr;   /* MADR/TADR, counter pointer, callback, or next queue address */
};
