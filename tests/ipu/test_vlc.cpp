// Annex B variable-length codes: structure of every table (prefix-free, Kraft sums, VDEC length field) and decode
// vectors hand-derived from the printed tables of ISO/IEC 13818-2 (B.1-B.4, B.9-B.15), including the NeedBits /
// Invalid distinction for short input.
#include "ipu_test_util.h"

#include <cmath>
#include <utility>

using namespace it;
using namespace p3fes::ipu::mpeg2;

namespace {

// MSB-aligned window from a '0'/'1' string; returns the number of bits.
unsigned win(const char* s, u32& w) {
    w = 0;
    unsigned n = 0;
    for (const char* p = s; *p; ++p) {
        if (*p != '0' && *p != '1') continue;
        if (*p == '1') w |= 0x80000000u >> n;
        ++n;
    }
    return n;
}

struct V {
    const char* bits;
    int value;
};

void check_table(Vlc t, std::initializer_list<V> vectors) {
    for (const V& v : vectors) {
        u32 w = 0;
        const unsigned n = win(v.bits, w);
        unsigned len = 0;
        int value = 0;
        INFO("table " << static_cast<int>(t) << " code " << v.bits);
        REQUIRE(decode_vlc(t, w, n, len, value) == Decode::Ok);
        CHECK(len == n);
        CHECK(value == v.value);
        // the same code followed by arbitrary bits decodes the same way
        REQUIRE(decode_vlc(t, w | (0xFFFFFFFFu >> n), 32, len, value) == Decode::Ok);
        CHECK(len == n);
        CHECK(value == v.value);
    }
}

struct D {
    const char* bits;  // without the sign bit
    DctCode::Kind kind;
    int run, level;
};

void check_dct(bool table_one, std::initializer_list<D> vectors) {
    for (const D& d : vectors) {
        u32 w = 0;
        const unsigned n = win(d.bits, w);
        DctCode c;
        INFO("table " << (table_one ? "B.15" : "B.14") << " code " << d.bits);
        REQUIRE(decode_dct(table_one, w, n, c) == Decode::Ok);
        CHECK(c.length == n);
        CHECK(c.kind == d.kind);
        if (d.kind == DctCode::Coef) {
            CHECK(c.run == d.run);
            CHECK(c.level == d.level);
        }
    }
}

template <typename Row>
void check_prefix_free(const std::vector<Row>& rows, double& kraft) {
    kraft = 0;
    for (std::size_t i = 0; i < rows.size(); ++i) {
        kraft += std::ldexp(1.0, -static_cast<int>(rows[i].length));
        for (std::size_t j = 0; j < rows.size(); ++j) {
            if (i == j) continue;
            const Row& a = rows[i];
            const Row& b = rows[j];
            if (a.length > b.length) continue;
            // a must not be a prefix of b (equal-length duplicates are caught too)
            const bool prefix = (static_cast<u32>(b.code) >> (b.length - a.length)) == a.code;
            INFO("codes " << a.code << "/" << int(a.length) << " and " << b.code << "/" << int(b.length));
            CHECK_FALSE(prefix);
        }
    }
}

} // namespace

