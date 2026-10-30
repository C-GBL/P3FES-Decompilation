// IpuCore: registers, FIFO/BP semantics, every command on hand-built bit streams, stalls, back-pressure, timing,
// reset and traps.
#include "ipu_test_util.h"

using namespace it;
using namespace p3fes::ipu::mpeg2;

namespace {

std::vector<u8> bdec_dc_only(Core& k, bool field) {
    Bits b;
    put_dc_only_blocks(b);
    k.ctrl(mode(1));
    k.feed(b.qwords());
    k.cmd(bdec(true, true, field, 1));
    k.wait_idle();
    return k.drain();
}

// RAW16 Y sample (x, y) of a drained BDEC macroblock.
s16 y_at(const std::vector<u8>& o, unsigned x, unsigned y) { return s16_at(o, y * 16 + x); }

} // namespace

TEST_CASE("power-on state and the game's sceIpuInit sequence (docs/INTEGRATION_LOG.md M2 item 1)") {
    Core k;
    CHECK(k.c.read_ctrl(k.t) == 0);
    CHECK(k.c.read_bp(k.t) == 0);
    for (unsigned i = 0; i < 64; ++i) CHECK(k.c.intra_matrix()[i] == kDefaultIntraMatrix[i]);
    for (unsigned i = 0; i < 64; ++i) CHECK(k.c.nonintra_matrix()[i] == 16);

    // IPU_CTRL = RST, IPU_CMD = BCLR(0), each polled until BUSY clears
    k.ctrl(kCtrlRst);
    CHECK((k.c.read_ctrl(k.t) & kCtrlBusy) == 0);
    k.cmd(0x00000000u);
    CHECK((k.c.read_ctrl(k.t) & kCtrlBusy) != 0);
    CHECK(k.wait_idle() == 8);  // BCLR cost
    // 8 qwords queued before either SETIQ: a custom intra matrix (zigzag order: 1..64) and the non-intra 0x10s
    u8 m[128];
    for (int i = 0; i < 64; ++i) m[i] = static_cast<u8>(i + 1);
    for (int i = 64; i < 128; ++i) m[i] = 0x10;
    for (int q = 0; q < 8; ++q) CHECK(k.c.write_in_fifo(qw_bytes(m + 16 * q), k.t));
    CHECK(k.c.read_bp(k.t) == ((2u << kBpFpShift) | (6u << kBpIfcShift)));  // FP 2 + IFC 6
    CHECK((k.c.read_ctrl(k.t) & kCtrlIfcMask) == 6);
    k.cmd(kCmdSetiqIntra);
    CHECK(k.wait_idle() == 32);  // SETIQ cost
    for (int z = 0; z < 64; ++z) CHECK(k.c.intra_matrix()[kZigzag[z]] == z + 1);  // de-zigzagged
    CHECK(k.c.read_bp(k.t) == ((2u << kBpFpShift) | (2u << kBpIfcShift)));
    k.cmd(kCmdSetiqNonIntra);
    k.wait_idle();
    for (int i = 0; i < 64; ++i) CHECK(k.c.nonintra_matrix()[i] == 0x10);
    CHECK(k.c.read_bp(k.t) == 0);
    // 2 qwords: 16 little-endian RGB555 CLUT entries, SETVQ
    u8 clut[32];
    for (int i = 0; i < 16; ++i) {
        clut[2 * i] = static_cast<u8>(0x21 * i);
        clut[2 * i + 1] = static_cast<u8>(0x04 + i);
    }
    k.c.write_in_fifo(qw_bytes(clut), k.t);
    k.c.write_in_fifo(qw_bytes(clut + 16), k.t);
    k.cmd(kCmdSetvq);
    k.wait_idle();
    for (int i = 0; i < 16; ++i) CHECK(k.c.vqclut()[i] == static_cast<u16>((0x21 * i & 0xFF) | ((0x04 + i) << 8)));
    k.cmd(0x90200010u);  // SETTH TH0 0x10, TH1 0x20
    k.wait_idle();
    CHECK(k.c.th0() == 0x10);
    CHECK(k.c.th1() == 0x20);
    k.cmd(kCmdSetth);
    k.wait_idle();
    CHECK((k.c.th0() == 0 && k.c.th1() == 0));
    k.ctrl(kCtrlRst);
    k.cmd(0);
    k.wait_idle();
    CHECK(k.c.read_bp(k.t) == 0);
    CHECK(k.c.intra_matrix()[kZigzag[63]] == 64);  // RST keeps the matrices
    CHECK(k.traps.empty());
    CHECK(k.interrupts == 7);  // every command completion (INTC 8): BCLR, SETIQ x2, SETVQ, SETTH x2, BCLR
}

