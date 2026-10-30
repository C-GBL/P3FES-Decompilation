// Phase 5 pair tests for the game-side draw layer (game/src/render/draw_layer.cpp): the camera passes and the Im2D
// builders against their recompiled bodies, on identical guest machines built from random worlds (the main camera,
// the kwlnRoot fog colour, the fade state, the cursor work, the battle work records).
//
// The comparison is stricter than pair_harness.h's: these functions call RenderWare with their frames live on the
// stack, so per call this file compares
//   * the WHOLE main RAM after the run (dead stack included: the hand versions write the original prologue spills
//     and keep the vertex arrays at the original frame offsets),
//   * every register at the end (all 128-bit GPRs, the FPRs, ACC, FCR31, HI/LO), the cycles and the check points,
//   * and a trace of every check point (rt::check_events, i.e. every callee entry and every back-edge): the cycles,
//     $sp and the s-registers always, and at every check that is not the function's own (callee entries and their
//     loops) all GPRs and FPRs -- so every call is made with the same arguments, the same $ra, the same caller-saved
//     registers and the same stack.
// RenderWare's device pointers (RwRenderStateSet/Get, the Im2D pointers, the camera's begin/end and the clear device
// call) are pointed at small recompiled stand-ins: sub_1F1C50 (a non-leaf that spills the $ra it gets below its $sp
// and returns the word at gp-18968, which the worlds use to make RwCameraBeginUpdate succeed or fail), sub_321120
// (stores $a0 at gp-25288) and sub_1A8910 (stores 0 at $a0). The battle draw callees of btlUpdateDraw3DTask and the
// message draw sub_27A3B0 run their real recompiled bodies on empty battle records.
#include "pair_harness.h"

#include "p3fes/game/draw_layer.h"
#include "p3fes/game/ui.h"
#include "p3fes/rt_hooks.h"

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
#define P3FES_DECL_PAIR(name) \
    void name(EEContext&);    \
    void name##__recomp(EEContext&);
P3FES_DECL_PAIR(fn_kwlnRootUpdate2DDrawEndTask_00198b20)
P3FES_DECL_PAIR(fn_kwlnRootUpdate3DOn2DZClearTask_00198c10)
P3FES_DECL_PAIR(fn_kwlnRootUpdate3DOn2DDrawBeginTask_00198c60)
P3FES_DECL_PAIR(fn_kwlnRootUpdate3DOn2DDrawEndTask_00198d20)
P3FES_DECL_PAIR(fn_kwlnRootUpdateEtcDrawBeginTask_00198e90)
P3FES_DECL_PAIR(fn_kwlnRootUpdateDrawEndTask_00198fd0)
P3FES_DECL_PAIR(fn_K_SPipe_Update3DDrwBeginTask_00199520)
P3FES_DECL_PAIR(fn_K_SPipe_Update3DDrwEndTask_001995f0)
P3FES_DECL_PAIR(fn_kwlnRootUpdateShadowNodeCameraTask_00199740)
P3FES_DECL_PAIR(fn_btlDrawMessagePass_0027b310)
P3FES_DECL_PAIR(fn_btlUpdateDraw3DTask_0027ccf0)
P3FES_DECL_PAIR(fn_H_MoonIcon_UpdateTask_00187be0)
P3FES_DECL_PAIR(fn_H_Cursor_UpdateDrawTask_00100230)
P3FES_DECL_PAIR(fn_H_Fade_DrawBlue_001075b0)
P3FES_DECL_PAIR(fn_H_Fade_DrawWhite_001078a0)
P3FES_DECL_PAIR(fn_H_Fade_DrawColour_001081e0)
P3FES_DECL_PAIR(fn_sub_126710_00126710)
P3FES_DECL_PAIR(fn_dbgDrawRect_00395570)
P3FES_DECL_PAIR(fn_drawIm2DIndexedTriList_002699d0)
P3FES_DECL_PAIR(fn_sub_269F50_00269f50)
P3FES_DECL_PAIR(fn_btlDrawTexturedQuad_002bc9c0)
P3FES_DECL_PAIR(fn_sub_422670_00422670)
P3FES_DECL_PAIR(fn_drawGradientQuad_001997e0)
P3FES_DECL_PAIR(fn_frFontRasterDrawGlyph_003b38f0)
P3FES_DECL_PAIR(fn_dbgPrintDrawScreen_00104420)
P3FES_DECL_PAIR(fn_dbgPrintDrawStrings_00104710)
P3FES_DECL_PAIR(fn_dbgPrintDrawWindow_001053f0)
P3FES_DECL_PAIR(fn_H_MoonIcon_Draw_001875f0)
#undef P3FES_DECL_PAIR
}  // namespace p3fes::recomp_gen

