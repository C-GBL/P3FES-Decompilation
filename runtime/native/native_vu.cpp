// NativeG3 (native_vu.h): the g3 VU1 batches drawn without the VU1, the GIF and the GS front end.
#include "native_vu.h"

#include "p3fes/gs/gs_core.h"
#include "p3fes/gs/gs_ops.h"
#include "p3fes/prof.h"
#include "p3fes/vu1/vu1_interp.h"
#include "p3fes/vu1/vu1_profile.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <string>

namespace p3fes::native {

namespace {
u64 ns_since(std::chrono::steady_clock::time_point t0) {
    return static_cast<u64>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t0).count());
}

// The VU state an exact batch run leaves that a later exact run of this program reads (doc 31 §2.3): the resume
// point, vi15 (the jump back to the batch start) and the swapped output buffers.
void leave_like_exact(G3Prog p, vu1::VU1State& s) {
    s.tpc = g3_end_tpc(p);
    s.pc = s.tpc;
    s.running = false;
    s.ending = false;
    s.vi[15] = static_cast<u16>(g3_batch_pc(p) / 8u);
    const u16 t = s.vi[13];
    s.vi[13] = s.vi[14];
    s.vi[14] = t;
}
} // namespace

NativeG3::NativeG3(gs::GsCore& core, gs::GsOpRecorder& rec, vu1::IGifSink& gif_sink) : core_(core), rec_(rec), sink_(gif_sink) {
    batch_.clip_in_model = true;
}

// Frame interpolation (docs/ANALYSIS/32 §3, track H's key): key = FNV-1a over the first 8 input vertices, the last
// one, N and the program (the object-space block is the same bytes every frame while the mesh's resEntry is
// resident; equal keys = instances of one cluster, told apart by the rows), rows = the camera x object transform.
gs::NativeBatchTag NativeG3::batch_tag(G3Prog p, const vu1::VU1State& s, u32 top, u32 n) {
    gs::NativeBatchTag t;
    const u32 stride = p == G3Prog::Generic ? 4u : 5u;
    u64 h = 0xcbf29ce484222325ull ^ (static_cast<u64>(n) << 8) ^ static_cast<u64>(p);
    const auto mix = [&](u32 qw) {
        const u8* d = s.data + ((top + qw) & 1023u) * 16u;
        u64 a, b;
        std::memcpy(&a, d, 8);
        std::memcpy(&b, d + 8, 8);
        h = (h ^ a) * 0x100000001b3ull;
        h = (h ^ b) * 0x100000001b3ull;
    };
    const u32 nv = std::min<u32>(n, 8u);
    for (u32 i = 0; i < nv * stride; ++i) mix(i);
    if (n > 8) for (u32 i = 0; i < stride; ++i) mix((n - 1) * stride + i);
    t.key = h;
    std::memcpy(t.rows, s.data + 0x3F0 * 16, 64);
    t.prog = static_cast<u8>(p);
    return t;
}

void NativeG3::fallback_begin(const gs::NativeBatchTag& tag) {
    if (diff_ || verify_every_) return;
    fb_open_ = true;
    if (emit_) emit_([this, tag] { rec_.on_native_fallback_begin(tag); });
    else rec_.on_native_fallback_begin(tag);
}

G3Prog NativeG3::identify(const vu1::MicroMemory& m) {
    if (m.generation() == gen_) return prog_;
    gen_ = m.generation();
    ++st_.identifies;
    prog_ = g3_identify(m.bytes().data());
    return prog_;
}

