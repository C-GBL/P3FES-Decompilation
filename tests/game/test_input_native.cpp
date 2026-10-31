// Modernize layer 2 (docs/MODERNIZE_PLAN.md §3, ADR-0017): the native branches of the game's pad wrapper
// (game/include/p3fes/game/input_native.h) with the host's pad (runtime/native/input/native_pad.h) installed:
//   - H_Pad_Init opens both ports on the service (no libpad, no SIF RPC, the DMA buffers untouched);
//   - H_Pad_UpdateAll drives H_Pad_UpdateWorkPad's own state machine to its reading state (analog mode, actuators
//     aligned) on the service's answers and fills the work records: buttons, sticks, port 2 unplugged then plugged;
//   - the game's actuator words reach the rumble sink through SetActAlign's map;
//   - without the service the same bodies take the faithful path (the pair tests of test_field8_sys / test_font2 /
//     test_sweep5a cover that byte for byte).
#include "pair_harness.h"
#include "stand_ins.h"

#include "native_pad.h"
#include "p3fes/game/input_native.h"

#include <algorithm>
#include <cstring>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

using namespace p3fes;
using namespace p3fes::game_test;
namespace ni = p3fes::native::input;

#if P3FES_GAME_HAVE_GENERATED

namespace p3fes::recomp_gen {
void fn_H_Pad_Init_00103000(EEContext&);
void fn_H_Pad_UpdateWorkPad_00103110(EEContext&);
void fn_sub_103580_00103580(EEContext&);  // H_Pad_UpdateAll
}  // namespace p3fes::recomp_gen

#define LOAD_ELF_OR_SKIP(m)                                                                                   \
    if (const char* err = (m).load_elf(elf_path())) {                                                         \
        MESSAGE("SKIP: cannot load the ELF (" << std::string(elf_path()) << "): " << std::string(err)        \
                                              << " (set P3FES_ELF)");                                         \
        return;                                                                                               \
    }

namespace {

constexpr u32 kRecord0 = 0x7E09B0u, kRecord1 = 0x7E09E6u;  // 54 bytes per port
constexpr u32 kDmaBuffer0 = 0x7E0840u, kDmaBuffer1 = 0x7E0740u;
constexpr u32 kLibpadRecords = 0x96DD10u;

struct ServiceScope {
    explicit ServiceScope(ni::PadService* s) { ni::g_service = s; }
    ~ServiceScope() { ni::g_service = nullptr; }
};

u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
void st16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }

bool all_zero(Machine& m, u32 va, u32 n) {
    for (u32 i = 0; i < n; ++i)
        if (m.at(va)[i]) return false;
    return true;
}

// One game frame: the VBLANK_START's report, then the frame's H_Pad_UpdateAll.
void frame(Machine& m, ni::NativePad& pad) {
    pad.vblank();
    run(m, &recomp_gen::fn_sub_103580_00103580, {}, 1);
}

}  // namespace

