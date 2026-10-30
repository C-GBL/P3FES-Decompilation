// p3fes_native_check: the g3 semantic model (runtime/native/g3_model.h) against the exact VU1 interpreter on
// captured batch inputs (p3fes --vu1-capture / --native-capture, save_run_input format). For every capture of
// vu1_prog_042_g3_generic (006b8d4c) / vu1_prog_064_g3_skin (006f8b1c): run the interpreter, collect its PATH1
// packets, run the model, compare field by field, print per (program, variant) statistics.
//
//   p3fes_native_check DIR [--verbose N]
#include "../g3_model.h"

#include "p3fes/vu1/vu1_interp.h"
#include "p3fes/vu1/vu1_profile.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace p3fes;

namespace {

struct Sink final : vu1::IGifSink {
    std::vector<std::vector<u128>> kicks;
    void kick(std::span<const u128> q) override { kicks.emplace_back(q.begin(), q.end()); }
};

struct Stat {
    u64 batches = 0, modelled = 0, unmodelled = 0, kick_mismatch = 0, verts = 0, culled_all = 0, clipped = 0;
    u64 tag_diff = 0, adc_diff = 0, xy_diff = 0, z_diff = 0, rgba_diff = 0, stq_diff = 0, fog_diff = 0;
    double max_xy = 0, max_z_rel = 0, max_rgba = 0, max_stq_rel = 0, max_fog = 0;
    u64 xy_gt1 = 0, rgba_gt1 = 0;
    u64 lights[32] = {};
    u64 morph = 0;
};

float asf(u32 v) {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

double rel(float a, float b) {
    const double d = std::fabs(double(a) - double(b)), m = std::max(std::fabs(double(a)), std::fabs(double(b)));
    return m == 0 ? 0 : d / m;
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: p3fes_native_check DIR [--verbose N]\n");
        return 2;
    }
    int verbose = 0;
    for (int i = 2; i < argc; ++i)
        if (!std::strcmp(argv[i], "--verbose") && i + 1 < argc) verbose = std::atoi(argv[++i]);
    std::map<std::string, Stat> stats;
    auto st = std::make_unique<vu1::VU1State>();
    auto vu = std::make_unique<vu1::VU1Interpreter>();
    u64 files = 0;
    double model_ns = 0;
    u64 model_verts = 0;
    int shown = 0;
    for (const auto& de : std::filesystem::recursive_directory_iterator(argv[1])) {
        if (!de.is_regular_file()) continue;
        u32 pc = 0;
        std::string prog;
        if (!vu1::load_run_input(de.path().string(), *st, pc, prog)) continue;
        const native::G3Prog gp = native::g3_identify(st->micro.bytes().data());
        if (gp == native::G3Prog::None) continue;
        ++files;
        // truth
        Sink sink;
        vu->set_sink(&sink);
        vu->state() = *st;
        vu1::RunResult r = pc == 0 ? vu->mscal(0) : vu->mscnt();
        (void)r;
        if (const char* tf = std::getenv("P3FES_TRACE_FILE"); tf && de.path().filename().string() == tf) {
            Sink none;
            vu->set_sink(&none);
            vu->state() = *st;
            vu->start(pc == 0 ? 0 : st->tpc);
            const u32 lo = static_cast<u32>(std::strtoul(std::getenv("P3FES_TRACE_LO"), nullptr, 16));
            const u32 hi = static_cast<u32>(std::strtoul(std::getenv("P3FES_TRACE_HI"), nullptr, 16));
            for (int k = 0; k < 20000; ++k) {
                const vu1::VU1State& z = vu->state();
                const u32 p = z.pc / 8;
                if (p >= lo && p <= hi)
                    std::printf("pc %03X mac %04X vi01 %04X vi03 %04X vi04 %04X vi07 %04X clip %06X vf19z %08X vf20z %08X\n", p,
                                z.mac, z.vi[1], z.vi[3], z.vi[4], z.vi[7], z.clip, z.vf[19][2], z.vf[20][2]);
                if (vu->step().status != vu1::RunStatus::Running) break;
            }
        }
        // the model's input: the state at the batch start (MSCAL 0: run the init to the batch pc)
        vu1::VU1State& m = *st;
        if (pc == 0) {
            Sink none;
            vu->set_sink(&none);
            vu->state() = *st;
            vu->start(0);
            for (int k = 0; k < 400 && vu->state().pc != native::g3_batch_pc(gp); ++k) vu->step();
            m = vu->state();
            if (std::getenv("P3FES_EMU_INIT")) {  // the native path's own init instead: compare what it sets
                auto e = std::make_unique<vu1::VU1State>(vu->state());
                auto pre = std::make_unique<vu1::VU1State>();
                u32 pc2 = 0;
                std::string prog2;
                vu1::load_run_input(de.path().string(), *pre, pc2, prog2);
                native::g3_init(gp, *pre);
                static int shown_init = 0;
                for (int r : {2, 28, 29, 30, 31})
                    for (int l = 0; l < 4; ++l)
                        if (pre->vf[r][l] != e->vf[r][l] && shown_init < 20) {
                            ++shown_init;
                            std::printf("init diff vf%02d.%c: emu %08X vu %08X\n", r, "xyzw"[l], pre->vf[r][l], e->vf[r][l]);
                        }
                for (int r : {12, 13, 14})
                    if (pre->vi[r] != e->vi[r] && shown_init < 20) {
                        ++shown_init;
                        std::printf("init diff vi%02d: emu %04X vu %04X\n", r, pre->vi[r], e->vi[r]);
                    }
                static int shown_data = 0;
                for (u32 q = 0; q < 1024 && shown_data < 12; ++q)
                    if (std::memcmp(pre->data + q * 16, e->data + q * 16, 16) != 0) {
                        ++shown_data;
                        const u32* a = reinterpret_cast<const u32*>(pre->data + q * 16);
                        const u32* bq = reinterpret_cast<const u32*>(e->data + q * 16);
                        std::printf("init diff data qw %03X (%s): emu %08X %08X %08X %08X vu %08X %08X %08X %08X\n", q,
                                    de.path().filename().string().c_str(), a[0], a[1], a[2], a[3], bq[0], bq[1], bq[2], bq[3]);
                    }
                static int shown_top = 0;
                if ((pre->top != e->top || pre->itop != e->itop) && shown_top++ < 5)
                    std::printf("init diff top/itop: emu %u/%u vu %u/%u\n", pre->top, pre->itop, e->top, e->itop);
                m = *pre;
            }
        }
        native::G3Batch b;
        b.want_dbg = true;
        const auto tm0 = std::chrono::steady_clock::now();
        bool ok = false;
        for (int rep = 0; rep < 20; ++rep) ok = native::g3_model(gp, m, b);
        model_ns += static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - tm0).count()) / 20.0;
        model_verts += b.n;
        const std::string key = std::string(gp == native::G3Prog::Generic ? "generic " : gp == native::G3Prog::Skin ? "skin " : "skinpar ") +
                                native::to_string(b.variant);
        Stat& S = stats[key];
        ++S.batches;
        if (b.morph) ++S.morph;
        S.lights[b.lights & 31]++;
        if (b.clipped) ++S.clipped;
        if (!ok) {
            ++S.unmodelled;
            continue;
        }
        ++S.modelled;
        if (b.culled_all) {
            ++S.culled_all;
            if (!sink.kicks.empty()) ++S.kick_mismatch;
            continue;
        }
        if (sink.kicks.size() != 1 || sink.kicks[0].size() != 1 + 3 * b.n) {
            ++S.kick_mismatch;
            continue;
        }
        const u32* t = reinterpret_cast<const u32*>(sink.kicks[0].data());
        bool bad = false;
        if (std::memcmp(t, b.tag, 16) != 0) {
            ++S.tag_diff;
            bad = true;
        }
        for (u32 i = 0; i < b.n; ++i) {
            const u32* q = t + 4 + i * 12;
            const native::G3OutVertex& o = b.v[i];
            ++S.verts;
            const double stq = std::max({rel(asf(q[0]), o.s), rel(asf(q[1]), o.t), rel(asf(q[2]), o.q)});
            S.max_stq_rel = std::max(S.max_stq_rel, stq);
            if (stq > 1e-5) ++S.stq_diff;
            double rg = 0;
            for (int j = 0; j < 4; ++j) rg = std::max(rg, std::fabs(double(s32(q[4 + j])) - o.rgba[j]));
            S.max_rgba = std::max(S.max_rgba, rg);
            if (rg > 0) ++S.rgba_diff;
            if (rg > 1) ++S.rgba_gt1;
            const double xy = std::max(std::fabs(double(s32(q[8])) - o.xyzw[0]), std::fabs(double(s32(q[9])) - o.xyzw[1]));
            S.max_xy = std::max(S.max_xy, xy);
            if (xy > 0) ++S.xy_diff;
            if (xy > 1) ++S.xy_gt1;
            const double zr = rel(float(s32(q[10])), float(o.xyzw[2]));
            S.max_z_rel = std::max(S.max_z_rel, zr);
            if (s32(q[10]) != o.xyzw[2]) ++S.z_diff;
            const bool adc_t = (q[11] >> 15) & 1u, adc_m = (u32(o.xyzw[3]) >> 15) & 1u;
            if (adc_t != adc_m) {
                ++S.adc_diff;
                bad = true;
            }
            const double fd = std::fabs(double((q[11] >> 4) & 0xFFu) - double((u32(o.xyzw[3]) >> 4) & 0xFFu));
            S.max_fog = std::max(S.max_fog, fd);
            if (fd > 0) ++S.fog_diff;
            if ((xy > 2 || rg > 2 || stq > 1e-3) && !bad) bad = true;
        }
        if (bad && shown < verbose) {
            ++shown;
            std::printf("--- %s %s n=%u pc=%u lights=%u morph=%d\n", de.path().filename().string().c_str(), key.c_str(),
                        b.n, pc, b.lights, b.morph);
            std::printf("  tag  vu %08X %08X %08X %08X  model %08X %08X %08X %08X\n", t[0], t[1], t[2], t[3], b.tag[0],
                        b.tag[1], b.tag[2], b.tag[3]);
            for (u32 i = 0; i < std::min<u32>(b.n, 8); ++i) {
                const u32* q = t + 4 + i * 12;
                const native::G3OutVertex& o = b.v[i];
                std::printf("  v%-2u vu  stq %.6g %.6g %.6g rgba %d %d %d %d xyzw %d %d %d %08X\n", i, asf(q[0]), asf(q[1]),
                            asf(q[2]), s32(q[4]), s32(q[5]), s32(q[6]), s32(q[7]), s32(q[8]), s32(q[9]), s32(q[10]), q[11]);
                if (i >= 2 && i - 2 < b.dbg.size()) std::printf("      det %g\n", b.dbg[i - 2]);
                std::printf("      mdl stq %.6g %.6g %.6g rgba %d %d %d %d xyzw %d %d %d %08X\n", o.s, o.t, o.q, o.rgba[0],
                            o.rgba[1], o.rgba[2], o.rgba[3], o.xyzw[0], o.xyzw[1], o.xyzw[2], u32(o.xyzw[3]));
            }
        }
    }
    std::printf("%llu captures; model %.1f ns per vertex (%llu vertices)\n", static_cast<unsigned long long>(files),
                model_ns / double(model_verts ? model_verts : 1), static_cast<unsigned long long>(model_verts));
    for (const auto& [k, S] : stats) {
        std::printf("%-22s batches %6llu modelled %6llu unmodelled %5llu (clipped %llu) culled_all %llu kick_mismatch %4llu verts %8llu morph %llu\n",
                    k.c_str(), (unsigned long long)S.batches, (unsigned long long)S.modelled, (unsigned long long)S.unmodelled, (unsigned long long)S.clipped, (unsigned long long)S.culled_all,
                    (unsigned long long)S.kick_mismatch, (unsigned long long)S.verts, (unsigned long long)S.morph);
        std::printf("    tag %llu adc %llu | xy diff %llu (>1: %llu, max %.0f) z diff %llu (max rel %.2g) rgba diff %llu (>1: %llu, max %.0f)"
                    " stq diff %llu (max rel %.2g) fog diff %llu (max %.0f)\n",
                    (unsigned long long)S.tag_diff, (unsigned long long)S.adc_diff, (unsigned long long)S.xy_diff,
                    (unsigned long long)S.xy_gt1, S.max_xy, (unsigned long long)S.z_diff, S.max_z_rel,
                    (unsigned long long)S.rgba_diff, (unsigned long long)S.rgba_gt1, S.max_rgba, (unsigned long long)S.stq_diff,
                    S.max_stq_rel, (unsigned long long)S.fog_diff, S.max_fog);
        std::printf("    lights:");
        for (int l = 0; l < 32; ++l)
            if (S.lights[l]) std::printf(" %d:%llu", l, (unsigned long long)S.lights[l]);
        std::printf("\n");
    }
    return 0;
}