namespace {

namespace draw = p3fes::game::draw;

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

#define PAIR(name) &recomp_gen::name, &recomp_gen::name##__recomp

constexpr u32 kGpBase = 0x007D2CF0u;
constexpr u32 gpv(s32 off) { return kGpBase + static_cast<u32>(off); }
constexpr u64 kOwnRa = 0x00100008u;  // pair_harness: the $ra every run starts with

// Stand-ins for RenderWare's device calls (recompiled functions reached through the dispatch table).
constexpr u32 kStubNonLeaf = 0x1F1C50u;  // spills $ra in a 16-byte frame, returns *(gp-18968)
constexpr u32 kStubStoreA0 = 0x321120u;  // *(s16*)(gp-25288) = $a0
constexpr u32 kStubZeroAt = 0x1A8910u;   // *(u32*)$a0 = 0
constexpr s32 kGpStubResult = -18968;

// Arena layout.
constexpr u32 kCamera = kArena;            // RwCamera: +0x18 begin, +0x1C end, +0x80 near plane
constexpr u32 kWork = kArena + 0x200;      // task work records
constexpr u32 kTask = kArena + 0x100;      // a kwln task record (+0x3C = work)
constexpr u32 kBattle = kArena + 0x800;    // the battle work at gp-18692 (empty lists, +12 bit 2)
constexpr u32 kDeadTask = kArena + 0xC00;  // a zeroed record: kwlnTaskDestroyWithHierarchy rejects it (state 0)
constexpr u32 kObj = kArena + 0x1000;      // dbgDrawRect's object (+1648..+1656)

// --- the check-point spy -----------------------------------------------------------------------------------------
class Spy final : public RtHooks {
public:
    struct Rec {
        u128 gpr[32];
        u32 fpr[32];
        u64 cycles;
        u32 acc;
        u32 own;  // a check of the function under test itself ($ra still the run's): entry and back-edges
    };
    rt_test::TestHooks inner;
    std::vector<Rec> log;

    void syscall(EEContext& ctx, u32 pc) override { inner.syscall(ctx, pc); }
    void check_events(EEContext& ctx) override {
        inner.check_events(ctx);
        Rec r;
        r.cycles = ctx.cycles;
        r.own = ctx.gpr[GPR_RA].u64[0] == kOwnRa;
        std::memcpy(r.gpr, ctx.gpr, sizeof r.gpr);
        std::memcpy(r.fpr, ctx.fpr, sizeof r.fpr);
        r.acc = ctx.acc;
        log.push_back(r);
    }
    hle::HwBus& bus() override { return inner.bus(); }
    void trap(EEContext& ctx, u32 pc, u32 kind, u32 code) override { inner.trap(ctx, pc, kind, code); }
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { inner.fatal(ctx, pc, what); }
    void vu_control_write(EEContext& ctx, u32 reg, u32 value) override { inner.vu_control_write(ctx, reg, value); }
};

bool same128(const u128& a, const u128& b) { return a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]; }

struct Run {
    EEContext end;
    std::vector<Spy::Rec> log;
    int checks = 0;
};

// The world a pair starts from: the RAM image (taken once) and the register setup.
struct World {
    Machine& m;
    std::vector<u8> base;  // main RAM before the run
    explicit World(Machine& mm) : m(mm) {}
    void snapshot() { base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize); }
    void restore() { std::memcpy(m.mem.main_ram(), base.data(), base.size()); }
};

using Setup = void (*)(EEContext&, std::mt19937&);

using Fprs = std::vector<std::pair<unsigned, u32>>;
using Gprs = std::vector<std::pair<unsigned, u64>>;

Run run_once(Machine& m, Fn fn, const Args& args, u32 seed, const Fprs& fprs, const Gprs& gprs) {
    Spy spy;
    rt_test::HooksScope scope{&spy};
    rt::bind_context(&m.ctx);
    std::mt19937 rng{seed};
    m.fresh_context(args, rng);
    for (unsigned i = 0; i < 32; ++i) m.ctx.fpr[i] = rng();
    for (const auto& [r, v] : fprs) m.ctx.fpr[r] = v;
    for (const auto& [r, v] : gprs) m.ctx.gpr[r].u64[0] = v;
    fn(m.ctx);
    Run r;
    r.end = m.ctx;
    r.log = std::move(spy.log);
    r.checks = spy.inner.checks;
    return r;
}