TEST_CASE("game(input_native): H_Pad_Init and H_Pad_UpdateAll with --native input read the host's pad") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    std::memset(m.at(kDmaBuffer1), 0, kDmaBuffer0 + 0x100 - kDmaBuffer1);  // both, port 2 first
    std::memset(m.at(kLibpadRecords), 0, 0x100);
    ni::NativePad pad;
    ServiceScope svc(&pad);

    run(m, &recomp_gen::fn_H_Pad_Init_00103000, {}, 1);
    CHECK(pad.is_open(0));
    CHECK(pad.is_open(1));
    CHECK(all_zero(m, kDmaBuffer1, kDmaBuffer0 + 0x100 - kDmaBuffer1));  // scePadPortOpen did not prepare them
    CHECK(all_zero(m, kLibpadRecords, 0x100));  // nor open libpad's port records
    CHECK(ld16(m, kRecord0 + 8) == 0);  // port
    CHECK(ld16(m, kRecord1 + 8) == 1);
    CHECK(ld16(m, kRecord0 + 4) == 3);  // wanted: analog, locked

    // The state machine: 0 -> SetMainMode(analog) 1 -> 3 -> InfoAct / SetActAlign 4 -> 5 (reading).
    std::vector<u16> states;
    for (int f = 0; f < 16 && ld16(m, kRecord0 + 2) != 5; ++f) {
        frame(m, pad);
        states.push_back(ld16(m, kRecord0 + 2));
    }
    REQUIRE(ld16(m, kRecord0 + 2) == 5);
    CHECK(pad.mode_id(0) == ni::kModeDualShock);
    CHECK(states.front() == 0);  // no report in the first frame (the faithful latency)
    CHECK(std::find(states.begin(), states.end(), 1) != states.end());
    CHECK(std::find(states.begin(), states.end(), 3) != states.end());
    CHECK(std::find(states.begin(), states.end(), 4) != states.end());
    CHECK(ld16(m, kRecord1 + 2) == 0);  // port 2: nothing plugged in

    // Buttons and sticks: handed in at a VBLANK_START, in the report of the next one.
    ni::PadState in;
    in.buttons = 0x4000 | 0x0010;  // Cross, Up
    in.lx = 0x00;
    in.ly = 0xFF;
    in.rx = 0x40;
    in.ry = 0xC0;
    pad.set_input(0, in);
    frame(m, pad);
    frame(m, pad);
    // held (+12): the pressed mask byte-swapped (~data[2] << 8 | ~data[3]); sticks +30 lx, +31 ly, +32 rx, +33 ry
    CHECK(ld16(m, kRecord0 + 12) == 0x1040);
    CHECK(m.at(kRecord0 + 30)[0] == 0x00);
    CHECK(m.at(kRecord0 + 31)[0] == 0xFF);
    CHECK(m.at(kRecord0 + 32)[0] == 0x40);
    CHECK(m.at(kRecord0 + 33)[0] == 0xC0);
    CHECK(m.at(0x7E0701)[0] == ni::kModeDualShock);  // the read buffer: the report's data

    // Releasing everything.
    pad.set_input(0, ni::PadState{});
    frame(m, pad);
    frame(m, pad);
    CHECK(ld16(m, kRecord0 + 12) == 0);
    CHECK(m.at(kRecord0 + 30)[0] == 0x80);

    // Port 2 plugged in: its own record walks the same states and reads its own pad.
    ni::PadState two;
    two.buttons = 0x2000;  // Circle
    pad.set_input(1, two);
    for (int f = 0; f < 16 && ld16(m, kRecord1 + 2) != 5; ++f) frame(m, pad);
    REQUIRE(ld16(m, kRecord1 + 2) == 5);
    frame(m, pad);
    // H_Pad_UpdateAll clears port 2's held word and centres its sticks after every update: its record's +12 / +30..33
    // are the shared block's frame-edge words 0x7E09F2.. and analogue bytes 0x7E0A04.. (only port 1 reaches the game).
    CHECK(ld16(m, kRecord1 + 12) == 0);
    CHECK(m.at(kRecord1 + 30)[0] == 0x80);
    CHECK(m.at(0x7E0703)[0] == static_cast<u8>(~0x20));  // but it was read: Circle in the read buffer
    // H_Pad_UpdateWorkPad alone shows the read in the record.
    pad.vblank();
    run(m, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, Args{kRecord1, 0, 0, 0}, 1);
    CHECK(ld16(m, kRecord1 + 12) == 0x0020);  // Circle 0x2000, byte-swapped
    CHECK(ld16(m, kRecord0 + 12) == 0);

    // Port 1 unplugged: back to state 0, the record cleared and centred.
    ni::PadState off;
    off.connected = false;
    pad.set_input(0, off);
    frame(m, pad);
    frame(m, pad);
    CHECK(ld16(m, kRecord0 + 2) == 0);
    CHECK(ld16(m, kRecord0 + 12) == 0);
    CHECK(m.at(kRecord0 + 30)[0] == 0x80);
}

TEST_CASE("game(input_native): the game's actuator words reach the rumble sink through SetActAlign's map") {
    Machine m;
    LOAD_ELF_OR_SKIP(m);
    ni::NativePad pad;
    std::vector<ni::Rumble> sent;
    pad.set_rumble_sink([&sent](u32 port, ni::Rumble r) {
        if (port == 0) sent.push_back(r);
    });
    ServiceScope svc(&pad);
    run(m, &recomp_gen::fn_H_Pad_Init_00103000, {}, 1);
    const Args rec0{kRecord0, 0, 0, 0};
    for (int f = 0; f < 16 && ld16(m, kRecord0 + 2) != 5; ++f) {
        pad.vblank();
        run(m, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, rec0, 1);
    }
    REQUIRE(ld16(m, kRecord0 + 2) == 5);
    pad.vblank();
    run(m, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, rec0, 1);  // the first read sends the motors' state once
    const std::size_t base = sent.size();
    st16(m, kRecord0 + 46, 1);    // small motor on (0x7E09DE)
    st16(m, kRecord0 + 48, 200);  // large motor (0x7E09E0)
    pad.vblank();
    run(m, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, rec0, 1);
    REQUIRE(sent.size() == base + 1);
    CHECK(sent.back().small_motor == 1);
    CHECK(sent.back().large_motor == 200);
    pad.vblank();
    run(m, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, rec0, 1);
    CHECK(sent.size() == base + 1);  // unchanged values are not sent again
    st16(m, kRecord0 + 46, 0);
    st16(m, kRecord0 + 48, 0);
    pad.vblank();
    run(m, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, rec0, 1);
    REQUIRE(sent.size() == base + 2);
    CHECK(sent.back().small_motor == 0);
    CHECK(sent.back().large_motor == 0);
}

#endif  // P3FES_GAME_HAVE_GENERATED
