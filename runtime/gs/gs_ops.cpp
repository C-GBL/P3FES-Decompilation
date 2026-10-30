// GsOpRecorder / OpList (runtime/include/p3fes/gs/gs_ops.h): the GS front end's op list for a GPU back end.
#include "p3fes/gs/gs_ops.h"

#include "gs_raster.h"

#include <algorithm>
#include <climits>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <bit>

namespace p3fes::gs {

namespace {

float u2f(u32 v) {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

u32 zmax_of(u32 zpsm) { return zpsm == 0x31 ? 0xFFFFFFu : (zpsm == 0x32 || zpsm == 0x3A) ? 0xFFFFu : 0xFFFFFFFFu; }

GpuDrawCB make_cb(const detail::DrawState& ds) {
    GpuDrawCB c{};
    c.tme = ds.tme;
    c.fge = ds.fge;
    c.abe = ds.abe;
    c.fst = ds.fst;
    c.iip = ds.iip;
    c.sprite = ds.prim == 6;
    c.fbp = ds.fbp;
    c.fbw = ds.fbw;
    c.fpsm = ds.fpsm;
    c.fbmsk = ds.fbmsk;
    c.zbp = ds.zbp;
    c.zpsm = ds.zpsm;
    c.zmsk = ds.zmsk;
    c.ate = ds.ate;
    c.atst = ds.atst;
    c.aref = ds.aref;
    c.afail = ds.afail;
    c.date = ds.date;
    c.datm = ds.datm;
    c.ztst = ds.ztst;
    c.ba = ds.a;
    c.bb = ds.b;
    c.bc = ds.c;
    c.bd = ds.d;
    c.fix = ds.fix;
    c.pabe = ds.pabe;
    c.fba = ds.fba;
    c.colclamp = ds.colclamp;
    c.dthe = ds.dthe;
    c.scanmsk = ds.scanmsk;
    c.fogcol = ds.fogcol;
    c.zmax = zmax_of(ds.zpsm);
    std::memcpy(c.dimx, ds.dimx, sizeof c.dimx);
    if (ds.tme) {
        const detail::TexState& t = ds.tex;
        c.tpsm = t.psm;
        c.tcc = t.tcc;
        c.tfx = t.tfx;
        c.cpsm = t.cpsm;
        c.csa = t.csa;
        c.wms = t.wms;
        c.wmt = t.wmt;
        c.minu = t.minu;
        c.maxu = t.maxu;
        c.minv = t.minv;
        c.maxv = t.maxv;
        c.ta0 = t.ta0;
        c.ta1 = t.ta1;
        c.aem = t.aem;
        c.mmag_linear = t.mmag_linear;
        c.mmin = t.mmin;
        c.mxl = t.mxl;
        c.lcm = t.lcm;
        c.lshift = t.l;
        c.k16 = t.k16;
        for (int i = 0; i < 7; ++i) {
            c.lv[i][0] = t.level[i].tbp;
            c.lv[i][1] = t.level[i].tbw;
            c.lv[i][2] = t.level[i].tw;
            c.lv[i][3] = t.level[i].th;
        }
    }
    return c;
}

bool same_state(const GpuDrawCB& a, const GpuDrawCB& b) {
    return std::memcmp(&a, &b, offsetof(GpuDrawCB, prim_base)) == 0 &&
           std::memcmp(&a.k16, &b.k16, sizeof(GpuDrawCB) - offsetof(GpuDrawCB, k16)) == 0;
}

u32 rgba8(const GsVertex& g) { return g.r | (g.g << 8) | (g.b << 16) | (static_cast<u32>(g.a) << 24); }

// `rgba`: the vertex's own colour (Gouraud) or the kicking vertex's (flat).
inline void vtx(s32 ofx, s32 ofy, const GsVertex& g, u32 rgba, GpuVertex& o) {
    o.x = static_cast<s32>(g.x) - ofx;
    o.y = static_cast<s32>(g.y) - ofy;
    o.z = static_cast<float>(g.z);
    o.rgba = rgba;
    o.s = u2f(g.s);
    o.t = u2f(g.t);
    o.q = u2f(g.q);
    o.uv = g.u | (g.v << 16);
    o.f = g.f;
}

void tri_rec(s32 ofx, s32 ofy, const GsVertex* v, GpuPrimRec& r) {
    // Every field written (no zero fill first: this runs per triangle).
    r.xy2k[2] = r.xy2k[3] = 0;
    r.rgba[3] = r.uv[3] = 0;
    r.s[3] = r.t[3] = r.q[3] = 0.0f;
    r.xy01[0] = static_cast<s32>(v[0].x) - ofx;
    r.xy01[1] = static_cast<s32>(v[0].y) - ofy;
    r.xy01[2] = static_cast<s32>(v[1].x) - ofx;
    r.xy01[3] = static_cast<s32>(v[1].y) - ofy;
    r.xy2k[0] = static_cast<s32>(v[2].x) - ofx;
    r.xy2k[1] = static_cast<s32>(v[2].y) - ofy;
    for (int i = 0; i < 3; ++i) {
        r.rgba[i] = rgba8(v[i]);
        r.zf[i] = v[i].z;
        r.uv[i] = v[i].u | (v[i].v << 16);
        r.s[i] = u2f(v[i].s);
        r.t[i] = u2f(v[i].t);
        r.q[i] = u2f(v[i].q);
    }
    r.zf[3] = v[0].f | (v[1].f << 8) | (static_cast<u32>(v[2].f) << 16);
}

// Two triangles; attributes as gs_raster_ref.cpp's Raster::sprite interpolates them (u/s/q along x, v/t along y;
// colour, Z and fog from the second vertex). `r` is filled when given (exact mode).
bool sprite(s32 ofx, s32 ofy, const GsVertex& v0, const GsVertex& v1, GpuVertex* out, GpuPrimRec* r) {
    s32 x0 = static_cast<s32>(v0.x) - ofx, x1 = static_cast<s32>(v1.x) - ofx;
    s32 y0 = static_cast<s32>(v0.y) - ofy, y1 = static_cast<s32>(v1.y) - ofy;
    u32 iu0 = v0.u, iu1 = v1.u, iv0 = v0.v, iv1 = v1.v;
    float s0 = u2f(v0.s), s1 = u2f(v1.s), t0 = u2f(v0.t), t1 = u2f(v1.t), q0 = u2f(v0.q), q1 = u2f(v1.q);
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(iu0, iu1);
        std::swap(s0, s1);
    }
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(iv0, iv1);
        std::swap(t0, t1);
    }
    if (x0 == x1 || y0 == y1) return false;
    GpuVertex base{};
    base.z = static_cast<float>(v1.z);
    base.rgba = rgba8(v1);
    base.f = v1.f;
    auto corner = [&](bool right, bool bottom) {
        GpuVertex o = base;
        o.x = right ? x1 : x0;
        o.y = bottom ? y1 : y0;
        o.s = right ? s1 : s0;
        o.q = right ? q1 : q0;
        o.t = bottom ? t1 : t0;
        o.uv = (right ? iu1 : iu0) | ((bottom ? iv1 : iv0) << 16);
        return o;
    };
    out[0] = corner(false, false);
    out[1] = corner(true, false);
    out[2] = corner(false, true);
    out[3] = corner(true, false);
    out[4] = corner(true, true);
    out[5] = corner(false, true);
    if (!r) return true;
    *r = GpuPrimRec{};
    r->xy01[0] = x0;
    r->xy01[1] = y0;
    r->xy01[2] = x1;
    r->xy01[3] = y1;
    r->xy2k[2] = 1;
    r->rgba[1] = rgba8(v1);
    r->zf[1] = v1.z;
    r->zf[3] = static_cast<u32>(v1.f) << 8;
    r->uv[0] = iu0 | (iv0 << 16);
    r->uv[1] = iu1 | (iv1 << 16);
    r->s[0] = s0;
    r->s[1] = s1;
    r->t[0] = t0;
    r->t[1] = t1;
    r->q[0] = q0;
    r->q[1] = q1;
    return true;
}

} // namespace