// Runs hand and recomp from the world's RAM and compares everything (header comment).
void pair(World& w, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const Fprs& fprs = {},
          const Gprs& gprs = {}) {
    INFO(what << " seed " << seed);
    w.restore();
    // The whole main RAM through a PairRange (write_tracker.h): restored to the world's RAM between the bodies and
    // compared after them, copying only the pages written (three more 32 MiB copies and a compare per pair before).
    PairRange ram(w.m.mem.main_ram(), w.m.mem.main_ram() + EEMemory::kMainRamSize);
    const Run h = run_once(w.m, hand, args, seed, fprs, gprs);
    ram.between();
    const Run r = run_once(w.m, recomp, args, seed, fprs, gprs);
    // Memory: the whole main RAM.
    const u8* b = w.m.mem.main_ram();
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("first differing byte at 0x" << std::hex << first << " hand " << unsigned(ram.first_body_byte(first)) << " recomp "
                                          << unsigned(b[first]));
        CHECK(false);
    }
    // Registers at the end.
    CHECK(h.end.cycles == r.end.cycles);
    CHECK(h.checks == r.checks);
    for (unsigned i = 0; i < 32; ++i) {
        INFO("gpr " << i);
        CHECK(same128(h.end.gpr[i], r.end.gpr[i]));
    }
    for (unsigned i = 0; i < 32; ++i) {
        INFO("fpr " << i);
        CHECK(h.end.fpr[i] == r.end.fpr[i]);
    }
    CHECK(h.end.acc == r.end.acc);
    CHECK(h.end.fcr31 == r.end.fcr31);
    CHECK(same128(h.end.hi, r.end.hi));
    CHECK(same128(h.end.lo, r.end.lo));
    // The check-point trace.
    REQUIRE(h.log.size() == r.log.size());
    for (std::size_t k = 0; k < h.log.size(); ++k) {
        const Spy::Rec& x = h.log[k];
        const Spy::Rec& y = r.log[k];
        INFO("check point " << k);
        CHECK(x.cycles == y.cycles);
        CHECK(x.own == y.own);
        const unsigned always[] = {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_GP, GPR_SP, GPR_FP, GPR_RA};
        for (unsigned g : always) {
            INFO("gpr " << g);
            CHECK(same128(x.gpr[g], y.gpr[g]));
        }
        {
            for (unsigned g = 0; g < 32; ++g) {
                INFO("gpr (low 64) " << g);
                CHECK(x.gpr[g].u64[0] == y.gpr[g].u64[0]);
            }
            for (unsigned f = 0; f < 32; ++f) {
                INFO("fpr " << f);
                CHECK(x.fpr[f] == y.fpr[f]);
            }
        }
    }
}

void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
u32 f32bits(float f) {
    u32 v;
    std::memcpy(&v, &f, 4);
    return v;
}
u32 pick(std::mt19937& rng, std::initializer_list<u32> xs) { return *(xs.begin() + rng() % xs.size()); }
bool chance(std::mt19937& rng, unsigned percent) { return rng() % 100 < percent; }
void fill_random(Machine& m, u32 va, u32 len, std::mt19937& rng) {
    for (u32 i = 0; i < len; ++i) m.at(va)[i] = static_cast<u8>(rng());
}
u32 stub(std::mt19937& rng) { return pick(rng, {kStubNonLeaf, kStubNonLeaf, kStubStoreA0}); }
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100000) / 100000.0f; }

// The RenderWare side every draw function sees: the main camera, the device pointers, the stand-ins' state.
void common_world(Machine& m, std::mt19937& rng, bool begin_ok) {
    std::memset(m.at(kArena), 0, kArenaSize);
    std::memset(m.at(kSp - 0x2000), 0, 0x2000);
    w32(m, gpv(draw::kGpRootCamera), kCamera);
    w32(m, kCamera + draw::kCameraBeginUpdate, stub(rng));
    w32(m, kCamera + 0x1C, chance(rng, 25) ? kStubZeroAt : stub(rng));  // RwCameraEndUpdate(camera) -> *camera = 0
    w32(m, kCamera + draw::kCameraNearPlane, f32bits(frand(rng, 0.05f, 20.0f)));
    w32(m, gpv(kGpStubResult), begin_ok ? kCamera : 0);
    w32(m, draw::kPfnRenderStateSet, stub(rng));
    w32(m, draw::kPfnRenderStateGet, stub(rng));
    w32(m, draw::kPfnIm2DRenderTriangle, stub(rng));
    w32(m, draw::kPfnIm2DRenderPrimitive, stub(rng));
    w32(m, draw::kPfnIm2DRenderIndexedPrimitive, stub(rng));
    w32(m, 0x96010Cu, stub(rng));  // the camera clear device call of RwCameraClear
    w32(m, draw::kIm2DNearScreenZ, f32bits(frand(rng, -100.0f, 70000.0f)));
    // kwlnRoot fog.
    w32(m, gpv(draw::kGpFogEnabled), pick(rng, {0u, 1u, 1u, 2u}));
    for (s32 off : {draw::kGpFogRed, draw::kGpFogGreen, draw::kGpFogBlue, draw::kGpFogAlpha}) w32(m, gpv(off), rng());
    // Battle records (btlUpdateDraw3DTask's callees, the message pass): empty lists, effects off.
    w32(m, gpv(-18692), kBattle);
    w32(m, kBattle + 12, 4);
    w32(m, gpv(-18716), kArena + 0x900);  // sub_27A3B0's work: bit 0 clear
}

}  // namespace

