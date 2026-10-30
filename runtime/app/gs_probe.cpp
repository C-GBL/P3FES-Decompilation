// Opt-in GS diagnostics (gs_probe.h). Nothing here writes guest memory, guest registers or GS state.
#include "gs_probe.h"

#include <algorithm>
#include <cstdio>
#include <map>

namespace p3fes::app {

namespace {

using gs::bits;

const char* psm_short(u32 psm) {
    switch (psm) {
    case 0x00: return "CT32";
    case 0x01: return "CT24";
    case 0x02: return "CT16";
    case 0x0A: return "CT16S";
    case 0x13: return "T8";
    case 0x14: return "T4";
    case 0x1B: return "T8H";
    case 0x24: return "T4HL";
    case 0x2C: return "T4HH";
    case 0x30: return "Z32";
    case 0x31: return "Z24";
    case 0x32: return "Z16";
    case 0x3A: return "Z16S";
    default: return "PSM?";
    }
}

// Page geometry of a format: page width/height in pixels and whether the buffer width counts in 128-pixel pages.
void page_geom(u32 psm, int& pw, int& ph, bool& half_bw) {
    switch (gs::psm_bits(psm)) {
    case 16: pw = 64; ph = 64; half_bw = false; break;
    case 8: pw = 128; ph = 64; half_bw = true; break;
    case 4: pw = 128; ph = 128; half_bw = true; break;
    default:  // 32/24 and the 8H/4HL/4HH formats that live in 32-bit words
        pw = 64; ph = 32; half_bw = false; break;
    }
}

std::string fmtv(const char* f, unsigned long long a = 0, unsigned long long b = 0, unsigned long long c = 0,
                 unsigned long long d = 0, unsigned long long e = 0, unsigned long long g = 0) {
    char buf[256];
    std::snprintf(buf, sizeof buf, f, a, b, c, d, e, g);
    return buf;
}

const char* kPrim[8] = {"point", "line", "linestrip", "triangle", "tristrip", "trifan", "sprite", "prohibited"};
const char* kAtst[8] = {"NEVER", "ALWAYS", "LESS", "LEQUAL", "EQUAL", "GEQUAL", "GREATER", "NOTEQUAL"};
const char* kAfail[4] = {"KEEP", "FB_ONLY", "ZB_ONLY", "RGB_ONLY"};
const char* kZtst[4] = {"NEVER", "ALWAYS", "GEQUAL", "GREATER"};
const char* kTfx[4] = {"MODULATE", "DECAL", "HIGHLIGHT", "HIGHLIGHT2"};
const char* kWrap[4] = {"REPEAT", "CLAMP", "REGION_CLAMP", "REGION_REPEAT"};
const char* kMin[8] = {"NEAREST", "LINEAR", "NEAREST_MIPMAP_NEAREST", "NEAREST_MIPMAP_LINEAR", "LINEAR_MIPMAP_NEAREST",
                       "LINEAR_MIPMAP_LINEAR", "min6?", "min7?"};
const char* kAbcd[4] = {"Cs", "Cd", "0", "res"};
const char* kC[4] = {"As", "Ad", "FIX", "res"};

} // namespace

GsProbe::GsProbe(const GsProbeConfig& cfg, gs::GsSystem& gs, const hle::Timebase& time)
    : cfg_(cfg), gs_(gs), time_(time) {
    std::sort(cfg_.marks.begin(), cfg_.marks.end());
    cfg_.marks.erase(std::unique(cfg_.marks.begin(), cfg_.marks.end()), cfg_.marks.end());
    if (cfg_.marks.empty() || cfg_.marks.front() != 0) cfg_.marks.insert(cfg_.marks.begin(), 0);
    if (!cfg_.record.empty() && cfg_.record_at.empty()) cfg_.record_at.push_back(0);
    std::sort(cfg_.record_at.begin(), cfg_.record_at.end());
    segs_.resize(cfg_.marks.size());
    for (std::size_t i = 0; i < segs_.size(); ++i) {
        segs_[i].from_vblank = cfg_.marks[i];
        segs_[i].to_vblank = i + 1 < cfg_.marks.size() ? cfg_.marks[i + 1] : ~0ull;
    }
}

GsProbe::~GsProbe() { finish(); }

GsProbe::Counters GsProbe::counters() const {
    Counters c;
    c.core = gs_.core().stats();
    c.gif = gs_.gif().stats();
    c.priv = gs_.priv().stats();
    return c;
}

std::size_t GsProbe::segment_index(std::uint64_t vb) const {
    std::size_t i = 0;
    while (i + 1 < cfg_.marks.size() && vb >= cfg_.marks[i + 1]) ++i;
    return i;
}

void GsProbe::roll_segment() {
    const std::size_t want = segment_index(time_.vblanks);
    if (want == cur_) return;
    const auto now = std::chrono::steady_clock::now();
    const Counters c = counters();
    if (cur_ != SIZE_MAX) {
        Segment& s = segs_[cur_];
        s.wall_s = std::chrono::duration<double>(now - seg_t0_).count();
        s.at_close = c;
    }
    cur_ = want;
    seg_t0_ = now;
    segs_[cur_].at_open = c;
}

void GsProbe::mark_pages(std::uint32_t bp, std::uint32_t bw, std::uint32_t psm, int x0, int y0, int x1, int y1,
                         std::uint64_t serial, bool upload) {
    int pw, ph;
    bool half;
    page_geom(psm, pw, ph, half);
    const int bwp = std::max(1, static_cast<int>(half ? bw / 2 : bw));
    x0 = std::max(x0, 0);
    y0 = std::max(y0, 0);
    if (x1 < x0 || y1 < y0) return;
    for (int py = y0 / ph; py <= y1 / ph; ++py)
        for (int px = x0 / pw; px <= std::min(x1 / pw, bwp - 1); ++px) {
            const u32 page = ((bp + static_cast<u32>(py * bwp + px) * 32u) / 32u) & 511u;
            (upload ? page_upload_ : page_draw_)[page] = serial;
        }
}

bool GsProbe::any_rendered(std::uint32_t bp, std::uint32_t bw, std::uint32_t psm, int x0, int y0, int x1, int y1,
                           int* area) const {
    int pw, ph;
    bool half;
    page_geom(psm, pw, ph, half);
    const int bwp = std::max(1, static_cast<int>(half ? bw / 2 : bw));
    x0 = std::max(x0, 0);
    y0 = std::max(y0, 0);
    bool hit = false;
    for (int py = y0 / ph; py <= y1 / ph && !hit; ++py)
        for (int px = x0 / pw; px <= std::min(x1 / pw, bwp - 1); ++px) {
            const u32 page = ((bp + static_cast<u32>(py * bwp + px) * 32u) / 32u) & 511u;
            if (page_draw_[page] > page_upload_[page]) {
                hit = true;
                if (area) *area = page < 140 ? 1 : page < 280 ? 0 : page < 350 ? 2 : 3;
                break;
            }
        }
    return hit;
}

void GsProbe::on_draw(const gs::GsRegs& r, const gs::GsVertex* v, u32 count, u64 pixels, u64 ns) {
    if (cfg_.census.empty()) return;
    roll_segment();
    Segment& s = segs_[cur_];
    ++serial_;
    const u64 attr = (r.prmodecont & 1u) ? r.prim : r.prmode;
    const u32 prim = static_cast<u32>(r.prim) & 7u;
    const u32 ctxt = static_cast<u32>((attr >> 9) & 1u);
    const gs::GsContextRegs& c = r.ctx[ctxt];
    const bool tme = (attr >> 4) & 1u, abe = (attr >> 6) & 1u, fge = (attr >> 5) & 1u;
    const u32 fbp = bits(c.frame, 0, 9), fbw = bits(c.frame, 16, 6), fpsm = bits(c.frame, 24, 6);
    const u32 fbmsk = bits(c.frame, 32, 32);
    const u32 zbp = bits(c.zbuf, 0, 9), zpsm = 0x30u | bits(c.zbuf, 24, 4), zmsk = bits(c.zbuf, 32, 1);
    const u32 fbmsk_class = fbmsk == 0 ? 0u : fbmsk == 0xFF000000u ? 1u : fbmsk == 0xFFFFFFFFu ? 2u : 3u;
    const u32 test = static_cast<u32>(c.test) & 0x7FFFFu;
    const bool ate = test & 1u, zte = (test >> 16) & 1u;
    const u32 ztst = zte ? bits(test, 17, 2) : 1u;

    Key k;
    k.k[0] = (attr & 0x3F8u) | prim | (static_cast<u64>(fpsm) << 10) | (static_cast<u64>(fbp) << 16) |
             (static_cast<u64>(fbw) << 25) | (static_cast<u64>(zpsm & 0xFu) << 31) | (static_cast<u64>(zbp) << 35) |
             (static_cast<u64>(zmsk) << 44) | (static_cast<u64>(fbmsk_class) << 45) | ((r.scanmsk & 3ull) << 47) |
             ((r.colclamp & 1ull) << 49) | ((r.dthe & 1ull) << 50) | ((r.pabe & 1ull) << 51) | ((c.fba & 1ull) << 52);
    u64 t = ate ? test : (test & ~0x3FFFu & 0x7FFFFu) | (test & 0xC000u);  // drop ATST/AREF/AFAIL when ATE = 0
    if (!zte) t &= ~(3ull << 17);
    k.k[1] = t | (abe ? ((c.alpha & 0xFFull) << 19) | (((c.alpha >> 32) & 0xFFull) << 27) : 0ull);
    if (tme) {
        const u64 t0 = c.tex0, t1 = c.tex1, cl = c.clamp;
        const u32 psm = bits(t0, 20, 6);
        const bool idx = psm == 0x13 || psm == 0x14 || psm == 0x1B || psm == 0x24 || psm == 0x2C;
        k.k[2] = psm | (idx ? (static_cast<u64>(bits(t0, 51, 4)) << 6) | (static_cast<u64>(bits(t0, 55, 1)) << 10) |
                                  (static_cast<u64>(bits(t0, 56, 5)) << 11) | (static_cast<u64>(bits(t0, 61, 3)) << 45)
                            : 0ull) |
                 (static_cast<u64>(bits(t0, 35, 2)) << 16) | (static_cast<u64>(bits(t0, 34, 1)) << 18) |
                 (static_cast<u64>(bits(t0, 26, 4)) << 19) | (static_cast<u64>(bits(t0, 30, 4)) << 23) |
                 (static_cast<u64>(bits(t0, 14, 6)) << 27) | (static_cast<u64>(cl & 15u) << 33) |
                 (static_cast<u64>(t1 & 1u) << 37) | (static_cast<u64>(bits(t1, 2, 3)) << 38) |
                 (static_cast<u64>(bits(t1, 5, 1)) << 41) | (static_cast<u64>(bits(t1, 6, 3)) << 42) |
                 ((r.texa & 0xFFull) << 48) | (((r.texa >> 15) & 1ull) << 56) | (((r.texa >> 32) >= 0x80 ? 1ull : 0ull) << 57) |
                 (static_cast<u64>((attr >> 8) & 1u) << 58);
    }
    const bool std_off = bits(c.xyoffset, 0, 16) == 0x6C00u && bits(c.xyoffset, 32, 16) == 0x7200u;
    k.k[3] = (c.scissor & 0x7FFull) | (((c.scissor >> 16) & 0x7FFull) << 11) | (((c.scissor >> 32) & 0x7FFull) << 22) |
             (((c.scissor >> 48) & 0x7FFull) << 33) | (static_cast<u64>(std_off ? 0 : 1) << 44) |
             (static_cast<u64>(fge ? 1 : 0) << 45);
    Agg& a = s.keys[k];
    ++a.prims;
    a.pixels += pixels;
    a.ns += ns;
    ++s.prims;
    s.pixels += pixels;
    s.raster_ns += ns;
    if (fbp != 0 && fbp != 140) {
        ++s.offscreen_draws;
        s.offscreen_pixels += pixels;
    }

    // Screen bounding box of the primitive (pixels), clipped to the scissor.
    const int ofx = static_cast<int>(bits(c.xyoffset, 0, 16)), ofy = static_cast<int>(bits(c.xyoffset, 32, 16));
    int x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    for (u32 i = 0; i < count; ++i) {
        const int x = (static_cast<int>(v[i].x) - ofx) >> 4, y = (static_cast<int>(v[i].y) - ofy) >> 4;
        x0 = std::min(x0, x); y0 = std::min(y0, y); x1 = std::max(x1, x + 1); y1 = std::max(y1, y + 1);
    }
    x0 = std::max(x0, static_cast<int>(bits(c.scissor, 0, 11)));
    x1 = std::min(x1, static_cast<int>(bits(c.scissor, 16, 11)));
    y0 = std::max(y0, static_cast<int>(bits(c.scissor, 32, 11)));
    y1 = std::min(y1, static_cast<int>(bits(c.scissor, 48, 11)));

    if (tme) {
        const u64 t0 = c.tex0;
        const u32 tbp = bits(t0, 0, 14), tbw = bits(t0, 14, 6), psm = bits(t0, 20, 6);
        const int tw = 1 << std::min(bits(t0, 26, 4), 10u), th = 1 << std::min(bits(t0, 30, 4), 10u);
        int area = 3;
        if (any_rendered(tbp, tbw, psm, 0, 0, tw - 1, th - 1, &area)) {
            ++s.tex_draws_rendered_src;
            s.tex_pixels_rendered_src += pixels;
            ++s.rendered_src_by_area[area];
        }
        // Texture overlapping the frame buffer being drawn (block ranges of the two footprints intersect).
        const u32 fb0 = fbp * 32u, fb1 = fb0 + 140u * 32u;
        if (tbp >= fb0 && tbp < fb1) ++s.tex_draws_self_feedback;
    }
    if (x0 <= x1 && y0 <= y1 && pixels) {
        if (fbmsk != 0xFFFFFFFFu) mark_pages(fbp * 32u, fbw, fpsm, x0, y0, x1, y1, serial_, false);
        if (!zmsk && ztst != 0) mark_pages(zbp * 32u, fbw, zpsm, x0, y0, x1, y1, serial_, false);
    }
}

void GsProbe::on_clut_load(u64 tex0, u64 /*texclut*/) {
    if (cfg_.census.empty()) return;
    roll_segment();
    Segment& s = segs_[cur_];
    ++s.clut_loads;
    const u32 cbp = bits(tex0, 37, 14), cpsm = bits(tex0, 51, 4);
    if (any_rendered(cbp, 1, cpsm, 0, 0, 15, 15)) ++s.clut_loads_rendered;
}

void GsProbe::on_transfer_span(u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 n) {
    if (cfg_.census.empty() || n == 0) return;
    if (cur_ == SIZE_MAX) roll_segment();
    Segment& s = segs_[cur_];
    s.upload_pixels_by_psm[psm & 63u] += n;
    const u64 trxpos = gs_.core().regs().trxpos;
    if (x == bits(trxpos, 32, 11) && y == bits(trxpos, 48, 11)) xfer_over_rendered_counted_ = false;  // first pixel
    const int xi = static_cast<int>(x), yi = static_cast<int>(y), xe = xi + static_cast<int>(n) - 1;
    if (any_rendered(bp, bw, psm, xi, yi, xe, yi)) {
        s.upload_pixels_over_rendered += n;  // page granular
        if (!xfer_over_rendered_counted_) {
            ++s.uploads_over_rendered;
            xfer_over_rendered_counted_ = true;
        }
    }
    mark_pages(bp, bw, psm, xi, yi, xe, yi, ++serial_, true);
}

void GsProbe::on_local_copy(u64 b, u64 p, u64 rg) {
    if (cfg_.census.empty()) return;
    roll_segment();
    Segment& s = segs_[cur_];
    ++s.local_copies;
    const u32 sbp = bits(b, 0, 14), sbw = bits(b, 16, 6), spsm = bits(b, 24, 6);
    const int sx = static_cast<int>(bits(p, 0, 11)), sy = static_cast<int>(bits(p, 16, 11));
    const int w = static_cast<int>(bits(rg, 0, 12)), h = static_cast<int>(bits(rg, 32, 12));
    const bool rendered = any_rendered(sbp, sbw, spsm, sx, sy, sx + w - 1, sy + h - 1);
    if (rendered) ++s.local_copies_rendered_src;
    if (s.events.size() < 24)
        s.events.push_back(fmtv("vblank %llu local->local %llux%llu ", time_.vblanks, static_cast<unsigned long long>(w),
                                static_cast<unsigned long long>(h)) +
                           psm_short(spsm) + fmtv(" from bp %llu to bp %llu", sbp, bits(b, 32, 14)) +
                           (rendered ? " (source holds draw output)" : ""));
    // The destination now holds a copy; treat it as rendered when the source was.
    if (rendered)
        mark_pages(bits(b, 32, 14), bits(b, 48, 6), bits(b, 56, 6), static_cast<int>(bits(p, 32, 11)),
                   static_cast<int>(bits(p, 48, 11)), static_cast<int>(bits(p, 32, 11)) + w - 1,
                   static_cast<int>(bits(p, 48, 11)) + h - 1, ++serial_, false);
}

void GsProbe::on_local_read(u64 b, u64 p, u64 rg) {
    if (cfg_.census.empty()) return;
    roll_segment();
    Segment& s = segs_[cur_];
    ++s.local_reads;
    const u32 sbp = bits(b, 0, 14), sbw = bits(b, 16, 6), spsm = bits(b, 24, 6);
    const int sx = static_cast<int>(bits(p, 0, 11)), sy = static_cast<int>(bits(p, 16, 11));
    const int w = static_cast<int>(bits(rg, 0, 12)), h = static_cast<int>(bits(rg, 32, 12));
    s.local_read_pixels += static_cast<u64>(w) * static_cast<u64>(h);
    const bool rendered = any_rendered(sbp, sbw, spsm, sx, sy, sx + w - 1, sy + h - 1);
    if (rendered) ++s.local_reads_rendered;
    if (s.events.size() < 24)
        s.events.push_back(fmtv("vblank %llu local->host %llux%llu ", time_.vblanks, static_cast<unsigned long long>(w),
                                static_cast<unsigned long long>(h)) +
                           psm_short(spsm) + fmtv(" bp %llu bw %llu at (%llu,%llu)", sbp, sbw, static_cast<unsigned long long>(sx),
                                                  static_cast<unsigned long long>(sy)) +
                           (rendered ? " (holds draw output)" : ""));
}

std::filesystem::path GsProbe::record_path(std::size_t i) const {
    if (cfg_.record_at.size() <= 1) return cfg_.record;
    std::filesystem::path p = cfg_.record;
    const std::string stem = p.stem().string() + "_v" + std::to_string(cfg_.record_at[i]);
    return p.replace_filename(stem + p.extension().string());
}

void GsProbe::on_flip(const gs::FlipEvent& e) {
    if (cfg_.record.empty() || rec_next_ >= cfg_.record_at.size()) return;
    if (!rec_.recording()) {
        if (e.vblank >= cfg_.record_at[rec_next_]) {
            rec_.begin(gs_.core(), e.vblank, e.count);
            std::printf("p3fes: gs-record: started at flip %llu (vblank %llu)\n", static_cast<unsigned long long>(e.count),
                        static_cast<unsigned long long>(e.vblank));
        }
        return;
    }
    rec_.end(gs_.core(), gs_.priv().display(), e.vblank, e.count);
    const std::filesystem::path path = record_path(rec_next_++);
    std::string err;
    if (rec_.write(path, err))
        std::printf("p3fes: gs-record: flip %llu (vblank %llu): %zu event bytes -> %s\n", static_cast<unsigned long long>(e.count),
                    static_cast<unsigned long long>(e.vblank), rec_.event_bytes(), path.string().c_str());
    else
        std::fprintf(stderr, "p3fes: gs-record: %s\n", err.c_str());
    // The next recording point may already be due: it starts at this flip.
    if (rec_next_ < cfg_.record_at.size() && e.vblank >= cfg_.record_at[rec_next_]) rec_.begin(gs_.core(), e.vblank, e.count);
}

void GsProbe::finish() {
    if (finished_) return;
    finished_ = true;
    if (rec_.recording()) {
        rec_.end(gs_.core(), gs_.priv().display(), time_.vblanks, gs_.priv().flip_count());
        std::string err;
        if (!rec_.write(record_path(rec_next_), err)) std::fprintf(stderr, "p3fes: gs-record: %s\n", err.c_str());
    }
    if (cfg_.census.empty()) return;
    if (cur_ != SIZE_MAX) {
        Segment& s = segs_[cur_];
        s.wall_s = std::chrono::duration<double>(std::chrono::steady_clock::now() - seg_t0_).count();
        s.at_close = counters();
        s.to_vblank = time_.vblanks;
    }
    write_census();
}

void GsProbe::write_census() const {
    FILE* f = std::fopen(cfg_.census.string().c_str(), "w");
    if (!f) {
        std::fprintf(stderr, "p3fes: gs-census: cannot create %s\n", cfg_.census.string().c_str());
        return;
    }
    std::fprintf(f, "# p3fes --gs-census: per-draw GS feature census (docs/ANALYSIS/25_d3d11_gs_backend.md)\n"
                    "# columns: prims  pixels(written)  raster_ms  value\n");
    for (std::size_t si = 0; si < segs_.size(); ++si) {
        const Segment& s = segs_[si];
        if (s.at_close.core.reg_writes == 0 && s.keys.empty()) continue;
        std::fprintf(f, "\n=== segment %zu: vblank %llu .. %llu ===\n", si, static_cast<unsigned long long>(s.from_vblank),
                     static_cast<unsigned long long>(s.to_vblank));
        const double vbs = static_cast<double>(std::min<std::uint64_t>(s.to_vblank, time_.vblanks) - s.from_vblank);
        std::fprintf(f, "wall_s %.3f  speed %.3fx  raster_s %.3f (%.1f%% of wall)  prims %llu  pixels %llu  distinct_states %zu\n",
                     s.wall_s, s.wall_s > 0 ? vbs / 59.94 / s.wall_s : 0.0, static_cast<double>(s.raster_ns) * 1e-9,
                     s.wall_s > 0 ? 100.0 * static_cast<double>(s.raster_ns) * 1e-9 / s.wall_s : 0.0,
                     static_cast<unsigned long long>(s.prims), static_cast<unsigned long long>(s.pixels), s.keys.size());
        const auto& a = s.at_open;
        const auto& b = s.at_close;
        std::fprintf(f, "core: image_qwords_in %llu  image_qwords_out(local->host) %llu  local_copies %llu  clut_loads %llu  "
                        "unknown_reg_writes %llu  invalid_psm %llu\n",
                     static_cast<unsigned long long>(b.core.image_qwords_in - a.core.image_qwords_in),
                     static_cast<unsigned long long>(b.core.image_qwords_out - a.core.image_qwords_out),
                     static_cast<unsigned long long>(b.core.local_copies - a.core.local_copies),
                     static_cast<unsigned long long>(b.core.clut_loads - a.core.clut_loads),
                     static_cast<unsigned long long>(b.core.unknown_reg_writes - a.core.unknown_reg_writes),
                     static_cast<unsigned long long>(b.core.invalid_psm - a.core.invalid_psm));
        static const char* kFlg[4] = {"packed", "reglist", "image", "disabled"};
        std::fprintf(f, "gif:");
        for (int p = 1; p <= 3; ++p) {
            std::fprintf(f, "  path%d qwords %llu", p, static_cast<unsigned long long>(b.gif.qwords[p] - a.gif.qwords[p]));
            for (int g = 0; g < 4; ++g)
                if (b.gif.tags[p][g] != a.gif.tags[p][g])
                    std::fprintf(f, " %s %llu", kFlg[g], static_cast<unsigned long long>(b.gif.tags[p][g] - a.gif.tags[p][g]));
        }
        std::fprintf(f, "\npriv: signals %llu  finishes %llu  labels %llu  dispfb_writes %llu  resets %llu  EE reads:",
                     static_cast<unsigned long long>(b.priv.signals - a.priv.signals),
                     static_cast<unsigned long long>(b.priv.finishes - a.priv.finishes),
                     static_cast<unsigned long long>(b.priv.labels - a.priv.labels),
                     static_cast<unsigned long long>(b.priv.dispfb_writes - a.priv.dispfb_writes),
                     static_cast<unsigned long long>(b.priv.resets - a.priv.resets));
        static const char* kPriv[32] = {"PMODE", "SMODE1", "SMODE2", "SRFSH", "SYNCH1", "SYNCH2", "SYNCV", "DISPFB1",
                                        "DISPLAY1", "DISPFB2", "DISPLAY2", "EXTBUF", "EXTDATA", "EXTWRITE", "BGCOLOR", "0xF0",
                                        "CSR", "IMR", "0x1020", "0x1030", "BUSDIR", "0x1050", "0x1060", "0x1070",
                                        "SIGLBLID", "0x1090", "0x10A0", "0x10B0", "0x10C0", "0x10D0", "0x10E0", "0x10F0"};
        bool any = false;
        for (int i = 0; i < 32; ++i)
            if (b.priv.reads[i] != a.priv.reads[i]) {
                std::fprintf(f, " %s %llu", kPriv[i], static_cast<unsigned long long>(b.priv.reads[i] - a.priv.reads[i]));
                any = true;
            }
        if (!any) std::fprintf(f, " none");
        std::fprintf(f, "\nuploads (host->local pixels by PSM):");
        for (u32 p = 0; p < 64; ++p)
            if (s.upload_pixels_by_psm[p])
                std::fprintf(f, " %s %llu", psm_short(p), static_cast<unsigned long long>(s.upload_pixels_by_psm[p]));
        std::fprintf(f, "\ncoherence: uploads_into_rendered_pages %llu (pixels %llu)  textured_draws_sampling_rendered_pages %llu "
                        "(pixels %llu; by area FB0 %llu FB1 %llu Z %llu other %llu)  texture_in_own_framebuffer %llu  "
                        "clut_loads %llu (from rendered pages %llu)  local_copies %llu (rendered source %llu)  "
                        "local_reads %llu (rendered %llu, pixels %llu)  offscreen_draws %llu (pixels %llu)\n",
                     static_cast<unsigned long long>(s.uploads_over_rendered),
                     static_cast<unsigned long long>(s.upload_pixels_over_rendered),
                     static_cast<unsigned long long>(s.tex_draws_rendered_src),
                     static_cast<unsigned long long>(s.tex_pixels_rendered_src),
                     static_cast<unsigned long long>(s.rendered_src_by_area[0]),
                     static_cast<unsigned long long>(s.rendered_src_by_area[1]),
                     static_cast<unsigned long long>(s.rendered_src_by_area[2]),
                     static_cast<unsigned long long>(s.rendered_src_by_area[3]),
                     static_cast<unsigned long long>(s.tex_draws_self_feedback), static_cast<unsigned long long>(s.clut_loads),
                     static_cast<unsigned long long>(s.clut_loads_rendered), static_cast<unsigned long long>(s.local_copies),
                     static_cast<unsigned long long>(s.local_copies_rendered_src), static_cast<unsigned long long>(s.local_reads),
                     static_cast<unsigned long long>(s.local_reads_rendered), static_cast<unsigned long long>(s.local_read_pixels),
                     static_cast<unsigned long long>(s.offscreen_draws), static_cast<unsigned long long>(s.offscreen_pixels));
        for (const std::string& e : s.events) std::fprintf(f, "  event: %s\n", e.c_str());

        // Feature tables from the state keys.
        std::map<std::string, std::map<std::string, Agg>> feat;
        std::vector<std::pair<Agg, std::string>> sigs;
        for (const auto& [key, ag] : s.keys) {
            const u64 k0 = key.k[0], k1 = key.k[1], k2 = key.k[2], k3 = key.k[3];
            const u32 prim = k0 & 7u;
            const bool iip = (k0 >> 3) & 1u, tme = (k0 >> 4) & 1u, fge = (k0 >> 5) & 1u, abe = (k0 >> 6) & 1u,
                       aa1 = (k0 >> 7) & 1u, fst = (k0 >> 8) & 1u, ctxt = (k0 >> 9) & 1u;
            const u32 fpsm = (k0 >> 10) & 63u, fbp = (k0 >> 16) & 511u, fbw = (k0 >> 25) & 63u, zpsm = 0x30u | ((k0 >> 31) & 15u),
                      zbp = (k0 >> 35) & 511u, zmsk = (k0 >> 44) & 1u, fbm = (k0 >> 45) & 3u, scan = (k0 >> 47) & 3u;
            const bool colclamp = (k0 >> 49) & 1u, dthe = (k0 >> 50) & 1u, pabe = (k0 >> 51) & 1u, fba = (k0 >> 52) & 1u;
            const u32 test = k1 & 0x7FFFFu;
            const bool ate = test & 1u, date = (test >> 14) & 1u, datm = (test >> 15) & 1u, zte = (test >> 16) & 1u;
            const u32 atst = (test >> 1) & 7u, aref = (test >> 4) & 255u, afail = (test >> 12) & 3u, ztst = (test >> 17) & 3u;
            const u32 alpha = (k1 >> 19) & 255u, fix = (k1 >> 27) & 255u;
            auto add = [&](const char* name, const std::string& val) {
                Agg& x = feat[name][val];
                x.prims += ag.prims;
                x.pixels += ag.pixels;
                x.ns += ag.ns;
            };
            add("01 prim", std::string(kPrim[prim]) + (iip ? " gouraud" : " flat") + (tme ? (fst ? " tex-UV" : " tex-STQ") : "") +
                               (fge ? " fog" : "") + (aa1 ? " AA1" : "") + (ctxt ? " ctx2" : ""));
            add("02 frame", fmtv("FBP %llu FBW %llu ", fbp, fbw) + psm_short(fpsm) +
                                (fbm == 0 ? "" : fbm == 1 ? " FBMSK=alpha" : fbm == 2 ? " FBMSK=all" : " FBMSK=other"));
            add("03 zbuf", fmtv("ZBP %llu ", zbp) + psm_short(zpsm) + (zmsk ? " ZMSK" : "") +
                               (zte ? std::string(" ZTST ") + kZtst[ztst] : std::string(" ZTE=0")));
            add("04 alpha test", ate ? std::string(kAtst[atst]) + fmtv(" AREF 0x%02llX ", aref) + kAfail[afail] : std::string("off"));
            add("05 dest alpha test", date ? std::string(datm ? "DATE pass Ad=1" : "DATE pass Ad=0") : std::string("off"));
            add("06 blend", abe ? std::string("(") + kAbcd[alpha & 3] + "-" + kAbcd[(alpha >> 2) & 3] + ")*" + kC[(alpha >> 4) & 3] +
                                      "+" + kAbcd[(alpha >> 6) & 3] + fmtv(" ALPHA 0x%02llX", alpha) +
                                      (((alpha >> 4) & 3) == 2 ? fmtv(" FIX 0x%02llX", fix) : std::string())
                                : std::string("off"));
            add("07 pabe/fba/colclamp/dthe", fmtv("PABE %llu FBA %llu COLCLAMP %llu DTHE %llu", pabe, fba, colclamp, dthe));
            add("08 scanmsk", fmtv("%llu", scan));
            const u32 sx0 = k3 & 0x7FFu, sx1 = (k3 >> 11) & 0x7FFu, sy0 = (k3 >> 22) & 0x7FFu, sy1 = (k3 >> 33) & 0x7FFu;
            add("09 scissor", fmtv("%llu,%llu - %llu,%llu", sx0, sy0, sx1, sy1) + (((k3 >> 44) & 1u) ? " (non-std XYOFFSET)" : ""));
            if (tme) {
                const u32 psm = k2 & 63u, cpsm = (k2 >> 6) & 15u, csm = (k2 >> 10) & 1u, csa = (k2 >> 11) & 31u;
                const u32 tfx = (k2 >> 16) & 3u, tcc = (k2 >> 18) & 1u, tw = (k2 >> 19) & 15u, th = (k2 >> 23) & 15u;
                const u32 tbw = (k2 >> 27) & 63u, wms = (k2 >> 33) & 3u, wmt = (k2 >> 35) & 3u, lcm = (k2 >> 37) & 1u;
                const u32 mxl = (k2 >> 38) & 7u, mmag = (k2 >> 41) & 1u, mmin = (k2 >> 42) & 7u, cld = (k2 >> 45) & 7u;
                const u32 ta0 = (k2 >> 48) & 255u, aem = (k2 >> 56) & 1u, ta1hi = (k2 >> 57) & 1u;
                const bool idx = psm == 0x13 || psm == 0x14 || psm == 0x1B || psm == 0x24 || psm == 0x2C;
                add("10 tex psm", std::string(psm_short(psm)) +
                                      (idx ? std::string(" CLUT ") + psm_short(cpsm) + (csm ? " CSM2" : " CSM1") + fmtv(" CSA %llu", csa)
                                           : std::string()));
                if (idx) add("11 clut load (CLD at draw)", fmtv("CLD %llu", cld));
                add("12 tex size", fmtv("%llux%llu TBW %llu", 1ull << tw, 1ull << th, tbw));
                add("13 tex function", std::string(kTfx[tfx]) + (tcc ? " RGBA" : " RGB"));
                add("14 tex filter", std::string("MMAG ") + (mmag ? "LINEAR" : "NEAREST") + " MMIN " + kMin[mmin] +
                                         fmtv(" MXL %llu LCM %llu", mxl, lcm));
                add("15 tex wrap", std::string(kWrap[wms]) + " / " + kWrap[wmt]);
                if (psm == 0x01 || psm == 0x02 || psm == 0x0A || (idx && cpsm != 0))
                    add("16 TEXA (24/16-bit expansion)", fmtv("TA0 0x%02llX AEM %llu TA1>=0x80 %llu", ta0, aem, ta1hi));
            }
            char sig[512];
            std::snprintf(sig, sizeof sig, "%s%s%s%s FB%u/%s Z%u/%s%s%s A%s T%s %s",
                          kPrim[prim], iip ? "/G" : "/F", tme ? (fst ? "/UV" : "/STQ") : "", abe ? "/ABE" : "", fbp, psm_short(fpsm),
                          zbp, psm_short(zpsm), zmsk ? "/M" : "", zte ? kZtst[ztst] : "-",
                          abe ? fmtv("%02llX", alpha).c_str() : "--",
                          ate ? (std::string(kAtst[atst]) + fmtv("%02llX", aref) + "/" + kAfail[afail]).c_str() : "--",
                          tme ? (std::string(psm_short(k2 & 63u)) + ((k2 >> 41) & 1u ? "/lin" : "/pt")).c_str() : "");
            sigs.push_back({ag, sig});
        }
        for (const auto& [name, vals] : feat) {
            std::fprintf(f, "-- %s\n", name.c_str());
            std::vector<std::pair<std::string, Agg>> rows(vals.begin(), vals.end());
            std::sort(rows.begin(), rows.end(), [](const auto& x, const auto& y) { return x.second.pixels > y.second.pixels; });
            for (const auto& [val, ag] : rows)
                std::fprintf(f, "  %10llu %12llu %10.1f  %s\n", static_cast<unsigned long long>(ag.prims),
                             static_cast<unsigned long long>(ag.pixels), static_cast<double>(ag.ns) * 1e-6, val.c_str());
        }
        std::sort(sigs.begin(), sigs.end(), [](const auto& x, const auto& y) { return x.first.pixels > y.first.pixels; });
        std::fprintf(f, "-- top state signatures by pixels\n");
        for (std::size_t i = 0; i < sigs.size() && i < 25; ++i)
            std::fprintf(f, "  %10llu %12llu %10.1f  %s\n", static_cast<unsigned long long>(sigs[i].first.prims),
                         static_cast<unsigned long long>(sigs[i].first.pixels), static_cast<double>(sigs[i].first.ns) * 1e-6,
                         sigs[i].second.c_str());
    }
    std::fclose(f);
    std::printf("p3fes: gs-census written to %s\n", cfg_.census.string().c_str());
}

} // namespace p3fes::app