TEST_CASE("sequence header with a custom intra matrix: SETIQ reads 64 bytes at bit 95 (not byte-aligned)") {
    // ISO 13818-2 §6.2.2.1: start code 32, horizontal_size 12 (640), vertical_size 12 (448), aspect 4, frame_rate 4,
    // bit_rate 18, marker 1, vbv 10, constrained 1, load_intra_quantiser_matrix 1 -> the matrix starts at bit 95 —
    // the shape of the stream the M2 run found at the movie start (`00 00 01 B3 28 01 C0 ...`).
    Bits b;
    b.byte(0).byte(0).byte(1).byte(0xB3).v(640, 12).v(448, 12).v(1, 4).v(4, 4).v(0x3FFFF, 18).s("1").v(112, 10).s("0").s("1");
    REQUIRE(b.nbits == 95);
    for (int z = 0; z < 64; ++z) b.byte(static_cast<u8>(2 + z));
    b.s("0");  // load_non_intra_quantiser_matrix
    Core k;
    k.feed(b.qwords());
    k.cmd(fdec(0));
    k.wait_idle();
    CHECK(static_cast<u32>(k.c.read_cmd(k.t)) == 0x000001B3u);
    CHECK(k.c.read_bp(k.t) == ((2u << kBpFpShift) | (3u << kBpIfcShift)));
    k.cmd(fdec(32));  // the library's NextBit(32) after the start code
    k.wait_idle();
    CHECK(static_cast<u32>(k.c.read_cmd(k.t)) == 0x2801C014u);  // 640 | 448 | aspect 1 | frame rate 4
    k.cmd(fdec(63));
    k.wait_idle();
    CHECK(k.c.bit_pointer() == 95);
    k.cmd(kCmdSetiqIntra);
    k.wait_idle();
    for (int z = 0; z < 64; ++z) CHECK(k.c.intra_matrix()[kZigzag[z]] == 2 + z);
    CHECK(k.c.bit_pointer() == (95 + 512) - 512);  // 4 qwords retired
    k.cmd(fdec(0));
    k.wait_idle();
    CHECK((static_cast<u32>(k.c.read_cmd(k.t)) >> 31) == 0);  // load_non_intra_quantiser_matrix = 0
}

TEST_CASE("IPU_BP / IPU_TOP / FDEC: bit pointer, FP + IFC accounting, qword retirement, 64-bit reads") {
    Core k;
    u8 bytes[48];
    for (int i = 0; i < 48; ++i) bytes[i] = static_cast<u8>(i);
    std::vector<u128> q = {qw_bytes(bytes), qw_bytes(bytes + 16), qw_bytes(bytes + 32)};
    CHECK(k.feed(q) == 3);
    CHECK(k.c.read_bp(k.t) == ((2u << kBpFpShift) | (1u << kBpIfcShift)));
    CHECK(k.c.read_top(k.t) == 0x00010203u);  // 32 bits available, not busy
    k.cmd(fdec(0));
    CHECK((k.c.read_cmd(k.t) >> 63) == 1);  // BUSY in bit 63 of the 64-bit IPU_CMD
    k.wait_idle();
    CHECK(k.c.read_cmd(k.t) == 0x00010203u);
    CHECK((k.c.read_bp(k.t) & kBpMask) == 0);
    k.cmd(fdec(8));
    k.wait_idle();
    CHECK(k.c.read_cmd(k.t) == 0x01020304u);
    CHECK((k.c.read_bp(k.t) & kBpMask) == 8);
    k.cmd(fdec(63));  // BP 71: bits 71..102 = byte 8 bit 7 onwards
    k.wait_idle();
    CHECK((k.c.read_bp(k.t) & kBpMask) == 71);
    CHECK(k.c.read_cmd(k.t) == ((0x08090A0Bu << 7) | (0x0Cu >> 1)));
    k.cmd(fdec(57));  // BP 128: the first qword retires
    k.wait_idle();
    CHECK(k.c.read_bp(k.t) == ((2u << kBpFpShift) | (0u << kBpIfcShift)));
    CHECK(k.c.read_cmd(k.t) == 0x10111213u);
    // 256 bits buffered: FB 63 three times -> BP 189 -> the second qword retires too (BP 61 of the last one, FP 1,
    // 67 bits left). A fourth FDEC 63 skips its 63 bits, then waits for a full 32-bit window: 4 bits left, BUSY —
    // the state the game's _sceMpegWaitIpuIdle tests ((IFC + FP) * 128 - BP < 32 with D4_QWC 0 -> ask for data).
    for (int i = 0; i < 3; ++i) {
        k.cmd(fdec(63));
        k.wait_idle();
    }
    CHECK(k.c.buffered_bits() == 67);
    CHECK(k.c.read_bp(k.t) == ((1u << kBpFpShift) | 61u));
    k.cmd(fdec(63));
    CHECK(k.wait_idle(5000) == 5000);  // still busy: stalled for input
    CHECK(k.c.buffered_bits() == 4);
    CHECK(k.c.read_bp(k.t) == ((1u << kBpFpShift) | 124u));
    CHECK((k.c.read_top(k.t) >> 63) == 1);
    CHECK(k.c.stats().input_stalls > 0);
    u8 more[16] = {0xAB, 0xCD, 0xEF, 0x01};
    CHECK(k.c.push_input(reinterpret_cast<const u128*>(more), 1, k.t) == 1);
    k.wait_idle();
    CHECK((k.c.read_bp(k.t) & kBpMask) == 61 + 63);
    CHECK((k.c.read_ctrl(k.t) & kCtrlBusy) == 0);
}

