// Modernize layer 4 (docs/MODERNIZE_PLAN.md §3 "4. Movies", ADR-0017): the native branches of CRI's SFD video
// decoder on its sceMpeg path (game/include/p3fes/game/movies_native.h) with the host's decoder
// (runtime/native/movies/native_movies.h) installed, on the ELF's own code: viBufCreate's ring reset writes no DMA
// tag; the faithful feed (sub_594EC8) fills the ring; the DMA restart / flush / stop keep the ring record by the
// faithful arithmetic from the native read position; the picture call decodes exactly what the decoder decodes
// from the elementary stream, picture for picture through a whole movie fed and consumed through the 512 KiB ring,
// and at the stream's end takes CRI's starvation path (the end code fed after the data, the abort mark). No access
// reaches an IPU or DMAC register. Reads one movie of the user's disc (P3FCT007.SFD, beside the ELF's extracted
// tree; the case skips without it). Without the service the same bodies run their faithful path (the pair tests of
// test_libs13 / test_sweep5b / test_sweep5c cover those).
#include "pair_harness.h"
#include "stand_ins.h"

#include "mpeg_video.h"
#include "native_movies.h"
#include "p3fes/game/movies_native.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using namespace p3fes::game_test;
namespace nm = p3fes::native::movies;

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
void fn_viBufCreate_00594130(EEContext&);
void fn_sub_5944A8_005944a8(EEContext&);  // flush
void fn_sub_5946A8_005946a8(EEContext&);  // DMA stop
void fn_sub_5947A8_005947a8(EEContext&);  // DMA restart
void fn_sub_594AC0_00594ac0(EEContext&);  // destroy
void fn_sub_594EC8_00594ec8(EEContext&);  // feed
void fn_sub_5942E8_005942e8(EEContext&);  // free pieces
}  // namespace p3fes::recomp_gen

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

namespace {

namespace gen = ::p3fes::recomp_gen;

struct ServiceScope {
    explicit ServiceScope(nm::MoviesService* s) { nm::g_service = s; }
    ~ServiceScope() { nm::g_service = nullptr; }
};

u32 ld32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void st32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

// guest layout (free RAM above the harness's arena)
constexpr u32 kWork = 0x01900000u;             // the video work (vdec::)
constexpr u32 kVibuf = kWork + 4504u;          // its ring record
constexpr u32 kMpegRec = kWork + 4432u;        // its sceMpeg record
constexpr u32 kHandle = 0x01910000u;           // the SFD handle (+56: the format)
constexpr u32 kFrame = 0x01911000u;            // a frame record (+32: its buffer)
constexpr u32 kRingData = 0x01A00000u;         // 256 sectors
constexpr u32 kRingTags = 0x01A80000u;         // the DMA tag area
constexpr u32 kRingEntries = 0x01A90000u;      // 512 x 24 bytes
constexpr u32 kChunk = 0x01AB0000u;            // a feed chunk
constexpr u32 kOut = 0x01B00000u;              // the frame buffer (920 macroblocks x 1,024)

// sfd_native_get_picture on the register ABI, for run(): $a0 work, $a1 frame record, $a2 handle; the cycles to $v0
void call_get_picture(EEContext& ctx) {
    auto arg = [&](unsigned r) { return static_cast<u32>(ctx.gpr[GPR_A0 + r].u64[0]); };
    ctx.gpr[GPR_V0].u64[0] = game::sfd_native_get_picture(ctx, *nm::service(), arg(0), arg(1), arg(2));
}
// viBufCreate with all six arguments ($t0 the entry table, $t1 its count), as sub_594C38 calls it
void call_vibuf_create(EEContext& ctx) {
    ctx.gpr[8].u64[0] = kRingEntries;  // $t0
    ctx.gpr[9].u64[0] = 512;           // $t1
    gen::fn_viBufCreate_00594130(ctx);
}
void call_mpeg_create(EEContext& ctx) {
    game::sfd_native_mpeg_create(ctx, *nm::service(), static_cast<u32>(ctx.gpr[GPR_A0].u64[0]));
}

std::vector<u8> read_file(const std::filesystem::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return {};
    return std::vector<u8>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

}  // namespace

TEST_CASE("game(movies_native): the sceMpeg path with --native movies plays a whole movie through the ring") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    const std::filesystem::path sfd =
        std::filesystem::path(elf_path()).parent_path().parent_path() / "DATA" / "SFD" / "P3FCT007.SFD";
    const std::vector<u8> file = read_file(sfd);
    if (file.empty()) {
        MESSAGE("SKIP: no " << sfd.string());
        return;
    }
    nm::SfdStreams es;
    REQUIRE(nm::demux_sfd(file.data(), file.size(), es));
    // the reference: the decoder over the whole elementary stream
    std::vector<u64> ref;
    {
        nm::MpegDecoder d;
        nm::DirectEngine e(es.video.data(), es.video.size());
        std::vector<u8> o(1u << 20);
        while (d.decode(e, true, o.data(), o.size()) == nm::Status::Shown) ref.push_back(nm::fnv1a64(o.data(), d.frame_bytes(true)));
    }
    REQUIRE(ref.size() == 270);

