// Private interface between GsCore (register file, vertex queue) and the software rasteriser (gs_raster.cpp).
#pragma once

#include "p3fes/gs/gs_core.h"

#include <array>

namespace p3fes::gs::detail {

struct TexLevel {
    u32 tbp = 0; // block address
    u32 tbw = 0; // buffer width in 64-pixel units
    u32 tw = 0;  // log2 width
    u32 th = 0;  // log2 height
};

struct TexState {
    u32 psm = 0;
    bool tcc = false;
    u32 tfx = 0;
    u32 cpsm = 0;
    u32 csa = 0;
    std::array<TexLevel, 7> level{};
    u32 mxl = 0;
    bool lcm = false;
    s32 k16 = 0; // TEX1.K, signed, 4 fraction bits
    u32 l = 0;
    bool mmag_linear = false;
    u32 mmin = 0;
    u32 wms = 0, wmt = 0, minu = 0, maxu = 0, minv = 0, maxv = 0;
    u32 ta0 = 0, ta1 = 0;
    bool aem = false;
};

// Everything one primitive needs, decoded once at the kick (GS User's Manual register fields).
struct DrawState {
    u32 prim = 0;
    bool iip = false, tme = false, fge = false, abe = false, aa1 = false, fst = false;
    u32 ctxt = 0;

    u32 fbp = 0; // block address (FRAME.FBP * 32)
    u32 fbw = 0;
    u32 fpsm = 0;
    u32 fbmsk = 0;
    u32 zbp = 0; // block address (ZBUF.ZBP * 32)
    u32 zpsm = 0x30;
    bool zmsk = false;

    bool ate = false;
    u32 atst = 0, aref = 0, afail = 0;
    bool date = false, datm = false;
    bool zte = false;
    u32 ztst = 0;

    u32 a = 0, b = 0, c = 0, d = 0, fix = 0;
    bool pabe = false, fba = false, colclamp = false, dthe = false;
    s32 dimx[4][4] = {};

    s32 scax0 = 0, scax1 = 0, scay0 = 0, scay1 = 0;
    s32 ofx = 0, ofy = 0; // 12.4
    u32 scanmsk = 0;

    TexState tex{};
    u32 fogcol = 0;
};

DrawState decode_draw_state(const GsRegs& r);

// Rasterise one primitive (`count` vertices as the kick rule delivered them, last = kicking vertex).
void rasterize(GsMemory& mem, const std::array<u16, 512>& clut, const DrawState& ds, const GsVertex* v, u32 count,
               GsCoreStats& stats);

// Texture lookup in isolation (tests): texel coordinates in 1/16 texel units, level 0, the state's filter for
// magnification. Returns 0xAABBGGRR.
u32 sample_texture(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, s32 u16ths, s32 v16ths,
                   bool linear, u32 level);

// The reference implementation (gs_raster_ref.cpp): the same pipeline as one generic operation per pixel, kept
// verbatim from the pre-optimisation rasteriser. `rasterize` above must produce identical memory for every input
// (tests/gs/test_gs_fast.cpp); it also uses `ref::sample` for texture states it does not specialise.
namespace ref {
void rasterize(GsMemory& mem, const std::array<u16, 512>& clut, const DrawState& ds, const GsVertex* v, u32 count,
               GsCoreStats& stats);
u32 sample(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, s32 u16ths, s32 v16ths,
           float q) noexcept;
u32 sample_level(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, s32 u16ths, s32 v16ths,
                 bool linear, u32 level) noexcept;
} // namespace ref

} // namespace p3fes::gs::detail
