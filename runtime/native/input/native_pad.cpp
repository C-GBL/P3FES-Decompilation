// Modernize layer 2: the host's DUALSHOCK 2 for the game's pad wrapper (native_pad.h).
#include "native_pad.h"

#include <algorithm>

#include "p3fes/state_io.h"

namespace p3fes::native::input {

namespace {
constexpr u8 kStateDisconnected = 0, kStateExec = 5, kStateStable = 6;
constexpr u8 kReqComplete = 0, kReqBusy = 2;
}  // namespace

NativePad::NativePad() { ports_[1].input.connected = false; }

NativePad::Port* NativePad::port_of(u32 port, u32 slot) {
    return port < kPorts && slot == 0 ? &ports_[port] : nullptr;
}

// libpad's scePadGetDmaStr: the slot with the greater counter, the first one on a tie (signed compare).
const NativePad::Report& NativePad::newest(const Port& p) const {
    return static_cast<s32>(p.slots[0].counter) < static_cast<s32>(p.slots[1].counter) ? p.slots[1] : p.slots[0];
}
NativePad::Report& NativePad::newest(Port& p) {
    return static_cast<s32>(p.slots[0].counter) < static_cast<s32>(p.slots[1].counter) ? p.slots[1] : p.slots[0];
}

u32 NativePad::open(u32 port, u32 slot) {
    Port* p = port_of(port, slot);
    if (!p || p->open) return 0;
    const PadState in = p->input;
    *p = Port{};
    p->input = in;
    p->open = true;
    // scePadPortOpen prepares both halves of its buffer: no report yet, the pad "executing", a request busy.
    for (Report& r : p->slots) {
        r = Report{};
        r.state = kStateExec;
        r.req_state = kReqBusy;
        r.data.fill(0xFF);
    }
    return 1;
}

NativePad::Report NativePad::take_report(const Port& p) const {
    Report r;
    r.counter = p.counter;
    r.req_state = p.req_state;
    if (!p.input.connected) {
        r.state = kStateDisconnected;
        r.data.fill(0xFF);
        return r;
    }
    // The button data as the pad sends it: [0] 0, [1] the mode id, [2..3] the buttons active low, [4..7] right x / y,
    // left x / y in analog mode (no pressure bytes: the game never enters pressure mode).
    r.data[1] = p.mode_id;
    r.data[2] = static_cast<u8>(~(p.input.buttons & 0xFFu));
    r.data[3] = static_cast<u8>(~(p.input.buttons >> 8));
    if (p.mode_id != kModeDigital) {
        r.data[4] = p.input.rx;
        r.data[5] = p.input.ry;
        r.data[6] = p.input.lx;
        r.data[7] = p.input.ly;
    }
    r.length = 32;
    r.state = kStateStable;
    r.current_task = 1;
    r.mode_config = 2;
    r.nr_act = 2;
    return r;
}

void NativePad::vblank() {
    for (Port& p : ports_) {
        if (!p.open) continue;
        // Report n goes to slot (n + 1) & 1, so it is the newer one from now on.
        p.slots[(p.counter + 1u) & 1u] = take_report(p);
        ++p.counter;
        ++stats_.reports;
        if (p.busy_reports > 0 && --p.busy_reports == 0) p.req_state = kReqComplete;
    }
}

void NativePad::set_input(u32 port, const PadState& in) {
    if (port >= kPorts) return;
    Port& p = ports_[port];
    const bool unplugged = p.input.connected && !in.connected;
    p.input = in;
    if (unplugged && (p.rumble.small_motor || p.rumble.large_motor)) set_rumble(port, p, Rumble{});
}

void NativePad::request_busy(Port& p) {
    p.req_state = kReqBusy;
    p.busy_reports = 1;  // the next report says BUSY, the one after COMPLETE
    newest(p).req_state = kReqBusy;  // scePadSetReqState(BUSY) on the newest report
}

u32 NativePad::get_state(u32 port, u32 slot) {
    Port* p = port_of(port, slot);
    if (!p || !p->open) return 99;
    const Report& r = newest(*p);
    if (r.state == kStateStable && r.req_state == kReqBusy) return 5;
    return r.state;
}

u32 NativePad::get_req_state(u32 port, u32 slot) {
    Port* p = port_of(port, slot);
    if (!p || !p->open) return 0;
    return newest(*p).req_state;
}

u32 NativePad::info_act(u32 port, u32 slot, s32 actno, u32 term) {
    Port* p = port_of(port, slot);
    if (!p || !p->open) return 0;
    const Report& r = newest(*p);
    if (r.current_task != 1 || r.mode_config < 2) return 0;
    if (!(actno < static_cast<s32>(r.nr_act))) return 0;
    if (actno == -1) return r.nr_act;
    if (actno < 0 || term < 1 || term > 4) return 0;
    return kActuatorInfo[static_cast<std::size_t>(actno) * 4 + (term - 1)];
}

u32 NativePad::set_act_align(u32 port, u32 slot, std::span<const u8, 6> align) {
    Port* p = port_of(port, slot);
    if (!p || !p->open) return 0;
    std::copy(align.begin(), align.end(), p->align.begin());
    request_busy(*p);
    return 1;
}

u32 NativePad::set_main_mode(u32 port, u32 slot, u32 mode, u32 lock) {
    Port* p = port_of(port, slot);
    if (!p || !p->open) return 0;
    p->mode_id = mode == 1 ? kModeDualShock : kModeDigital;
    p->lock = static_cast<u8>(lock);
    ++stats_.mode_changes;
    request_busy(*p);
    return 1;
}

u32 NativePad::read(u32 port, u32 slot, std::span<u8, 32> out) {
    Port* p = port_of(port, slot);
    if (!p || !p->open) return 0;
    const Report& r = newest(*p);
    const u32 n = std::min<u32>(r.length, 32);
    std::copy_n(r.data.begin(), n, out.begin());
    if (n) ++stats_.reads;
    return n;
}

u32 NativePad::set_act_direct(u32 port, u32 slot, std::span<const u8, 6> direct) {
    Port* p = port_of(port, slot);
    if (!p || !p->open || newest(*p).current_task != 1) return 0;
    Rumble r;
    for (std::size_t i = 0; i < 6; ++i) {
        if (p->align[i] == 0) r.small_motor = direct[i];
        else if (p->align[i] == 1) r.large_motor = direct[i];
    }
    ++stats_.act_direct;
    if (r.small_motor || r.large_motor) ++stats_.rumble_on;
    set_rumble(port, *p, r);
    return 1;
}

void NativePad::set_rumble(u32 port, Port& p, Rumble r) {
    p.rumble = r;
    if (rumble_sink_) rumble_sink_(port, r);
}

void NativePad::state(StateIo& io) { io(ports_, stats_); }

}  // namespace p3fes::native::input
