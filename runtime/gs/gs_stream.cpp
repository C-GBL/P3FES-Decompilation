// GS command-stream recording and software replay (runtime/include/p3fes/gs/gs_stream.h). Diagnostics only: nothing
// here runs unless a host asks for a recording, and a recorder never changes what the core computes.
#include "p3fes/gs/gs_stream.h"

#include <cstdio>
#include <cstring>

namespace p3fes::gs {

namespace {

constexpr char kMagic[8] = {'P', '3', 'G', 'S', 'T', 'R', 'M', '1'};
constexpr u32 kVersion = 1;

// Field-by-field (padding-free) form of the state structures.
struct Writer {
    std::vector<u8>& out;
    template <class T> void v(const T& x) {
        const auto* p = reinterpret_cast<const u8*>(&x);
        out.insert(out.end(), p, p + sizeof(T));
    }
};
struct Reader {
    const u8* p;
    const u8* end;
    bool ok = true;
    template <class T> void v(T& x) {
        if (static_cast<std::size_t>(end - p) < sizeof(T)) {
            ok = false;
            x = T{};
            return;
        }
        std::memcpy(&x, p, sizeof(T));
        p += sizeof(T);
    }
};

template <class IO, class Regs> void io_regs(IO& io, Regs& r) {
    io.v(r.prim); io.v(r.rgbaq); io.v(r.st); io.v(r.uv); io.v(r.fog); io.v(r.prmodecont); io.v(r.prmode);
    io.v(r.texclut); io.v(r.scanmsk); io.v(r.texa); io.v(r.fogcol); io.v(r.dimx); io.v(r.dthe); io.v(r.colclamp);
    io.v(r.pabe); io.v(r.bitbltbuf); io.v(r.trxpos); io.v(r.trxreg); io.v(r.trxdir);
    for (auto& c : r.ctx) {
        io.v(c.tex0); io.v(c.clamp); io.v(c.tex1); io.v(c.xyoffset); io.v(c.miptbp1); io.v(c.miptbp2);
        io.v(c.scissor); io.v(c.alpha); io.v(c.test); io.v(c.fba); io.v(c.frame); io.v(c.zbuf);
    }
    io.v(r.q_internal);
}

template <class IO, class State> void io_state(IO& io, State& s) {
    io_regs(io, s.regs);
    for (auto& q : s.queue) {
        io.v(q.x); io.v(q.y); io.v(q.z); io.v(q.r); io.v(q.g); io.v(q.b); io.v(q.a);
        io.v(q.q); io.v(q.s); io.v(q.t); io.v(q.u); io.v(q.v); io.v(q.f);
    }
    io.v(s.queued);
    for (auto& c : s.clut) io.v(c);
    io.v(s.cbp0); io.v(s.cbp1); io.v(s.xfer_active); io.v(s.xfer_dir); io.v(s.xfer_x); io.v(s.xfer_y);
    io.v(s.xfer_bitbuf); io.v(s.xfer_bitcount);
}

template <class IO, class Disp> void io_disp(IO& io, Disp& d) {
    io.v(d.pmode); io.v(d.smode1); io.v(d.smode2); io.v(d.dispfb[0]); io.v(d.dispfb[1]); io.v(d.display[0]);
    io.v(d.display[1]); io.v(d.bgcolor);
}

std::vector<u8> state_bytes(const GsCoreState& s) {
    std::vector<u8> out;
    Writer w{out};
    io_state(w, const_cast<GsCoreState&>(s));
    return out;
}

std::vector<u8> vram_copy(const GsCore& core) {
    return std::vector<u8>(core.mem().data(), core.mem().data() + kVramBytes);
}

} // namespace

void GsStreamRecorder::put(const void* p, std::size_t n) {
    const auto* b = static_cast<const u8*>(p);
    events_.insert(events_.end(), b, b + n);
}

void GsStreamRecorder::begin(GsCore& core, u64 vblank, u64 flip) {
    events_.clear();
    finished_ = false;
    start_vblank_ = vblank;
    start_flip_ = flip;
    start_state_ = core.save_state();
    start_vram_ = vram_copy(core);
    core_ = &core;
    core.set_stream_sink(this);
}

void GsStreamRecorder::end(GsCore& core, const DisplayRegs& disp, u64 vblank, u64 flip) {
    core.set_stream_sink(nullptr);
    core_ = nullptr;
    const u8 e = static_cast<u8>(StreamEvent::End);
    put(&e, 1);
    end_vblank_ = vblank;
    end_flip_ = flip;
    end_state_ = core.save_state();
    end_vram_ = vram_copy(core);
    disp_ = disp;
    finished_ = true;
}

void GsStreamRecorder::on_reg(u32 reg, u64 value) {
    const u8 k = static_cast<u8>(StreamEvent::Reg), r = static_cast<u8>(reg);
    put(&k, 1);
    put(&r, 1);
    put(&value, 8);
}
void GsStreamRecorder::on_packed(u32 desc, const u128& q) {
    const u8 k = static_cast<u8>(StreamEvent::Packed), d = static_cast<u8>(desc);
    put(&k, 1);
    put(&d, 1);
    put(q.u8, 16);
}
void GsStreamRecorder::on_gif_tag() {
    const u8 k = static_cast<u8>(StreamEvent::GifTag);
    put(&k, 1);
}
void GsStreamRecorder::on_image(std::span<const u128> qwords) {
    const u8 k = static_cast<u8>(StreamEvent::Image);
    const u32 n = static_cast<u32>(qwords.size());
    put(&k, 1);
    put(&n, 4);
    for (const u128& q : qwords) put(q.u8, 16);
}
void GsStreamRecorder::on_hwreg(u64 value) {
    const u8 k = static_cast<u8>(StreamEvent::HwReg);
    put(&k, 1);
    put(&value, 8);
}
void GsStreamRecorder::on_read_image(std::size_t qwords) {
    const u8 k = static_cast<u8>(StreamEvent::ReadImage);
    const u32 n = static_cast<u32>(qwords);
    put(&k, 1);
    put(&n, 4);
}
void GsStreamRecorder::on_reset() {
    const u8 k = static_cast<u8>(StreamEvent::Reset);
    put(&k, 1);
}

bool GsStreamRecorder::write(const std::filesystem::path& path, std::string& error) const {
    if (!finished_) {
        error = "recording not finished";
        return false;
    }
    std::vector<u8> head;
    Writer w{head};
    head.insert(head.end(), kMagic, kMagic + 8);
    const std::vector<u8> s0 = state_bytes(start_state_), s1 = state_bytes(end_state_);
    w.v(kVersion);
    w.v(static_cast<u32>(s0.size()));
    w.v(static_cast<u32>(kVramBytes));
    w.v(static_cast<u32>(0));
    w.v(start_vblank_); w.v(end_vblank_); w.v(start_flip_); w.v(end_flip_);
    std::vector<u8> tail;
    Writer wt{tail};
    io_disp(wt, const_cast<DisplayRegs&>(disp_));
    FILE* f = std::fopen(path.string().c_str(), "wb");
    if (!f) {
        error = "cannot create " + path.string();
        return false;
    }
    bool ok = std::fwrite(head.data(), 1, head.size(), f) == head.size();
    ok = ok && std::fwrite(s0.data(), 1, s0.size(), f) == s0.size();
    ok = ok && std::fwrite(start_vram_.data(), 1, start_vram_.size(), f) == start_vram_.size();
    ok = ok && std::fwrite(events_.data(), 1, events_.size(), f) == events_.size();
    ok = ok && std::fwrite(tail.data(), 1, tail.size(), f) == tail.size();
    ok = ok && std::fwrite(s1.data(), 1, s1.size(), f) == s1.size();
    ok = ok && std::fwrite(end_vram_.data(), 1, end_vram_.size(), f) == end_vram_.size();
    ok = (std::fclose(f) == 0) && ok;
    if (!ok) error = "write failed: " + path.string();
    return ok;
}

bool read_stream(const std::filesystem::path& path, GsStream& out, std::string& error) {
    FILE* f = std::fopen(path.string().c_str(), "rb");
    if (!f) {
        error = "cannot open " + path.string();
        return false;
    }
    std::vector<u8> all;
    u8 buf[1 << 16];
    for (std::size_t n; (n = std::fread(buf, 1, sizeof buf, f)) > 0;) all.insert(all.end(), buf, buf + n);
    std::fclose(f);
    if (all.size() < 48 || std::memcmp(all.data(), kMagic, 8) != 0) {
        error = "not a P3GSTRM1 file";
        return false;
    }
    Reader r{all.data() + 8, all.data() + all.size()};
    u32 version = 0, state_size = 0, vram = 0, reserved = 0;
    r.v(version); r.v(state_size); r.v(vram); r.v(reserved);
    const std::size_t expect_state = state_bytes(GsCoreState{}).size();
    if (version != kVersion || state_size != expect_state || vram != kVramBytes) {
        error = "stream version/layout mismatch (recorded by another build?)";
        return false;
    }
    r.v(out.start_vblank); r.v(out.end_vblank); r.v(out.start_flip); r.v(out.end_flip);
    io_state(r, out.start_state);
    if (!r.ok || static_cast<std::size_t>(r.end - r.p) < kVramBytes) {
        error = "truncated stream (start)";
        return false;
    }
    out.start_vram.assign(r.p, r.p + kVramBytes);
    r.p += kVramBytes;
    // Walk the events to find the End marker.
    const u8* ev0 = r.p;
    for (;;) {
        if (r.p >= r.end) {
            error = "truncated stream (events)";
            return false;
        }
        const auto k = static_cast<StreamEvent>(*r.p++);
        std::size_t skip = 0;
        switch (k) {
        case StreamEvent::End: break;
        case StreamEvent::Reg: skip = 9; break;
        case StreamEvent::Packed: skip = 17; break;
        case StreamEvent::GifTag: case StreamEvent::Reset: skip = 0; break;
        case StreamEvent::HwReg: skip = 8; break;
        case StreamEvent::ReadImage: skip = 4; break;
        case StreamEvent::Image: {
            u32 n = 0;
            r.v(n);
            skip = static_cast<std::size_t>(n) * 16u;
            break;
        }
        default:
            error = "bad event kind";
            return false;
        }
        if (k == StreamEvent::End) break;
        if (static_cast<std::size_t>(r.end - r.p) < skip) {
            error = "truncated event";
            return false;
        }
        r.p += skip;
    }
    out.events.assign(ev0, r.p);
    io_disp(r, out.disp);
    io_state(r, out.end_state);
    if (!r.ok || static_cast<std::size_t>(r.end - r.p) < kVramBytes) {
        error = "truncated stream (end)";
        return false;
    }
    out.end_vram.assign(r.p, r.p + kVramBytes);
    return true;
}

void load_stream_start(const GsStream& s, GsCore& core) {
    core.load_state(s.start_state);
    std::memcpy(core.mem().data(), s.start_vram.data(), kVramBytes);
}

std::size_t replay_events(const GsStream& s, GsCore& core, std::string& error) {
    Reader r{s.events.data(), s.events.data() + s.events.size()};
    std::size_t n = 0;
    std::vector<u128> image;
    while (r.p < r.end) {
        const auto k = static_cast<StreamEvent>(*r.p++);
        switch (k) {
        case StreamEvent::End: return n;
        case StreamEvent::Reg: {
            u8 reg = 0;
            u64 v = 0;
            r.v(reg);
            r.v(v);
            core.write_reg(reg, v);
            break;
        }
        case StreamEvent::Packed: {
            u8 d = 0;
            u128 q{};
            r.v(d);
            r.v(q);
            core.write_packed(d, q);
            break;
        }
        case StreamEvent::GifTag: core.on_gif_tag(); break;
        case StreamEvent::Image: {
            u32 cnt = 0;
            r.v(cnt);
            image.resize(cnt);
            for (u32 i = 0; i < cnt; ++i) r.v(image[i]);
            core.write_image(image);
            break;
        }
        case StreamEvent::HwReg: {
            u64 v = 0;
            r.v(v);
            core.write_hwreg(v);
            break;
        }
        case StreamEvent::ReadImage: {
            u32 cnt = 0;
            r.v(cnt);
            image.assign(cnt, u128{});
            core.read_image(image);
            break;
        }
        case StreamEvent::Reset: core.reset(); break;
        default:
            error = "bad event kind";
            return n;
        }
        if (!r.ok) {
            error = "truncated event";
            return n;
        }
        ++n;
    }
    error = "no End marker";
    return n;
}

ReplayCheck replay_software(const GsStream& s, GsCore& core, std::string& error) {
    ReplayCheck c;
    load_stream_start(s, core);
    core.set_software_raster(true);
    c.events = replay_events(s, core, error);
    const u8* a = core.mem().data();
    for (std::size_t i = 0; i < kVramBytes; ++i) c.vram_bytes_differing += a[i] != s.end_vram[i];
    c.state_equal = state_bytes(core.save_state()) == state_bytes(s.end_state);
    return c;
}

} // namespace p3fes::gs
