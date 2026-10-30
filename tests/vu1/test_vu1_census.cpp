// Reproduce symbols/vu1_micro_census.json (written by tools/ours/vu1/vu1_census.py with vu1_decode.py) from the 114
// gitignored dumps ida/logs/vu1/<code_va>.bin with the C++ decoder: per-program unit counts, flag counts, E pcs,
// xgkick/branch counts and the exact upper/lower mnemonic histograms, then the aggregate histograms. This is the
// proof that the C++ tables agree with the verified Python decoder on every pair the game ships. Skips cleanly when
// the dumps (game data) are absent.
#include "mini_json.h"
#include "vu1_test_util.h"

#include <algorithm>
#include <map>
#include <string>

using namespace p3fes;
using namespace p3fes::vu1;
using namespace p3fes::vu1::test;
namespace json = p3fes::test::json;

namespace {

using Hist = std::map<std::string, long long>;

Hist hist_of(const json::Value* obj) {
    Hist h;
    if (!obj) return h;
    for (const auto& [k, v] : obj->object) h[k] = v.as_int();
    return h;
}

struct ProgramCounts {
    Hist upper, lower;
    long long units = 0, unknown = 0, xgkick = 0, branches = 0;
    long long flags[5] = {}; // I E M D T
    std::vector<long long> e_pcs;
};

ProgramCounts count(const std::vector<u8>& bytes) {
    ProgramCounts c;
    c.units = static_cast<long long>(bytes.size() / 8);
    for (std::size_t k = 0; k + 8 <= bytes.size(); k += 8) {
        u32 lo_w, hi_w;
        std::memcpy(&lo_w, bytes.data() + k, 4);
        std::memcpy(&hi_w, bytes.data() + k + 4, 4);
        const DecodedPair d = decode_pair(lo_w, hi_w);
        ++c.upper[std::string(mnemonic(d.upper.op))];
        ++c.lower[std::string(mnemonic(d.lower.op))];
        if (d.upper.op == UpperOp::Unknown) ++c.unknown;
        if (d.lower.op == LowerOp::Unknown) ++c.unknown;
        if (d.lower.op == LowerOp::XGKICK) ++c.xgkick;
        if (is_branch(d.lower.op)) ++c.branches;
        c.flags[0] += d.i;
        c.flags[1] += d.e;
        c.flags[2] += d.m;
        c.flags[3] += d.d;
        c.flags[4] += d.t;
        if (d.e) c.e_pcs.push_back(static_cast<long long>(k / 8));
    }
    return c;
}

} // namespace

TEST_CASE("census: C++ decoder reproduces symbols/vu1_micro_census.json on the 114 dumps") {
    const auto text = read_file(repo_dir() / "symbols" / "vu1_micro_census.json");
    if (!text) {
        MESSAGE("skipped: symbols/vu1_micro_census.json not present");
        return;
    }
    const auto doc = json::parse(std::string_view(reinterpret_cast<const char*>(text->data()), text->size()));
    REQUIRE(doc.has_value());
    const json::Value* programs = doc->get("programs");
    const json::Value* aggregate = doc->get("aggregate");
    REQUIRE(programs != nullptr);
    REQUIRE(aggregate != nullptr);
    REQUIRE(programs->array.size() == 114);

    Hist all_upper, all_lower;
    long long all_units = 0, all_unknown = 0, all_xgkick = 0, all_branches = 0;
    std::size_t present = 0, missing = 0;
    for (const json::Value& p : programs->array) {
        const std::string name = p.get("name")->string;
        const u32 code_va = static_cast<u32>(std::stoul(p.get("code_va")->string, nullptr, 16));
        const auto bytes = read_file(dump_path(code_va));
        if (!bytes) {
            ++missing;
            continue;
        }
        ++present;
        CAPTURE(name);
        CHECK(static_cast<long long>(bytes->size()) == p.get("bytes")->as_int());
        CHECK(static_cast<long long>(bytes->size() % 8) == p.get("trailing_bytes")->as_int());
        const ProgramCounts c = count(*bytes);
        CHECK(c.units == p.get("units")->as_int());
        CHECK(c.unknown == 0);
        CHECK(p.get("unknown_count")->as_int() == 0);
        CHECK(c.upper == hist_of(p.get("upper")));
        CHECK(c.lower == hist_of(p.get("lower")));
        CHECK(c.xgkick == p.get("xgkick")->as_int());
        CHECK(c.branches == p.get("branches")->as_int());
        const json::Value* flags = p.get("flags");
        const char* names[5] = {"I", "E", "M", "D", "T"};
        for (int f = 0; f < 5; ++f) CHECK(c.flags[f] == flags->get(names[f])->as_int());
        std::vector<long long> e_pcs;
        for (const json::Value& e : p.get("e_pcs")->array) e_pcs.push_back(e.as_int());
        CHECK(c.e_pcs == e_pcs);

        for (const auto& [k, v] : c.upper) all_upper[k] += v;
        for (const auto& [k, v] : c.lower) all_lower[k] += v;
        all_units += c.units;
        all_unknown += c.unknown;
        all_xgkick += c.xgkick;
        all_branches += c.branches;
    }
    if (present == 0) {
        MESSAGE("skipped: no dumps under " << dumps_dir().string());
        return;
    }
    if (missing) {
        MESSAGE("aggregate comparison skipped: " << missing << " of 114 dumps missing under " << dumps_dir().string());
        return;
    }
    CHECK(all_units == aggregate->get("units")->as_int());
    CHECK(all_units == 123095);
    CHECK(all_unknown == 0);
    CHECK(all_xgkick == aggregate->get("xgkick")->as_int());
    CHECK(all_branches == aggregate->get("branches")->as_int());
    CHECK(all_upper == hist_of(aggregate->get("upper")));
    CHECK(all_lower == hist_of(aggregate->get("lower")));
    CHECK(static_cast<long long>(all_upper.size()) == aggregate->get("distinct_upper")->as_int());
    CHECK(static_cast<long long>(all_lower.size()) == aggregate->get("distinct_lower")->as_int());
    CHECK(all_upper.size() == 43);
    CHECK(all_lower.size() == 45);

    // The interpreter's census allow-list is exactly the observed set: nothing the game uses traps, nothing else runs.
    std::size_t census_upper = 0, census_lower = 0;
    for (unsigned k = 0; k < static_cast<unsigned>(UpperOp::Count); ++k) {
        const auto op = static_cast<UpperOp>(k);
        const bool observed = all_upper.count(std::string(mnemonic(op))) != 0 && op != UpperOp::Unknown;
        CAPTURE(mnemonic(op));
        CHECK(in_census(op) == observed);
        census_upper += in_census(op);
    }
    for (unsigned k = 0; k < static_cast<unsigned>(LowerOp::Count); ++k) {
        const auto op = static_cast<LowerOp>(k);
        const bool observed = all_lower.count(std::string(mnemonic(op))) != 0 && op != LowerOp::Unknown;
        CAPTURE(mnemonic(op));
        CHECK(in_census(op) == observed);
        census_lower += in_census(op);
    }
    CHECK(census_upper == 43);
    CHECK(census_lower == 45);
}

