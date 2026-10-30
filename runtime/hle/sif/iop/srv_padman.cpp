// PADMAN: libpad RPC functions + one pad_data_new frame per vblank into each opened port's EE buffer.
// Layout and result words: srv_padman.h. Controller model: a DUALSHOCK 2 that starts in digital mode
// (0x41) and switches to analog (0x73) on scePadSetMainMode(port, slot, 1, lock) -- the game drives that
// state machine itself (H_Pad_UpdateWorkPad 0x103110) and never enters pressure mode
// (scePadEnterPressMode has no callers, `12` §3), so id 0x79 never appears (inf: as on hardware).
#include "srv_padman.h"

#include <cstring>

namespace p3fes::hle::sif::detail {

std::array<u8, pad_frame::kSize> encode_pad_frame(const PadPortState& p) {
    using namespace pad_frame;
    std::array<u8, kSize> f{};
    store32(f, kFrame, p.counter);
    if (!p.input.connected) {
        std::memset(f.data() + kData, 0xFF, 32);
        f[kState] = pad_state::kDisconnected;
        f[kReqState] = p.req_state;
        return f;
    }
    // Button data as PADMAN copies it from the SIO2 reply: [0] 0, [1] mode id, [2..3] buttons (active
    // low), [4..7] right x/y, left x/y. inf: bytes 8..31 (pressure / spare) read 0.
    f[kData + 0] = 0x00;
    f[kData + 1] = p.mode_id;
    f[kData + 2] = static_cast<u8>(~(p.input.buttons & 0xFFu));
    f[kData + 3] = static_cast<u8>(~(p.input.buttons >> 8));
    if (p.mode_id != kPadIdDigital) {
        f[kData + 4] = p.input.rx;
        f[kData + 5] = p.input.ry;
        f[kData + 6] = p.input.lx;
        f[kData + 7] = p.input.ly;
    }
    store32(f, kLength, 32);
    // Actuators (InfoAct): 2 motors {func, sub, size, curr}; one combination. inf: DUALSHOCK-style values.
    const u8 act[8] = {1, 0, 0, 1, 1, 1, 8, 1};
    std::memcpy(f.data() + kActData, act, sizeof act);
    const u8 comb[4] = {2, 0, 1, 0};
    std::memcpy(f.data() + kCombData, comb, sizeof comb);
    // Mode table (InfoMode PAD_MODETABLE): digital (type 4), DUALSHOCK (type 7).
    f[kModeTable + 0] = 0x04;
    f[kModeTable + 2] = 0x07;
    f[kModeConfig] = 2;  // InfoMode/InfoAct require >= 2 (obs 0x511CB0)
    f[kModeCurId] = p.mode_id;
    f[kModel] = 3;  // inf: DUALSHOCK 2
    f[kButtonDataReady] = 1;
    f[kNrOfModes] = 2;
    f[kModeCurOffs] = p.mode_offs;
    f[kNrOfActuators] = 2;
    f[kNumActComb] = 1;
    f[kMode] = p.mode_offs;
    f[kLock] = p.lock;
    f[kState] = pad_state::kStable;
    f[kReqState] = p.req_state;
    f[kCurrentTask] = 1;  // InfoMode/InfoAct require 1 (obs 0x511CA0, 0x511ED0)
    return f;
}

void PadmanServer::set_input(unsigned port, const PadInput& in) {
    if (port < inputs_.size()) inputs_[port] = in;
}

void PadmanServer::reboot() {
    ports_ = {};
    last_vblank_ = ~0ull;
}

bool PadmanServer::call(IopCore& core, const RpcRequest& req, RpcReply& reply, u32 /*ticket*/) {
    reply.rdata.assign(req.data.begin(), req.data.end());
    reply.rdata.resize(128, 0);
    if (req.sid != pad_sid::kMain || req.fno != 1) {
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, req.fno, "PADMAN rpc not used by libpad (echoed)");
        return true;
    }
    const u32 fn = req_word(req, 0);
    const u32 port = req_word(req, 4);
    PadPortState* p = port < ports_.size() ? &ports_[port] : nullptr;
    auto request_busy = [](PadPortState* s) {
        if (s) {
            s->req_state = pad_state::kReqBusy;
            s->busy_frames = 1;  // one frame BUSY, then COMPLETE (inf: the real command takes a few frames)
        }
    };
    switch (fn) {
    case 16:  // Init2
    case 15:  // End
        put_word(reply.rdata, 12, 1);
        break;
    case 1:  // PortOpen(port, slot, ee buffer)
        if (p) {
            const PadInput in = p->input;
            *p = PadPortState{};
            p->open = true;
            p->ee_buffer = req_word(req, 16);
            p->iop_buffer = core.ram().arena_alloc(64);  // 2 x 32-byte actuator packets (_send_to_iop)
            p->input = in;
        }
        put_word(reply.rdata, 12, p ? 1u : 0u);
        put_word(reply.rdata, 20, p ? p->iop_buffer : 0u);
        break;
    case 14:  // PortClose
        if (p) p->open = false;
        put_word(reply.rdata, 12, 1);
        break;
    case 6:  // SetMainMode(port, slot, mode, lock)
        if (p) {
            const bool dualshock = req_word(req, 12) == 1;
            p->mode_id = dualshock ? kPadIdDualShock : kPadIdDigital;
            p->mode_offs = dualshock ? 1 : 0;
            p->lock = static_cast<u8>(req_word(req, 16));
        }
        request_busy(p);
        put_word(reply.rdata, 20, 1);
        break;
    case 8:  // SetActAlign
        request_busy(p);
        put_word(reply.rdata, 20, 1);
        break;
    case 10:  // SetButtonInfo
        request_busy(p);
        put_word(reply.rdata, 16, 1);
        break;
    case 11:  // SetVrefParam
        request_busy(p);
        put_word(reply.rdata, 28, 1);
        break;
    case 12: put_word(reply.rdata, 12, 2); break;       // GetPortMax
    case 13: put_word(reply.rdata, 12, 1); break;       // GetSlotMax (no multitap)
    case 18: put_word(reply.rdata, 12, 0x0400); break;  // GetModVersion: major 4 required (0x511210); inf minor
    case 20: put_word(reply.rdata, 8, 1); break;        // SetWarningLevel
    case 24: put_word(reply.rdata, 12, 1); break;       // SetDmaCallback (callback never set by the game)
    default:
        core.note_unknown(UnknownEvent::Kind::Function, req.sid, fn, "libpad function not modelled (answered 0)");
        put_word(reply.rdata, 12, 0);
        break;
    }
    return true;
}

void PadmanServer::write_frame(IopCore& core, PadPortState& p) {
    const auto frame = encode_pad_frame(p);
    // Frame n lands in half (n + 1) & 1 (the newer counter wins in scePadGetDmaStr).
    const u32 dest = p.ee_buffer + ((p.counter + 1u) & 1u) * static_cast<u32>(pad_frame::kSize);
    if (core.ee_store(dest, frame)) ++core.stats().pad_frames;
    ++p.counter;
    if (p.busy_frames > 0 && --p.busy_frames == 0) p.req_state = pad_state::kReqComplete;
}

void PadmanServer::tick(IopCore& core, u64 /*now*/, const Timebase& tb) {
    if (tb.vblanks == last_vblank_) return;
    last_vblank_ = tb.vblanks;
    for (std::size_t i = 0; i < ports_.size(); ++i) {
        PadPortState& p = ports_[i];
        p.input = inputs_[i];
        if (p.open) write_frame(core, p);
    }
}

}  // namespace p3fes::hle::sif::detail
