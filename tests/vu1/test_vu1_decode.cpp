// Decoder vectors mirroring tools/ours/vu1/vu1_decode.py --selftest (same hand-built words, same expected
// mnemonics and fields), so the two decoders are checked against one table even without the game dumps.
#include "vu1_test_util.h"

using namespace p3fes;
using namespace p3fes::vu1;
using namespace p3fes::vu1::test;

namespace {
std::string_view um(u32 hi) { return mnemonic(decode_upper(hi).op); }
std::string_view lm(u32 lo_w) { return mnemonic(decode_lower(lo_w, false).op); }
} // namespace

TEST_CASE("decode: upper funct table (hand: VU User's Manual; mirrors vu1_decode.py)") {
    CHECK(um(up(0x00, 1, 2, 3, 15)) == "ADDbc");
    CHECK(um(up(0x05, 1, 2, 3, 15)) == "SUBbc");
    CHECK(um(up(0x0A, 1, 2, 3, 15)) == "MADDbc");
    CHECK(um(up(0x0F, 1, 2, 3, 15)) == "MSUBbc");
    CHECK(um(up(0x10, 1, 2, 3, 15)) == "MAXbc");
    CHECK(um(up(0x15, 1, 2, 3, 15)) == "MINIbc");
    CHECK(um(up(0x18, 1, 2, 3, 15)) == "MULbc");
    const char* rest[] = {"MULq", "MAXi", "MULi", "MINIi", "ADDq", "MADDq", "ADDi", "MADDi", "SUBq", "MSUBq",
                          "SUBi", "MSUBi", "ADD", "MADD", "MUL", "MAX", "SUB", "MSUB", "OPMSUB", "MINI"};
    for (u32 k = 0; k < 20; ++k) CHECK(um(up(0x1C + k, 1, 2, 3, 15)) == rest[k]);
    for (u32 f = 0x30; f < 0x3C; ++f) CHECK(um(up(f, 1, 2, 3, 15)) == "UNKNOWN");
    const UpperInsn u = decode_upper(up(0x03, 1, 2, 3, 0xA));
    CHECK(u.dest == 0xA);
    CHECK(u.fd == 1);
    CHECK(u.fs == 2);
    CHECK(u.ft == 3);
    CHECK(u.bc == 3);
}

TEST_CASE("decode: upper special table (hand: VU User's Manual; mirrors vu1_decode.py)") {
    CHECK(um(up_sp(0x00, 2, 3, 15)) == "ADDAbc");
    CHECK(um(up_sp(0x06, 2, 3, 15)) == "SUBAbc");
    CHECK(um(up_sp(0x09, 2, 3, 15)) == "MADDAbc");
    CHECK(um(up_sp(0x0C, 2, 3, 15)) == "MSUBAbc");
    const char* conv[] = {"ITOF0", "ITOF4", "ITOF12", "ITOF15", "FTOI0", "FTOI4", "FTOI12", "FTOI15"};
    for (u32 k = 0; k < 8; ++k) CHECK(um(up_sp(0x10 + k, 2, 3, 15)) == conv[k]);
    CHECK(um(up_sp(0x1B, 2, 3, 15)) == "MULAbc");
    const char* q[] = {"MULAq", "ABS", "MULAi", "CLIP", "ADDAq", "MADDAq", "ADDAi", "MADDAi",
                       "SUBAq", "MSUBAq", "SUBAi", "MSUBAi", "ADDA", "MADDA", "MULA"};
    for (u32 k = 0; k < 15; ++k) CHECK(um(up_sp(0x1C + k, 2, 3, 15)) == q[k]);
    CHECK(um(up_sp(0x2B, 2, 3, 15)) == "UNKNOWN");
    CHECK(um(up_sp(0x2C, 2, 3, 15)) == "SUBA");
    CHECK(um(up_sp(0x2D, 2, 3, 15)) == "MSUBA");
    CHECK(um(up_sp(0x2E, 2, 3, 15)) == "OPMULA");
    CHECK(um(0x000002FFu) == "NOP");
    CHECK(um(up_sp(0x2F, 7, 9, 3)) == "NOP"); // any fields: index 0x2F
    for (u32 idx = 0x30; idx < 0x80; ++idx) CHECK(um(up_sp(idx, 2, 3, 15)) == "UNKNOWN");
}

