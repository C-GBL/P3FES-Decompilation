// p3fes_gsdecode: decode a texture or buffer out of a 4 MiB GS local-memory image with the GS core's own
// swizzle (gs_mem.h) and write it as PNG.
//
//   p3fes_gsdecode <vram.bin> --tbp 0x2E60 --tbw 8 --psm T8 --w 512 --h 512 [--cbp 0x3260 [--cpsm CT32]]
//                  [--offset N] [--out tex.png] [--raw-index]
//
// vram.bin is our `gsMemory.bin` (snapshot) or PCSX2's save-state `GS.bin` (`--offset 425` skips its register
// header; the offset of the 4 MiB VRAM block inside GS.bin for PCSX2 2.8.2, found by block alignment against a
// snapshot of ours). PSM names as gs_types.h prints them (CT32, CT24, CT16, CT16S, T8, T4, T8H, T4HL, T4HH, Z*),
// or a number. For T8/T4/T8H/T4HL/T4HH a CLUT at `--cbp` (CSM1 layout, `--cpsm` CT32 or CT16, default CT32) turns
// the index into a colour; `--raw-index` writes the index as a grey level instead. Alpha is dropped by the PNG
// writer (gs_output.h). Purpose: check the read path of a format against VRAM that another implementation
// filled -- if PCSX2's title textures decode into pictures with our swizzle, the swizzle is right.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "p3fes/gs/gs_mem.h"
#include "p3fes/gs/gs_output.h"