TEST_CASE("census: every dumped program runs from MSCAL 0 without trapping on its first 64 pairs (smoke)") {
    // Not a semantic check: zeroed data memory, TOP = ITOP = 0. It only shows the census allow-list covers the
    // programs' entry code; the batch tests drive full runs of null_transform and rt2d_fill.
    const auto text = read_file(repo_dir() / "symbols" / "vu1_micro_census.json");
    if (!text) {
        MESSAGE("skipped: symbols/vu1_micro_census.json not present");
        return;
    }
    const auto doc = json::parse(std::string_view(reinterpret_cast<const char*>(text->data()), text->size()));
    REQUIRE(doc.has_value());
    std::size_t ran = 0;
    for (const json::Value& p : doc->get("programs")->array) {
        const u32 code_va = static_cast<u32>(std::stoul(p.get("code_va")->string, nullptr, 16));
        const auto bytes = read_file(dump_path(code_va));
        if (!bytes) continue;
        auto vu = std::make_unique<VU1Interpreter>();
        vu->load_micro(0, *bytes);
        vu->start(0);
        const RunResult r = vu->run(64);
        CAPTURE(p.get("name")->string);
        CHECK(r.status != RunStatus::Trapped);
        ++ran;
    }
    if (!ran) MESSAGE("skipped: no dumps under " << dumps_dir().string());
}

constexpr u32 kProbeVerts = 6;

TEST_CASE("census: every referenced program reaches E from MSCAL 0 on a small batch; none traps (ITOP 6, zeroed data)") {
    // Robustness, not semantics: zero data memory, TOP 0, ITOP 6. Observed while writing this test: with ITOP 1 the
    // software-pipelined loops of the unreferenced and some matfx programs overshoot their `ibne` bound and wrap the
    // 16-bit counter (prologue advances the pointer twice), and 4 unreferenced programs (020/021/026/027) read their
    // vertex stride from 0x3EF.x, so zero data never advances them. Both are input properties, so the E check is
    // limited to the 86 referenced programs; the no-trap check covers all 114.
    const auto text = read_file(repo_dir() / "symbols" / "vu1_micro_census.json");
    if (!text) {
        MESSAGE("skipped: symbols/vu1_micro_census.json not present");
        return;
    }
    const auto doc = json::parse(std::string_view(reinterpret_cast<const char*>(text->data()), text->size()));
    REQUIRE(doc.has_value());
    std::size_t ran = 0, ended = 0, referenced = 0;
    u64 max_steps = 0, kicks = 0;
    for (const json::Value& p : doc->get("programs")->array) {
        const u32 code_va = static_cast<u32>(std::stoul(p.get("code_va")->string, nullptr, 16));
        const auto bytes = read_file(dump_path(code_va));
        if (!bytes) continue;
        auto vu = std::make_unique<VU1Interpreter>();
        vu->load_micro(0, *bytes);
        vu->set_tops(0, kProbeVerts);
        const RunResult r = vu->mscal(0, 200000);
        const bool is_referenced = p.get("family")->string != "unreferenced";
        CAPTURE(p.get("name")->string);
        CAPTURE(r.steps);
        CHECK(r.status != RunStatus::Trapped);
        if (is_referenced) {
            CHECK(r.status == RunStatus::Ended);
            ++referenced;
        }
        ++ran;
        if (r.status == RunStatus::Ended) {
            ++ended;
            max_steps = std::max(max_steps, r.steps);
        }
        kicks += vu->stats().kicks;
    }
    if (!ran) {
        MESSAGE("skipped: no dumps under " << dumps_dir().string());
        return;
    }
    CHECK(referenced == 86);
    MESSAGE("small batch: " << ended << "/" << ran << " programs ended on E (max " << max_steps << " pairs), "
                            << kicks << " kicks");
}