TEST_CASE("render_game: camera passes (Begin / End / Z clear / fog states) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns fns[] = {
        {PAIR(fn_kwlnRootUpdate2DDrawEndTask_00198b20), "kwlnRootUpdate2DDrawEndTask"},
        {PAIR(fn_kwlnRootUpdate3DOn2DZClearTask_00198c10), "kwlnRootUpdate3DOn2DZClearTask 3D on 2D Zclear"},
        {PAIR(fn_kwlnRootUpdate3DOn2DDrawBeginTask_00198c60), "kwlnRootUpdate3DOn2DDrawBeginTask 3D on 2D Draw Begin"},
        {PAIR(fn_kwlnRootUpdate3DOn2DDrawEndTask_00198d20), "kwlnRootUpdate3DOn2DDrawEndTask 3D on 2D Draw End"},
        {PAIR(fn_kwlnRootUpdateEtcDrawBeginTask_00198e90), "kwlnRootUpdateEtcDrawBeginTask etc Draw Begin"},
        {PAIR(fn_kwlnRootUpdateDrawEndTask_00198fd0), "kwlnRootUpdateDrawEndTask"},
        {PAIR(fn_K_SPipe_Update3DDrwBeginTask_00199520), "K_SPipe_Update3DDrwBeginTask 3D Draw Begin"},
        {PAIR(fn_K_SPipe_Update3DDrwEndTask_001995f0), "K_SPipe_Update3DDrwEndTask 3D Draw End"},
        {PAIR(fn_kwlnRootUpdateShadowNodeCameraTask_00199740), "kwlnRootUpdateShadowNodeCameraTask Shadow Node Camera"},
        {PAIR(fn_btlDrawMessagePass_0027b310), "btlDrawMessagePass battle message pass"},
        {PAIR(fn_btlUpdateDraw3DTask_0027ccf0), "btlUpdateDraw3DTask battle draw 3d"},
    };
    std::mt19937 rng{2026u};
    int pairs = 0;
    for (const Fns& f : fns) {
        for (int i = 0; i < 24; ++i) {
            common_world(m, rng, i % 3 != 0);
            // The battle message work of btlDrawMessagePass: null (K_Assert continues and reads address 0), bit 0 clear or set.
            const u32 msg = pick(rng, {0u, kArena + 0xA00u, kArena + 0xA00u});
            w32(m, gpv(-18708), msg);
            if (msg) w32(m, msg, rng() & ~(chance(rng, 50) ? 1u : 0u));
            w.snapshot();
            pair(w, f.hand, f.recomp, {sx(kTask), 0, 0, 0}, 100 + i, f.name);
            ++pairs;
        }
    }
    CHECK(pairs == 11 * 24);
}

TEST_CASE("render_game: the day HUD moon task (H_MoonIcon_UpdateTask) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{187u};
    constexpr u32 kFlag5153 = 0x83A21Cu + 161 * 4;  // datGetFlag(5153): bit 1
    for (int i = 0; i < 60; ++i) {
        common_world(m, rng, i % 5 != 0);
        w32(m, kTask + 0x3C, kWork);
        fill_random(m, kWork, 0x20, rng);
        // States 0 (init), 1 (wait: the counter around 0), 2 with flag 5153 set (alpha reset), unknown states.
        // State 2 without the flag and state 3 draw through H_MoonIcon_Draw, whose RenderWare matrix callees are not
        // part of this test build (the battle and dorm gates run them).
        const u32 state = pick(rng, {0u, 1u, 1u, 2u, 4u, 0xFFFFFFFFu});
        w32(m, kWork + 0, state);
        if (state == 1) w32(m, kWork + 4, pick(rng, {0u, 1u, 2u, 0xFFFFFFFFu, 10u}));
        u32 flags;
        std::memcpy(&flags, m.at(kFlag5153), 4);
        w32(m, kFlag5153, flags | 2u);
        w.snapshot();
        pair(w, PAIR(fn_H_MoonIcon_UpdateTask_00187be0), {sx(kTask), 0, 0, 0}, 300 + i, "H_MoonIcon_UpdateTask");
    }
}

