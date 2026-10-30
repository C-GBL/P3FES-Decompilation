// Batch runs of real game microcode on synthetic input (09 §2 batch model: MSCAL 0 runs setup and the first batch,
// MSCNT resumes at the pair after E for the next one). The dumps are gitignored game data read in place; the tests
// skip when they are absent. Expected packet sizes come from our static reading of the program (marked [der]); the
// rest is a determinism check: two independent runs must agree bit for bit. None of this is hardware-verified.
#include "vu1_test_util.h"

#include <cstring>

using namespace p3fes;
using namespace p3fes::vu1;
using namespace p3fes::vu1::test;

namespace {

struct Snapshot {
    std::vector<std::vector<u128>> packets;
    std::vector<u8> regs; // vf, vi, acc, q p i r, flags, tpc
    std::vector<u8> data;
    u32 tpc = 0;
};

Snapshot snapshot(const VU1Interpreter& vu, const CaptureSink& sink) {
    const VU1State& s = vu.state();
    Snapshot out;
    out.packets = sink.packets;
    const auto put = [&](const void* p, std::size_t n) {
        const auto* b = static_cast<const u8*>(p);
        out.regs.insert(out.regs.end(), b, b + n);
    };
    put(s.vf, sizeof s.vf);
    put(s.vi, sizeof s.vi);
    put(s.acc, sizeof s.acc);
    const u32 scalars[9] = {s.q, s.p, s.i, s.r, s.mac, s.status, s.clip, s.tpc, s.pc};
    put(scalars, sizeof scalars);
    out.data.assign(s.data, s.data + kDataBytes);
    out.tpc = s.tpc;
    return out;
}

bool same_packets(const std::vector<std::vector<u128>>& a, const std::vector<std::vector<u128>>& b) {
    if (a.size() != b.size()) return false;
    for (std::size_t k = 0; k < a.size(); ++k) {
        if (a[k].size() != b[k].size()) return false;
        if (!a[k].empty() && std::memcmp(a[k].data(), b[k].data(), a[k].size() * sizeof(u128)) != 0) return false;
    }
    return true;
}

// rt2d_fill vu1_prog_089 (tag 0x741470, code 0x74147c, 1123 pairs, E at 0x45f, resume 0x461 -> jr 0x27).
constexpr u32 kRt2dFillCode = 0x74147c;
constexpr u32 kRt2dFillE = 0x45f;
constexpr u32 kVerts = 4;

// Synthetic material block (uploaded once; VU1 data memory persists across MSCAL/MSCNT, 09 §2.5): flags word
// 0x3FF.x = 0 selects the plain fill path (continuation 0xb2, read statically from the setup code, which the program
// itself stores in 0x3FF.y); 0x3FA.yzw supplies the GIF tag's upper 96 bits (PACKED, NREG 3, REGS ST/RGBAQ/XYZ2) the
// way the Rt2d bridge's UNPACK V4-32 to 0x3FA does (14 §2); 0x3F0..0x3F3 an identity matrix.
void setup_material(VU1State& s) {
    set_qword(s, 0x3F0, f2u(1), 0, 0, 0);
    set_qword(s, 0x3F1, 0, f2u(1), 0, 0);
    set_qword(s, 0x3F2, 0, 0, f2u(1), 0);
    set_qword(s, 0x3F3, 0, 0, 0, f2u(1));
    set_qword(s, 0x3F7, f2u(1), f2u(1), f2u(1), 0);
    set_qword(s, 0x3F8, f2u(2048), f2u(2048), 0, 0);
    set_qword(s, 0x3F9, 0, 0, 0, 0);
    set_qword(s, 0x3FA, 0, 3u << 28, 0x512u, 0);
    set_qword(s, 0x3FF, 0, 0, 0, 0);
}

// Synthetic input batch at TOP: kVerts * 3 qwords.
void write_batch(VU1State& s, u32 top, float base) {
    for (u32 v = 0; v < kVerts * 3; ++v) {
        const float f = base + static_cast<float>(v);
        set_qword(s, top + v, f2u(f), f2u(f * 2), f2u(1), f2u(1));
    }
}

Snapshot run_rt2d_fill(const std::vector<u8>& code, RunResult (&results)[2]) {
    CaptureSink sink;
    auto vu = std::make_unique<VU1Interpreter>(&sink);
    vu->load_micro(0, code);
    setup_material(vu->state());
    write_batch(vu->state(), 0, 10.0f);
    vu->set_tops(0, kVerts);
    results[0] = vu->mscal(0);
    // Second batch from the other VIF double buffer; MSCNT resumes at 0x461 (`jr vi15` -> batch entry 0x27).
    write_batch(vu->state(), 0x100, 50.0f);
    vu->set_tops(0x100, kVerts);
    results[1] = vu->mscnt();
    return snapshot(*vu, sink);
}

} // namespace