bool NativeG3::run(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) {
    vu1::VU1State& s = vu.state();
    if (pending_) diff_close();
    pre_valid_ = false;
    if (fb_open_) {  // defensive: a declined batch whose after_exact never came
        fb_open_ = false;
        rec_.on_native_fallback_end();
    }
    const G3Prog p = identify(s.micro);
    const bool side = rec_.native_side_table();  // frame interpolation (doc 32): batches carry their tag
    if (p == G3Prog::None || !(mask_ & (p == G3Prog::Generic ? 1u : p == G3Prog::Skin ? 2u : 4u))) return false;
    ++st_.runs;
    const bool mscal = r.op == 0x14 || r.op == 0x15;
    if ((mscal && r.imm != 0) || (!mscal && s.tpc != g3_end_tpc(p))) {
        ++st_.fb_entry;
        return false;
    }
    if (r.gif_busy) {  // the exact path would queue its PATH1 packet behind PATH2/PATH3: keep that order
        ++st_.fb_gif_busy;
        if (side) fallback_begin(batch_tag(p, s, r.top, s.itop & 1023u));
        return false;
    }
    if (!capture_dir_.empty() && (capture_seq_++ % capture_every_) == 0 && st_.captured < capture_max_) {
        char name[64];
        std::snprintf(name, sizeof name, "/g3_%06llu.vu1in", static_cast<unsigned long long>(st_.captured));
        if (vu1::save_run_input(capture_dir_ + name, s, mscal ? r.imm * 8u : s.tpc,
                                p == G3Prog::Generic ? "006b8d4c" : p == G3Prog::Skin ? "006f8b1c" : "006f598c"))
            ++st_.captured;
    }
    if (mscal) {
        g3_init(p, s);  // idempotent with the program's own init, so a fallback below may still run it
        ++st_.inits;
    }
    const bool check = diff_ || (verify_every_ != 0 && (verify_seq_++ % verify_every_) == 0);
    batch_.clip_in_model = !check;  // a checked batch is compared with the VU1 packet: model the clipper as it decides
    if (check) {  // the model on the state as it is, then the exact run kicks into kick() below
        if (g3_model(p, s, batch_)) {
            pending_ = true;
            kicks_ = 0;
            ++st_.diff_batches;
            if (diff_) {
                if (!pre_) pre_ = std::make_unique<vu1::VU1State>();
                *pre_ = s;
                leave_like_exact(p, *pre_);
                pre_valid_ = true;
            }
        }
        return false;
    }
    // The GPU vertex stage's vertices never reach the CPU: with the frame interpolation's side table on (doc 32),
    // batches take the CPU model, whose converted vertices the side table records.
    if (gpu_ && !side) {
        const auto tg = std::chrono::steady_clock::now();
        if (prepare_gpu(p, s, work_)) {
            work_.has_tag = false;
            if (emit_) {
                auto w = std::make_shared<GsWork>(std::move(work_));
                work_ = GsWork{};
                emit_([this, w] { apply_gs(*w); });
            } else {
                apply_gs(work_);
            }
            st_.submit_ns += ns_since(tg);
            ++st_.native;
            ++st_.gpu_batches;
            leave_like_exact(p, s);
            return true;
        }
        st_.submit_ns += ns_since(tg);
    }
    const auto t0 = std::chrono::steady_clock::now();
    const bool modelled = g3_model(p, s, batch_);
    st_.model_ns += ns_since(t0);
    const auto t1 = std::chrono::steady_clock::now();
    const bool ok = modelled && prepare(batch_, work_);
    work_.has_tag = ok && side;
    if (work_.has_tag) work_.tag = batch_tag(p, s, r.top, batch_.n);
    if (!ok) {
        st_.submit_ns += ns_since(t1);
        if (batch_.clipped) ++st_.fb_clipped;
        ++st_.fb_model;
        if (side) fallback_begin(batch_tag(p, s, r.top, s.itop & 1023u));
        return false;
    }
    if (!batch_.culled_all) {
        if (emit_) {
            auto w = std::make_shared<GsWork>(std::move(work_));
            work_ = GsWork{};
            emit_([this, w] { apply_gs(*w); });
        } else {
            apply_gs(work_);
        }
    }
    st_.submit_ns += ns_since(t1);
    ++st_.native;
    ++st_.variant[static_cast<int>(batch_.variant)];
    leave_like_exact(p, s);
    return true;
}

// The packet the program would kick, without building it (VU1 stage): the tag decides PRIM and the register order;
// the triangles the GS would kick (strip: every vertex from the third on, list: every third; ADC set = no kick) become
// index triples. Returns false (nothing done) for a tag this path does not expect.
bool NativeG3::prepare(const G3Batch& b, GsWork& w) {
    if (b.culled_all) return true;  // the clipper kicked nothing (every vertex outside one plane)
    if (b.v.size() != b.n && !b.explicit_tris) return false;
    const u32 tag_hi = b.tag[1];
    const bool pre = (tag_hi >> 14) & 1u;
    const u32 prim = (tag_hi >> 15) & 0x7FFu;
    const u32 flg = (tag_hi >> 26) & 3u;
    const u32 nreg = (tag_hi >> 28) & 0xFu;
    const u64 regs = static_cast<u64>(b.tag[2]) | (static_cast<u64>(b.tag[3]) << 32);
    if (flg != 0 || nreg != 3 || !pre) return false;  // every g3 tag carries PRE (else PRIM would be GS state)
    const u32 r0 = regs & 0xF, r1 = (regs >> 4) & 0xF, r2 = (regs >> 8) & 0xF;
    if (r0 != 0x2 || r1 != 0x1 || (r2 != 0x4 && r2 != 0x5)) return false;
    const u32 type = prim & 7u;
    if (type != 3 && type != 4) return false;
    w.gpu = false;  // work_ is reused: a CPU-path batch after a GPU one
    w.write_prim = true;
    w.prim = prim;
    w.fogged = r2 == 0x4;
    w.type = type;
    w.v.assign(b.v.begin(), b.v.end());
    w.idx.clear();
    const u32 n = b.n;
    if (b.explicit_tris) {  // the in-model clipper's triangles
        w.idx.assign(b.tris.begin(), b.tris.end());
        st_.verts += static_cast<u32>(b.v.size());
        st_.tris += w.idx.size() / 3;
        ++st_.clipped_native;
        return true;
    }
    for (u32 i = 2; i < n; ++i) {
        if (type == 3 && i % 3 != 2) continue;
        if ((static_cast<u32>(b.v[i].xyzw[3]) >> 15) & 1u) {
            ++st_.culled;
            continue;
        }
        w.idx.push_back(static_cast<u16>(i - 2));
        w.idx.push_back(static_cast<u16>(i - 1));
        w.idx.push_back(static_cast<u16>(i));
    }
    st_.verts += n;
    st_.tris += w.idx.size() / 3;
    return true;
}