void OpList::clear() {
    ops.clear();
    verts.clear();
    prims.clear();
    cbs.clear();
    cluts.clear();
    words.clear();
    pages.clear();
    nat_in.clear();
    nat_tab.clear();
    nat_slots = 0;
    nat_batches.clear();
    nat_verts.clear();
    nat_src.clear();
    clut_tab.clear();
}

void OpList::append(const OpList& o) {
    const u32 nv = static_cast<u32>(verts.size()), np = static_cast<u32>(prims.size()), nc = static_cast<u32>(cbs.size());
    const u32 ncl = static_cast<u32>(cluts.size()), nw = static_cast<u32>(words.size() / 3);
    const u32 npg = static_cast<u32>(pages.size() / kPageRecordWords);
    const u32 nver = static_cast<u32>(clut_tab.size() / 512);
    for (GpuOp op : o.ops) {
        switch (op.kind) {
        case GpuOpKind::Draw:
            op.first += op.native ? nat_slots * 3u : nv;
            op.prim_base += np;
            op.cb += nc;
            break;
        case GpuOpKind::Scatter: op.first += nw; break;
        case GpuOpKind::Pages: op.first += npg; break;
        case GpuOpKind::Clut: op.cb += ncl; break;
        case GpuOpKind::Copy: break;
        case GpuOpKind::ClutResolve: op.cb += nver; break;
        }
        ops.push_back(op);
    }
    const std::size_t v0 = verts.size();
    verts.insert(verts.end(), o.verts.begin(), o.verts.end());
    if (nc)
        for (std::size_t i = v0; i < verts.size(); ++i) verts[i].cbi += nc;
    clut_tab.insert(clut_tab.end(), o.clut_tab.begin(), o.clut_tab.end());
    prims.insert(prims.end(), o.prims.begin(), o.prims.end());
    for (GpuDrawCB c : o.cbs) {
        c.prim_base += np;
        if (c.clut_ver != kClutLive) c.clut_ver += nver;
        cbs.push_back(c);
    }
    cluts.insert(cluts.end(), o.cluts.begin(), o.cluts.end());
    words.insert(words.end(), o.words.begin(), o.words.end());
    pages.insert(pages.end(), o.pages.begin(), o.pages.end());
    const u32 nin = static_cast<u32>(nat_in.size());
    for (std::size_t i = 0; i + 4 <= o.nat_tab.size(); i += 4) {  // record offsets inside a record are relative
        const u32 te[4] = {o.nat_tab[i] + nat_slots, o.nat_tab[i + 1] + nin, o.nat_tab[i + 2], 0};
        nat_tab.insert(nat_tab.end(), te, te + 4);
    }
    nat_in.insert(nat_in.end(), o.nat_in.begin(), o.nat_in.end());
    if (nc)
        for (std::size_t i = 0; i + 4 <= o.nat_tab.size(); i += 4) nat_in[nin + o.nat_tab[i + 1] + 11] += nc;  // cbi
    nat_slots += o.nat_slots;
    const u32 nnv = static_cast<u32>(nat_verts.size()), nns = static_cast<u32>(nat_src.size());
    for (NativeBatchRec b : o.nat_batches) {
        b.vfirst += nnv;
        b.dfirst += nv;
        b.sfirst += nns;
        nat_batches.push_back(b);
    }
    nat_verts.insert(nat_verts.end(), o.nat_verts.begin(), o.nat_verts.end());
    nat_src.insert(nat_src.end(), o.nat_src.begin(), o.nat_src.end());
}

void GsOpRecorder::note_native_batch(const NativeBatchTag& tag, const GpuVertex* all, u32 nv, const u16* src, u32 dcount,
                                     bool flat) {
    if (!side_table_ || nv == 0 || dcount > l_.verts.size()) return;
    NativeBatchRec b;
    b.key = tag.key;
    std::copy(std::begin(tag.rows), std::end(tag.rows), std::begin(b.rows));
    b.prog = tag.prog;
    b.flat = flat ? 1 : 0;
    b.nv = nv;
    b.vfirst = static_cast<u32>(l_.nat_verts.size());
    b.dfirst = static_cast<u32>(l_.verts.size()) - dcount;
    b.dcount = dcount;
    b.sfirst = static_cast<u32>(l_.nat_src.size());
    l_.nat_verts.insert(l_.nat_verts.end(), all, all + nv);
    l_.nat_src.insert(l_.nat_src.end(), src, src + dcount);
    l_.nat_batches.push_back(b);
}