TEST_CASE("BCLR: empties the input side and sets BP; the next data starts at that bit") {
    Core k;
    u8 b[16] = {0xFF, 0x00, 0xFF, 0x00, 0xAA, 0x55};
    k.feed({qw_bytes(b), qw_bytes(b)});
    k.cmd(0x00000005u);  // BCLR BP 5
    k.wait_idle();
    CHECK(k.c.read_bp(k.t) == 5);  // IFC 0, FP 0, BP 5
    k.feed({qw_bytes(b)});
    CHECK(k.c.read_bp(k.t) == ((1u << kBpFpShift) | 5u));
    k.cmd(fdec(0));
    k.wait_idle();
    // bits 5.. of FF 00 FF 00 AA: 111 00000000 11111111 00000000 10101 = 0xE01FE015
    CHECK(k.c.read_cmd(k.t) == 0xE01FE015u);
}

TEST_CASE("VDEC: result = length << 16 | value, per table; PCT selects the MB-type table; MP1 the stuffing code") {
    struct Case {
        u32 ctrl, cmd;
        const char* bits;
        u32 data;
        bool ecd;
    };
    const Case cases[] = {
        {mode(1), vdec(0), "1", 0x00010001u, false},              // MBAI 1
        {mode(1), vdec(0), "0000 0100 000", 0x000B0019u, false},  // MBAI 25
        {mode(1), vdec(0), "0000 0001 000", 0x000B0023u, false},  // macroblock_escape
        {mode(1, 0, true), vdec(0), "0000 0001 111", 0x000B0022u, false},  // MPEG-1 stuffing
        {mode(1), vdec(0), "0000 0001 111", 0, true},             // MPEG-2: not a code -> ECD, DATA 0
        {mode(1), vdec(1), "01", 0x00020011u, false},             // I: intra + quant
        {mode(2), vdec(1), "1", 0x0001000Au, false},              // P: MC coded
        {mode(2), vdec(1), "000001", 0x00060011u, false},         // P: intra + quant
        {mode(3), vdec(1), "11", 0x0002000Eu, false},             // B: interpolated coded
        {mode(4), vdec(1), "1", 0x00010001u, false},              // D: intra
        {mode(0), vdec(1), "1", 0, true},                         // PCT 0: no table
        {mode(1), vdec(2), "1", 0x00010000u, false},              // motion_code 0 (non-zero DATA)
        {mode(1), vdec(2), "0000 0011 001", 0x000BFFF0u, false},  // motion_code -16
        {mode(1), vdec(3), "11", 0x0002FFFFu, false},             // dmvector -1
        {mode(1), vdec(2, 3), "101 0011", 0x0004FFFEu, false},    // FB 3 skipped, then -2
    };
    for (const Case& c : cases) {
        Core k;
        Bits b;
        b.s(c.bits).v(0x5A5A5A5A, 32);  // trailing data so availability never limits
        k.ctrl(c.ctrl);
        k.feed(b.qwords());
        k.cmd(c.cmd);
        k.wait_idle();
        INFO("cmd " << std::hex << c.cmd << " bits " << c.bits);
        CHECK(static_cast<u32>(k.c.read_cmd(k.t)) == c.data);
        CHECK(((k.c.read_ctrl(k.t) & kCtrlEcd) != 0) == c.ecd);
        if (c.ecd) {
            CHECK(k.c.bit_pointer() == 0);  // the invalid code is not consumed
            k.cmd(fdec(0));                 // the next command clears ECD
            k.wait_idle();
            CHECK((k.c.read_ctrl(k.t) & kCtrlEcd) == 0);
        } else {
            CHECK(k.c.bit_pointer() == (c.data >> 16) + (c.cmd & 0x3Fu));
        }
    }
}

