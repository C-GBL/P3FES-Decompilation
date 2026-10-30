// Frame interpolation core (hfr_interp.h; docs/ANALYSIS/32_high_frame_rate.md §3-§4).
#include "hfr_interp.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <unordered_map>

namespace p3fes::hfr {

using gs::GpuVertex;
using gs::NativeBatchRec;
using gs::OpList;

std::vector<BatchView> batch_views(const OpList& l) {
    std::vector<BatchView> v;
    v.reserve(l.nat_batches.size());
    for (const NativeBatchRec& b : l.nat_batches) v.push_back({b.key, b.rows, b.nv});
    return v;
}

namespace {

float len3(const float* t) { return std::sqrt(t[0] * t[0] + t[1] * t[1] + t[2] * t[2]); }
float dist3(const float* a, const float* b) {
    const float d[3] = {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
    return len3(d);
}

// Largest screen move (pixels) of any source vertex of batch `bi` of `nl` against batch `ai` of `pl`.
float max_move_px(const OpList& pl, u32 ai, const OpList& nl, u32 bi) {
    const NativeBatchRec& A = pl.nat_batches[ai];
    const NativeBatchRec& B = nl.nat_batches[bi];
    if (A.nv != B.nv || A.vfirst + A.nv > pl.nat_verts.size() || B.vfirst + B.nv > nl.nat_verts.size())
        return std::numeric_limits<float>::infinity();
    int m = 0;
    for (u32 k = 0; k < B.nv; ++k) {
        const GpuVertex& a = pl.nat_verts[A.vfirst + k];
        const GpuVertex& b = nl.nat_verts[B.vfirst + k];
        m = std::max({m, std::abs(b.x - a.x), std::abs(b.y - a.y)});
    }
    return static_cast<float>(m) / 16.0f;
}

} // namespace

FrameMatch match_frames(std::span<const BatchView> prev, std::span<const BatchView> next, const InterpParams& p,
                        const OpList* prev_list, const OpList* next_list) {
    FrameMatch m;
    m.prev_of.assign(next.size(), -1);
    m.st.batches = static_cast<u32>(next.size());
    std::unordered_map<u64, std::vector<int>> by_key;
    by_key.reserve(prev.size() * 2);
    for (std::size_t j = 0; j < prev.size(); ++j) by_key[prev[j].key].push_back(static_cast<int>(j));
    std::vector<char> claimed(prev.size(), 0);
    const bool screen_test = prev_list && next_list && prev_list->nat_batches.size() == prev.size() &&
                             next_list->nat_batches.size() == next.size();
    for (std::size_t i = 0; i < next.size(); ++i) {
        const BatchView& b = next[i];
        m.st.verts += b.nv;
        const auto it = by_key.find(b.key);
        int best = -1;
        if (it != by_key.end()) {
            float best_d = std::numeric_limits<float>::infinity();
            int candidates = 0;
            for (int j : it->second) {
                if (claimed[j] || prev[j].nv != b.nv) continue;
                ++candidates;
                const float d = (b.rows && prev[j].rows) ? dist3(b.rows + 12, prev[j].rows + 12) : 0.0f;
                if (d < best_d) {
                    best_d = d;
                    best = j;
                }
            }
            // Several instances of the key: the nearest is the same object only if it is near enough.
            if (best >= 0 && it->second.size() > 1 && b.rows && prev[best].rows) {
                const float ref = std::max({len3(b.rows + 12), len3(prev[best].rows + 12), 1e-3f});
                if (best_d > p.instance_rel * ref) best = -1;
            }
            (void)candidates;
        }
        if (best < 0) {
            ++m.st.unmatched;
            continue;
        }
        claimed[best] = 1;
        ++m.st.matched;
        m.st.matched_verts += b.nv;
        bool held = false;
        if (b.rows && prev[best].rows) {
            const float ref = std::max({len3(b.rows + 12), len3(prev[best].rows + 12), 1e-3f});
            if (dist3(b.rows + 12, prev[best].rows + 12) > p.max_jump_rel * ref) held = true;
            else if (turn_angle(prev[best].rows, b.rows) > p.max_turn_rad) held = true;
        }
        if (!held && screen_test && max_move_px(*prev_list, static_cast<u32>(best), *next_list, static_cast<u32>(i)) > p.max_move_px)
            held = true;
        if (held) {
            ++m.st.held;
            m.st.held_verts += b.nv;
            continue;
        }
        m.prev_of[i] = best;
    }
    for (char c : claimed) m.st.vanished += c ? 0u : 1u;
    if (m.st.verts == 0) {
        m.st.cut = true;  // nothing native to blend: the frame is shown as it is
        m.st.cut_reason = MatchStats::CutEmpty;
    } else {
        const double matched_share = static_cast<double>(m.st.matched_verts) / static_cast<double>(m.st.verts);
        const double held_share = m.st.matched_verts ? static_cast<double>(m.st.held_verts) / static_cast<double>(m.st.matched_verts) : 1.0;
        if (matched_share < p.min_matched_share) m.st.cut_reason = MatchStats::CutUnmatched;
        else if (held_share > p.cut_held_share) m.st.cut_reason = MatchStats::CutHeld;
        m.st.cut = m.st.cut_reason != MatchStats::CutNone;
    }
    if (m.st.cut) std::fill(m.prev_of.begin(), m.prev_of.end(), -1);
    return m;
}

bool blend_vertex(const GpuVertex& a, const GpuVertex& b, float alpha, bool colour, GpuVertex& out) {
    out = b;
    const double qa = a.q, qb = b.q;
    if (!(qa > 0.0) || !(qb > 0.0) || !std::isfinite(qa) || !std::isfinite(qb)) return false;
    const double wa = 1.0 / qa, wb = 1.0 / qb, t = alpha;
    const double w = wa + (wb - wa) * t;
    if (!(w > 0.0) || !std::isfinite(w)) return false;
    const double x = ((1.0 - t) * wa * a.x + t * wb * b.x) / w;
    const double y = ((1.0 - t) * wa * a.y + t * wb * b.y) / w;
    if (!(std::fabs(x) < 1e9) || !(std::fabs(y) < 1e9)) return false;
    out.x = static_cast<s32>(std::lround(x));
    out.y = static_cast<s32>(std::lround(y));
    const double qn = 1.0 / w;
    // Z = offset + scale * q for the g3 programs: take it at the blended q (alpha when q hardly changes).
    const double dq = qb - qa;
    const double beta = std::fabs(dq) > 1e-6 * std::max(qa, qb) ? (qn - qa) / dq : t;
    out.z = static_cast<float>(std::max(0.0, a.z + (static_cast<double>(b.z) - a.z) * beta));
    out.s = static_cast<float>(b.s / qb * qn);
    out.t = static_cast<float>(b.t / qb * qn);
    out.q = static_cast<float>(qn);
    if (colour) {
        auto lerp255 = [t](u32 u, u32 v) {
            return static_cast<u32>(std::lround(std::clamp(static_cast<double>(u) + (static_cast<double>(v) - static_cast<double>(u)) * t, 0.0, 255.0)));
        };
        u32 c = 0;
        for (int k = 0; k < 32; k += 8) c |= lerp255((a.rgba >> k) & 0xFFu, (b.rgba >> k) & 0xFFu) << k;
        out.rgba = c;
        out.f = lerp255(a.f & 0xFFu, b.f & 0xFFu);
    }
    return true;
}

BlendStats blend_vertices(const OpList& prev, const OpList& next, const FrameMatch& m, float alpha, const InterpParams& p,
                          std::vector<GpuVertex>& verts) {
    BlendStats st;
    thread_local std::vector<GpuVertex> tmp;
    thread_local std::vector<u32> stamp;
    thread_local u32 gen = 0;
    const std::size_t n = std::min(m.prev_of.size(), next.nat_batches.size());
    for (std::size_t i = 0; i < n; ++i) {
        const int j = m.prev_of[i];
        if (j < 0 || static_cast<std::size_t>(j) >= prev.nat_batches.size()) continue;
        const NativeBatchRec& A = prev.nat_batches[static_cast<std::size_t>(j)];
        const NativeBatchRec& B = next.nat_batches[i];
        if (A.nv != B.nv || A.vfirst + A.nv > prev.nat_verts.size() || B.vfirst + B.nv > next.nat_verts.size() ||
            B.sfirst + B.dcount > next.nat_src.size() || B.dfirst + B.dcount > verts.size())
            continue;
        // Only the source vertices frame N's triangles use (a strip vertex serves up to three of them; vertices of
        // culled triangles only are skipped).
        tmp.resize(B.nv);
        stamp.resize(std::max<std::size_t>(stamp.size(), B.nv), 0u);
        if (++gen == 0) {
            std::fill(stamp.begin(), stamp.end(), 0u);
            gen = 1;
        }
        for (u32 e = 0; e < B.dcount; ++e) {
            const u16 s = next.nat_src[B.sfirst + e];
            if (s >= B.nv) continue;
            if (stamp[s] != gen) {
                stamp[s] = gen;
                if (!blend_vertex(prev.nat_verts[A.vfirst + s], next.nat_verts[B.vfirst + s], alpha, p.blend_colour, tmp[s])) ++st.refused;
            }
            GpuVertex& d = verts[B.dfirst + e];
            const u32 cbi = d.cbi;  // the draw state the recorder gave this primitive (merged draws carry several)
            d = tmp[s];
            d.cbi = cbi;
        }
        if (B.flat) {
            for (u32 e = 0; e + 2 < B.dcount; e += 3) {
                GpuVertex* t = &verts[B.dfirst + e];
                t[0].rgba = t[1].rgba = t[2].rgba;
            }
        }
        ++st.batches;
        st.verts += B.nv;
    }
    return st;
}

// ---- transform blending ---------------------------------------------------------------------------------------

namespace {

void mat3_of(const float m[16], double a[9]) {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c) a[r * 3 + c] = m[r * 4 + c];
}
double det3(const double a[9]) {
    return a[0] * (a[4] * a[8] - a[5] * a[7]) - a[1] * (a[3] * a[8] - a[5] * a[6]) + a[2] * (a[3] * a[7] - a[4] * a[6]);
}
// Inverse transpose; false when singular.
bool inv_t3(const double a[9], double o[9]) {
    const double d = det3(a);
    if (!(std::fabs(d) > 1e-30) || !std::isfinite(d)) return false;
    // cofactor matrix / det = inverse transpose
    o[0] = (a[4] * a[8] - a[5] * a[7]) / d;
    o[1] = -(a[3] * a[8] - a[5] * a[6]) / d;
    o[2] = (a[3] * a[7] - a[4] * a[6]) / d;
    o[3] = -(a[1] * a[8] - a[2] * a[7]) / d;
    o[4] = (a[0] * a[8] - a[2] * a[6]) / d;
    o[5] = -(a[0] * a[7] - a[1] * a[6]) / d;
    o[6] = (a[1] * a[5] - a[2] * a[4]) / d;
    o[7] = -(a[0] * a[5] - a[2] * a[3]) / d;
    o[8] = (a[0] * a[4] - a[1] * a[3]) / d;
    return true;
}

bool polar3d(const float m[16], double r[9], double s[9]) {
    double a[9];
    mat3_of(m, a);
    const double d = det3(a);
    if (!(std::fabs(d) > 1e-30) || !std::isfinite(d)) return false;
    const double sign = d < 0 ? -1.0 : 1.0;
    double x[9];
    for (int i = 0; i < 9; ++i) x[i] = a[i] * sign;
    for (int it = 0; it < 40; ++it) {
        double it3[9];
        if (!inv_t3(x, it3)) return false;
        double diff = 0;
        for (int i = 0; i < 9; ++i) {
            const double nx = 0.5 * (x[i] + it3[i]);
            diff = std::max(diff, std::fabs(nx - x[i]));
            x[i] = nx;
        }
        if (diff < 1e-12) break;
    }
    for (int i = 0; i < 9; ++i) r[i] = x[i];
    // S = R^T * M
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            double v = 0;
            for (int k = 0; k < 3; ++k) v += r[k * 3 + i] * a[k * 3 + j];
            s[i * 3 + j] = v;
        }
    return true;
}

} // namespace