GsOpRecorder::GsOpRecorder(const GsCore& core, bool split_overlaps, bool prim_records)
    : core_(core), split_(split_overlaps), records_(prim_records), mask_(kVramBytes / 4, 0u), page_bits_(512 * 32, 0ull),
      page_dirty_(512, 0), tiles_(256 * 256, 0u), drawn_gen_(512, 0u), upload_gen_(kVramBytes / 4, 0u) {
    // Diagnostics: P3FES_GS_GPU_CLUT=1 loads every CLUT on the GPU (the pre-2026-10-25 op lists).
    char* e = nullptr;
    std::size_t n = 0;
    if (_dupenv_s(&e, &n, "P3FES_GS_GPU_CLUT") == 0 && e) {
        clut_cpu_ = std::strcmp(e, "1") != 0;
        std::free(e);
    }
}

void GsOpRecorder::finish() {
    close_draw();
    close_writes();
}

void GsOpRecorder::take(OpList& out) {
    finish();
    const std::size_t nat_words = l_.nat_in.size(), nat_tabs = l_.nat_tab.size();
    end_list();
    nat_pal_at_ = ~0ull;  // the stored palette belongs to the list handed out
    ++st_.frames;
    out.clear();
    std::swap(out, l_);
    l_.nat_in.reserve(nat_words + nat_words / 4);  // the next list grows to about the same size: no regrowth copies
    l_.nat_tab.reserve(nat_tabs + nat_tabs / 4);
}

// Decodes the draw state once per GsCore state generation (register writes other than the per-vertex ones).
void GsOpRecorder::refresh_state(const GsRegs& r, u64 gen) {
    gen_ = gen;
    const detail::DrawState ds = detail::decode_draw_state(r);
    kind_ = (ds.prim >= 3 && ds.prim <= 5) ? 1u : ds.prim == 6 ? 2u : 0u;
    iip_ = ds.iip;
    ofx_ = ds.ofx;
    ofy_ = ds.ofy;
    sc_.left = std::max(ds.scax0, 0);
    sc_.top = std::max(ds.scay0, 0);
    sc_.right = std::min(ds.scax1, 2047) + 1;
    sc_.bottom = std::min(ds.scay1, 2047) + 1;
    sc_empty_ = sc_.left >= sc_.right || sc_.top >= sc_.bottom;
    cb_ = make_cb(ds);
    cb_.sc[0] = sc_.left;
    cb_.sc[1] = sc_.top;
    cb_.sc[2] = sc_.right;
    cb_.sc[3] = sc_.bottom;
    cb_.clut_ver = cur_clut_;
    open_match_ = open_ && same_state(cb_, l_.cbs.back());
}

void GsOpRecorder::on_draw(const GsRegs& r, const GsVertex* v, u32 count, u64, u64) {
    ++st_.prims;
    const u64 gen = core_.state_generation();
    if (gen != gen_) [[unlikely]]
        refresh_state(r, gen);
    if (clut_pending_) [[unlikely]]
        capture_clut();
    GpuVertex out[6];
    GpuPrimRec rec;
    int n = 0;
    if (kind_ == 1 && count >= 3) {
        ++st_.tris;
        if (iip_) {
            for (int i = 0; i < 3; ++i) vtx(ofx_, ofy_, v[i], rgba8(v[i]), out[i]);
        } else {
            const u32 c = rgba8(v[2]);
            for (int i = 0; i < 3; ++i) vtx(ofx_, ofy_, v[i], c, out[i]);
        }
        n = 3;
    } else if (kind_ == 2 && count >= 2) {
        ++st_.sprites;
        if (!sprite(ofx_, ofy_, v[0], v[1], out, records_ ? &rec : nullptr)) return;
        n = 6;
    } else {
        ++st_.unsupported;  // points and lines: not used by this game (docs/ANALYSIS/25 section 1)
        if (sync_hook) sync_hook(GpuSyncReason::Unsupported);
        return;
    }
    int minx = out[0].x, maxx = out[0].x, miny = out[0].y, maxy = out[0].y;
    for (int i = 1; i < n; ++i) {
        minx = std::min(minx, out[i].x);
        maxx = std::max(maxx, out[i].x);
        miny = std::min(miny, out[i].y);
        maxy = std::max(maxy, out[i].y);
    }
    if (sc_empty_) return;
    const int bx0 = std::max<int>(sc_.left, (minx >> 4) - 1), by0 = std::max<int>(sc_.top, (miny >> 4) - 1);
    const int bx1 = std::min<int>(sc_.right - 1, (maxx >> 4) + 1), by1 = std::min<int>(sc_.bottom - 1, (maxy >> 4) + 1);
    if (bx0 > bx1 || by0 > by1) return;

    if (!dirty_pages_.empty() || !dirty_.empty()) [[unlikely]]
        close_writes();  // transfers before this primitive go first
    if (!(open_ && open_match_)) {
        if (open_) ++st_.state_breaks;
        close_draw();
        open_draw(cb_, sc_);
        open_match_ = true;
    }
    if (split_) {
        bool hit = false;
        for (int ty = by0 >> 3; ty <= by1 >> 3 && !hit; ++ty)
            for (int tx = bx0 >> 3; tx <= bx1 >> 3; ++tx)
                if (tiles_[static_cast<std::size_t>(ty) * 256 + tx] == tile_gen_) {
                    hit = true;
                    break;
                }
        if (hit) {
            ++st_.overlap_breaks;
            close_draw();
            open_draw(cb_, sc_);
            open_match_ = true;
        }
        for (int ty = by0 >> 3; ty <= by1 >> 3; ++ty)
            for (int tx = bx0 >> 3; tx <= bx1 >> 3; ++tx) tiles_[static_cast<std::size_t>(ty) * 256 + tx] = tile_gen_;
    }
    for (int i = 0; i < n; ++i) out[i].cbi = cur_.cb;
    // The pixel rows the primitive can write (pixel centres at Y = 16 py): from the first row at or below the top
    // vertex to the last row at or above the bottom one (a sprite's bottom edge is exclusive), inside the scissor.
    const int ry0 = std::max<int>(sc_.top, (miny + 15) >> 4);
    const int ry1 = std::min<int>(sc_.bottom - 1, n == 6 ? ((maxy + 15) >> 4) - 1 : (maxy >> 4));
    if (ry0 <= ry1) {
        wy0_ = std::min(wy0_, ry0);
        wy1_ = std::max(wy1_, ry1);
        if (!dbox_) {
            dby0_ = ry0;
            dby1_ = ry1;
            dbox_ = true;
        } else {
            dby0_ = std::min(dby0_, ry0);
            dby1_ = std::max(dby1_, ry1);
        }
    }
    l_.verts.insert(l_.verts.end(), out, out + n);
    if (records_) {
        if (n == 3) tri_rec(ofx_, ofy_, v, rec);
        for (int k = 0; k < n / 3; ++k) l_.prims.push_back(rec);
    }
    cur_.count += static_cast<u32>(n);
}