TEST_CASE("BDEC intra, DC-only blocks (hand-built stream): RAW16 output, CBP, predictors, frame and field DCT") {
    Core k;
    const std::vector<u8> o = bdec_dc_only(k, false);
    REQUIRE(o.size() == 768);
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) CHECK(y_at(o, x, y) == kDcY[(y / 8) * 2 + x / 8]);
    for (unsigned i = 0; i < 64; ++i) {
        CHECK(s16_at(o, 256 + i) == kDcCb);
        CHECK(s16_at(o, 320 + i) == kDcCr);
    }
    CHECK(((k.c.read_ctrl(k.t) >> kCtrlCbpShift) & 0x3F) == 0x3F);
    CHECK(k.c.bit_pointer() == 46);
    CHECK(k.c.dc_predictor(0) == 134);
    CHECK(k.c.dc_predictor(1) == 118);
    CHECK(k.c.dc_predictor(2) == 148);
    CHECK(k.c.stats().macroblocks == 1);

    Core f;
    const std::vector<u8> of = bdec_dc_only(f, true);  // dct_type 1: blocks 0/1 even lines, 2/3 odd lines
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) CHECK(y_at(of, x, y) == kDcY[(y & 1) * 2 + x / 8]);
}

TEST_CASE("BDEC: DC predictors carry over without DCR, reset to 128 << IDP with it; FB skip; intra_dc_precision") {
    Core k;
    Bits b;
    put_dc_only_blocks(b);
    // second macroblock, DCR = 0: every block size 0 (Y '100', C '00') -> the predictors as left by the first MB
    b.s("100 10").s("100 10").s("100 10").s("100 10").s("00 10").s("00 10");
    k.ctrl(mode(1));
    k.feed(b.qwords());
    k.cmd(bdec(true, true, false, 1));
    k.wait_idle();
    k.drain();
    k.cmd(bdec(true, false, false, 1));
    k.wait_idle();
    const std::vector<u8> o = k.drain();
    REQUIRE(o.size() == 768);
    CHECK(y_at(o, 0, 0) == 134);
    CHECK(y_at(o, 15, 15) == 134);
    CHECK(s16_at(o, 256) == 118);
    CHECK(s16_at(o, 320) == 148);

    // IDP 2 (10-bit DC): reset to 512, DC multiplier 2: diff 0 -> F00 = 1024 -> 128; FB 5 skips '10110'
    Core p;
    Bits c;
    c.s("10110");
    for (int blk = 0; blk < 4; ++blk) c.s("100 10");
    c.s("00 10").s("00 10");
    p.ctrl(mode(1, 2));
    p.feed(c.qwords());
    p.cmd(bdec(true, true, false, 1, 5));
    p.wait_idle();
    const std::vector<u8> o2 = p.drain();
    REQUIRE(o2.size() == 768);
    CHECK(p.c.dc_predictor(0) == 512);
    CHECK(y_at(o2, 3, 3) == 128);
}

TEST_CASE("BDEC non-intra: CBP decode, '1s' first coefficient, AC run/level, escapes (MPEG-2 and MPEG-1)") {
    // CBP '1010' = 32 (block 0 only); block 0: first coefficient '1 0' = +1, EOB. QSC 8 -> qs 16:
    // F00 = (3 * 16 * 16) / 32 = 24, mismatch F77 = 1 -> every sample 3.
    {
        Core k;
        Bits b;
        b.s("1010").s("1 0").s("10");
        k.ctrl(mode(2));
        k.feed(b.qwords());
        k.cmd(bdec(false, false, false, 8));
        k.wait_idle();
        const std::vector<u8> o = k.drain();
        REQUIRE(o.size() == 768);
        for (unsigned y = 0; y < 16; ++y)
            for (unsigned x = 0; x < 16; ++x) CHECK(y_at(o, x, y) == (x < 8 && y < 8 ? 3 : 0));
        for (unsigned i = 256; i < 384; ++i) CHECK(s16_at(o, i) == 0);
        CHECK(((k.c.read_ctrl(k.t) >> kCtrlCbpShift) & 0x3F) == 32);
    }
    // CBP '01011' = 1 (Cr only): '0100 0' (0,2) +2 at k 0; '011 1' (1,1) -1 -> k 2; escape run 3 level -100 (12-bit
    // 0xF9C) -> k 6; '00101 0' (0,3) +3 -> k 7; EOB.
    {
        Core k;
        Bits b;
        b.s("01011").s("0100 0").s("011 1").s("000001").v(3, 6).v(0xF9C, 12).s("00101 0").s("10");
        k.ctrl(mode(2));
        k.feed(b.qwords());
        k.cmd(bdec(false, false, false, 5));
        k.wait_idle();
        const std::vector<u8> o = k.drain();
        REQUIRE(o.size() == 768);
        s32 qf[64] = {};
        qf[0] = 2;
        qf[2] = -1;
        qf[6] = -100;
        qf[7] = 3;
        QuantParams p;
        p.intra = false;
        p.quantiser_scale = 10;
        p.matrix = k.c.nonintra_matrix();
        s32 f[64];
        inverse_quantize(qf, p, f);
        s16 ref[64];
        idct(f, ref);
        for (unsigned i = 0; i < 64; ++i) CHECK(s16_at(o, 320 + i) == ref[i]);
        for (unsigned i = 0; i < 320; ++i) CHECK(s16_at(o, i) == 0);
        CHECK(k.c.bit_pointer() == b.nbits);
    }
    // MPEG-1 escapes: 8-bit level 0x9C = -100; '0000 0000' + 8-bit 200 = +200; '1000 0000' + 0x38 = 0x38 - 256 = -200
    {
        Core k;
        Bits b;
        b.s("1010").s("000001").v(0, 6).v(0x9C, 8).s("000001").v(1, 6).v(0, 8).v(200, 8).s("000001").v(0, 6)
            .v(0x80, 8).v(0x38, 8).s("10");
        k.ctrl(mode(2, 0, true));
        k.feed(b.qwords());
        k.cmd(bdec(false, false, false, 4));
        k.wait_idle();
        const std::vector<u8> o = k.drain();
        REQUIRE(o.size() == 768);
        s32 qf[64] = {};
        qf[0] = -100;
        qf[2] = 200;
        qf[3] = -200;
        QuantParams p;
        p.intra = false;
        p.mpeg1 = true;
        p.quantiser_scale = quantiser_scale(4, false, true);
        p.matrix = k.c.nonintra_matrix();
        s32 f[64];
        inverse_quantize(qf, p, f);
        s16 ref[64];
        idct(f, ref);
        for (unsigned y = 0; y < 8; ++y)
            for (unsigned x = 0; x < 8; ++x) CHECK(y_at(o, x, y) == ref[y * 8 + x]);
        CHECK(k.c.bit_pointer() == b.nbits);
    }
}

