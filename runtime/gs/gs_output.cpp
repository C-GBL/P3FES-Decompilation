// CRTC composition (GS User's Manual §8 PMODE/SMODE2/DISPFB/DISPLAY/BGCOLOR) and a dependency-free PNG writer.
#include "p3fes/gs/gs_output.h"

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace p3fes::gs {

namespace {

struct Circuit {
    bool on = false;
    s32 x = 0, y = 0;   // placement in display coordinates (pixels / lines after MAGH/MAGV)
    u32 w = 0, h = 0;
    u32 fbp = 0, fbw = 0, psm = 0, dbx = 0, dby = 0;
};

Circuit decode_circuit(const DisplayRegs& r, u32 c) {
    Circuit k;
    k.on = ((r.pmode >> c) & 1u) != 0;
    if (!k.on) return k;
    const u64 d = r.display[c], f = r.dispfb[c];
    const u32 magh = bits(d, 23, 4) + 1u, magv = bits(d, 27, 2) + 1u;
    k.w = (bits(d, 32, 12) + 1u) / magh;
    k.h = (bits(d, 44, 11) + 1u) / magv;
    k.x = static_cast<s32>(bits(d, 0, 12) / magh);
    k.y = static_cast<s32>(bits(d, 12, 11) / magv);
    k.fbp = bits(f, 0, 9) * kBlocksPerPage;
    k.fbw = bits(f, 9, 6);
    k.psm = bits(f, 15, 5);
    k.dbx = bits(f, 32, 11);
    k.dby = bits(f, 43, 11);
    if (k.w == 0 || k.h == 0 || k.w > 2048 || k.h > 2048) k.on = false;
    return k;
}

// Display pixel -> 0xAABBGGRR with the alpha the merge circuit sees (CT24 and the PS-GPU24 format carry none: 0x80).
u32 read_display_pixel(const GsMemory& mem, const Circuit& k, u32 x, u32 y) {
    switch (k.psm) {
    case 0x01:
    case 0x12: return (mem.read(0x01, k.fbp, k.fbw, x, y) & 0xFFFFFFu) | 0x80000000u;
    case 0x02:
    case 0x0A: {
        const u32 c = mem.read(k.psm, k.fbp, k.fbw, x, y);
        return ((c & 0x1Fu) << 3) | (((c >> 5) & 0x1Fu) << 11) | (((c >> 10) & 0x1Fu) << 19) | ((c & 0x8000u) ? 0x80000000u : 0u);
    }
    default: return mem.read(0x00, k.fbp, k.fbw, x, y);
    }
}

u32 crc32(const u8* p, std::size_t n, u32 crc = 0) {
    static const auto table = [] {
        std::array<u32, 256> t{};
        for (u32 i = 0; i < 256; ++i) {
            u32 c = i;
            for (int k = 0; k < 8; ++k) c = (c & 1u) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            t[i] = c;
        }
        return t;
    }();
    crc = ~crc;
    for (std::size_t i = 0; i < n; ++i) crc = table[(crc ^ p[i]) & 0xFFu] ^ (crc >> 8);
    return ~crc;
}

void put_be32(std::vector<u8>& out, u32 v) {
    out.push_back(static_cast<u8>(v >> 24));
    out.push_back(static_cast<u8>(v >> 16));
    out.push_back(static_cast<u8>(v >> 8));
    out.push_back(static_cast<u8>(v));
}

void put_chunk(std::vector<u8>& out, const char* type, const std::vector<u8>& data) {
    put_be32(out, static_cast<u32>(data.size()));
    const std::size_t start = out.size();
    out.insert(out.end(), type, type + 4);
    out.insert(out.end(), data.begin(), data.end());
    put_be32(out, crc32(out.data() + start, out.size() - start));
}

} // namespace

Frame compose(const GsMemory& mem, const DisplayRegs& regs, ComposeInfo* info) {
    Frame out;
    Circuit k[2] = {decode_circuit(regs, 0), decode_circuit(regs, 1)};
    if (!k[0].on && !k[1].on) return out;
    s32 x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    for (const Circuit& c : k) {
        if (!c.on) continue;
        x0 = std::min(x0, c.x);
        y0 = std::min(y0, c.y);
        x1 = std::max(x1, c.x + static_cast<s32>(c.w));
        y1 = std::max(y1, c.y + static_cast<s32>(c.h));
    }
    out.width = static_cast<u32>(std::min(x1 - x0, 2048));
    out.height = static_cast<u32>(std::min(y1 - y0, 2048));
    out.rgba.assign(static_cast<std::size_t>(out.width) * out.height, 0xFF000000u);
    if (info) {
        for (u32 c = 0; c < 2; ++c) {
            info->circuit_enabled[c] = k[c].on;
            info->circuit_width[c] = k[c].w;
            info->circuit_height[c] = k[c].h;
            info->circuit_x[c] = k[c].x - x0;
            info->circuit_y[c] = k[c].y - y0;
        }
    }
    const bool interlaced = (regs.smode2 & 1u) != 0;
    const bool frame_mode = ((regs.smode2 >> 1) & 1u) != 0;
    const bool mmod = ((regs.pmode >> 5) & 1u) != 0;
    const bool slbg = ((regs.pmode >> 7) & 1u) != 0;
    const u32 alp = bits(regs.pmode, 8, 8);
    const u32 bg = static_cast<u32>(regs.bgcolor & 0xFFFFFFu);

    const auto fetch = [&](const Circuit& c, s32 ox, s32 oy, u32& px) -> bool {
        if (!c.on) return false;
        const s32 lx = ox + x0 - c.x, ly = oy + y0 - c.y;
        if (lx < 0 || ly < 0 || lx >= static_cast<s32>(c.w) || ly >= static_cast<s32>(c.h)) return false;
        const u32 line = (interlaced && frame_mode) ? static_cast<u32>(ly) / 2u : static_cast<u32>(ly);
        px = read_display_pixel(mem, c, c.dbx + static_cast<u32>(lx), c.dby + line);
        return true;
    };

    for (u32 y = 0; y < out.height; ++y) {
        for (u32 x = 0; x < out.width; ++x) {
            u32 p1 = 0, p2 = 0;
            const bool h1 = fetch(k[0], static_cast<s32>(x), static_cast<s32>(y), p1);
            const bool h2 = fetch(k[1], static_cast<s32>(x), static_cast<s32>(y), p2);
            const u32 under = (!slbg && h2) ? (p2 & 0xFFFFFFu) : bg;
            u32 rgb = under;
            if (h1) {
                const u32 a = mmod ? alp : (p1 >> 24);
                rgb = 0;
                for (u32 sh = 0; sh < 24; sh += 8) {
                    const u32 c1 = (p1 >> sh) & 0xFFu, c2 = (under >> sh) & 0xFFu;
                    const u32 v = std::min<u32>((c1 * a + c2 * (255u - std::min<u32>(a, 255u)) + 127u) / 255u, 255u);
                    rgb |= v << sh;
                }
            }
            out.rgba[static_cast<std::size_t>(y) * out.width + x] = rgb | 0xFF000000u;
        }
    }
    return out;
}

std::vector<u8> encode_png(const Frame& frame) {
    std::vector<u8> png = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
    std::vector<u8> ihdr;
    put_be32(ihdr, frame.width);
    put_be32(ihdr, frame.height);
    ihdr.insert(ihdr.end(), {8, 2, 0, 0, 0}); // 8-bit RGB, deflate, adaptive filtering, no interlace
    put_chunk(png, "IHDR", ihdr);

    std::vector<u8> raw;
    raw.reserve(static_cast<std::size_t>(frame.height) * (1u + frame.width * 3u));
    for (u32 y = 0; y < frame.height; ++y) {
        raw.push_back(0); // filter: none
        for (u32 x = 0; x < frame.width; ++x) {
            const u32 p = frame.at(x, y);
            raw.push_back(static_cast<u8>(p));
            raw.push_back(static_cast<u8>(p >> 8));
            raw.push_back(static_cast<u8>(p >> 16));
        }
    }
    std::vector<u8> z = {0x78, 0x01};
    std::size_t pos = 0;
    do {
        const std::size_t n = std::min<std::size_t>(raw.size() - pos, 65535u);
        const bool last = pos + n == raw.size();
        z.push_back(last ? 1 : 0);
        z.push_back(static_cast<u8>(n));
        z.push_back(static_cast<u8>(n >> 8));
        z.push_back(static_cast<u8>(~n));
        z.push_back(static_cast<u8>(~n >> 8));
        z.insert(z.end(), raw.begin() + static_cast<std::ptrdiff_t>(pos), raw.begin() + static_cast<std::ptrdiff_t>(pos + n));
        pos += n;
    } while (pos < raw.size());
    u32 s1 = 1, s2 = 0;
    for (u8 b : raw) {
        s1 = (s1 + b) % 65521u;
        s2 = (s2 + s1) % 65521u;
    }
    put_be32(z, (s2 << 16) | s1);
    put_chunk(png, "IDAT", z);
    put_chunk(png, "IEND", {});
    return png;
}

bool write_png(const std::string& path, const Frame& frame) {
    if (frame.empty()) return false;
    const std::vector<u8> png = encode_png(frame);
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) return false;
    const bool ok = std::fwrite(png.data(), 1, png.size(), f) == png.size();
    return std::fclose(f) == 0 && ok;
}

