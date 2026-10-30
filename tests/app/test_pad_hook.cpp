// The host hook at the production boundary: at each VBLANK_START the kernel runs the SIF service (PADMAN writes that
// vblank's frame) and then GameHost::host_service, which calls feed_pad_input; the state latched at vblank N is in
// PADMAN's frame for N + 1 -- the timing the former P3FES_PAD_SCRIPT block had. The EE side is tests/sif's
// re-enactment of the game's libpad RPC calls.
#include <doctest.h>

#include <map>

#include "../sif/sif_harness.h"
#include "input.h"

using namespace p3fes;  // u8/u16/u32 and app::
using namespace p3fes::test;

namespace {

struct PadRig {
    EeSide e;
    u32 cd = 0;
    static constexpr u32 kBuf0 = 0x00900000;

    PadRig() {
        e.init_rpc();
        cd = e.bind(0x80000100u);
        call({16, 0, 0, 0, 0, 0x782754});  // Init2
        // scePadPortOpen initialises both frames itself (0x511660): counter 0, state EXECCMD, reqState BUSY
        for (u32 f = 0; f < 2; ++f) {
            e.w32(kBuf0 + f * 128 + 88, 0);
            e.mem.write<u8>(kBuf0 + f * 128 + 112, 5);
            e.mem.write<u8>(kBuf0 + f * 128 + 113, 2);
        }
        REQUIRE(load32(call({1, 0, 0, 0, kBuf0}), 12) == 1);  // PortOpen(0, 0, buf)
    }
    std::vector<u8> call(std::initializer_list<u32> w) {
        std::vector<u8> b(128, 0);
        std::size_t i = 0;
        for (u32 x : w) {
            store32(b, i, x);
            i += 4;
        }
        return e.call_sync(cd, 1, b, 128);
    }
    // The newest frame (scePadGetDmaStr 0x511830).
    std::vector<u8> newest() {
        const u32 f0 = e.r32(kBuf0 + 88), f1 = e.r32(kBuf0 + 216);
        return e.read(kBuf0 + (f0 < f1 ? 128u : 0u), 128);
    }
    // ~(data[2] | data[3] << 8) as libpad reads it, once the frame is stable.
    u16 buttons() {
        const auto f = newest();
        REQUIRE(f[112] == 6);
        return static_cast<u16>(~(f[2] | (f[3] << 8)));
    }
    // One VBLANK_START as the kernel runs it: the time base advances, then the device services in registration
    // order -- the SIF service, then the host's (feed_pad_input).
    void vblank() {
        e.bus.vblank();
        e.sif.service();
        app::feed_pad_input(e.bus.tb.vblanks, e.sif.iop());
    }
};

} // namespace

TEST_CASE("feed_pad_input after SifHle::service: the press scripted for vblank N is in PADMAN's frames from N + 1") {
    PadRig rig;
    app::PadFeed feed;
    std::vector<app::ScriptPress> s;
    std::string err;
    REQUIRE(app::parse_input_script("6:cross:2,9:start+up:1", s, err));
    feed.add_script(s);
    app::set_active_pad_feed(&feed);
    std::map<std::uint64_t, u16> frame_buttons;
    for (int i = 0; i < 12; ++i) {
        rig.vblank();
        const std::uint64_t v = rig.e.bus.tb.vblanks;
        if (v < 2) continue;  // PADMAN's first frame after PortOpen is not the newest one yet
        frame_buttons[v] = rig.buttons();
        // A SIF syscall later in the same vblank runs the services again: nothing changes.
        PadInput other;
        other.buttons = pad_button::kSquare;
        feed.set_live(other);
        rig.e.sif.service();
        app::feed_pad_input(v, rig.e.sif.iop());
        CHECK(rig.buttons() == frame_buttons[v]);
        feed.set_live(PadInput{});
    }
    app::set_active_pad_feed(nullptr);
    CHECK(frame_buttons[6] == 0);
    CHECK(frame_buttons[7] == pad_button::kCross);
    CHECK(frame_buttons[8] == pad_button::kCross);
    CHECK(frame_buttons[9] == 0);
    CHECK(frame_buttons[10] == (pad_button::kStart | pad_button::kUp));
    CHECK(frame_buttons[11] == 0);
    CHECK(feed.current_vblank() == 12);
}

TEST_CASE("feed_pad_input without an active feed leaves PADMAN's own state alone") {
    PadRig rig;
    PadInput in;
    in.buttons = pad_button::kTriangle;
    rig.e.sif.iop().set_pad_input(0, in);
    app::set_active_pad_feed(nullptr);
    rig.vblank();
    rig.vblank();
    rig.vblank();
    CHECK(rig.buttons() == pad_button::kTriangle);
}