TEST_CASE("VLC tables: prefix-free, Kraft sums, VDEC length field = code length") {
    const std::pair<Vlc, double> tables[] = {
        // Kraft sums computed from the printed tables (1 = complete code).
        {Vlc::MbAddrInc, -1},       {Vlc::MbAddrIncMpeg1, -1}, {Vlc::MbTypeI, 0.75},    {Vlc::MbTypeP, 0.984375},
        {Vlc::MbTypeB, -1},         {Vlc::MbTypeD, 0.5},       {Vlc::MotionCode, -1},   {Vlc::DmVector, 1.0},
        {Vlc::DcSizeLuma, 1.0},     {Vlc::DcSizeChroma, 1.0},  {Vlc::Cbp, -1},
    };
    for (const auto& [t, expect] : tables) {
        const std::vector<VlcCodeInfo> rows = vlc_codes(t);
        REQUIRE(!rows.empty());
        double kraft = 0;
        check_prefix_free(rows, kraft);
        INFO("table " << static_cast<int>(t) << " Kraft " << kraft);
        CHECK(kraft <= 1.0);
        if (expect >= 0) CHECK(kraft == doctest::Approx(expect).epsilon(1e-12));
        const bool vdec_table = t != Vlc::DcSizeLuma && t != Vlc::DcSizeChroma && t != Vlc::Cbp;  // BDEC-internal
        for (const VlcCodeInfo& r : rows) CHECK(r.vdec_length == (vdec_table ? r.length : 0u));
    }
    CHECK(vlc_codes(Vlc::MbAddrInc).size() == 34);       // 1..33 + escape
    CHECK(vlc_codes(Vlc::MbAddrIncMpeg1).size() == 35);  // + stuffing
    CHECK(vlc_codes(Vlc::Cbp).size() == 64);             // every 4:2:0 pattern 0..63 has a code
    std::vector<bool> seen(64, false);
    for (const VlcCodeInfo& r : vlc_codes(Vlc::Cbp)) {
        REQUIRE(r.value >= 0);
        REQUIRE(r.value < 64);
        CHECK_FALSE(seen[static_cast<std::size_t>(r.value)]);
        seen[static_cast<std::size_t>(r.value)] = true;
    }
    for (bool one : {false, true}) {
        const std::vector<DctCodeInfo> rows = dct_codes(one);
        double kraft = 0;
        check_prefix_free(rows, kraft);
        CHECK(kraft <= 1.0);
        // every (run, level) pair appears once
        for (std::size_t i = 0; i < rows.size(); ++i)
            for (std::size_t j = i + 1; j < rows.size(); ++j)
                if (rows[i].kind == DctCode::Coef && rows[j].kind == DctCode::Coef)
                    CHECK_FALSE((rows[i].run == rows[j].run && rows[i].level == rows[j].level));
        CHECK(rows.size() == 111 + 1 + 1);  // 111 run/level codes (B.14 / B.15), escape, end_of_block
    }
    CHECK(vlc_max_length(Vlc::MbAddrInc) == 11);
    CHECK(vlc_max_length(Vlc::Cbp) == 9);
    CHECK(vlc_max_length(Vlc::MotionCode) == 11);
}

TEST_CASE("VLC B.1 macroblock_address_increment (hand vectors) and the MPEG-1-only stuffing code") {
    const std::initializer_list<V> rows = {
        {"1", 1}, {"011", 2}, {"010", 3}, {"0011", 4}, {"0010", 5}, {"00011", 6}, {"00010", 7}, {"0000111", 8},
        {"0000110", 9}, {"00001011", 10}, {"00001010", 11}, {"00001001", 12}, {"00001000", 13}, {"00000111", 14},
        {"00000110", 15}, {"0000010111", 16}, {"0000010110", 17}, {"0000010101", 18}, {"0000010100", 19},
        {"0000010011", 20}, {"0000010010", 21}, {"00000100011", 22}, {"00000100010", 23}, {"00000100001", 24},
        {"00000100000", 25}, {"00000011111", 26}, {"00000011110", 27}, {"00000011101", 28}, {"00000011100", 29},
        {"00000011011", 30}, {"00000011010", 31}, {"00000011001", 32}, {"00000011000", 33},
        {"00000001000", kMbaiEscape},
    };
    check_table(Vlc::MbAddrInc, rows);
    check_table(Vlc::MbAddrIncMpeg1, rows);
    check_table(Vlc::MbAddrIncMpeg1, {{"00000001111", kMbaiStuffing}});
    u32 w = 0;
    unsigned len = 0;
    int v = 0;
    const unsigned n = win("00000001111", w);
    CHECK(decode_vlc(Vlc::MbAddrInc, w, n, len, v) == Decode::Invalid);
    // short input: 7 zeros may still become escape/stuffing; 8 zeros can begin no code
    win("0000000", w);
    CHECK(decode_vlc(Vlc::MbAddrInc, w, 7, len, v) == Decode::NeedBits);
    win("00000000", w);
    CHECK(decode_vlc(Vlc::MbAddrInc, w, 8, len, v) == Decode::Invalid);
    win("0000011", w);  // '0000 011' is a proper prefix of '0000 0110' (15) and '0000 0111' (14)
    CHECK(decode_vlc(Vlc::MbAddrInc, w, 7, len, v) == Decode::NeedBits);
    CHECK(decode_vlc(Vlc::MbAddrInc, 0, 0, len, v) == Decode::NeedBits);
}

