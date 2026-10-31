// Modernize layer 4 (docs/MODERNIZE_PLAN.md §3 "4. Movies", runtime/native/movies): the native MPEG decoder on
// streams built here (no game data): every shown picture identical through the native engine and through the
// emulated IPU (the same core, IpuCore driven by commands); libmpeg's display order (a reference is shown when the
// next one is decoded, B pictures at once, the last reference at the sequence end); the I picture's known pixels;
// plan()'s byte counts are enough to decode; the service over a wrapping ring; the state round trip.
#include <doctest.h>

#include <cstring>
#include <vector>

#include "mpeg_video.h"
#include "native_movies.h"
#include "p3fes/ipu/mpeg2.h"
#include "p3fes/state_io.h"

using namespace p3fes;
using namespace p3fes::native::movies;
namespace m2 = p3fes::ipu::mpeg2;

namespace {

// ---- a small MPEG video writer ---------------------------------------------------------------------------------
struct Writer {
    std::vector<u8> b;
    u64 bits = 0;
    void put(u32 v, unsigned n) {
        for (unsigned i = n; i-- > 0;) {
            if ((bits & 7) == 0) b.push_back(0);
            if ((v >> i) & 1u) b.back() |= static_cast<u8>(0x80u >> (bits & 7));
            ++bits;
        }
    }
    void align() {
        while (bits & 7) put(0, 1);
    }
    void start(u8 code) {
        align();
        put(0x000001u, 24);
        put(code, 8);
    }
    void vlc(m2::Vlc t, int value) {
        for (const m2::VlcCodeInfo& c : m2::vlc_codes(t))
            if (c.value == value) {
                put(c.code, c.length);
                return;
            }
        FAIL("no code for value " << value);
    }
    // One coefficient (not the first of a non-intra block) of table zero / one, with its sign.
    void coef(bool table_one, unsigned run, int level) {
        for (const m2::DctCodeInfo& c : m2::dct_codes(table_one))
            if (c.kind == m2::DctCode::Coef && c.run == run && c.level == static_cast<unsigned>(level < 0 ? -level : level)) {
                put(c.code, c.length);
                put(level < 0 ? 1u : 0u, 1);
                return;
            }
        FAIL("no code for run " << run << " level " << level);
    }
    void eob(bool table_one) {
        for (const m2::DctCodeInfo& c : m2::dct_codes(table_one))
            if (c.kind == m2::DctCode::Eob) {
                put(c.code, c.length);
                return;
            }
    }
};

struct Enc {
    Writer w;
    bool mpeg2 = false, ivf = false, qst = false;
    unsigned idp = 0;
    void sequence(unsigned width, unsigned height) {
        w.start(0xB3);
        w.put(width, 12);
        w.put(height, 12);
        w.put(1, 4);  // aspect
        w.put(4, 4);  // 29.97
        w.put(0x3FFFF, 18);
        w.put(1, 1);
        w.put(16, 10);
        w.put(0, 1);
        w.put(0, 1);  // default intra matrix
        w.put(0, 1);  // default non-intra matrix
        if (mpeg2) {
            w.start(0xB5);
            w.put(1, 4);
            w.put(0x48, 8);
            w.put(1, 1);  // progressive_sequence
            w.put(1, 2);  // 4:2:0
            w.put(0, 2);
            w.put(0, 2);
            w.put(0, 12);
            w.put(1, 1);
            w.put(0, 8);
            w.put(0, 1);
            w.put(0, 2);
            w.put(0, 5);
        }
    }
    void gop() {
        w.start(0xB8);
        w.put(0, 25 - 1 - 6);
        w.put(1, 1);  // marker inside the time code
        w.put(0, 6);
        w.put(1, 1);  // closed_gop
        w.put(0, 1);
    }
    void picture(unsigned tref, unsigned type) {
        w.start(0x00);
        w.put(tref, 10);
        w.put(type, 3);
        w.put(0xFFFF, 16);
        if (type >= 2) {
            w.put(0, 1);
            w.put(mpeg2 ? 7u : 1u, 3);
        }
        if (type == 3) {
            w.put(0, 1);
            w.put(mpeg2 ? 7u : 1u, 3);
        }
        w.put(0, 1);  // extra_bit_picture
        if (mpeg2) {
            w.start(0xB5);
            w.put(8, 4);
            for (unsigned i = 0; i < 4; ++i) w.put(type == 1 ? 15u : (type == 2 && i >= 2 ? 15u : 1u), 4);
            w.put(idp, 2);
            w.put(3, 2);  // frame picture
            w.put(0, 1);
            w.put(1, 1);  // frame_pred_frame_dct
            w.put(0, 1);
            w.put(qst ? 1u : 0u, 1);
            w.put(ivf ? 1u : 0u, 1);
            w.put(0, 1);
            w.put(0, 1);
            w.put(1, 1);
            w.put(1, 1);
            w.put(0, 1);
        }
    }
    void slice(unsigned row, unsigned qsc) {
        w.start(static_cast<u8>(row + 1));
        w.put(qsc, 5);
        w.put(0, 1);
    }
    void mbai(unsigned inc) { w.vlc(mpeg2 ? m2::Vlc::MbAddrInc : m2::Vlc::MbAddrIncMpeg1, static_cast<int>(inc)); }
    void mbtype(unsigned pct, int flags) {
        w.vlc(pct == 1 ? m2::Vlc::MbTypeI : pct == 2 ? m2::Vlc::MbTypeP : m2::Vlc::MbTypeB, flags);
    }
    void mv(int dx, int dy) {  // f_code 1: motion_code = delta
        w.vlc(m2::Vlc::MotionCode, dx);
        w.vlc(m2::Vlc::MotionCode, dy);
    }
    // An intra block: DC differential `dc` (luma / chroma table), then (run, level) pairs, EOB.
    void intra_block(bool luma, int dc, std::initializer_list<std::pair<unsigned, int>> ac = {}) {
        unsigned size = 0;
        for (int a = dc < 0 ? -dc : dc; a; a >>= 1) ++size;
        w.vlc(luma ? m2::Vlc::DcSizeLuma : m2::Vlc::DcSizeChroma, static_cast<int>(size));
        if (size) w.put(static_cast<u32>(dc > 0 ? dc : dc + (1 << size) - 1), size);
        for (auto [r, l] : ac) w.coef(mpeg2 && ivf, r, l);
        w.eob(mpeg2 && ivf);
    }
    // A non-intra block: the first coefficient run 0 level +-1 as '1s', then the others.
    void inter_block(int first, std::initializer_list<std::pair<unsigned, int>> ac = {}) {
        w.put(1, 1);
        w.put(first < 0 ? 1u : 0u, 1);
        for (auto [r, l] : ac) w.coef(false, r, l);
        w.eob(false);
    }
    void intra_mb(int base) {
        for (unsigned b = 0; b < 4; ++b) {
            if (b == 0) intra_block(true, base, {{0, 3}, {2, -1}});
            else intra_block(true, b == 2 ? -5 : 2);
        }
        intra_block(false, 3);
        intra_block(false, -2, {{1, 2}});
    }
};

// I P B B (decode order) at 48 x 32 (3 x 2 macroblocks), every macroblock kind and skip rule libmpeg handles.
std::vector<u8> make_stream(bool mpeg2) {
    Enc e;
    e.mpeg2 = mpeg2;
    e.ivf = mpeg2;
    e.qst = mpeg2;
    e.idp = mpeg2 ? 2u : 0u;
    e.sequence(48, 32);
    e.gop();
    // I
    e.picture(0, 1);
    for (unsigned row = 0; row < 2; ++row) {
        e.slice(row, 8);
        for (unsigned x = 0; x < 3; ++x) {
            e.mbai(1);
            e.mbtype(1, m2::kMbIntra);
            e.intra_mb(row == 0 && x == 0 ? 0 : static_cast<int>(x * 7 + row * 3) - 6);
        }
    }
    // P: MC coded (half-pel), skipped, no-MC coded; intra, MC not coded, MC coded + quant
    e.picture(3, 2);
    e.slice(0, 8);
    e.mbai(1);
    e.mbtype(2, m2::kMbForward | m2::kMbPattern);
    e.mv(3, 1);
    e.w.vlc(m2::Vlc::Cbp, 0x20);
    e.inter_block(1, {{1, -2}});
    e.mbai(2);  // macroblock 1 skipped
    e.mbtype(2, m2::kMbPattern);
    e.w.vlc(m2::Vlc::Cbp, 0x01);
    e.inter_block(-1);
    e.slice(1, 8);
    e.mbai(1);
    e.mbtype(2, m2::kMbIntra);
    e.intra_mb(4);
    e.mbai(1);
    e.mbtype(2, m2::kMbForward);
    e.mv(-2, 2);
    e.mbai(1);
    e.mbtype(2, m2::kMbQuant | m2::kMbForward | m2::kMbPattern);
    e.w.put(4, 5);
    e.mv(1, -3);  // after (-2, 2): (-1, -1)
    e.w.vlc(m2::Vlc::Cbp, 0x3F);
    for (unsigned b = 0; b < 6; ++b) e.inter_block(b & 1 ? -1 : 1);
    // B 1: bidirectional coded with both vectors half-pel in x and y (libmpeg's _rix_111 rounding), skipped (same
    // prediction), backward not coded; forward coded, intra, bidirectional not coded
    e.picture(1, 3);
    e.slice(0, 8);
    e.mbai(1);
    e.mbtype(3, m2::kMbForward | m2::kMbBackward | m2::kMbPattern);
    e.mv(1, 1);
    e.mv(1, 1);
    e.w.vlc(m2::Vlc::Cbp, 0x10);
    e.inter_block(1);
    e.mbai(2);
    e.mbtype(3, m2::kMbBackward);
    e.mv(-2, -1);
    e.slice(1, 8);
    e.mbai(1);
    e.mbtype(3, m2::kMbForward | m2::kMbPattern);
    e.mv(2, 0);
    e.w.vlc(m2::Vlc::Cbp, 0x02);
    e.inter_block(1, {{0, 1}});
    e.mbai(1);
    e.mbtype(3, m2::kMbIntra);
    e.intra_mb(-3);
    e.mbai(1);
    e.mbtype(3, m2::kMbForward | m2::kMbBackward);
    e.mv(1, -1);
    e.mv(-1, 1);
    // B 2: bidirectional not coded and two skipped; forward not coded and two skipped
    e.picture(2, 3);
    e.slice(0, 8);
    e.mbai(1);
    e.mbtype(3, m2::kMbForward | m2::kMbBackward);
    e.mv(0, 1);
    e.mv(1, 0);
    e.mbai(3);
    e.mbtype(3, m2::kMbForward | m2::kMbBackward);
    e.mv(0, 0);
    e.mv(0, 0);
    e.slice(1, 8);
    e.mbai(1);
    e.mbtype(3, m2::kMbForward);
    e.mv(1, 0);
    e.mbai(2);
    e.mbtype(3, m2::kMbForward);
    e.mv(0, 0);
    e.w.start(0xB7);
    e.w.align();
    return e.w.b;
}

struct Shown {
    std::vector<std::vector<u8>> frames;
    std::vector<u32> types;
    Status end = Status::Shown;
};

template <class E>
Shown decode_all(const std::vector<u8>& s, bool rgb32) {
    Shown r;
    MpegDecoder d;
    E e(s.data(), s.size());
    std::vector<u8> out(64u * 1024u);
    for (int i = 0; i < 16; ++i) {
        const Status st = d.decode(e, rgb32, out.data(), out.size());
        if (st != Status::Shown) {
            r.end = st;
            break;
        }
        r.frames.emplace_back(out.begin(), out.begin() + static_cast<std::ptrdiff_t>(d.frame_bytes(rgb32)));
        r.types.push_back(d.last_shown_type());
    }
    return r;
}

}  // namespace