void GsOpRecorder::on_native_gpu_batch(const GsRegs& r, const u32* words, u32 nwords, u32 slots, const NativeBatchTag*,
                                       const u32* pal, u32 palwords) {
    if (slots == 0) return;
    st_.prims += slots;
    st_.tris += slots;
    if (!nat_cache_ || std::memcmp(&nat_regs_, &r, sizeof(GsRegs)) != 0) {
        const detail::DrawState ds = detail::decode_draw_state(r);
        nat_sc_.left = std::max(ds.scax0, 0);
        nat_sc_.top = std::max(ds.scay0, 0);
        nat_sc_.right = std::min(ds.scax1, 2047) + 1;
        nat_sc_.bottom = std::min(ds.scay1, 2047) + 1;
        nat_cb_ = make_cb(ds);
        nat_ofx_ = ds.ofx;
        nat_ofy_ = ds.ofy;
        std::memcpy(&nat_regs_, &r, sizeof(GsRegs));
        nat_cache_ = true;
    }
    const GpuRect sc = nat_sc_;
    if (sc.left >= sc.right || sc.top >= sc.bottom) return;
    if (clut_pending_) capture_clut();
    if (!dirty_pages_.empty() || !dirty_.empty()) close_writes();
    GpuDrawCB cbv = nat_cb_;
    cbv.sc[0] = sc.left;
    cbv.sc[1] = sc.top;
    cbv.sc[2] = sc.right;
    cbv.sc[3] = sc.bottom;
    cbv.clut_ver = cur_clut_;
    const GpuDrawCB& cb = cbv;
    const bool same = open_ && cur_.native && same_state(cb, l_.cbs.back()) && sc.left == cur_.sc.left &&
                      sc.top == cur_.sc.top && sc.right == cur_.sc.right && sc.bottom == cur_.sc.bottom;
    if (!same) {
        if (open_) ++st_.state_breaks;
        close_draw();
        open_draw(cb, sc);
        cur_.native = 1;
        cur_.first = l_.nat_slots * 3u;
    }
    open_match_ = false;  // on_draw's cached state: never append CPU vertices to a native op
    // The rows the GPU's triangles may write: all of the scissor's (decide_merge, mark_drawn).
    wy0_ = std::min(wy0_, sc.top);
    wy1_ = std::max(wy1_, sc.bottom - 1);
    if (!dbox_) {
        dby0_ = sc.top;
        dby1_ = sc.bottom - 1;
        dbox_ = true;
    } else {
        dby0_ = std::min(dby0_, sc.top);
        dby1_ = std::max(dby1_, sc.bottom - 1);
    }
    const u32 rec = static_cast<u32>(l_.nat_in.size());
    l_.nat_in.insert(l_.nat_in.end(), words, words + nwords);
    u32* h = l_.nat_in.data() + rec;
    h[4] = static_cast<u32>(nat_ofx_);
    h[5] = static_cast<u32>(nat_ofy_);
    h[6] = static_cast<u32>(r.uv & 0x3FFFu) | (static_cast<u32>((r.uv >> 16) & 0x3FFFu) << 16);
    h[7] = static_cast<u32>(r.fog >> 56);
    h[11] = cur_.cb;  // GpuVertex::cbi of the batch's vertices (merged draws)
    if (palwords) {
        u64 at;
        if (nat_pal_at_ != ~0ull && nat_pal_words_ >= palwords && nat_pal_at_ + nat_pal_words_ <= l_.nat_in.size() &&
            std::memcmp(l_.nat_in.data() + nat_pal_at_, pal, palwords * 4u) == 0) {
            at = nat_pal_at_;
        } else {
            at = l_.nat_in.size();
            l_.nat_in.insert(l_.nat_in.end(), pal, pal + palwords);
            nat_pal_at_ = at;
            nat_pal_words_ = palwords;
        }
        l_.nat_in[rec + 10] = static_cast<u32>((static_cast<s64>(at) - static_cast<s64>(rec)) / 4);
    }
    const u32 te[4] = {l_.nat_slots, rec, slots, 0};
    l_.nat_tab.insert(l_.nat_tab.end(), te, te + 4);
    l_.nat_slots += slots;
    cur_.count += slots * 3u;
}

void GsOpRecorder::on_native_fallback_begin(const NativeBatchTag&) {
    ++native_fallbacks_;
    in_native_fallback_ = true;
}

void GsOpRecorder::on_native_fallback_end() { in_native_fallback_ = false; }

