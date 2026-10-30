/* vu1_gs.h -- Phase 2 topic 14 types (RenderWare PS2 PDS pipeline data, VU1 code packets, video modes).
 * Re-parseable with ida_typeinf.parse_decls; apply list: symbols/types/vu1_gs.apply.txt.
 * Evidence: docs/ANALYSIS/14_vu1_gs_census.md sections 1, 2, 5. Field names are ours unless RW 3.7 public headers name them. */

/* VIF1 code word (32 bit): IMM[15:0] NUM[23:16] CMD[30:24] IRQ[31]. */
struct VifCode {
    unsigned short imm;
    unsigned char num;
    unsigned char cmd;      /* 0x4A = MPG, 0x14 = MSCAL, 0x50 = DIRECT, 0x6x/0x7x = UNPACK */
};

/* Source-chain DMA tag (64 bit) followed by two VIF codes in the tag's upper 64 bits (TTE). */
struct DmaTagVif {
    unsigned short qwc;
    unsigned char pce_id;   /* bits 26-27 PCE, 28-30 ID (6 = ret), 31 IRQ -> (id = (pce_id >> 4) & 7) */
    unsigned char spr_flag; /* unused/pad in these packets */
    unsigned int addr;
    struct VifCode vif0;    /* NOP in every microcode packet */
    struct VifCode vif1;    /* MPG num, addr 0 in every microcode packet */
};

/* Head of a RenderWare VU1 microcode 'ret' packet (docs 14 section 1). The microcode (qwc*16 - 0 or 8 bytes) follows. */
struct RwVu1CodePacket {
    struct DmaTagVif tag;
};

/* {code array, count} pair referenced from a PDS material pipe definition at +108 (RpPDSSkyMatPipeCreate 0x46ad80). */
struct RwVu1CodeDesc {
    struct RwVu1CodePacket **codeArray;
    int count;
};

/* RenderWare PS2All cluster request (pipe definition +8.., up to 10 pairs, terminated by a 0 attribute pointer). */
struct RpPDSClusterRef {
    void *attribute;        /* RxClusterDefinition* */
    unsigned int flags;
};

/* 132-byte RpPDS material pipe definition consumed by RpPDSSkyMatPipeCreate 0x46ad80 (offsets observed in Hex-Rays). */
struct RpPDSMatPipeDef {
    unsigned int pluginId;              /* +0  0x131 */
    unsigned int pipeId;                /* +4  e.g. 0x1100b */
    struct RpPDSClusterRef clusters[10];/* +8  */
    unsigned int primType;              /* +88 RW: 1/2 line, 3/4/5 tri list/strip/fan, 6 point list */
    unsigned int vuBufferA;             /* +92 RxPipelineNodePS2AllMat*SetVUBufferSizes args */
    unsigned int vuBufferB;             /* +96 */
    unsigned int vuBufferC;             /* +100 */
    unsigned int vifOffset;             /* +104 RxPipelineNodePS2AllMatSetVIFOffset */
    struct RwVu1CodeDesc *vu1Code;      /* +108 RxPipelineNodePS2AllMatSetVU1CodeArray */
    void *cbMeshInstanceTest;           /* +112 PS2All callback 1 */
    void *cbResEntryAlloc;              /* +116 callback 2 */
    void *cbInstance;                   /* +120 callback 3 */
    void *cbBridge;                     /* +124 callback 4 */
    void *cbPostMesh;                   /* +128 callback 5 */
};

/* The videoModes table 0x77e710 (entry 82 used) is typed by topic 10 as RwVideoMode[90] (symbols/types/frame_loop_gs.h). */