TEST_CASE("BDEC intra with intra_vlc_format 1 (B.15) and alternate scan") {
    Core k;
    Bits b;
    // Y0: DC size 0, then B.15 '010 1' (1,1) -1 -> scan 2 (alternate: raster 16), EOB '0110'; others DC 0 + EOB
    b.s("100").s("010 1").s("0110");
    for (int blk = 1; blk < 4; ++blk) b.s("100 0110");
    b.s("00 0110").s("00 0110");
    k.ctrl(mode(1, 0, false, true, true));
    k.feed(b.qwords());
    k.cmd(bdec(true, true, false, 3));
    k.wait_idle();
    const std::vector<u8> o = k.drain();
    REQUIRE(o.size() == 768);
    s32 qf[64] = {};
    qf[0] = 128;
    qf[2] = -1;
    QuantParams p;
    p.intra = true;
    p.quantiser_scale = 6;
    p.matrix = k.c.intra_matrix();
    p.alternate_scan = true;
    s32 f[64];
    inverse_quantize(qf, p, f);
    CHECK(f[16] != 0);  // alternate scan position 2 = raster 16
    s16 ref[64];
    idct(f, ref);
    for (unsigned y = 0; y < 8; ++y)
        for (unsigned x = 0; x < 8; ++x) CHECK(y_at(o, x, y) == ref[y * 8 + x]);
    CHECK(y_at(o, 8, 0) == 128);
}

TEST_CASE("BDEC errors: an invalid code sets ECD, ends the command without output; a run past 63 too") {
    Core k;
    Bits b;
    b.s("100").v(0, 16);  // Y0 DC size 0, then sixteen zeros: no B.14 code
    k.ctrl(mode(1));
    k.feed(b.qwords());
    k.cmd(bdec(true, true, false, 1));
    k.wait_idle();
    CHECK((k.c.read_ctrl(k.t) & kCtrlEcd) != 0);
    CHECK(k.c.out_qwords() == 0);
    CHECK(k.c.bit_pointer() == 3);  // the DC element was consumed, the bad code was not
    CHECK(k.c.stats().errors == 1);
    Core r;
    Bits c;
    c.s("1010").s("1 0");
    for (int i = 0; i < 3; ++i) c.s("000001").v(30, 6).v(1, 12);  // runs 30 + 30 + 30 > 63
    r.ctrl(mode(2));
    r.feed(c.qwords());
    r.cmd(bdec(false, false, false, 1));
    r.wait_idle();
    CHECK((r.c.read_ctrl(r.t) & kCtrlEcd) != 0);
}