    nm::NativeMovies svc;
    ServiceScope scope(&svc);
    // the ring: viBufCreate's faithful body (a semaphore through the syscall stub), its reset through the native branch
    run(m, &call_vibuf_create, {kVibuf, kRingData, kRingTags, 256}, 1);
    CHECK(ld32(m, kVibuf + 68) == 1);
    CHECK(ld32(m, kVibuf + 24) == 256u * 2048u);
    CHECK(ld32(m, kVibuf + 84) == 512);
    for (u32 o = 0; o < 257 * 16; o += 4) REQUIRE(ld32(m, kRingTags + o) == 0);  // no DMA tag written
    run(m, &call_mpeg_create, {kWork, 0, 0, 0}, 2);
    CHECK(svc.decoder(kMpegRec) != nullptr);
    st32(m, kWork + 12, 640);
    st32(m, kWork + 16, 368);
    st32(m, kHandle + 56, 2);  // RGB32
    st32(m, kFrame + 32, kOut);

    std::size_t fed = 0, pic = 0, calls = 0;
    u32 seed = 10;
    bool ended = false;
    while (!ended && calls < 400) {
        // feed whole 2,018-byte chunks while they fit (the SFD server's feed, faithful)
        for (;;) {
            const std::size_t n = std::min<std::size_t>(2018, es.video.size() - fed);
            if (n == 0) break;
            std::memcpy(m.at(kChunk), es.video.data() + fed, n);
            if (run(m, &gen::fn_sub_594EC8_00594ec8, {kVibuf, kChunk, n, 0}, ++seed).v0 == 0) break;
            fed += n;
        }
        // the picture call as sub_595390 makes it: restart, flush, in-decode mark, the picture, stop
        run(m, &gen::fn_sub_5947A8_005947a8, {kVibuf, 0, 0, 0}, ++seed);
        CHECK(ld32(m, kVibuf + 68) == 1);
        run(m, &gen::fn_sub_5944A8_005944a8, {kVibuf, 0, 0, 0}, ++seed);
        // the record's invariants: queued sectors end where the service's queue end is
        CHECK((ld32(m, kVibuf + 12) + ld32(m, kVibuf + 16)) % 256 == (svc.ring_queue_end(kVibuf) / 2048) % 256);
        st32(m, kWork + 4412, 1);
        const u64 cost = run(m, &call_get_picture, {kWork, kFrame, kHandle, 0}, ++seed).v0;
        st32(m, kWork + 4412, 0);
        run(m, &gen::fn_sub_5946A8_005946a8, {kVibuf, 0, 0, 0}, ++seed);
        CHECK(ld32(m, kVibuf + 68) == 0);
        ++calls;
        const u32 shown = svc.decoder(kMpegRec)->frames_shown();
        if (shown > pic) {
            REQUIRE(pic < ref.size());
            CHECK(nm::fnv1a64(m.at(kOut), 920u * 1024u) == ref[pic]);
            CHECK(ld32(m, kMpegRec + 0) == 640);
            CHECK(ld32(m, kMpegRec + 4) == 368);
            CHECK(ld32(m, kMpegRec + 8) == pic);  // frameCount: the shown picture's number
            CHECK(cost > 100000);                  // the faithful call's modelled time
            pic = shown;
        }
        ended = svc.decoder(kMpegRec)->ended();
    }
    CHECK(pic == ref.size());
    CHECK(fed == es.video.size());
    // the stream's last bytes lay in the ring's unqueued part: CRI's starvation callback path fed the end code
    CHECK(ld32(m, kWork + 4416) == 1);
    CHECK(svc.stats().errors == 0);
    // nothing reached the IPU or the DMAC
    for (const auto& a : m.hooks.bus_.log) {
        INFO("hardware access at 0x" << std::hex << a.pa);
        CHECK(false);
    }
    run(m, &gen::fn_sub_594AC0_00594ac0, {kVibuf, 0, 0, 0}, ++seed);
    CHECK(svc.ring_queue_end(kVibuf) == 0);  // closed
}

#endif  // P3FES_GAME_HAVE_GENERATED