namespace {

using namespace p3fes;
using namespace p3fes::gs;

u32 parse_psm(const char* s) {
    static const struct { const char* n; u32 v; } k[] = {
        {"CT32", 0x00}, {"CT24", 0x01}, {"CT16", 0x02}, {"CT16S", 0x0A}, {"T8", 0x13}, {"T4", 0x14}, {"T8H", 0x1B},
        {"T4HL", 0x24}, {"T4HH", 0x2C}, {"Z32", 0x30}, {"Z24", 0x31}, {"Z16", 0x32}, {"Z16S", 0x3A},
    };
    for (const auto& e : k)
        if (_stricmp(e.n, s) == 0) return e.v;
    return static_cast<u32>(std::strtoul(s, nullptr, 0));
}

u32 expand16(u32 p) {  // CT16 -> RGBA8 (5:5:5:1), as the CLUT/texture expansion with TA0 = 0, TA1 = 0x80
    const u32 r = (p & 0x1F) << 3, g = ((p >> 5) & 0x1F) << 3, b = ((p >> 10) & 0x1F) << 3;
    const u32 a = (p & 0x8000) ? 0x80u : 0u;
    return r | (g << 8) | (b << 16) | (a << 24);
}

// CSM1 CLUT lookup for an index: the CLUT is stored as a 16x16 (CT32) or 8x2-per-16 (CT16) image at cbp with
// bw 1; PSMT8 indices address the CT32 CLUT with the GS's bit-3/bit-4 swap (GS User's Manual, CLUT storage).
u32 clut_lookup(const GsMemory& m, u32 cbp, u32 cpsm, u32 index, bool t4) {
    u32 i = index;
    if (!t4 && cpsm == 0x00) i = (index & ~0x18u) | ((index & 0x08u) << 1) | ((index & 0x10u) >> 1);
    if (cpsm == 0x00) {  // CT32: 16 x 16 texels, bw 1
        return m.read(0x00, cbp, 1, i & 15u, i >> 4);
    }
    // CT16: 16 x 2 rows of 8? The 16-bit CLUT is a 16x16 CT16 image too (64x64 page); CSM1 index order is linear.
    return expand16(m.read(0x02, cbp, 1, i & 15u, i >> 4));
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: p3fes_gsdecode <vram.bin> --tbp N --tbw N --psm F --w N --h N [--cbp N [--cpsm F]] [--offset N] [--out f.png] [--raw-index]\n");
        return 2;
    }
    const char* path = argv[1];
    u32 tbp = 0, tbw = 1, psm = 0, w = 64, h = 64, cbp = 0, cpsm = 0;
    bool have_clut = false, raw_index = false;
    std::size_t offset = 0;
    std::string out = "decoded.png";
    for (int i = 2; i < argc; ++i) {
        const char* a = argv[i];
        const bool has1 = i + 1 < argc;
        if (!std::strcmp(a, "--tbp") && has1) tbp = static_cast<u32>(std::strtoul(argv[++i], nullptr, 0));
        else if (!std::strcmp(a, "--tbw") && has1) tbw = static_cast<u32>(std::strtoul(argv[++i], nullptr, 0));
        else if (!std::strcmp(a, "--psm") && has1) psm = parse_psm(argv[++i]);
        else if (!std::strcmp(a, "--w") && has1) w = static_cast<u32>(std::strtoul(argv[++i], nullptr, 0));
        else if (!std::strcmp(a, "--h") && has1) h = static_cast<u32>(std::strtoul(argv[++i], nullptr, 0));
        else if (!std::strcmp(a, "--cbp") && has1) { cbp = static_cast<u32>(std::strtoul(argv[++i], nullptr, 0)); have_clut = true; }
        else if (!std::strcmp(a, "--cpsm") && has1) cpsm = parse_psm(argv[++i]);
        else if (!std::strcmp(a, "--offset") && has1) offset = std::strtoull(argv[++i], nullptr, 0);
        else if (!std::strcmp(a, "--out") && has1) out = argv[++i];
        else if (!std::strcmp(a, "--raw-index")) raw_index = true;
        else { std::fprintf(stderr, "p3fes_gsdecode: unknown argument %s\n", a); return 2; }
    }
    std::ifstream f(path, std::ios::binary);
    if (!f) { std::fprintf(stderr, "p3fes_gsdecode: cannot open %s\n", path); return 2; }
    f.seekg(static_cast<std::streamoff>(offset));
    GsMemory mem;
    f.read(reinterpret_cast<char*>(mem.data()), kVramBytes);
    if (f.gcount() != static_cast<std::streamsize>(kVramBytes)) {
        std::fprintf(stderr, "p3fes_gsdecode: %s holds %lld bytes after offset %zu, need %u\n", path,
                     static_cast<long long>(f.gcount()), offset, kVramBytes);
        return 2;
    }
    const bool indexed = psm == 0x13 || psm == 0x14 || psm == 0x1B || psm == 0x24 || psm == 0x2C;
    const bool t4 = psm == 0x14 || psm == 0x24 || psm == 0x2C;
    Frame fr;
    fr.width = w;
    fr.height = h;
    fr.rgba.resize(static_cast<std::size_t>(w) * h);
    for (u32 y = 0; y < h; ++y)
        for (u32 x = 0; x < w; ++x) {
            const u32 raw = mem.read(psm, tbp, tbw, x, y);
            u32 c;
            if (indexed) {
                if (have_clut && !raw_index) c = clut_lookup(mem, cbp, cpsm, raw, t4);
                else {
                    const u32 g = t4 ? raw * 17u : raw;
                    c = g | (g << 8) | (g << 16) | 0xFF000000u;
                }
            } else if (psm == 0x02 || psm == 0x0A || psm == 0x32 || psm == 0x3A) {
                c = expand16(raw);
            } else {
                c = raw;
            }
            fr.rgba[static_cast<std::size_t>(y) * w + x] = c;
        }
    if (!write_png(out, fr)) { std::fprintf(stderr, "p3fes_gsdecode: cannot write %s\n", out.c_str()); return 2; }
    std::printf("p3fes_gsdecode: %s +%zu tbp 0x%X tbw %u psm %s %ux%u%s -> %s (hash 0x%016llX)\n", path, offset, tbp, tbw,
                psm_name(psm), w, h, have_clut ? " with CLUT" : "", out.c_str(),
                static_cast<unsigned long long>(frame_hash(fr)));
    return 0;
}