TEST_CASE("IDEC: intra macroblocks through CSC until a start code; SCD; BP left at the start code") {
    Core k;
    Bits b;
    b.s("1");  // macroblock_type I: intra
    put_dc_only_blocks(b);
    b.s("1");   // macroblock_address_increment 1
    b.s("01").v(2, 5);  // second MB: intra + quant, quantiser_scale_code 2
    for (int blk = 0; blk < 4; ++blk) b.s("100 10");
    b.s("00 10").s("00 10");
    b.start_code(0xB3);
    const unsigned sc_bit = b.nbits - 32;
    k.ctrl(mode(1));
    k.cmd(idec(1));
    const std::vector<u8> o = k.stream(b.qwords());
    CHECK((k.c.read_ctrl(k.t) & kCtrlScd) != 0);
    CHECK((k.c.read_ctrl(k.t) & kCtrlEcd) == 0);
    CHECK(k.c.bit_pointer() == sc_bit);
    REQUIRE(o.size() == 2 * 1024);
    // MB 1: hand-computed colours of (Y, 118, 148): Y 130 -> (165, 120, 113), 129 -> (163, 119, 111), 134 -> (169, 125, 117)
    const u8 rgb[4][3] = {{165, 120, 113}, {165, 120, 113}, {163, 119, 111}, {169, 125, 117}};
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) {
            const u8* px = o.data() + 4 * (y * 16 + x);
            const u8* e = rgb[(y / 8) * 2 + x / 8];
            CHECK(px[0] == e[0]);
            CHECK(px[1] == e[1]);
            CHECK(px[2] == e[2]);
            CHECK(px[3] == 0x80);
        }
    // MB 2: predictors continue (134, 118, 148) -> all (169, 125, 117)
    CHECK(o[1024 + 0] == 169);
    CHECK(o[1024 + 4 * 255 + 2] == 117);
    k.cmd(fdec(0));
    k.wait_idle();
    CHECK(static_cast<u32>(k.c.read_cmd(k.t)) == 0x000001B3u);
    CHECK(k.c.stats().macroblocks == 2);
}

TEST_CASE("IDEC: DTD reads dct_type per macroblock; RGB16 output; SGN traps (not modelled)") {
    Core k;
    Bits b;
    b.s("1").s("1");  // intra, dct_type 1 (DTD)
    put_dc_only_blocks(b);
    b.start_code(0x01);
    k.ctrl(mode(1));
    k.cmd(idec(1, true, true));
    const std::vector<u8> o = k.stream(b.qwords());
    REQUIRE(o.size() == 512);
    auto px16 = [&](unsigned x, unsigned y) { return static_cast<u16>(o[2 * (y * 16 + x)] | (o[2 * (y * 16 + x) + 1] << 8)); };
    // field DCT: odd lines of the left half come from Y2 (129 -> (163, 119, 111)), even lines from Y0 (130)
    CHECK(px16(0, 0) == static_cast<u16>((165 >> 3) | ((120 >> 3) << 5) | ((113 >> 3) << 10) | 0x8000));
    CHECK(px16(0, 1) == static_cast<u16>((163 >> 3) | ((119 >> 3) << 5) | ((111 >> 3) << 10) | 0x8000));
    CHECK(k.traps.empty());
    Core s;
    s.feed(b.qwords());
    s.ctrl(mode(1));
    s.cmd(idec(1) | (1u << 25));
    REQUIRE(s.traps.size() == 1);
    CHECK(s.traps[0].kind == IpuTrap::Kind::Unsupported);
}

TEST_CASE("CSC: MBC macroblocks of RAW8 -> RGB32 / RGB16 (the game's CSC 0x70000000 | n, TH 0)") {
    Core k;
    std::vector<u8> raw(2 * 384);
    for (std::size_t i = 0; i < raw.size(); ++i) raw[i] = static_cast<u8>((i * 37 + 11) & 0xFF);
    std::vector<u128> in(raw.size() / 16);
    std::memcpy(in.data(), raw.data(), raw.size());
    std::size_t fed = k.c.push_input(in.data(), in.size(), k.t);
    CHECK(fed == kInCapacityQw);  // no command yet: the input side fills up and stalls the "DMA"
    k.cmd(kCmdCsc | 2u);
    std::vector<u8> out;
    while (fed < in.size() || k.c.busy()) {
        fed += k.c.push_input(in.data() + fed, in.size() - fed, k.t);
        const std::vector<u8> d = k.drain(8);  // a DMA that takes 8 qwords per call
        out.insert(out.end(), d.begin(), d.end());
        ++k.t;
    }
    REQUIRE(out.size() == 2048);
    u8 ref[1024];
    for (int mb = 0; mb < 2; ++mb) {
        csc(raw.data() + 384 * mb, CscParams{}, ref);
        CHECK(std::memcmp(out.data() + 1024 * mb, ref, 1024) == 0);
    }
    Core r;
    r.cmd(kCmdCsc | (1u << 27) | 1u);  // RGB16
    const std::vector<u8> o16 = r.stream(std::vector<u128>(in.begin(), in.begin() + 24));
    REQUIRE(o16.size() == 512);
    CscParams p16;
    p16.rgb16 = true;
    csc(raw.data(), p16, ref);
    CHECK(std::memcmp(o16.data(), ref, 512) == 0);
    Core z;
    z.cmd(kCmdCsc);  // MBC 0: completes without data
    CHECK(z.wait_idle() == 64);
}