TEST_CASE("VLC B.2/B.3/B.4 macroblock_type and the D-picture table (flags quant 0x10 fwd 8 bwd 4 pattern 2 intra 1)") {
    check_table(Vlc::MbTypeI, {{"1", 0x01}, {"01", 0x11}});
    check_table(Vlc::MbTypeP, {{"1", 0x0A}, {"01", 0x02}, {"001", 0x08}, {"00011", 0x01}, {"00010", 0x1A},
                               {"00001", 0x12}, {"000001", 0x11}});
    check_table(Vlc::MbTypeB, {{"10", 0x0C}, {"11", 0x0E}, {"010", 0x04}, {"011", 0x06}, {"0010", 0x08}, {"0011", 0x0A},
                               {"00011", 0x01}, {"00010", 0x1E}, {"000011", 0x1A}, {"000010", 0x16}, {"000001", 0x11}});
    check_table(Vlc::MbTypeD, {{"1", 0x01}});
    u32 w = 0;
    unsigned len = 0;
    int v = 0;
    win("00", w);
    CHECK(decode_vlc(Vlc::MbTypeI, w, 2, len, v) == Decode::Invalid);
    win("000000", w);
    CHECK(decode_vlc(Vlc::MbTypeP, w, 6, len, v) == Decode::Invalid);
}

TEST_CASE("VLC B.10 motion_code, B.11 dmvector") {
    check_table(Vlc::MotionCode,
                {{"1", 0},           {"010", 1},          {"011", -1},         {"0010", 2},         {"0011", -2},
                 {"00010", 3},       {"00011", -3},       {"0000110", 4},      {"0000111", -4},     {"00001010", 5},
                 {"00001011", -5},   {"00001000", 6},     {"00001001", -6},    {"00000110", 7},     {"00000111", -7},
                 {"0000010110", 8},  {"0000010111", -8},  {"0000010100", 9},   {"0000010101", -9},  {"0000010010", 10},
                 {"0000010011", -10}, {"00000100010", 11}, {"00000100011", -11}, {"00000100000", 12},
                 {"00000100001", -12}, {"00000011110", 13}, {"00000011111", -13}, {"00000011100", 14},
                 {"00000011101", -14}, {"00000011010", 15}, {"00000011011", -15}, {"00000011000", 16},
                 {"00000011001", -16}});
    check_table(Vlc::DmVector, {{"0", 0}, {"10", 1}, {"11", -1}});
}