u64 frame_hash(const Frame& frame) noexcept {
    u64 h = 0xCBF29CE484222325ull;
    for (u32 p : frame.rgba) {
        for (u32 sh = 0; sh < 24; sh += 8) {
            h ^= (p >> sh) & 0xFFu;
            h *= 0x100000001B3ull;
        }
    }
    return h;
}

Frame resample_bilinear(const Frame& src, u32 width, u32 height) {
    Frame out;
    if (src.empty() || width == 0 || height == 0) return out;
    out.width = width;
    out.height = height;
    out.rgba.resize(static_cast<std::size_t>(width) * height);
    const double sx = static_cast<double>(src.width) / width, sy = static_cast<double>(src.height) / height;
    for (u32 y = 0; y < height; ++y) {
        const double fy = std::clamp((y + 0.5) * sy - 0.5, 0.0, static_cast<double>(src.height - 1));
        const u32 y0 = static_cast<u32>(fy), y1 = std::min(y0 + 1, src.height - 1);
        const double wy = fy - y0;
        for (u32 x = 0; x < width; ++x) {
            const double fx = std::clamp((x + 0.5) * sx - 0.5, 0.0, static_cast<double>(src.width - 1));
            const u32 x0 = static_cast<u32>(fx), x1 = std::min(x0 + 1, src.width - 1);
            const double wx = fx - x0;
            u32 p = 0;
            for (u32 sh = 0; sh < 32; sh += 8) {
                const double a = (src.at(x0, y0) >> sh) & 0xFFu, b = (src.at(x1, y0) >> sh) & 0xFFu;
                const double c = (src.at(x0, y1) >> sh) & 0xFFu, d = (src.at(x1, y1) >> sh) & 0xFFu;
                const double v = (a * (1 - wx) + b * wx) * (1 - wy) + (c * (1 - wx) + d * wx) * wy;
                p |= static_cast<u32>(std::lround(std::clamp(v, 0.0, 255.0))) << sh;
            }
            out.rgba[static_cast<std::size_t>(y) * width + x] = p;
        }
    }
    return out;
}