void GsOpRecorder::on_native_triangles(const GsRegs& r, const GsVertex* v, u32 nv, const u16* idx, u32 ntri,
                                       bool prim_records, const NativeBatchTag* tag) {
    if (ntri == 0) return;
    st_.prims += ntri;
    st_.tris += ntri;
    if (clut_pending_) capture_clut();
    const detail::DrawState ds = detail::decode_draw_state(r);
    GpuRect sc;
    sc.left = std::max(ds.scax0, 0);
    sc.top = std::max(ds.scay0, 0);
    sc.right = std::min(ds.scax1, 2047) + 1;
    sc.bottom = std::min(ds.scay1, 2047) + 1;
    if (sc.left >= sc.right || sc.top >= sc.bottom) return;
    native_gv_.resize(nv);
    for (u32 i = 0; i < nv; ++i) vtx(ds.ofx, ds.ofy, v[i], rgba8(v[i]), native_gv_[i]);
    GpuDrawCB cb = make_cb(ds);
    cb.sc[0] = sc.left;
    cb.sc[1] = sc.top;
    cb.sc[2] = sc.right;
    cb.sc[3] = sc.bottom;
    cb.clut_ver = cur_clut_;
    bool state_checked = false;
    const bool side = side_table_ && tag != nullptr;  // frame interpolation (docs/ANALYSIS/32): the side record
    if (side) native_src_.clear();
    // GpuPrimRecs exactly when this recorder writes them (exact mode); the native renderer runs in play mode, without.
    const bool records = records_;
    (void)prim_records;
    for (u32 k = 0; k < ntri; ++k) {
        const u16* t = idx + 3 * k;
        GpuVertex out[3] = {native_gv_[t[0]], native_gv_[t[1]], native_gv_[t[2]]};
        if (!ds.iip) out[0].rgba = out[1].rgba = out[2].rgba;  // flat: the kicking vertex's colour
        const int minx = std::min({out[0].x, out[1].x, out[2].x}), maxx = std::max({out[0].x, out[1].x, out[2].x});
        const int miny = std::min({out[0].y, out[1].y, out[2].y}), maxy = std::max({out[0].y, out[1].y, out[2].y});
        const int bx0 = std::max<int>(sc.left, (minx >> 4) - 1), by0 = std::max<int>(sc.top, (miny >> 4) - 1);
        const int bx1 = std::min<int>(sc.right - 1, (maxx >> 4) + 1), by1 = std::min<int>(sc.bottom - 1, (maxy >> 4) + 1);
        if (bx0 > bx1 || by0 > by1) continue;
        if (!state_checked) {
            if (!dirty_pages_.empty() || !dirty_.empty()) close_writes();  // transfers before these primitives go first
            if (!(open_ && !cur_.native && same_state(cb, l_.cbs.back()))) {
                if (open_) ++st_.state_breaks;
                close_draw();
                open_draw(cb, sc);
            }
            open_match_ = open_ && same_state(cb_, l_.cbs.back());  // for on_draw's cached state
            state_checked = true;
        }
        if (split_) {
            bool hit = false;
            for (int ty = by0 >> 3; ty <= by1 >> 3 && !hit; ++ty)
                for (int tx = bx0 >> 3; tx <= bx1 >> 3; ++tx)
                    if (tiles_[static_cast<std::size_t>(ty) * 256 + tx] == tile_gen_) {
                        hit = true;
                        break;
                    }
            if (hit) {
                ++st_.overlap_breaks;
                close_draw();
                open_draw(cb, sc);
            }
            for (int ty = by0 >> 3; ty <= by1 >> 3; ++ty)
                for (int tx = bx0 >> 3; tx <= bx1 >> 3; ++tx) tiles_[static_cast<std::size_t>(ty) * 256 + tx] = tile_gen_;
        }
        for (GpuVertex& o : out) o.cbi = cur_.cb;
        const int ry0 = std::max<int>(sc.top, (miny + 15) >> 4), ry1 = std::min<int>(sc.bottom - 1, maxy >> 4);
        if (ry0 <= ry1) {
            wy0_ = std::min(wy0_, ry0);
            wy1_ = std::max(wy1_, ry1);
            if (!dbox_) {
                dby0_ = ry0;
                dby1_ = ry1;
                dbox_ = true;
            } else {
                dby0_ = std::min(dby0_, ry0);
                dby1_ = std::max(dby1_, ry1);
            }
        }
        l_.verts.insert(l_.verts.end(), out, out + 3);
        if (side) native_src_.insert(native_src_.end(), t, t + 3);
        if (records) {
            const GsVertex tv[3] = {v[t[0]], v[t[1]], v[t[2]]};
            GpuPrimRec rec;
            tri_rec(ds.ofx, ds.ofy, tv, rec);
            l_.prims.push_back(rec);
        }
        cur_.count += 3;
    }
    if (side && !native_src_.empty())
        note_native_batch(*tag, native_gv_.data(), nv, native_src_.data(), static_cast<u32>(native_src_.size()), !ds.iip);
}

void GsOpRecorder::on_clut_load(u64 tex0, u64 texclut) {
    ++st_.clut_loads;
    if (clut_pending_) capture_clut();  // the previous load's result, before GsCore overwrites its CLUT buffer
    mark_drawn();                       // what the open draw may have written so far counts for the source check
    const u32 psm = bits(tex0, 20, 6);
    GpuClutCB c{};
    c.cbp = bits(tex0, 37, 14);
    c.cpsm = bits(tex0, 51, 4);
    c.csm2 = bits(tex0, 55, 1);
    c.csa = bits(tex0, 56, 5);
    c.eight = (psm == 0x13 || psm == 0x1B) ? 1u : 0u;
    c.cbw = bits(texclut, 0, 6);
    c.cou = bits(texclut, 6, 6);
    c.cov = bits(texclut, 12, 10);
    if (clut_cpu_ && clut_clean(c)) {
        // GsCore's CPU result is the GPU's: the slots this load writes (GsCore::load_clut) come from it.
        ++st_.clut_versions;
        auto set = [this](u32 s) { list_slots_[(s >> 6) & 7u] |= 1ull << (s & 63u); };
        const u32 entries = c.eight ? 256u : 16u;
        for (u32 i = 0; i < entries; ++i) {
            if (c.cpsm == 0x0u || c.cpsm == 0x1u) {
                const u32 slot = c.eight ? i : ((c.csa & 15u) * 16u + i) & 255u;
                set(slot);
                set(slot + 256u);
            } else {
                set(c.eight ? i : (c.csa * 16u + i) & 511u);
            }
        }
        clut_pending_ = true;  // captured after GsCore has loaded it (next primitive / load / take)
        return;
    }
    ++st_.clut_gpu_loads;
    close_draw();
    close_writes();
    // A GPU load (from GPU memory, in order with the draws): the GPU CLUT buffer first takes the current version,
    // then this load; later versions of the list inherit from the buffer as it is after this load.
    if (cur_clut_ != kClutLive) {
        GpuOp r;
        r.kind = GpuOpKind::ClutResolve;
        r.cb = cur_clut_;
        l_.ops.push_back(r);
    }
    set_clut_version(kClutLive);
    std::memset(list_slots_, 0, sizeof list_slots_);
    for (auto& r : recent_) r = {0, ~0u};
    GpuOp op;
    op.kind = GpuOpKind::Clut;
    op.cb = static_cast<u32>(l_.cluts.size());
    l_.cluts.push_back(c);
    l_.ops.push_back(op);
}