bool polar3(const float m[16], float r[9], float s[9]) {
    double rd[9], sd[9];
    if (!polar3d(m, rd, sd)) return false;
    for (int i = 0; i < 9; ++i) {
        r[i] = static_cast<float>(rd[i]);
        s[i] = static_cast<float>(sd[i]);
    }
    return true;
}

Quat quat_from_rot(const float m[9]) {
    // Shepperd: the largest of w, x, y, z first (m row-major, column-vector convention).
    Quat q;
    const float tr = m[0] + m[4] + m[8];
    if (tr > 0) {
        const float s = std::sqrt(tr + 1.0f) * 2.0f;
        q.w = 0.25f * s;
        q.x = (m[7] - m[5]) / s;
        q.y = (m[2] - m[6]) / s;
        q.z = (m[3] - m[1]) / s;
    } else if (m[0] > m[4] && m[0] > m[8]) {
        const float s = std::sqrt(1.0f + m[0] - m[4] - m[8]) * 2.0f;
        q.w = (m[7] - m[5]) / s;
        q.x = 0.25f * s;
        q.y = (m[1] + m[3]) / s;
        q.z = (m[2] + m[6]) / s;
    } else if (m[4] > m[8]) {
        const float s = std::sqrt(1.0f + m[4] - m[0] - m[8]) * 2.0f;
        q.w = (m[2] - m[6]) / s;
        q.x = (m[1] + m[3]) / s;
        q.y = 0.25f * s;
        q.z = (m[5] + m[7]) / s;
    } else {
        const float s = std::sqrt(1.0f + m[8] - m[0] - m[4]) * 2.0f;
        q.w = (m[3] - m[1]) / s;
        q.x = (m[2] + m[6]) / s;
        q.y = (m[5] + m[7]) / s;
        q.z = 0.25f * s;
    }
    const float n = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    if (n > 0) {
        q.w /= n;
        q.x /= n;
        q.y /= n;
        q.z /= n;
    }
    return q;
}