TEST_CASE("batch: null_transform (0x5cdb10) ends on E and resumes with MSCNT (hand: decoded program)") {
    const auto code = read_file(dump_path(0x5cdb1c));
    if (!code) {
        MESSAGE("skipped: dump not present: " << dump_path(0x5cdb1c).string());
        return;
    }
    REQUIRE(code->size() == 32);
    Snapshot runs[2];
    for (Snapshot& snap : runs) {
        CaptureSink sink;
        auto vu = std::make_unique<VU1Interpreter>(&sink);
        vu->load_micro(0, *code);
        RunResult r = vu->mscal(0);
        CHECK(r.status == RunStatus::Ended);
        CHECK(r.steps == 2); // E nop | nop, then its delay pair
        CHECK(vu->state().tpc == 16);
        r = vu->mscnt(); // b 0; nop; E pair; delay
        CHECK(r.status == RunStatus::Ended);
        CHECK(r.steps == 4);
        CHECK(vu->state().tpc == 16);
        CHECK(sink.packets.empty());
        snap = snapshot(*vu, sink);
    }
    CHECK(runs[0].regs == runs[1].regs);
    CHECK(runs[0].data == runs[1].data);
}

TEST_CASE("batch: rt2d_fill (0x741470) runs two batches to E with one GIF packet each, bit-identical across runs") {
    const auto code = read_file(dump_path(kRt2dFillCode));
    if (!code) {
        MESSAGE("skipped: dump not present: " << dump_path(kRt2dFillCode).string());
        return;
    }
    REQUIRE(code->size() == 1123 * 8);
    RunResult first[2], second[2];
    const Snapshot a = run_rt2d_fill(*code, first);
    const Snapshot b = run_rt2d_fill(*code, second);
    for (const RunResult& r : first) {
        CHECK(r.status == RunStatus::Ended);
        CHECK(r.steps > 0);
        CHECK(r.steps < 10000);
    }
    // [der] the plain fill path kicks once per batch from 0xd5: GIF tag + 3 qwords (ST, RGBAQ, XYZ2) per vertex.
    REQUIRE(a.packets.size() == 2);
    for (const auto& p : a.packets) {
        REQUIRE(p.size() == 1 + 3 * kVerts);
        const u64 tag = p[0].u64[0];
        CHECK((tag & 0x7FFFu) == kVerts); // NLOOP = ITOP, written by `ior vi15, vi08, vi09; isw.x`
        CHECK(((tag >> 15) & 1u) == 1u);   // EOP
        CHECK((tag >> 60) == 3u);          // NREG from 0x3FA.y
        CHECK(p[0].u64[1] == 0x512u);      // REGS from 0x3FA.zw
    }
    CHECK(a.regs.size() == b.regs.size());
    CHECK(a.regs == b.regs);
    CHECK(a.data == b.data);
    CHECK(same_packets(a.packets, b.packets));
    CHECK(first[0].steps == second[0].steps);
    CHECK(first[1].steps == second[1].steps);
    CHECK(first[1].steps < first[0].steps); // MSCNT skips the setup code at 0x00..0x26
    // TPC after each batch: the pair after the E pair's delay slot.
    CHECK(a.tpc == (kRt2dFillE + 2) * 8);
    MESSAGE("rt2d_fill batch steps: " << first[0].steps << " + " << first[1].steps
                                      << ", qwords kicked: " << a.packets[0].size() + a.packets[1].size());
}