TEST_CASE("render_game: H_Cursor_UpdateDrawTask matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{230u};
    for (int i = 0; i < 80; ++i) {
        common_world(m, rng, true);
        w32(m, kTask + 0x3C, kWork);
        fill_random(m, kWork, sizeof(game::HCursorWork), rng);
        const u32 work = kWork;
        w32(m, work + offsetof(game::HCursorWork, should_draw), chance(rng, 85) ? pick(rng, {1u, 2u, 0x80000000u}) : 0u);
        w16(m, work + offsetof(game::HCursorWork, state), static_cast<u16>(pick(rng, {0u, 0u, 1u, 1u, 2u, 3u, 0xFFFFu})));
        w32(m, work + offsetof(game::HCursorWork, pos_x), f32bits(frand(rng, -50.0f, 700.0f)));
        w32(m, work + offsetof(game::HCursorWork, pos_y), f32bits(frand(rng, -50.0f, 500.0f)));
        w32(m, work + offsetof(game::HCursorWork, rect) + 8, rng() % 600);
        w32(m, work + offsetof(game::HCursorWork, rect) + 12, chance(rng, 90) ? rng() % 400 : rng());
        w32(m, work + offsetof(game::HCursorWork, z_offset), f32bits(frand(rng, -10.0f, 1000.0f)));
        w.snapshot();
        pair(w, PAIR(fn_H_Cursor_UpdateDrawTask_00100230), {sx(kTask), 0, 0, 0}, 500 + i, "H_Cursor_UpdateDrawTask");
    }
}

TEST_CASE("render_game: the three screen fades match their recompiled bodies (state machine, alpha, quad)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    struct Fns {
        Fn hand, recomp;
        const char* name;
    };
    const Fns fns[] = {
        {PAIR(fn_H_Fade_DrawBlue_001075b0), "H_Fade_DrawBlue blue fade"},
        {PAIR(fn_H_Fade_DrawWhite_001078a0), "H_Fade_DrawWhite white fade"},
        {PAIR(fn_H_Fade_DrawColour_001081e0), "H_Fade_DrawColour colour fade"},
    };
    std::mt19937 rng{1075u};
    for (const Fns& f : fns) {
        for (int i = 0; i < 70; ++i) {
            common_world(m, rng, true);
            w16(m, gpv(draw::kGpFadeState), static_cast<u16>(i < 42 ? i % 7 : rng() % 7));
            const u16 duration = static_cast<u16>(pick(rng, {30u, 1u, 60u, 0u, 0xFFF0u, 15u}));
            w16(m, gpv(draw::kGpFadeDuration), duration);
            w16(m, gpv(draw::kGpFadeCounter), static_cast<u16>(chance(rng, 50) ? duration - 1 + rng() % 3 : rng() % 70));
            w32(m, gpv(draw::kGpFadeActive), rng());
            w32(m, gpv(draw::kGpFadeTaskA), pick(rng, {0u, kDeadTask, 0xFFFFFFFFu}));
            w32(m, gpv(draw::kGpFadeTaskB), pick(rng, {0u, kDeadTask, 0xFFFFFFFFu}));
            for (s32 off : {draw::kGpFadeColourR, draw::kGpFadeColourG, draw::kGpFadeColourB}) w32(m, gpv(off), rng());
            w.snapshot();
            pair(w, f.hand, f.recomp, {0, 0, 0, 0}, 700 + i, f.name);
        }
    }
}

TEST_CASE("render_game: sub_126710 (two textured strips) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{126u};
    for (int i = 0; i < 40; ++i) {
        common_world(m, rng, true);
        w32(m, kWork, rng());  // the raster pointer the strips use
        const u64 xy = (static_cast<u64>(f32bits(frand(rng, -600.0f, 600.0f))) << 32) | f32bits(frand(rng, -300.0f, 700.0f));
        w.snapshot();
        pair(w, PAIR(fn_sub_126710_00126710), {sx(kWork), xy, sx(rng() % 300), sx(rng())}, 900 + i, "sub_126710",
             {{12, f32bits(frand(rng, -5.0f, 500.0f))}});
    }
}