void rot_from_quat(const Quat& q, float m[9]) {
    const float w = q.w, x = q.x, y = q.y, z = q.z;
    m[0] = 1 - 2 * (y * y + z * z);
    m[1] = 2 * (x * y - w * z);
    m[2] = 2 * (x * z + w * y);
    m[3] = 2 * (x * y + w * z);
    m[4] = 1 - 2 * (x * x + z * z);
    m[5] = 2 * (y * z - w * x);
    m[6] = 2 * (x * z - w * y);
    m[7] = 2 * (y * z + w * x);
    m[8] = 1 - 2 * (x * x + y * y);
}

Quat slerp(Quat a, Quat b, float t) {
    float d = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    if (d < 0) {  // the shorter way round
        b = {-b.w, -b.x, -b.y, -b.z};
        d = -d;
    }
    float ka, kb;
    if (d > 0.9995f) {  // nearly parallel: nlerp
        ka = 1 - t;
        kb = t;
    } else {
        const float th = std::acos(std::min(d, 1.0f));
        const float s = std::sin(th);
        ka = std::sin((1 - t) * th) / s;
        kb = std::sin(t * th) / s;
    }
    Quat q{ka * a.w + kb * b.w, ka * a.x + kb * b.x, ka * a.y + kb * b.y, ka * a.z + kb * b.z};
    const float n = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    if (n > 0) q = {q.w / n, q.x / n, q.y / n, q.z / n};
    return q;
}