// The frame (and Z, when written) rows of the open draw's bounding box: pages that may now hold draw output.
void GsOpRecorder::mark_drawn() {
    if (!dbox_) return;
    dbox_ = false;
    if (!open_) return;
    const GpuDrawCB& c = l_.cbs[cur_.cb];
    const u32 seq = ++seq_;
    auto mark = [&](u32 bp, u32 psm) {
        u32 ph;  // page height in pixels (all frame / Z pages are 64 pixels wide)
        switch (psm) {
        case 0x00: case 0x01: case 0x30: case 0x31: ph = 32; break;
        case 0x02: case 0x0A: case 0x32: case 0x3A: ph = 64; break;
        default: ph = 0; break;
        }
        if (ph == 0 || c.fbw == 0) {
            std::fill(drawn_gen_.begin(), drawn_gen_.end(), seq);
            return;
        }
        const u32 p0 = bp / kBlocksPerPage + (static_cast<u32>(dby0_) / ph) * c.fbw;
        const u32 p1 = bp / kBlocksPerPage + (static_cast<u32>(dby1_) / ph + 1u) * c.fbw;
        if (p1 - p0 >= 512u) {
            std::fill(drawn_gen_.begin(), drawn_gen_.end(), seq);
            return;
        }
        for (u32 p = p0; p < p1; ++p) drawn_gen_[p & 511u] = seq;
    };
    mark(c.fbp, c.fpsm);
    if (!c.zmsk) mark(c.zbp, c.zpsm);
}

// True when every source word of the CLUT load holds what the CPU copy holds: its page was never drawn, or (32-bit
// CLUTs) the word was uploaded by a full-word transfer after the page's last draw.
bool GsOpRecorder::clut_clean(const GpuClutCB& c) {
    if (c.cpsm != 0x0u && c.cpsm != 0x1u && c.cpsm != 0x2u && c.cpsm != 0xAu) return false;
    const bool full = c.cpsm <= 1u;
    const u64 key = static_cast<u64>(c.cbp) | (static_cast<u64>(c.cpsm) << 14) | (static_cast<u64>(c.csm2) << 18) |
                    (static_cast<u64>(c.eight) << 19) |
                    (c.csm2 ? (static_cast<u64>(c.cbw) << 20) | (static_cast<u64>(c.cou) << 26) | (static_cast<u64>(c.cov) << 32) : 0ull);
    const std::vector<u32>* words = nullptr;
    for (const ClutWords& e : clut_words_)
        if (e.key == key) {
            words = &e.words;
            break;
        }
    if (!words) {
        if (clut_words_.size() >= 256) clut_words_.clear();
        ClutWords e{key, {}};
        const u32 entries = c.eight ? 256u : 16u;
        for (u32 i = 0; i < entries; ++i) {  // GsCore::load_clut's source pixels
            u32 x, y, bw;
            if (c.csm2) {
                x = c.cou * 16u + i;
                y = c.cov;
                bw = c.cbw;
            } else if (c.eight) {
                const u32 j = (i & ~0x18u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1);
                x = j & 15u;
                y = j >> 4;
                bw = 1;
            } else {
                x = i & 7u;
                y = i >> 3;
                bw = 1;
            }
            const u32 a = full ? GsMemory::addr32(c.cbp, bw, x, y) : GsMemory::addr16(c.cbp, bw, x, y, c.cpsm == 0xAu ? 1u : 0u);
            e.words.push_back((a & kVramMask) >> 2);
        }
        clut_words_.push_back(std::move(e));
        words = &clut_words_.back().words;
    }
    for (u32 w : *words) {
        const u32 g = drawn_gen_[w >> 11];
        if (g != 0 && (!full || upload_gen_[w] <= g)) return false;
    }
    return true;
}

// The CLUT version after the pending CPU-resolved load: this list's slots from GsCore, the rest inherited.
void GsOpRecorder::capture_clut() {
    clut_pending_ = false;
    u32 v[512];
    const std::array<u16, 512>& cl = core_.clut();
    u64 h = 0xCBF29CE484222325ull;
    for (u32 s = 0; s < 512; ++s) {
        v[s] = ((list_slots_[s >> 6] >> (s & 63u)) & 1u) ? cl[s] : kClutInherit;
        h = (h ^ v[s]) * 0x100000001B3ull;
    }
    const u32 nver = static_cast<u32>(l_.clut_tab.size() / 512);
    for (u32 k = 0; k < 8; ++k)  // the same palette as a recent version of this list
        if (recent_[k].hash == h && recent_[k].ver < nver &&
            std::memcmp(&l_.clut_tab[static_cast<std::size_t>(recent_[k].ver) * 512], v, sizeof v) == 0) {
            set_clut_version(recent_[k].ver);
            return;
        }
    l_.clut_tab.insert(l_.clut_tab.end(), v, v + 512);
    recent_[recent_next_++ & 7u] = {h, nver};
    set_clut_version(nver);
}

// The end of a list (take): the GPU CLUT buffer takes the last version; the next list starts from it.
void GsOpRecorder::end_list() {
    if (clut_pending_) capture_clut();
    if (cur_clut_ != kClutLive) {
        GpuOp r;
        r.kind = GpuOpKind::ClutResolve;
        r.cb = cur_clut_;
        l_.ops.push_back(r);
    }
    set_clut_version(kClutLive);
    std::memset(list_slots_, 0, sizeof list_slots_);
    for (auto& r : recent_) r = {0, ~0u};
}