TEST_CASE("VLC B.12/B.13 dct_dc_size, B.9 coded_block_pattern") {
    check_table(Vlc::DcSizeLuma, {{"100", 0}, {"00", 1}, {"01", 2}, {"101", 3}, {"110", 4}, {"1110", 5}, {"11110", 6},
                                  {"111110", 7}, {"1111110", 8}, {"11111110", 9}, {"111111110", 10},
                                  {"111111111", 11}});
    check_table(Vlc::DcSizeChroma, {{"00", 0}, {"01", 1}, {"10", 2}, {"110", 3}, {"1110", 4}, {"11110", 5},
                                    {"111110", 6}, {"1111110", 7}, {"11111110", 8}, {"111111110", 9},
                                    {"1111111110", 10}, {"1111111111", 11}});
    check_table(Vlc::Cbp, {{"111", 60},       {"1101", 4},        {"1100", 8},        {"1011", 16},
                           {"1010", 32},      {"10011", 12},      {"10010", 48},      {"10001", 20},
                           {"10000", 40},     {"01111", 28},      {"01110", 44},      {"01101", 52},
                           {"01100", 56},     {"01011", 1},       {"01010", 61},      {"01001", 2},
                           {"01000", 62},     {"001111", 24},     {"001110", 36},     {"001101", 3},
                           {"001100", 63},    {"0010111", 5},     {"0010110", 9},     {"0010101", 17},
                           {"0010100", 33},   {"0010011", 6},     {"0010010", 10},    {"0010001", 18},
                           {"0010000", 34},   {"00011111", 7},    {"00011110", 11},   {"00011101", 19},
                           {"00011100", 35},  {"00011011", 13},   {"00011010", 49},   {"00001111", 25},
                           {"00001000", 57},  {"00000100", 58},   {"000000111", 31},  {"000000110", 47},
                           {"000000101", 55}, {"000000100", 59},  {"000000011", 27},  {"000000010", 39},
                           {"000000001", 0}});
}

TEST_CASE("VLC B.14 DCT coefficients, table zero (hand vectors), escape, end_of_block") {
    check_dct(false, {
        {"10", DctCode::Eob, 0, 0},           {"11", DctCode::Coef, 0, 1},          {"011", DctCode::Coef, 1, 1},
        {"0100", DctCode::Coef, 0, 2},        {"0101", DctCode::Coef, 2, 1},        {"00101", DctCode::Coef, 0, 3},
        {"00111", DctCode::Coef, 3, 1},       {"00110", DctCode::Coef, 4, 1},       {"000110", DctCode::Coef, 1, 2},
        {"000111", DctCode::Coef, 5, 1},      {"000101", DctCode::Coef, 6, 1},      {"000100", DctCode::Coef, 7, 1},
        {"0000110", DctCode::Coef, 0, 4},     {"0000100", DctCode::Coef, 2, 2},     {"0000111", DctCode::Coef, 8, 1},
        {"0000101", DctCode::Coef, 9, 1},     {"000001", DctCode::Escape, 0, 0},    {"00100110", DctCode::Coef, 0, 5},
        {"00100001", DctCode::Coef, 0, 6},    {"00100101", DctCode::Coef, 1, 3},    {"00100100", DctCode::Coef, 3, 2},
        {"00100111", DctCode::Coef, 10, 1},   {"00100011", DctCode::Coef, 11, 1},   {"00100010", DctCode::Coef, 12, 1},
        {"00100000", DctCode::Coef, 13, 1},   {"0000001010", DctCode::Coef, 0, 7},  {"0000001100", DctCode::Coef, 1, 4},
        {"0000001011", DctCode::Coef, 2, 3},  {"0000001111", DctCode::Coef, 4, 2},  {"0000001001", DctCode::Coef, 5, 2},
        {"0000001110", DctCode::Coef, 14, 1}, {"0000001101", DctCode::Coef, 15, 1}, {"0000001000", DctCode::Coef, 16, 1},
        {"000000011101", DctCode::Coef, 0, 8}, {"000000011000", DctCode::Coef, 0, 9},
        {"000000010011", DctCode::Coef, 0, 10}, {"000000010000", DctCode::Coef, 0, 11},
        {"000000011011", DctCode::Coef, 1, 5}, {"000000010100", DctCode::Coef, 2, 4},
        {"000000011100", DctCode::Coef, 3, 3}, {"000000010010", DctCode::Coef, 4, 3},
        {"000000011110", DctCode::Coef, 6, 2}, {"000000010101", DctCode::Coef, 7, 2},
        {"000000010001", DctCode::Coef, 8, 2}, {"000000011111", DctCode::Coef, 17, 1},
        {"000000011010", DctCode::Coef, 18, 1}, {"000000011001", DctCode::Coef, 19, 1},
        {"000000010111", DctCode::Coef, 20, 1}, {"000000010110", DctCode::Coef, 21, 1},
        {"0000000011010", DctCode::Coef, 0, 12}, {"0000000011111", DctCode::Coef, 22, 1},
        {"00000000011111", DctCode::Coef, 0, 16}, {"000000000011000", DctCode::Coef, 0, 32},
        {"000000000011111", DctCode::Coef, 1, 8}, {"0000000000010011", DctCode::Coef, 1, 15},
        {"0000000000011111", DctCode::Coef, 27, 1}, {"0000000000011011", DctCode::Coef, 31, 1},
    });
    u32 w = 0;
    DctCode c;
    win("00000", w);
    CHECK(decode_dct(false, w, 5, c) == Decode::NeedBits);   // escape / longer codes still possible
    CHECK(decode_dct(false, 0, 11, c) == Decode::NeedBits);   // '0000 0000 0001 xxxx' (16-bit codes) still possible
    CHECK(decode_dct(false, 0, 12, c) == Decode::Invalid);    // twelve zeros begin no code
    CHECK(decode_dct(false, 0, 16, c) == Decode::Invalid);
}