TEST_CASE("PACK: RGB32 -> RGB16 (OFM 1) and INDX4 (OFM 0) with the VQ CLUT from SETVQ") {
    Core k;
    std::vector<u8> rgb(1024);
    for (std::size_t i = 0; i < rgb.size(); ++i) rgb[i] = static_cast<u8>(i * 13);
    std::vector<u128> in(64);
    std::memcpy(in.data(), rgb.data(), 1024);
    u8 clut[32] = {0x00, 0x00, 0x1F, 0x00, 0xE0, 0x03, 0x00, 0x7C, 0xFF, 0x7F};
    k.c.write_in_fifo(qw_bytes(clut), k.t);
    k.c.write_in_fifo(qw_bytes(clut + 16), k.t);
    k.cmd(kCmdSetvq);
    k.wait_idle();
    std::vector<u8> out;
    std::size_t fed = 0;
    k.cmd(0x88000001u);  // PACK RGB16, 1 MB
    while (fed < in.size() || k.c.busy()) {
        fed += k.c.push_input(in.data() + fed, in.size() - fed, k.t);
        const std::vector<u8> d = k.drain(8);
        out.insert(out.end(), d.begin(), d.end());
        ++k.t;
    }
    REQUIRE(out.size() == 512);
    u8 ref[512];
    pack(rgb.data(), true, false, k.c.vqclut(), ref);
    CHECK(std::memcmp(out.data(), ref, 512) == 0);
    Core q;
    q.c.write_in_fifo(qw_bytes(clut), q.t);
    q.c.write_in_fifo(qw_bytes(clut + 16), q.t);
    q.cmd(kCmdSetvq);
    q.wait_idle();
    q.cmd(0x80000001u);  // PACK INDX4
    fed = 0;
    out.clear();
    while (fed < in.size() || q.c.busy()) {
        fed += q.c.push_input(in.data() + fed, in.size() - fed, q.t);
        const std::vector<u8> d = q.drain(8);
        out.insert(out.end(), d.begin(), d.end());
        ++q.t;
    }
    REQUIRE(out.size() == 128);
    pack(rgb.data(), false, false, q.c.vqclut(), ref);
    CHECK(std::memcmp(out.data(), ref, 128) == 0);
}

TEST_CASE("input stall/resume: a stream fed one qword at a time decodes exactly like the bulk stream") {
    Bits b;
    for (int mb = 0; mb < 3; ++mb) {
        b.s("1010").s("1 0");  // non-intra, block 0, +1 ...
        for (int i = 0; i < 20; ++i) b.s("000001").v(0, 6).v(static_cast<u32>(i * 7 + 1), 12);  // long: > 10 qwords
        b.s("10");
    }
    const std::vector<u128> q = b.qwords();
    REQUIRE(q.size() > 10);
    auto decode = [&](bool dribble, IpuStats& st) {
        Core k;
        k.ctrl(mode(2));
        std::vector<u8> all;
        std::size_t fed = 0;
        for (int mb = 0; mb < 3; ++mb) {
            k.cmd(bdec(false, false, false, 2));
            while (k.c.busy()) {
                if (fed < q.size()) fed += k.c.push_input(q.data() + fed, dribble ? 1 : q.size() - fed, k.t);
                const std::vector<u8> d = k.drain();
                all.insert(all.end(), d.begin(), d.end());
                k.t += 4;
                k.c.update(k.t);
            }
            CHECK((k.c.read_ctrl(k.t) & kCtrlEcd) == 0);
        }
        st = k.c.stats();
        return all;
    };
    IpuStats bulk{}, drip{};
    const std::vector<u8> a = decode(false, bulk), d = decode(true, drip);
    REQUIRE(a.size() == 3 * 768);
    CHECK(a == d);
    CHECK(drip.input_stalls > 0);
    MESSAGE("input stalls: bulk " << bulk.input_stalls << ", one qword per call " << drip.input_stalls);
}

TEST_CASE("output back-pressure: OFC counts the 8-qword FIFO; the rest waits staged; BUSY until it is in the FIFO") {
    Core k;
    Bits b;
    put_dc_only_blocks(b);
    k.ctrl(mode(1));
    k.feed(b.qwords());
    k.cmd(bdec(true, true, false, 1));
    CHECK(((k.c.read_ctrl(k.t) >> kCtrlOfcShift) & 0xF) == 8);
    CHECK(k.c.staged_output_qwords() == 40);
    k.t += 1000;
    CHECK((k.c.read_ctrl(k.t) & kCtrlBusy) != 0);  // decoded, but its output is not all in the FIFO yet
    std::size_t total = 0;
    while (total < 48) {
        const std::vector<u8> d = k.drain(5);
        REQUIRE(!d.empty());
        total += d.size() / 16;
    }
    CHECK(k.c.out_qwords() == 0);
    CHECK((k.c.read_ctrl(k.t) & kCtrlBusy) == 0);
}