TEST_CASE("render_game: the debug rectangle, the indexed mesh and the battle panel match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{395u};
    for (int i = 0; i < 30; ++i) {
        common_world(m, rng, true);
        w32(m, kObj + 1648, chance(rng, 75) ? rng() | 1u : 0u);
        w32(m, kObj + 1652, rng() % 2000 - 1000);
        w32(m, kObj + 1656, chance(rng, 90) ? rng() % 2000 - 1000 : rng());
        w.snapshot();
        pair(w, PAIR(fn_dbgDrawRect_00395570), {sx(kObj), 0, 0, 0}, 1100 + i, "dbgDrawRect");
    }
    for (int i = 0; i < 20; ++i) {
        common_world(m, rng, true);
        fill_random(m, kWork, 24, rng);
        w.snapshot();
        pair(w, PAIR(fn_drawIm2DIndexedTriList_002699d0), {sx(kWork), 0, 0, 0}, 1200 + i, "drawIm2DIndexedTriList");
    }
    for (int i = 0; i < 40; ++i) {
        common_world(m, rng, true);
        const u32 panel = chance(rng, 85) ? kWork : 0u;
        w32(m, gpv(-18752), panel);
        if (panel) {
            w32(m, panel, rng() | (chance(rng, 80) ? 1u : 0u));
            w32(m, panel + 4, pick(rng, {0u, 1u, 0u, 1u, 2u, 0x80000000u}));
        }
        w32(m, gpv(-18780), chance(rng, 90) ? kArena + 0x1800 : 0u);  // sub_266E50's raster table (+76 + 4 * kind)
        fill_random(m, kArena + 0x1800, 0x60, rng);
        w.snapshot();
        pair(w, PAIR(fn_sub_269F50_00269f50), {0, 0, 0, 0}, 1300 + i, "sub_269F50");
    }
}

TEST_CASE("render_game: the textured quad, the second cursor task and the gradient quad match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{2709u};
    for (int i = 0; i < 50; ++i) {
        common_world(m, rng, true);
        const u32 raster = chance(rng, 80) ? kWork : 0u;
        w32(m, kWork + 12, pick(rng, {64u, 128u, 256u, 0u, rng()}));
        w32(m, kWork + 16, pick(rng, {32u, 128u, 512u, 0u, rng()}));
        w.snapshot();
        // x, y, w, h, u, v in $f12..$f17 (every other FPR random; a few runs keep random bits there too).
        Fprs fprs;
        if (i % 8 != 7) {
            fprs = {{12, f32bits(frand(rng, -100.0f, 600.0f))}, {13, f32bits(frand(rng, -100.0f, 450.0f))},
                    {14, f32bits(frand(rng, 0.0f, 300.0f))},    {15, f32bits(frand(rng, 0.0f, 300.0f))},
                    {16, f32bits(frand(rng, 0.0f, 256.0f))},    {17, f32bits(frand(rng, 0.0f, 256.0f))}};
        }
        pair(w, PAIR(fn_btlDrawTexturedQuad_002bc9c0), {sx(rng()), sx(raster), 0, 0}, 1500 + i, "btlDrawTexturedQuad", fprs);
    }
    for (int i = 0; i < 60; ++i) {
        common_world(m, rng, true);
        w32(m, kTask + 0x3C, kWork);
        fill_random(m, kWork, 0x150, rng);
        m.at(kWork + 318)[0] = static_cast<u8>(chance(rng, 20) ? 1 : rng());
        m.at(kWork + 0)[0] = static_cast<u8>(pick(rng, {0u, 0u, 1u, 1u, 2u, 3u, 0xFFu}));
        w32(m, kWork + 296, rng() % 600);
        w32(m, kWork + 300, chance(rng, 90) ? rng() % 400 : rng());
        for (u32 off : {304u, 308u, 312u}) w32(m, kWork + off, f32bits(frand(rng, -50.0f, 700.0f)));
        w.snapshot();
        pair(w, PAIR(fn_sub_422670_00422670), {sx(kTask), 0, 0, 0}, 1600 + i, "sub_422670");
    }
    for (int i = 0; i < 30; ++i) {
        common_world(m, rng, true);
        fill_random(m, kWork, 8, rng);
        w.snapshot();
        const Fprs fprs = {{12, f32bits(frand(rng, 0.0f, 640.0f))}, {13, f32bits(frand(rng, 0.0f, 448.0f))},
                           {14, f32bits(frand(rng, 0.0f, 640.0f))}, {15, f32bits(frand(rng, 0.0f, 448.0f))},
                           {16, f32bits(frand(rng, 0.0f, 70000.0f))}, {17, f32bits(frand(rng, 0.0f, 10.0f))}};
        pair(w, PAIR(fn_drawGradientQuad_001997e0), {sx(kWork), sx(kWork + 4), 0, 0}, 1700 + i, "drawGradientQuad", fprs);
    }
}