TEST_CASE("VLC B.15 DCT coefficients, table one (intra_vlc_format = 1)") {
    check_dct(true, {
        {"0110", DctCode::Eob, 0, 0},         {"10", DctCode::Coef, 0, 1},          {"010", DctCode::Coef, 1, 1},
        {"110", DctCode::Coef, 0, 2},         {"00101", DctCode::Coef, 2, 1},       {"0111", DctCode::Coef, 0, 3},
        {"00111", DctCode::Coef, 3, 1},       {"000110", DctCode::Coef, 4, 1},      {"00110", DctCode::Coef, 1, 2},
        {"000111", DctCode::Coef, 5, 1},      {"0000110", DctCode::Coef, 6, 1},     {"0000100", DctCode::Coef, 7, 1},
        {"11100", DctCode::Coef, 0, 4},       {"0000111", DctCode::Coef, 2, 2},     {"0000101", DctCode::Coef, 8, 1},
        {"1111000", DctCode::Coef, 9, 1},     {"000001", DctCode::Escape, 0, 0},    {"11101", DctCode::Coef, 0, 5},
        {"000101", DctCode::Coef, 0, 6},      {"1111001", DctCode::Coef, 1, 3},     {"00100110", DctCode::Coef, 3, 2},
        {"1111010", DctCode::Coef, 10, 1},    {"00100001", DctCode::Coef, 11, 1},   {"00100101", DctCode::Coef, 12, 1},
        {"00100100", DctCode::Coef, 13, 1},   {"000100", DctCode::Coef, 0, 7},      {"00100111", DctCode::Coef, 1, 4},
        {"11111100", DctCode::Coef, 2, 3},    {"11111101", DctCode::Coef, 4, 2},    {"000000100", DctCode::Coef, 5, 2},
        {"000000101", DctCode::Coef, 14, 1},  {"000000111", DctCode::Coef, 15, 1},  {"0000001101", DctCode::Coef, 16, 1},
        {"1111011", DctCode::Coef, 0, 8},     {"1111100", DctCode::Coef, 0, 9},     {"00100011", DctCode::Coef, 0, 10},
        {"00100010", DctCode::Coef, 0, 11},   {"00100000", DctCode::Coef, 1, 5},    {"0000001100", DctCode::Coef, 2, 4},
        {"000000011100", DctCode::Coef, 3, 3}, {"11111010", DctCode::Coef, 0, 12},  {"11111011", DctCode::Coef, 0, 13},
        {"11111110", DctCode::Coef, 0, 14},   {"11111111", DctCode::Coef, 0, 15},
    });
}