TEST_CASE("decode: flags, LOI and the lower NOP rule (hand: VU User's Manual; mirrors vu1_decode.py)") {
    const DecodedPair e = decode_pair(LNOP, 0x400002FFu);
    CHECK(e.e);
    CHECK_FALSE(e.i);
    CHECK(mnemonic(e.lower.op) == "NOP");
    const DecodedPair i = decode_pair(0x3F800000u, 0x800002FFu);
    CHECK(i.i);
    CHECK(i.lower.op == LowerOp::LOI);
    CHECK(i.lower.raw == 0x3F800000u);
    const DecodedPair mdt = decode_pair(LNOP, 0x380002FFu);
    CHECK((mdt.m && mdt.d && mdt.t));
    // `move.x vf00, vf00` is not the canonical nop word: it decodes as MOVE (vu1_decode.py does the same).
    CHECK(lm(l_move(X, 0, 0)) == "MOVE");
    // With I set, a word that would be a branch is the LOI immediate (09 §0: topic 14 over-counted these).
    CHECK(decode_lower(0x437F0000u, true).op == LowerOp::LOI);
    CHECK(decode_lower(0x437F0000u, false).op == LowerOp::BAL);
}

TEST_CASE("decode: lower opcode table and immediates (hand: VU User's Manual; mirrors vu1_decode.py)") {
    CHECK(lm(l_lq(XYZW, 1, 2, -1)) == "LQ");
    CHECK(decode_lower(l_lq(XYZW, 1, 2, -1), false).imm11 == -1);
    CHECK(lm(l_sq(XYZW, 2, 1, 3)) == "SQ");
    CHECK(lm(l_ilw(X, 1, 2, 0)) == "ILW");
    CHECK(lm(l_isw(X, 1, 2, 0)) == "ISW");
    const LowerInsn iaddiu = decode_lower((0x08u << 25) | (1u << 16) | (2u << 11) | (0xFu << 21) | 0x7FFu, false);
    CHECK(iaddiu.op == LowerOp::IADDIU);
    CHECK(iaddiu.imm15 == 0x7FFF);
    CHECK(decode_lower(l_iaddiu(1, 2, 0x4321), false).imm15 == 0x4321);
    CHECK(lm(l_isubiu(1, 2, 5)) == "ISUBIU");
    CHECK(decode_lower(l_fcset(0x123456), false).imm24 == 0x123456);
    CHECK(lm((0x10u << 25) | 0xABCDEFu) == "FCEQ");
    CHECK(lm(l_fcset(0)) == "FCSET");
    CHECK(lm(l_fcand(0)) == "FCAND");
    CHECK(lm(l_fcor(0)) == "FCOR");
    CHECK(lm(lo(0x14, 3, 0, 0, 0)) == "FSEQ");
    CHECK(decode_lower((0x15u << 25) | (1u << 21) | 0x7FFu, false).imm12 == 0xFFF);
    CHECK(lm(lo(0x16, 3, 0, 0, 0)) == "FSAND");
    CHECK(lm(lo(0x17, 3, 0, 0, 0)) == "FSOR");
    CHECK(lm(lo(0x18, 3, 4, 0, 0)) == "FMEQ");
    CHECK(lm(l_fmand(3, 4)) == "FMAND");
    CHECK(lm(lo(0x1B, 3, 4, 0, 0)) == "FMOR");
    CHECK(lm(l_fcget(3)) == "FCGET");
    CHECK(lm(l_b(-3)) == "B");
    CHECK(lm(l_bal(5, 2)) == "BAL");
    CHECK(lm(l_jr(7)) == "JR");
    CHECK(lm(lo(0x25, 5, 7, 0, 0)) == "JALR");
    CHECK(lm(l_ibeq(1, 2, 4)) == "IBEQ");
    CHECK(lm(l_ibne(1, 2, 0)) == "IBNE");
    CHECK(lm(l_ibltz(2, 0)) == "IBLTZ");
    CHECK(lm(l_ibgtz(2, 0)) == "IBGTZ");
    CHECK(lm(l_iblez(2, 0)) == "IBLEZ");
    CHECK(lm(l_ibgez(2, 0)) == "IBGEZ");
    for (u32 opc : {0x02u, 0x03u, 0x06u, 0x07u, 0x0Au, 0x0Fu, 0x19u, 0x1Du, 0x1Fu, 0x22u, 0x23u, 0x26u, 0x27u,
                    0x2Au, 0x2Bu, 0x41u, 0x7Fu})
        CHECK(lm(opc << 25) == "UNKNOWN");
}

