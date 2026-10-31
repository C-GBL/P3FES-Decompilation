// NativeG3Seam (native_g3.h): the g3 runs at the PS2All bridge seam, their kicks handed over as host packets.
#include "native_g3.h"

#include "p3fes/gs/gif.h"
#include "p3fes/vu1/vu1_aot.h"

#include <algorithm>
#include <cstring>

namespace p3fes::native::graphics {

namespace {
constexpr std::size_t kQueueMax = 1u << 12;
constexpr std::size_t kLook = kQueueMax;  // the whole queue: records of draws that never reach VU1 pile up in front

u64 head_of(const u8* p) noexcept {
    u64 h;
    std::memcpy(&h, p, 8);
    return h;
}

bool same_lanes(const u8* q, const u128& r, u32 first_lane) noexcept {
    return std::memcmp(q + 4u * first_lane, reinterpret_cast<const u8*>(&r) + 4u * first_lane, 16u - 4u * first_lane) == 0;
}
}  // namespace

const char* to_string(G3Family f) noexcept {
    switch (f) {
    case G3Family::Generic: return "g3_generic";
    case G3Family::Skin: return "g3_skin";
    case G3Family::MatFx: return "g3_matfx";
    case G3Family::SkinMatFx: return "g3_skin_matfx";
    default: return "none";
    }
}

G3Family g3_family_of(const char* name) noexcept {
    if (!name) return G3Family::None;
    // "vu1_prog_NNN_<family>"
    const char* p = std::strstr(name, "_g3_");
    if (!p) return G3Family::None;
    p += 1;
    if (std::strcmp(p, "g3_generic") == 0) return G3Family::Generic;
    if (std::strcmp(p, "g3_skin") == 0) return G3Family::Skin;
    if (std::strcmp(p, "g3_matfx") == 0) return G3Family::MatFx;
    if (std::strcmp(p, "g3_skin_matfx") == 0) return G3Family::SkinMatFx;
    return G3Family::None;
}

struct NativeG3Seam::Checker final : vu1::IGifSink {
    vu1::VU1Interpreter vu{this};
    u64 gen = ~0ull;
    std::vector<u128> kicked;
    u32 kicks = 0;
    void kick(std::span<const u128> q) override {
        kicked.insert(kicked.end(), q.begin(), q.end());
        ++kicks;
    }
};

NativeG3Seam::NativeG3Seam() {
    const vu1::AotProgram* t = vu1::aot_programs();
    for (std::size_t i = 0; i < vu1::aot_program_count(); ++i) {
        const G3Family f = g3_family_of(t[i].name);
        if (f != G3Family::None && t[i].image && t[i].pairs) add_program(std::span<const u8>(t[i].image, t[i].pairs * 8u), f);
    }
}
NativeG3Seam::~NativeG3Seam() = default;

void NativeG3Seam::add_program(std::span<const u8> image, G3Family f) {
    if (image.size() < 8 || image.size() > vu1::kMicroBytes || f == G3Family::None) return;
    Prog p;
    p.image.assign(image.begin(), image.end());
    p.head = head_of(image.data());
    p.fam = f;
    progs_.push_back(std::move(p));
    gen_ = ~0ull;
}

void NativeG3Seam::set_check(u32 every, std::FILE* log) {
    check_every_ = every;
    log_ = log;
    if (every && !chk_) chk_ = std::make_unique<Checker>();
}

void NativeG3Seam::clear_queue() {
    std::lock_guard<std::mutex> l(m_);
    q_.clear();
    miss_valid_ = false;
}

void NativeG3Seam::object(const G3ObjectRecord&) { ++st_.objects; }

void NativeG3Seam::mesh(const G3MeshRecord& m) {
    ++st_.meshes;
    if (m.matfx) ++st_.meshes_matfx;
    std::lock_guard<std::mutex> l(m_);
    if (q_.size() >= kQueueMax) {
        q_.pop_front();
        ++st_.overflow;
    }
    q_.push_back(m);
    miss_valid_ = false;
}

G3Family NativeG3Seam::identify(const vu1::MicroMemory& m) {
    if (m.generation() == gen_) return fam_;
    gen_ = m.generation();
    fam_ = G3Family::None;
    const u8* b = m.bytes().data();
    const u64 h = head_of(b);
    for (const Prog& p : progs_)
        if (p.head == h && std::memcmp(b, p.image.data(), p.image.size()) == 0) {
            fam_ = p.fam;
            break;
        }
    return fam_;
}

// The mesh record this run draws: the first queued one whose block (VU1 0x3FA yzw: the GIF tag's PRIM / FLG / NREG /
// REGS, 0x3FB the material colour, 0x3FC the surface properties) VU1 memory holds. A mesh's clusters are consecutive
// runs with the same block; a later match drops the records before it.
void NativeG3Seam::match(const vu1::VU1State& s) {
    const u8* a = s.data + 0x3FAu * 16u;
    std::lock_guard<std::mutex> l(m_);
    // the next cluster of a mesh no record holds: nothing reported since, the same answer without the scan
    if (miss_valid_ && q_.size() == miss_queue_ && std::memcmp(a, miss_block_, sizeof miss_block_) == 0) {
        ++st_.unmatched;
        return;
    }
    const std::size_t look = std::min(q_.size(), kLook);
    for (std::size_t k = 0; k < look; ++k) {
        const G3MeshRecord& r = q_[k];
        if (!same_lanes(a, r.block[0], 1) || !same_lanes(a + 16, r.block[1], 0) || !same_lanes(a + 32, r.block[2], 0)) continue;
        for (std::size_t d = 0; d < k; ++d) q_.pop_front();
        st_.dropped += k;
        ++st_.matched;
        miss_valid_ = false;
        return;
    }
    ++st_.unmatched;
    std::memcpy(miss_block_, a, sizeof miss_block_);
    miss_queue_ = q_.size();
    miss_valid_ = true;
}

bool NativeG3Seam::run(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) {
    forwarded_ = false;
    capturing_ = false;
    checking_ = false;
    vu1::VU1State& s = vu.state();
    const G3Family f = identify(s.micro);
    if (f == G3Family::None || next_) {  // other programs; with the play-mode renderer installed, everything is its
        ++st_.other_runs;
        forwarded_ = next_ != nullptr;
        return next_ ? next_->run(r, vu) : false;
    }
    ++st_.runs;
    ++st_.family[static_cast<int>(f)];
    match(s);
    if (check_every_ && (check_seq_++ % check_every_) == 0) {
        if (!before_) before_ = std::make_unique<vu1::VU1State>();
        *before_ = s;
        checking_ = true;
    }
    saved_ = vu.sink();
    vu.set_sink(this);
    capturing_ = true;
    npk_ = 0;
    return false;  // the program runs (compiled or interpreted), its kicks come to kick()
}

void NativeG3Seam::kick(std::span<const u128> q) {
    if (npk_ == pk_.size()) pk_.emplace_back();
    pk_[npk_++].assign(q.begin(), q.end());
}

void NativeG3Seam::after_exact(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) {
    if (forwarded_) {
        forwarded_ = false;
        if (next_) next_->after_exact(r, vu);
        return;
    }
    if (!capturing_) return;
    capturing_ = false;
    vu.set_sink(saved_);
    for (std::size_t i = 0; i < npk_; ++i) {
        const std::vector<u128>& p = pk_[i];
        ++st_.kicks;
        st_.kick_qw += p.size();
        if (!gs::Gif::host_form(p)) {
            ++st_.other_form[static_cast<int>(fam_)];
        }
        if (!saved_) continue;
        if (direct_) {
            saved_->kick_host(p);
            ++st_.host_kicks;
        } else {
            saved_->kick(p);
        }
    }
    if (checking_ && !vu.state().running) check(r, vu);  // (a trapped / step-limited run has no end state to compare)
    checking_ = false;
}

// The run from `before_` on the scratch interpreter (the oracle), compared with what the run left and kicked.
void NativeG3Seam::check(const gs::VuRunInfo& r, vu1::VU1Interpreter& vu) {
    Checker& c = *chk_;
    const vu1::VU1State& before = *before_;
    const vu1::VU1State& after = vu.state();
    vu1::VU1State& x = c.vu.state();
    if (c.gen != before.micro.generation()) {
        c.vu.load_micro(0, before.micro.bytes());
        c.gen = before.micro.generation();
    }
    const vu1::MicroMemory keep = x.micro;
    x = before;
    x.micro = keep;
    c.kicked.clear();
    c.kicks = 0;
    const bool mscal = r.op == 0x14 || r.op == 0x15;
    const vu1::RunResult rr = r.op == 0x15 ? c.vu.mscalf(r.imm) : mscal ? c.vu.mscal(r.imm) : c.vu.mscnt();
    ++st_.checked;
    std::size_t qw = 0;
    for (std::size_t i = 0; i < npk_; ++i) qw += pk_[i].size();
    bool same_kicks = c.kicks == npk_ && c.kicked.size() == qw;
    for (std::size_t i = 0, at = 0; same_kicks && i < npk_; at += pk_[i].size(), ++i)
        same_kicks = std::memcmp(c.kicked.data() + at, pk_[i].data(), pk_[i].size() * sizeof(u128)) == 0;
    const char* what = nullptr;
    if (rr.status != vu1::RunStatus::Ended) what = "the oracle run did not end";
    else if (std::memcmp(x.vf, after.vf, sizeof x.vf) != 0) what = "vf";
    else if (std::memcmp(x.vi, after.vi, sizeof x.vi) != 0) what = "vi";
    else if (std::memcmp(x.acc, after.acc, sizeof x.acc) != 0 || x.q != after.q || x.p != after.p || x.i != after.i ||
             x.r != after.r)
        what = "acc/q/p/i/r";
    else if (x.mac != after.mac || x.status != after.status || x.clip != after.clip) what = "flags";
    else if (x.pc != after.pc || x.npc != after.npc || x.tpc != after.tpc || x.running != after.running ||
             x.ending != after.ending || x.top != after.top || x.itop != after.itop)
        what = "pc/tpc";
    else if (std::memcmp(x.vi_before, after.vi_before, sizeof x.vi_before) != 0 || x.vi_delay_live != after.vi_delay_live)
        what = "branch view";
    else if (std::memcmp(x.data, after.data, sizeof x.data) != 0) what = "data memory";
    else if (!same_kicks) what = "kicked packets";
    if (what) {
        ++st_.check_bad;
        if (log_ && st_.check_bad <= 8)
            std::fprintf(log_, "p3fes: native graphics g3 check: run %llu (%s, op %02X, top %03X, itop %u): %s differs\n",
                         static_cast<unsigned long long>(st_.runs), to_string(fam_), r.op, before.top, before.itop, what);
    }
}

}  // namespace p3fes::native::graphics