TEST_CASE("render_game: frFontRasterDrawGlyph matches its recompiled body (cached glyph slots)") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x3B38F0u};
    // font +28 -> node, node +12 -> slot {+0 flags, +8 s16 code, +20 raster}. The slot holds the code being drawn
    // (frFontCacheGlyph, which refills a slot holding another code, needs the whole font world of test_font.cpp; the
    // dorm and M1 gates draw text through it).
    const u32 font = kWork, node = kWork + 0x40, slot = kWork + 0x80;
    int drawn = 0;
    for (int i = 0; i < 80; ++i) {
        common_world(m, rng, true);
        fill_random(m, kWork, 0x100, rng);
        const u16 code = static_cast<u16>(chance(rng, 50) ? 0x21 + rng() % 0x5E : rng() % 0x8000);
        w32(m, font + 28, chance(rng, 95) ? node : 0u);
        w32(m, node + 12, slot);
        w32(m, 0 + 12, slot);  // a null font+28 reads its node at address 0 (after the K_Assert that continues)
        w16(m, slot + 8, code);
        const u64 rgba = sx(chance(rng, 15) ? rng() & ~0xFFu : rng());
        drawn += (rgba & 0xFF) != 0;
        const u64 gw = chance(rng, 85) ? rng() % 64 : sx(rng());
        const u64 gh = chance(rng, 85) ? rng() % 64 : sx(rng());
        w.snapshot();
        pair(w, PAIR(fn_frFontRasterDrawGlyph_003b38f0), {sx(rng() % 10240), sx(rng() % 3584), sx(font), code}, 1800 + i,
             "frFontRasterDrawGlyph", {{12, f32bits(frand(rng, -10.0f, 100.0f))}},
             {{GPR_T0, gw}, {GPR_T1, gh}, {GPR_T2, rgba}});
    }
    CHECK(drawn > 50);
}

TEST_CASE("render_game: the debug text screen (dbgPrintDrawScreen) matches its recompiled body") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x104420u};
    constexpr u32 kGrid = 0x7E1E30u, kGridSize = 40 * 53;
    for (int i = 0; i < 8; ++i) {
        common_world(m, rng, true);
        // The grid: spaces with a few printable characters, some control bytes and high bytes (atlas wrap).
        const unsigned density = pick(rng, {0u, 2u, 10u, 40u});
        for (u32 k = 0; k < kGridSize; ++k) {
            const u32 r = rng() % 100;
            m.at(kGrid + k)[0] = static_cast<u8>(r < density ? (rng() % 8 ? 0x21 + rng() % 0x5E : rng()) : 0x20);
        }
        w32(m, gpv(-20000), rng());  // the debug font raster
        w32(m, gpv(-20008), 0);      // the two overlays' lists: empty
        w32(m, gpv(-20016), 0);
        w.snapshot();
        pair(w, PAIR(fn_dbgPrintDrawScreen_00104420), {0, 0, 0, 0}, 1900 + i, "dbgPrintDrawScreen");
    }
}

TEST_CASE("render_game: the debug string list (dbgPrintDrawStrings) and the debug window (dbgPrintDrawWindow) match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x104710u};
    const auto text = [&](u32 va, u32 len) {
        const u32 n = rng() % 4 == 0 ? len : rng() % 24;  // a NUL early, or none at all
        for (u32 k = 0; k < len; ++k) {
            const u32 r = rng() % 10;
            m.at(va + k)[0] = static_cast<u8>(k == n ? 0 : r < 5 ? 0x21 + rng() % 0x5E : r < 8 ? 0x20 : (rng() | 1));
        }
    };
    for (int i = 0; i < 24; ++i) {
        common_world(m, rng, true);
        w32(m, gpv(-20000), rng());
        // Up to three nodes of 0x118 bytes in the arena, depth 0 (2-D) or not (sub_105210's screen z).
        const u32 nodes = rng() % 4;
        u32 head = 0;
        for (u32 n = 0; n < nodes; ++n) {
            const u32 node = kWork + n * 0x120;
            w32(m, node + 0, head);
            head = node;
            w32(m, node + 4, f32bits(frand(rng, 0.0f, 600.0f)));
            w32(m, node + 8, f32bits(frand(rng, 0.0f, 440.0f)));
            w32(m, node + 12, chance(rng, 50) ? 0u : f32bits(frand(rng, 1.0f, 3000.0f)));
            text(node + 16, 256);
            w32(m, node + 272, f32bits(frand(rng, 0.0f, 50.0f)));
            w32(m, node + 276, rng());
        }
        w32(m, gpv(-20008), head);
        w.snapshot();
        pair(w, PAIR(fn_dbgPrintDrawStrings_00104710), {0, 0, 0, 0}, 2000 + i, "dbgPrintDrawStrings");
    }
    for (int i = 0; i < 24; ++i) {
        common_world(m, rng, true);
        w32(m, gpv(-20000), rng());
        w32(m, gpv(-20016), chance(rng, 85) ? 1u : 0u);
        m.at(gpv(-20012))[0] = static_cast<u8>(pick(rng, {0u, 1u, 2u, 3u, 0xFFu}));
        for (u32 l = 0; l < 3; ++l) text(0x7E0A30u + l * 256, 64);
        for (s32 off : {-31328, -31324, -31320, -31316}) w32(m, gpv(off), f32bits(frand(rng, 0.0f, 400.0f)));
        w.snapshot();
        pair(w, PAIR(fn_dbgPrintDrawWindow_001053f0), {0, 0, 0, 0}, 2100 + i, "dbgPrintDrawWindow");
    }
}