FrameDiff diff_frames(const Frame& a, const Frame& b, u32 tolerance, Frame* diff_image) {
    FrameDiff d;
    if (a.width != b.width || a.height != b.height) return d;
    d.pixels = a.rgba.size();
    if (diff_image) {
        diff_image->width = a.width;
        diff_image->height = a.height;
        diff_image->rgba.assign(a.rgba.size(), 0xFF000000u);
    }
    double sum = 0.0, sq = 0.0;
    for (std::size_t i = 0; i < a.rgba.size(); ++i) {
        u32 worst = 0, img = 0;
        for (u32 sh = 0; sh < 24; sh += 8) {
            const s32 ca = static_cast<s32>((a.rgba[i] >> sh) & 0xFFu), cb = static_cast<s32>((b.rgba[i] >> sh) & 0xFFu);
            const u32 e = static_cast<u32>(ca > cb ? ca - cb : cb - ca);
            worst = std::max(worst, e);
            sum += e;
            sq += static_cast<double>(e) * e;
            img |= std::min<u32>(e * 4u, 255u) << sh;
        }
        d.max_abs = std::max(d.max_abs, worst);
        if (worst > tolerance) ++d.pixels_over;
        if (diff_image) diff_image->rgba[i] = img | 0xFF000000u;
    }
    const double n = static_cast<double>(d.pixels) * 3.0;
    d.mean_abs = n > 0 ? sum / n : 0.0;
    const double mse = n > 0 ? sq / n : 0.0;
    d.psnr_db = mse > 0 ? 10.0 * std::log10(255.0 * 255.0 / mse) : 999.0;
    return d;
}

} // namespace p3fes::gs