// The GPU vertex stage's input for a batch the CPU does not need to model (every variant except the full clipper):
// the record of gs_native_hlsl.h. False when the batch should take the CPU path (clipper, odd tag).
bool NativeG3::prepare_gpu(G3Prog p, const vu1::VU1State& s, GsWork& w) {
    u32 prim = 0, slots = 0, palq = 0;
    if (!g3_gpu_record(p, s, w.rec, slots, prim, palq)) return false;
    w.pal.resize(static_cast<std::size_t>(palq) * 4u);
    if (palq) std::memcpy(w.pal.data(), s.data + 0x2B8u * 16u, palq * 16u);
    w.gpu = true;
    w.write_prim = true;
    w.prim = prim;
    w.slots = slots;
    st_.verts += s.itop & 1023u;
    st_.gpu_words += w.rec.size() + w.pal.size();
    return true;
}

// GS stage: the PRIM write the tag would make, the vertices exactly as GsCore::write_packed would form them from the
// STQ / RGBAQ / XYZ(F)2 words (the parts that depend on GS registers -- FOG for XYZ2, UV -- read here), the recorder.
void NativeG3::apply_gs(const GsWork& w) {
    if (w.write_prim) core_.write_reg(0x00 /* PRIM */, w.prim);
    if (w.gpu) {
        const prof::Scope prof_zone(prof::Zone::GsRaster);
        rec_.on_native_gpu_batch(core_.regs(), w.rec.data(), static_cast<u32>(w.rec.size()), w.slots, w.has_tag ? &w.tag : nullptr, w.pal.data(),
                                 static_cast<u32>(w.pal.size()));
        return;
    }
    const u8 fog_reg = static_cast<u8>(core_.regs().fog >> 56);
    const u32 uvx = static_cast<u32>(core_.regs().uv) & 0x3FFFu, uvy = static_cast<u32>(core_.regs().uv >> 16) & 0x3FFFu;
    const u32 n = static_cast<u32>(w.v.size());
    verts_.resize(n);
    for (u32 i = 0; i < n; ++i) {
        const G3OutVertex& o = w.v[i];
        gs::GsVertex& v = verts_[i];
        v.x = static_cast<u32>(o.xyzw[0]) & 0xFFFFu;
        v.y = static_cast<u32>(o.xyzw[1]) & 0xFFFFu;
        v.z = w.fogged ? (static_cast<u32>(o.xyzw[2]) >> 4) & 0xFFFFFFu : static_cast<u32>(o.xyzw[2]);
        v.f = w.fogged ? static_cast<u8>(static_cast<u32>(o.xyzw[3]) >> 4) : fog_reg;
        v.r = static_cast<u8>(o.rgba[0]);
        v.g = static_cast<u8>(o.rgba[1]);
        v.b = static_cast<u8>(o.rgba[2]);
        v.a = static_cast<u8>(o.rgba[3]);
        std::memcpy(&v.s, &o.s, 4);
        std::memcpy(&v.t, &o.t, 4);
        std::memcpy(&v.q, &o.q, 4);
        v.u = uvx;
        v.v = uvy;
    }
    const prof::Scope prof_zone(prof::Zone::GsRaster);
    rec_.on_native_triangles(core_.regs(), verts_.data(), n, w.idx.data(), static_cast<u32>(w.idx.size() / 3), prim_records_,
                             w.has_tag ? &w.tag : nullptr);
}

// Diff / verify modes: the packet the VU1 kicks, compared with the model's batch (tolerances: 2/16 pixel in X/Y, Z
// within 1e-4 relative or 4, colour 2, STQ 1e-4 relative, the ADC bit exact but counted apart -- sliver triangles).
void NativeG3::kick(std::span<const u128> q) {
    if (pending_) compare_packet(q);
    sink_.kick(q);
}