// Marks the 32-bit words (and the bits within them) a transfer stored; their values are read from the core's CPU
// memory when the scatter closes (only transfers and local copies write that memory while rasterisation is off).
void GsOpRecorder::on_transfer_span(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 n) {
    close_draw();  // draws queued before the transfer go first
    if (psm == 0x00 || psm == 0x30) {
        // Full 32-bit words: one bit per word in the page's bitmap; the page goes up as a whole record.
        const u32 seq = ++seq_;
        // GsMemory::addr32 with the row's swizzle row and page row taken once.
        const SwizzleTables& tab = swizzle_tables();
        const u16* row = (psm == 0x30 ? tab.z32 : tab.ct32)[y & 31u].data();
        const u32 prow = ((y & 2047u) >> 5) * bw;
        for (u32 i = 0; i < n; ++i) {
            const u32 xx = (x + i) & 2047u;
            const u32 w = ((((bp + (prow + (xx >> 6)) * kBlocksPerPage) * kBlockBytes + row[xx & 63u]) & kVramMask) >> 2);
            upload_gen_[w] = seq;
            const u32 page = w >> 11;
            if (!page_dirty_[page]) {
                page_dirty_[page] = 1;
                dirty_pages_.push_back(static_cast<u16>(page));
            }
            page_bits_[(w >> 6)] |= 1ull << (w & 63u);
        }
        return;
    }
    if (psm == 0x02 || psm == 0x0A || psm == 0x32 || psm == 0x3A) {
        // 16-bit pixels: GsMemory::addr16 with the row's swizzle row and page row taken once.
        const SwizzleTables& tab = swizzle_tables();
        const auto& t16 = psm == 0x0A ? tab.ct16s : psm == 0x32 ? tab.z16 : psm == 0x3A ? tab.z16s : tab.ct16;
        const u16* row = t16[y & 63u].data();
        const u32 prow = ((y & 2047u) >> 6) * bw;
        for (u32 i = 0; i < n; ++i) {
            const u32 xx = (x + i) & 2047u;
            const u32 addr = ((bp + (prow + (xx >> 6)) * kBlocksPerPage) * kBlockBytes + row[xx & 63u]) & kVramMask;
            const u32 w = addr >> 2;
            if (mask_[w] == 0) dirty_.push_back(w);
            mask_[w] |= 0xFFFFu << ((addr & 2u) * 8u);
        }
        return;
    }
    for (u32 i = 0; i < n; ++i) {
        u32 addr = 0, mask = 0;
        const u32 xi = x + i;
        switch (psm) {
        case 0x01: addr = GsMemory::addr32(bp, bw, xi, y); mask = 0x00FFFFFFu; break;
        case 0x30: addr = GsMemory::addr32(bp, bw, xi, y, true); mask = ~0u; break;
        case 0x31: addr = GsMemory::addr32(bp, bw, xi, y, true); mask = 0x00FFFFFFu; break;
        case 0x02: case 0x0A: case 0x32: case 0x3A: {
            const unsigned layout = psm == 0x0A ? 1 : psm == 0x32 ? 2 : psm == 0x3A ? 3 : 0;
            addr = GsMemory::addr16(bp, bw, xi, y, layout);
            mask = 0xFFFFu << ((addr & 2u) * 8u);
            break;
        }
        case 0x13: addr = GsMemory::addr8(bp, bw, xi, y); mask = 0xFFu << ((addr & 3u) * 8u); break;
        case 0x14: {
            const u32 nib = GsMemory::addr4(bp, bw, xi, y);
            addr = nib >> 1;
            mask = 0xFu << ((addr & 3u) * 8u + (nib & 1u) * 4u);
            break;
        }
        case 0x1B: addr = GsMemory::addr32(bp, bw, xi, y); mask = 0xFF000000u; break;
        case 0x24: addr = GsMemory::addr32(bp, bw, xi, y); mask = 0x0F000000u; break;
        case 0x2C: addr = GsMemory::addr32(bp, bw, xi, y); mask = 0xF0000000u; break;
        default: addr = GsMemory::addr32(bp, bw, xi, y); mask = ~0u; break;
        }
        const u32 w = (addr & kVramMask) >> 2;
        if (mask_[w] == 0) dirty_.push_back(w);
        mask_[w] |= mask;
    }
}

void GsOpRecorder::on_local_copy(u64 b, u64 p, u64 rg) {
    close_draw();
    close_writes();
    ++st_.local_copies;
    std::fill(drawn_gen_.begin(), drawn_gen_.end(), ++seq_);  // the copy's destination may now hold draw output
    GpuOp op;
    op.kind = GpuOpKind::Copy;
    op.b = b;
    op.p = p;
    op.rg = rg;
    l_.ops.push_back(op);
}

void GsOpRecorder::on_local_read(u64, u64, u64) {
    ++st_.local_reads;
    if (sync_hook) sync_hook(GpuSyncReason::LocalRead);
}

void GsOpRecorder::open_draw(const GpuDrawCB& cb, const GpuRect& sc) {
    cur_ = GpuOp{};
    cur_.kind = GpuOpKind::Draw;
    cur_.first = static_cast<u32>(l_.verts.size());
    cur_.prim_base = static_cast<u32>(l_.prims.size());
    cur_.cb = static_cast<u32>(l_.cbs.size());
    cur_.sc = sc;
    GpuDrawCB c = cb;
    c.prim_base = cur_.prim_base;
    c.sc[0] = sc.left;
    c.sc[1] = sc.top;
    c.sc[2] = sc.right;
    c.sc[3] = sc.bottom;
    c.clut_ver = cur_clut_;
    l_.cbs.push_back(c);
    open_ = true;
    wy0_ = INT_MAX;
    wy1_ = INT_MIN;
}

void GsOpRecorder::set_clut_version(u32 v) {
    if (v == cur_clut_) return;
    cur_clut_ = v;
    cb_.clut_ver = v;
    open_match_ = false;  // the following primitives read another CLUT: a new draw state
}

void GsOpRecorder::close_draw() {
    if (++tile_gen_ == 0) {
        std::fill(tiles_.begin(), tiles_.end(), 0u);
        tile_gen_ = 1;
    }
    if (!open_) return;
    mark_drawn();
    open_ = false;
    if (cur_.count == 0) {
        l_.cbs.pop_back();
        return;
    }
    ++st_.draws;
    decide_merge();
    l_.ops.push_back(cur_);
}