// The RenderWare matrix calls of the moon: RwMatrixCreate / RwMatrixDestroy go through the matrix free list's
// alloc / free pointers (0x960188 / 0x96018C), RwV3dTransformPoints through the engine's device table at
// 0x960070 + *(gp-17376) + 12; the worlds point them at stand-ins (the alloc stand-in returns *(gp-18968), a
// 64-byte matrix in the arena). RwMatrixRotateOneMinusCosineSine runs its real recompiled body.
void moon_world(Machine& m, std::mt19937& rng) {
    constexpr u32 kMatrix = kArena + 0x1C00, kDevice = kArena + 0x1E00;
    w32(m, gpv(kGpStubResult), kMatrix);
    w32(m, 0x960188u, kStubNonLeaf);
    w32(m, 0x96018Cu, stub(rng));
    w32(m, gpv(-17432), 0);
    w32(m, gpv(-17376), kDevice - 0x960070u);
    w32(m, kDevice + 12, stub(rng));
}

TEST_CASE("render_game: the day HUD moon draw (H_MoonIcon_Draw) and its task's drawing states match their recompiled bodies") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    LOAD_ELF_OR_SKIP(m);
    World w(m);
    std::mt19937 rng{0x1875F0u};
    for (int i = 0; i < 40; ++i) {
        common_world(m, rng, true);
        moon_world(m, rng);
        const u64 ax = sx(chance(rng, 70) ? rng() % 720 - 360 : rng() % 4000 - 2000);
        const u64 ay = sx(chance(rng, 70) ? rng() % 720 - 360 : rng() % 4000 - 2000);
        w.snapshot();
        pair(w, PAIR(fn_H_MoonIcon_Draw_001875f0), {ax, ay, sx(rng() % 256), 0}, 2200 + i, "H_MoonIcon_Draw");
    }
    // H_MoonIcon_UpdateTask's states 2 (flag 5153 clear: fade in) and 3 (fade out) draw through H_MoonIcon_Draw.
    constexpr u32 kFlag5153 = 0x83A21Cu + 161 * 4;
    for (int i = 0; i < 30; ++i) {
        common_world(m, rng, true);
        moon_world(m, rng);
        // BeginUpdate succeeds: its stand-ins return *(gp-18968) (the matrix area, non-zero) or their own address.
        w32(m, kTask + 0x3C, kWork);
        fill_random(m, kWork, 0x20, rng);
        w32(m, kWork + 0, i % 2 ? 2u : 3u);
        w32(m, kWork + 8, pick(rng, {0u, 20u, 250u, 255u, 10u}));
        w32(m, kWork + 12, rng() % 400);
        w32(m, kWork + 16, rng() % 400);
        u32 flags;
        std::memcpy(&flags, m.at(kFlag5153), 4);
        w32(m, kFlag5153, flags & ~2u);
        w.snapshot();
        pair(w, PAIR(fn_H_MoonIcon_UpdateTask_00187be0), {sx(kTask), 0, 0, 0}, 2300 + i, "H_MoonIcon_UpdateTask drawing");
    }
}

TEST_CASE("render_game: documented rules (22_rendering.md sections 1 and 6)") {
    // The RwIm2DVertex the builders fill is 64 bytes with recipZ at +0x18 and the colour floats at +0x20.
    static_assert(sizeof(draw::Im2DVertex) == 64);
    CHECK(draw::kVtxRecipZ == 0x18);
    CHECK(draw::kVtxA == 0x2C);
    // The kwlnRoot globals: gp-relative, the main camera at 0x7CE0C0 (sub_198590), the fog flag at 0x7CE0D4.
    CHECK(gpv(draw::kGpRootCamera) == 0x7CE0C0u);
    CHECK(gpv(draw::kGpFogEnabled) == 0x7CE0D4u);
    CHECK(gpv(draw::kGpClearColour) == 0x7CE128u);
}

#endif  // P3FES_GAME_HAVE_GENERATED