void NativeG3::compare_packet(std::span<const u128> q) {
    ++kicks_;
    const G3Batch& b = batch_;
    bool bad = false;
    u32 adc = 0;
    const u32* t = reinterpret_cast<const u32*>(q.data());
    if (b.culled_all || kicks_ > 1 || q.size() != 1 + 3 * static_cast<std::size_t>(b.n) || std::memcmp(t, b.tag, 16) != 0) {
        bad = true;
    } else {
        const auto rel = [](float a, float c) {
            const double d = std::fabs(double(a) - c), m = std::max(std::fabs(double(a)), std::fabs(double(c)));
            return m == 0 ? 0.0 : d / m;
        };
        for (u32 i = 0; i < b.n && !bad; ++i) {
            const u32* w = t + 4 + i * 12;
            const G3OutVertex& o = b.v[i];
            float fs, ft, fq;
            std::memcpy(&fs, w + 0, 4);
            std::memcpy(&ft, w + 1, 4);
            std::memcpy(&fq, w + 2, 4);
            if (rel(fs, o.s) > 1e-4 || rel(ft, o.t) > 1e-4 || rel(fq, o.q) > 1e-4) bad = true;
            for (int j = 0; j < 4; ++j)
                if (std::abs(static_cast<s32>(w[4 + j]) - o.rgba[j]) > 2) bad = true;
            if (std::abs(static_cast<s32>(w[8]) - o.xyzw[0]) > 2 || std::abs(static_cast<s32>(w[9]) - o.xyzw[1]) > 2) bad = true;
            const double z0 = static_cast<s32>(w[10]), z1 = o.xyzw[2];
            if (std::fabs(z0 - z1) > std::max(4.0, 1e-4 * std::fabs(z0))) bad = true;
            if (((w[11] >> 15) & 1u) != ((static_cast<u32>(o.xyzw[3]) >> 15) & 1u)) ++adc;
        }
        st_.diff_verts += b.n;
    }
    st_.diff_adc += adc;
    if (bad) {
        ++st_.diff_bad;
        if (log_ && logged_ < 40) {
            ++logged_;
            std::fprintf(log_, "native-diff: %s %s n=%u kick %u (%zu qw): tag vu %08X %08X model %08X %08X culled_all %d\n",
                         b.prog == G3Prog::Generic ? "generic" : b.prog == G3Prog::Skin ? "skin" : "skinpar", to_string(b.variant),
                         b.n, kicks_, q.size(), t[0], t[1], b.tag[0], b.tag[1], b.culled_all ? 1 : 0);
        }
    }
}

void NativeG3::diff_close() {
    pending_ = false;
    if (kicks_ == 0 && !batch_.culled_all) {
        ++st_.diff_kick_count;
        ++st_.diff_bad;
        if (log_ && logged_ < 40) {
            ++logged_;
            std::fprintf(log_, "native-diff: %s %s n=%u: the VU kicked nothing\n",
                         batch_.prog == G3Prog::Generic ? "generic" : batch_.prog == G3Prog::Skin ? "skin" : "skinpar",
                         to_string(batch_.variant), batch_.n);
        }
    }
}

// Diff mode: the VU state after the exact run against the state the native path would have left (registers and data
// memory). Differences are expected in what the batch uses as scratch (doc 31 §4.2 lists them); a difference in
// anything a later run reads before writing would show up in verify mode as a packet mismatch.
void NativeG3::after_exact(const gs::VuRunInfo&, vu1::VU1Interpreter& vu) {
    if (fb_open_) {
        fb_open_ = false;
        if (emit_) emit_([this] { rec_.on_native_fallback_end(); });
        else rec_.on_native_fallback_end();
    }
    if (pending_) diff_close();
    if (!pre_valid_) return;
    pre_valid_ = false;
    const vu1::VU1State& e = vu.state();
    const vu1::VU1State& n = *pre_;
    ++st_.st_runs;
    bool any = false;
    for (int r = 1; r < 32; ++r)
        if (std::memcmp(e.vf[r], n.vf[r], 16) != 0) {
            ++st_.st_vf[r];
            any = true;
        }
    for (int r = 1; r < 16; ++r)
        if (e.vi[r] != n.vi[r]) {
            ++st_.st_vi[r];
            any = true;
        }
    if (std::memcmp(e.acc, n.acc, 16) != 0 || e.q != n.q || e.p != n.p || e.i != n.i || e.mac != n.mac || e.status != n.status ||
        e.clip != n.clip || e.tpc != n.tpc) {
        ++st_.st_misc;
        any = true;
    }
    for (int blk = 0; blk < 64; ++blk)
        if (std::memcmp(e.data + blk * 256, n.data + blk * 256, 256) != 0) {
            ++st_.st_data[blk];
            any = true;
        }
    if (any) ++st_.st_runs_diff;
}

} // namespace p3fes::native