void GsOpRecorder::close_writes() {
    if (!dirty_pages_.empty()) {
        GpuOp op;
        op.kind = GpuOpKind::Pages;
        op.first = static_cast<u32>(l_.pages.size() / kPageRecordWords);
        op.count = static_cast<u32>(dirty_pages_.size());
        // Appended without value-initialising the records first (8 KiB per page that would only be overwritten).
        l_.pages.reserve(l_.pages.size() + dirty_pages_.size() * kPageRecordWords);
        for (u16 page : dirty_pages_) {
            u32 head[65];
            head[0] = page;
            u64* bits = &page_bits_[static_cast<std::size_t>(page) * 32u];
            for (u32 k = 0; k < 32; ++k) {
                head[1 + 2 * k] = static_cast<u32>(bits[k]);
                head[2 + 2 * k] = static_cast<u32>(bits[k] >> 32);
                st_.page_words += static_cast<u64>(std::popcount(bits[k]));
                bits[k] = 0;
            }
            const u32* src = reinterpret_cast<const u32*>(core_.mem().data() + static_cast<std::size_t>(page) * kPageBytes);
            l_.pages.insert(l_.pages.end(), head, head + 65);
            l_.pages.insert(l_.pages.end(), src, src + kPageBytes / 4);
            page_dirty_[page] = 0;
        }
        st_.pages += dirty_pages_.size();
        dirty_pages_.clear();
        l_.ops.push_back(op);
    }
    if (dirty_.empty()) return;
    GpuOp op;
    op.kind = GpuOpKind::Scatter;
    op.first = static_cast<u32>(l_.words.size() / 3);
    op.count = static_cast<u32>(dirty_.size());
    l_.words.reserve(l_.words.size() + dirty_.size() * 3);
    for (u32 w : dirty_) {
        l_.words.push_back(w);
        l_.words.push_back(mask_[w]);
        l_.words.push_back(core_.mem().read_u32(w * 4u));
        mask_[w] = 0;
    }
    st_.scatter_words += dirty_.size();
    ++st_.scatters;
    dirty_.clear();
    l_.ops.push_back(op);
}


// ---- Merged draws ----------------------------------------------------------------------------------------------

void GsOpRecorder::PageSet::add(u32 p0, u32 p1) {
    if (p1 <= p0) return;
    if (p1 - p0 >= 512u) {
        for (u64& w : b) w = ~0ull;
        return;
    }
    for (u32 p = p0; p < p1; ++p) b[(p >> 6) & 7u] |= 1ull << (p & 63u);
}

namespace {

// Pixel geometry of a page: width / height in pixels, and how many pages a buffer row of `bw` (64-pixel units)
// spans in GsMemory's addressing.
bool page_geometry(u32 psm, u32 bw, u32& pw, u32& ph, u32& ppr) {
    switch (psm) {
    case 0x00: case 0x01: case 0x1B: case 0x24: case 0x2C: case 0x30: case 0x31: pw = 64; ph = 32; ppr = bw; return true;
    case 0x02: case 0x0A: case 0x32: case 0x3A: pw = 64; ph = 64; ppr = bw; return true;
    case 0x13: pw = 128; ph = 64; ppr = bw >> 1; return true;
    case 0x14: pw = 128; ph = 128; ppr = bw >> 1; return true;
    default: return false;
    }
}

// Pages a w x h pixel rectangle at the origin of buffer {bp (blocks), bw, psm} can touch: [first, last) mod 512.
void rect_pages(u32 bp, u32 bw, u32 psm, u32 w, u32 h, u32& first, u32& last) {
    u32 pw, ph, ppr;
    if (!page_geometry(psm, bw, pw, ph, ppr)) {
        first = 0;
        last = 512;
        return;
    }
    w = std::max(1u, std::min(w, 2048u));
    h = std::max(1u, std::min(h, 2048u));
    first = bp / kBlocksPerPage;
    last = first + ((h - 1u) / ph) * ppr + (w - 1u) / pw + 1u + ((bp % kBlocksPerPage) ? 1u : 0u);
}

} // namespace

// The pages a draw's texture fetches can read (every mip level it may use; region modes widen the extent).
void GsOpRecorder::texture_pages(const GpuDrawCB& c, PageSet& out) {
    if (!c.tme) return;
    const u32 levels = c.mxl ? std::min(c.mxl, 6u) + 1u : 1u;
    for (u32 L = 0; L < levels; ++L) {
        u32 w = 1u << std::min(c.lv[L][2], 11u), h = 1u << std::min(c.lv[L][3], 11u);
        if (c.wms == 2) w = std::max(w, (c.maxu >> L) + 1u);
        if (c.wms == 3) w = 1024;
        if (c.wmt == 2) h = std::max(h, (c.maxv >> L) + 1u);
        if (c.wmt == 3) h = 1024;
        u32 p0, p1;
        rect_pages(c.lv[L][0], c.lv[L][1], c.tpsm, w, h, p0, p1);
        out.add(p0, p1);
    }
}

// The frame (and Z, when written) pages of the open draw's rows.
void GsOpRecorder::target_pages(const GpuDrawCB& c, s32 y0, s32 y1, PageSet& out) {
    auto rows = [&](u32 bp, u32 psm) {
        u32 pw, ph, ppr;
        if (!page_geometry(psm, c.fbw, pw, ph, ppr) || c.fbw == 0) {
            out.add(0, 512);
            return;
        }
        const u32 base = bp / kBlocksPerPage;
        out.add(base + (static_cast<u32>(y0) / ph) * ppr, base + (static_cast<u32>(y1) / ph + 1u) * ppr);
    };
    rows(c.fbp, c.fpsm);
    if (!c.zmsk) rows(c.zbp, c.zpsm);
}

// Called when the open draw closes with primitives: may it share a D3D draw call with the Draw op before it? Inside
// one draw call the ROV orders accesses to the same pixel, which is all the frame / Z traffic when both draws use the
// same frame and Z buffers; a texture fetch reads other pixels' memory, so no draw of the run may fetch from pages
// another draw of the run writes.
void GsOpRecorder::decide_merge() {
    const GpuDrawCB& c = l_.cbs[cur_.cb];
    PageSet w, r;
    target_pages(c, std::max(wy0_, 0), std::max(wy1_, 0), w);
    texture_pages(c, r);
    // (a native op's vertices live in the GPU vertex stage's buffer: it merges only with native ops)
    const bool after_draw = !l_.ops.empty() && l_.ops.back().kind == GpuOpKind::Draw && run_open_ &&
                            l_.ops.back().native == cur_.native;
    bool merge = false;
    if (after_draw && !split_) {
        const GpuDrawCB& p = l_.cbs[l_.ops.back().cb];
        merge = p.fbp == c.fbp && p.fbw == c.fbw && p.fpsm == c.fpsm && p.zbp == c.zbp && p.zpsm == c.zpsm &&
                !r.hits(run_w_) && !w.hits(run_r_) && !r.hits(w);
    }
    if (merge) {
        cur_.merge = 1;
        run_w_.join(w);
        run_r_.join(r);
        ++st_.merged_draws;
    } else {
        cur_.merge = 0;
        run_w_ = w;
        run_r_ = r;
        run_open_ = !r.hits(w);  // a draw that samples what it draws starts no run
    }
}

} // namespace p3fes::gs