TEST_CASE("IPU_TOP: invalid while the decoder still consumes bits, valid once the data flow ended (BUSY may remain)") {
    Core k;
    Bits b;
    put_dc_only_blocks(b);
    b.v(0xCAFEBABEu, 32);
    k.ctrl(mode(1));
    k.feed(b.qwords());
    k.cmd(bdec(true, true, false, 1));
    CHECK((k.c.read_top(k.t) >> 63) == 1);  // output still staged: the command's data flow is not over
    CHECK(k.drain().size() == 768);         // "D3" takes the whole macroblock at the same cycle
    CHECK((k.c.read_ctrl(k.t) & kCtrlBusy) != 0);  // BDEC cost: 64 cycles from the issue
    CHECK(k.c.read_top(k.t) == 0xCAFEBABEu);       // bits 46..77, BUSY bit clear (what _slice0 caches)
    CHECK(k.wait_idle() == 64);
}

TEST_CASE("timing: completion at max(issue + cost, data flow end); INTC 8 once; update() reports the deadline") {
    Core k;
    u8 b[16] = {0x12, 0x34, 0x56, 0x78, 0x9A};
    k.feed({qw_bytes(b)});
    k.t = 5000;
    k.cmd(fdec(0));
    CHECK(k.c.completion_cycle() == 5016);
    CHECK(k.c.update(5015) == 5016);
    CHECK(k.c.busy());
    CHECK(k.interrupts == 0);
    CHECK(k.c.update(5016) == kNever);
    CHECK_FALSE(k.c.busy());
    CHECK(k.interrupts == 1);
    CHECK(k.c.update(6000) == kNever);
    CHECK(k.interrupts == 1);
    // input arriving late: the data flow ends at 7100 > 6000 + 16
    k.cmd(0);
    k.c.update(k.t = 6000 + 8);
    k.t = 6000;
    k.cmd(fdec(0));
    CHECK(k.c.completion_cycle() == kNever);  // waiting for data
    k.t = 7100;
    k.feed({qw_bytes(b), qw_bytes(b)});
    CHECK_FALSE(k.c.busy());  // data flow ended at 7100 > 6000 + 16: complete at 7100, inside the push's update()
    CHECK(k.interrupts == 3);
}

TEST_CASE("RST aborts a stalled command without an interrupt and clears FIFOs; mode bits are stored, status ignored") {
    Core k;
    k.cmd(fdec(0));  // no data: stalls
    k.t += 100;
    CHECK(k.c.busy());
    k.ctrl(kCtrlRst | mode(3, 1, true));
    CHECK_FALSE(k.c.busy());
    CHECK(k.interrupts == 0);
    CHECK(k.c.read_ctrl(k.t) == mode(3, 1, true));
    // a read-modify-write that carries status bits back (BUSY, IFC, ECD...) changes only the mode bits
    k.ctrl(0xFFFFFFFFu & ~kCtrlRst);
    CHECK((k.c.read_ctrl(k.t) & ~kCtrlModeMask) == 0);
    CHECK((k.c.read_ctrl(k.t) & kCtrlModeMask) == kCtrlModeMask);
}

TEST_CASE("traps: command while busy, reserved codes, input FIFO overflow, output FIFO underflow") {
    Core k;
    k.cmd(fdec(0));
    k.cmd(fdec(8));
    REQUIRE(k.traps.size() == 1);
    CHECK(k.traps[0].kind == IpuTrap::Kind::CommandWhileBusy);
    k.ctrl(kCtrlRst);
    k.cmd(0xA0000000u);
    REQUIRE(k.traps.size() == 2);
    CHECK(k.traps[1].kind == IpuTrap::Kind::ReservedCommand);
    CHECK_FALSE(k.c.busy());
    u8 z[16] = {};
    for (unsigned i = 0; i < kInCapacityQw; ++i) CHECK(k.c.write_in_fifo(qw_bytes(z), k.t));
    CHECK_FALSE(k.c.write_in_fifo(qw_bytes(z), k.t));
    REQUIRE(k.traps.size() == 3);
    CHECK(k.traps[2].kind == IpuTrap::Kind::InFifoOverflow);
    CHECK(k.c.push_input(reinterpret_cast<const u128*>(z), 1, k.t) == 0);  // DMA: stalls instead of trapping
    u128 q{};
    CHECK_FALSE(k.c.read_out_fifo(q, k.t));
    REQUIRE(k.traps.size() == 4);
    CHECK(k.traps[3].kind == IpuTrap::Kind::OutFifoUnderflow);
}