TEST_CASE("decode: lower opcode 0x40 integer and special tables (hand: VU User's Manual; mirrors vu1_decode.py)") {
    CHECK(lm(l_iadd(3, 2, 1)) == "IADD");
    CHECK(lm(l_isub(3, 2, 1)) == "ISUB");
    const LowerInsn iaddi = decode_lower(l_iaddi(1, 2, -1), false);
    CHECK(iaddi.op == LowerOp::IADDI);
    CHECK(iaddi.imm5 == -1);
    CHECK(lm(l_iand(3, 2, 1)) == "IAND");
    CHECK(lm(l_ior(3, 2, 1)) == "IOR");
    CHECK(lm(lo_int(0x33, 0, 0, 0)) == "UNKNOWN");
    const struct {
        u32 index;
        const char* name;
    } sp[] = {{0x30, "MOVE"},  {0x31, "MR32"},   {0x34, "LQI"},    {0x35, "SQI"},     {0x36, "LQD"},
              {0x37, "SQD"},   {0x38, "DIV"},    {0x39, "SQRT"},   {0x3A, "RSQRT"},   {0x3B, "WAITQ"},
              {0x3C, "MTIR"},  {0x3D, "MFIR"},   {0x3E, "ILWR"},   {0x3F, "ISWR"},    {0x40, "RNEXT"},
              {0x41, "RGET"},  {0x42, "RINIT"},  {0x43, "RXOR"},   {0x64, "MFP"},     {0x68, "XTOP"},
              {0x69, "XITOP"}, {0x6C, "XGKICK"}, {0x70, "ESADD"},  {0x71, "ERSADD"},  {0x72, "ELENG"},
              {0x73, "ERLENG"}, {0x74, "EATANxy"}, {0x75, "EATANxz"}, {0x76, "ESUM"}, {0x78, "ESQRT"},
              {0x79, "ERSQRT"}, {0x7A, "ERCPR"}, {0x7B, "WAITP"},  {0x7C, "ESIN"},    {0x7D, "EATAN"},
              {0x7E, "EEXP"}};
    for (const auto& e : sp) CHECK(lm(lo_sp(e.index, 1, 2, 0)) == e.name);
    CHECK(lm(lo_sp(0x32, 0, 2, 15)) == "UNKNOWN");
    CHECK(lm(lo_sp(0x7F, 0, 2, 15)) == "UNKNOWN");
    const LowerInsn div = decode_lower(l_div(2, bw, 1, bx), false);
    CHECK(div.fsf == bw);
    CHECK(div.ftf == bx);
}

TEST_CASE("decode: branch targets wrap inside 16 KiB micro memory (hand: VU User's Manual)") {
    CHECK(branch_target(decode_lower(l_b(-3), false), 16) == 0);
    CHECK(branch_target(decode_lower(l_b(-2), false), 0) == 0x3FF8);           // raw -8
    CHECK(branch_target(decode_lower(l_b(0x2A5), false), 0x56C * 8) == 0x12 * 8); // raw 0x812 (09 §0)
    CHECK(branch_target(decode_lower(l_ibeq(1, 2, 4), false), 0) == 40);
}

TEST_CASE("decode: never fails on any opcode/funct/fd combination (robustness, mirrors vu1_decode.py)") {
    unsigned decoded = 0;
    for (u32 opc = 0; opc < 128; ++opc)
        for (u32 funct = 0; funct < 64; ++funct)
            for (u32 idf : {0u, 0x0Cu, 0x1Fu}) {
                (void)decode_pair((opc << 25) | (idf << 6) | funct, 0xFFFFFFFFu);
                (void)decode_pair((opc << 25) | (idf << 6) | funct, 0u);
                ++decoded;
            }
    for (u32 funct = 0; funct < 64; ++funct)
        for (u32 fd = 0; fd < 32; ++fd) (void)decode_upper((fd << 6) | funct);
    CHECK(decoded == 128u * 64u * 3u);
}

TEST_CASE("decode: the 4-unit null_transform image (hand: bytes of vu1_decode.py's self-test)") {
    const u8 img[32] = {0x3c, 0x03, 0x00, 0x80, 0xff, 0x02, 0x00, 0x40, 0x3c, 0x03, 0x00, 0x80, 0xff, 0x02, 0x00, 0x00,
                        0xfd, 0x07, 0x00, 0x40, 0xff, 0x02, 0x00, 0x00, 0x3c, 0x03, 0x00, 0x80, 0xff, 0x02, 0x00, 0x00};
    const char* lowers[4] = {"NOP", "NOP", "B", "NOP"};
    for (int k = 0; k < 4; ++k) {
        u32 lo_w, hi_w;
        std::memcpy(&lo_w, img + k * 8, 4);
        std::memcpy(&hi_w, img + k * 8 + 4, 4);
        const DecodedPair d = decode_pair(lo_w, hi_w);
        CHECK(mnemonic(d.upper.op) == "NOP");
        CHECK(mnemonic(d.lower.op) == lowers[k]);
        CHECK(d.e == (k == 0));
        if (k == 2) CHECK(branch_target(d.lower, 16) == 0);
    }
}