TEST_CASE("native movies: MPEG-1 and MPEG-2 streams decode identically through the native engine and the IPU") {
    for (const bool mpeg2 : {false, true}) {
        CAPTURE(mpeg2);
        const std::vector<u8> s = make_stream(mpeg2);
        const Shown n = decode_all<DirectEngine>(s, true);
        const Shown i = decode_all<IpuEngine>(s, true);
        CHECK(n.end == Status::End);
        CHECK(i.end == Status::End);
        // libmpeg's order: I (when P is decoded), B, B, then P at the sequence end
        REQUIRE(n.types == std::vector<u32>{1, 3, 3, 2});
        REQUIRE(i.types == n.types);
        for (std::size_t k = 0; k < n.frames.size(); ++k) {
            CAPTURE(k);
            CHECK(n.frames[k].size() == 6u * 1024u);
            CHECK(n.frames[k] == i.frames[k]);
        }
        // RAW8 output: the same pictures before the colour conversion
        const Shown r = decode_all<DirectEngine>(s, false);
        REQUIRE(r.frames.size() == 4);
        CHECK(r.frames[0].size() == 6u * 384u);
        CHECK(r.frames[3] == decode_all<IpuEngine>(s, false).frames[3]);
    }
}

TEST_CASE("native movies: the I picture's pixels, column-major macroblocks, the IPU's CSC") {
    const Shown r = decode_all<DirectEngine>(make_stream(false), false);
    REQUIRE(!r.frames.empty());
    // macroblock (0, 0): DC differential 0 on the predictor reset 128 -> luma block 0's DC 128 plus its two AC terms;
    // block 1 (DC +2 -> 130): flat 130 since the predictor carries; Cb (+3 -> 131) flat
    const std::vector<u8>& raw = r.frames[0];
    CHECK(raw[0 * 384 + 8] == 130);           // block 1 (x 8, y 0)
    CHECK(raw[0 * 384 + 256] == 131);         // Cb
    // column-major: index 1 is macroblock (column 0, row 1) -- row 1's slice resets the predictor: DC base -3 -> 125,
    // its block 1 (+2) flat 127 -- and index 2 is (column 1, row 0): the predictor carried from (0, 0)'s block 3 (127)
    // plus its base +1 -> 128, block 1 flat 130
    CHECK(raw[1 * 384 + 8] == 127);
    CHECK(raw[2 * 384 + 8] == 130);
    const Shown c = decode_all<DirectEngine>(make_stream(false), true);
    int rr = 0, g = 0, b = 0;
    m2::ycbcr_to_rgb(raw[8], raw[256 + 4], raw[320 + 4], rr, g, b);  // pixel (8, 0): chroma sample (4, 0)
    const u8* px = c.frames[0].data() + 8 * 4;
    CHECK(px[0] == rr);
    CHECK(px[1] == g);
    CHECK(px[2] == b);    CHECK(px[3] == 0x80);  // TH0 = TH1 = 0
}