float turn_angle(const float a[16], const float b[16]) {
    float ra[9], sa[9], rb[9], sb[9];
    if (!polar3(a, ra, sa) || !polar3(b, rb, sb)) return 1e9f;
    const Quat qa = quat_from_rot(ra), qb = quat_from_rot(rb);
    const float d = std::fabs(qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z);
    return 2.0f * std::acos(std::min(d, 1.0f));
}

void blend_affine(const float a[16], const float b[16], float t, float out[16]) {
    float ra[9], sa[9], rb[9], sb[9];
    if (!polar3(a, ra, sa) || !polar3(b, rb, sb)) {
        for (int i = 0; i < 16; ++i) out[i] = a[i] + (b[i] - a[i]) * t;
        return;
    }
    float r[9], s[9];
    rot_from_quat(slerp(quat_from_rot(ra), quat_from_rot(rb), t), r);
    for (int i = 0; i < 9; ++i) s[i] = sa[i] + (sb[i] - sa[i]) * t;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            float v = 0;
            for (int k = 0; k < 3; ++k) v += r[i * 3 + k] * s[k * 3 + j];
            out[i * 4 + j] = v;
        }
    for (int i = 0; i < 4; ++i) out[i * 4 + 3] = a[i * 4 + 3] + (b[i * 4 + 3] - a[i * 4 + 3]) * t;  // w column
    for (int j = 0; j < 3; ++j) out[12 + j] = a[12 + j] + (b[12 + j] - a[12 + j]) * t;           // translation
}

double quantise_alpha(double alpha, unsigned k) {
    if (k == 0) return alpha;
    if (!(alpha > 0.0)) return 0.0;
    // Ticks sit between two steps (the pacer keeps them half a refresh away from due times): round up, so the
    // tick just before a frame's due time shows that frame exactly.
    return std::ceil(alpha * k - 1e-3) / static_cast<double>(k);
}

} // namespace p3fes::hfr
