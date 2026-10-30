// p3fes_gscmp: compare a composed GS frame with a reference screenshot.
//
//   p3fes_gscmp <ours.png> <reference.png> [--tolerance N] [--max-over-percent P] [--diff <out.png>]
//
// PNGs are decoded with the Windows Imaging Component. When the sizes differ, `ours` is resampled bilinearly to
// the reference size (PCSX2 2.8.2 saves Screenshot.png at 640x480 while the game's display is 640x448). Prints the
// per-channel maximum and mean absolute difference, the share of pixels whose largest channel difference exceeds
// the tolerance, and PSNR. Exit 0 when that share is <= P percent (default 1.0), 1 when it is larger, 2 on errors.
// The reference is PCSX2's software renderer: remaining differences have to be explained (dithering, rounding,
// the 448 -> 480 aspect scaling), not hidden by raising the tolerance.
#include <windows.h>
#include <wincodec.h>
#include <wrl/client.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "p3fes/gs/gs_output.h"

namespace {

using Microsoft::WRL::ComPtr;
using p3fes::gs::Frame;

std::wstring widen(const char* s) {
    const int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, nullptr, 0);
    std::wstring w(static_cast<std::size_t>(n > 0 ? n - 1 : 0), L'\0');
    if (n > 1) MultiByteToWideChar(CP_UTF8, 0, s, -1, w.data(), n);
    return w;
}

bool load_png(IWICImagingFactory* f, const char* path, Frame& out) {
    ComPtr<IWICBitmapDecoder> dec;
    if (FAILED(f->CreateDecoderFromFilename(widen(path).c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &dec))) return false;
    ComPtr<IWICBitmapFrameDecode> frame;
    if (FAILED(dec->GetFrame(0, &frame))) return false;
    ComPtr<IWICFormatConverter> conv;
    if (FAILED(f->CreateFormatConverter(&conv))) return false;
    if (FAILED(conv->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.0,
                                WICBitmapPaletteTypeCustom))) {
        return false;
    }
    UINT w = 0, h = 0;
    if (FAILED(conv->GetSize(&w, &h)) || w == 0 || h == 0) return false;
    out.width = w;
    out.height = h;
    out.rgba.assign(static_cast<std::size_t>(w) * h, 0);
    return SUCCEEDED(conv->CopyPixels(nullptr, w * 4u, w * h * 4u, reinterpret_cast<BYTE*>(out.rgba.data())));
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 3) {
        std::fputs("usage: p3fes_gscmp <ours.png> <reference.png> [--tolerance N] [--max-over-percent P] [--diff out.png]\n", stderr);
        return 2;
    }
    unsigned tolerance = 8;
    double max_over = 1.0;
    const char* diff_path = nullptr;
    for (int i = 3; i < argc; ++i) {
        if (std::strcmp(argv[i], "--tolerance") == 0 && i + 1 < argc) tolerance = static_cast<unsigned>(std::strtoul(argv[++i], nullptr, 10));
        else if (std::strcmp(argv[i], "--max-over-percent") == 0 && i + 1 < argc) max_over = std::strtod(argv[++i], nullptr);
        else if (std::strcmp(argv[i], "--diff") == 0 && i + 1 < argc) diff_path = argv[++i];
        else {
            std::fprintf(stderr, "p3fes_gscmp: unknown argument '%s'\n", argv[i]);
            return 2;
        }
    }
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) return 2;
    int rc = 2;
    {
        ComPtr<IWICImagingFactory> factory;
        Frame ours, ref;
        if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory)))) {
            std::fputs("p3fes_gscmp: WIC unavailable\n", stderr);
        } else if (!load_png(factory.Get(), argv[1], ours) || !load_png(factory.Get(), argv[2], ref)) {
            std::fputs("p3fes_gscmp: cannot decode an input PNG\n", stderr);
        } else {
            std::printf("ours %ux%u, reference %ux%u\n", ours.width, ours.height, ref.width, ref.height);
            if (ours.width != ref.width || ours.height != ref.height) {
                ours = p3fes::gs::resample_bilinear(ours, ref.width, ref.height);
                std::printf("resampled ours to %ux%u (bilinear)\n", ref.width, ref.height);
            }
            Frame diff;
            const p3fes::gs::FrameDiff d = p3fes::gs::diff_frames(ours, ref, tolerance, diff_path ? &diff : nullptr);
            const double pct = d.pixels ? 100.0 * static_cast<double>(d.pixels_over) / static_cast<double>(d.pixels) : 0.0;
            std::printf("max |diff| %u, mean |diff| %.3f, PSNR %.2f dB, pixels over tolerance %u: %llu / %llu (%.3f%%)\n",
                        d.max_abs, d.mean_abs, d.psnr_db, tolerance, static_cast<unsigned long long>(d.pixels_over),
                        static_cast<unsigned long long>(d.pixels), pct);
            if (diff_path && !p3fes::gs::write_png(diff_path, diff)) std::fprintf(stderr, "p3fes_gscmp: cannot write %s\n", diff_path);
            rc = pct <= max_over ? 0 : 1;
            std::printf("%s (threshold %.3f%%)\n", rc == 0 ? "MATCH" : "DIFFER", max_over);
        }
    }
    CoUninitialize();
    return rc;
}