TEST_CASE("native movies: plan() names the bytes each call reads; the call decodes the same from just those") {
    const std::vector<u8> s = make_stream(false);
    const Shown all = decode_all<DirectEngine>(s, true);
    MpegDecoder d;
    std::size_t pos = 0;
    unsigned bit = 0;
    std::vector<u8> out(64u * 1024u);
    for (std::size_t k = 0; k <= all.frames.size(); ++k) {
        CAPTURE(k);
        const Plan p = d.plan(s.data() + pos, s.size() - pos, bit);
        // with one byte too few the plan asks for more
        if (p.status == Status::Shown && p.needed > 1) {
            const Plan q = d.plan(s.data() + pos, p.needed - 1, bit);
            CHECK(q.status == Status::NeedData);
        }
        std::vector<u8> cut(s.begin() + static_cast<std::ptrdiff_t>(pos),
                            s.begin() + static_cast<std::ptrdiff_t>(pos + p.needed));
        DirectEngine e(cut.data(), cut.size(), bit);
        const Status st = d.decode(e, true, out.data(), out.size());
        if (k == all.frames.size()) {
            CHECK(p.status == Status::End);
            CHECK(st == Status::End);
            break;
        }
        REQUIRE(p.status == Status::Shown);
        REQUIRE(st == Status::Shown);
        CHECK(!e.overrun());
        CHECK(std::memcmp(out.data(), all.frames[k].data(), all.frames[k].size()) == 0);
        const u64 at = u64{pos} * 8 + e.bitpos();
        pos = static_cast<std::size_t>(at / 8);
        bit = static_cast<unsigned>(at & 7);
    }
}

TEST_CASE("native movies: the service decodes from a wrapping ring and round-trips its state") {
    const std::vector<u8> s = make_stream(true);
    const Shown all = decode_all<DirectEngine>(s, true);
    constexpr u32 kRingSize = 4096, kVibuf = 0x1000, kMpeg = 0x2000;
    REQUIRE(s.size() < kRingSize - 400);
    auto avail = [&](const NativeMovies& m) { return m.ring_queue_end(kVibuf) - m.ring_cursor(kVibuf) / 8; };
    std::vector<u8> out(64u * 1024u);

    // the read position moves to `start` over zero bytes first (no start code: the call finds no picture), then the
    // stream lies across the ring's end
    NativeMovies a;
    a.ring_reset(0, kVibuf);
    a.mpeg_create(0, kMpeg, kVibuf);
    constexpr u32 start = kRingSize - 300;
    std::vector<u8> ring(kRingSize, 0);
    a.ring_set_queue_end(kVibuf, start);
    CHECK(a.mpeg_plan(kMpeg, ring.data(), kRingSize, avail(a)).kind == MoviePlan::NeedData);
    CHECK(a.mpeg_decode(0, kMpeg, ring.data(), kRingSize, avail(a), true, nullptr, 0).kind == MovieDecode::Error);
    const u64 cur = a.ring_cursor(kVibuf) / 8;
    REQUIRE(cur + 8 >= start);
    REQUIRE(cur <= start + 8);
    a.mpeg_reset(0, kMpeg);
    for (std::size_t k = 0; k < s.size(); ++k) ring[(cur + k) % kRingSize] = s[k];
    a.ring_set_queue_end(kVibuf, cur + s.size());
    for (std::size_t k = 0; k < 2; ++k) {
        CAPTURE(k);
        CHECK(a.mpeg_plan(kMpeg, ring.data(), kRingSize, avail(a)).kind == MoviePlan::Shown);
        const MovieDecode d =
            a.mpeg_decode(0, kMpeg, ring.data(), kRingSize, avail(a), true, out.data(), static_cast<u32>(out.size()));
        REQUIRE(d.kind == MovieDecode::Shown);
        CHECK(d.width == 48);
        CHECK(d.height == 32);
        CHECK(d.shown == k + 1);
        CHECK(d.cycles > 0);  // the faithful call's modelled guest time
        CHECK(std::memcmp(out.data(), all.frames[k].data(), 6 * 1024) == 0);
    }
    CHECK(a.stats().pictures[1] == 1);
    CHECK(a.stats().pictures[2] == 1);
    CHECK(a.stats().pictures[3] == 1);

    // save after two pictures, load into a fresh service: both go on identically to the end
    StateIo w;
    a.state(w);
    const std::vector<u8> st = w.take_buffer();
    NativeMovies b;
    StateIo r(st.data(), st.size());
    b.state(r);
    REQUIRE(r.ok());
    CHECK(r.at_end());
    CHECK(b.ring_cursor(kVibuf) == a.ring_cursor(kVibuf));
    CHECK(b.ring_queue_end(kVibuf) == a.ring_queue_end(kVibuf));
    for (std::size_t k = 2; k < 5; ++k) {
        CAPTURE(k);
        std::vector<u8> oa(64u * 1024u), ob(64u * 1024u);
        const u64 av = avail(a);
        const MovieDecode da = a.mpeg_decode(0, kMpeg, ring.data(), kRingSize, av, true, oa.data(), static_cast<u32>(oa.size()));
        const MovieDecode db = b.mpeg_decode(0, kMpeg, ring.data(), kRingSize, av, true, ob.data(), static_cast<u32>(ob.size()));
        CHECK(da.kind == db.kind);
        CHECK(da.cycles == db.cycles);
        CHECK(oa == ob);
        if (k < 4) {
            CHECK(da.kind == MovieDecode::Shown);
            CHECK(std::memcmp(oa.data(), all.frames[k].data(), 6 * 1024) == 0);
        } else {
            CHECK(da.kind == MovieDecode::End);
        }
    }
    CHECK(a.ring_cursor(kVibuf) / 8 >= cur + s.size() - 4);  // the whole stream read (the end code's padding aside)
    a.mpeg_delete(0, kMpeg);
    CHECK(a.decoder(kMpeg) == nullptr);
    a.ring_close(0, kVibuf);
    CHECK(a.ring_cursor(kVibuf) == 0);
}