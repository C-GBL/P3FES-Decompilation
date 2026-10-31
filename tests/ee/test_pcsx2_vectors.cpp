// PCSX2-observed vectors for runtime/include/p3fes/ee/{hilo,mmi,fpu,vu0,core}.h (GOAL.md Phase 4, ADR-0006 item 5).
//
// tests/ee/vectors/pcsx2_vectors.json is produced by tools/ours/eevec/gen_vectors.py (the vector tables and the
// R5900 test program) and tools/ours/eevec/run_pcsx2.py (runs the ELF under PCSX2 2.8.2 twice -- EE recompiler
// ("obs") and EE interpreter ("obs_int", stored only where it differs) -- and reads every result over PINE). This
// test replays each vector through our headers and compares every observed field against the ORACLE value: the
// interpreter's where the two engines differ (it is PCSX2's reference model), the common value otherwise.
//   agree                   every field equals the oracle (and lane-parallel MMI ops agree on the scalar AND SSE2 path)
//   agree-rec:<class>       differs from the interpreter but equals the recompiler; <class> names the interpreter
//                           shortcut (e.g. its raw CTC2 STATUS write, its dropped 64-bit carry in PMADDW)
//   disagree:<class>        a documented, deliberate difference from both engines (classify() below, and
//                           tools/ours/eevec/README.md); the observed value must still match what the class predicts
//   anything else           a real mismatch: the test fails and prints ours vs oracle
// Every vector in the JSON carries its `status` (written by tools/ours/eevec/annotate.py from this test's report,
// P3FES_EEVEC_REPORT=<path>); the test requires the stored status to equal the computed one, so the committed JSON
// always states the current agreement.
//
// Provenance tags used elsewhere in tests/ee/: "(PCSX2 2.8.2 observed: <vector id>)" refers to the ids here.
#include "ee_test_util.h"

#include "../vu1/mini_json.h"
#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/ee/mmi.h"
#include "p3fes/ee/vu0.h"
#include "p3fes/ee_memory.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace p3fes;
using namespace p3fes::ee;
using namespace p3fes::ee_test;
using Json = p3fes::test::json::Value;

namespace {

#ifndef P3FES_REPO_DIR
#define P3FES_REPO_DIR "."
#endif

u64 hx(const std::string& s, int hi_digit, int lo_digit) {
    // digits counted from the right of the hex text (after "0x")
    const std::string body = s.substr(2);
    u64 v = 0;
    for (int d = hi_digit; d >= lo_digit; --d) {
        const int idx = static_cast<int>(body.size()) - 1 - d;
        const char c = idx >= 0 ? body[static_cast<std::size_t>(idx)] : '0';
        v = (v << 4) | static_cast<u64>(c <= '9' ? c - '0' : (c | 0x20) - 'a' + 10);
    }
    return v;
}
u32 hx32(const Json& o, const char* k) { const Json* v = o.get(k); return v ? static_cast<u32>(hx(v->string, 7, 0)) : 0u; }
u64 hx64(const Json& o, const char* k) { const Json* v = o.get(k); return v ? hx(v->string, 15, 0) : 0u; }
u128 hx128(const Json& o, const char* k) {
    const Json* v = o.get(k);
    u128 r{};
    if (!v) return r;
    r.u64[0] = hx(v->string, 15, 0);
    r.u64[1] = hx(v->string, 31, 16);
    return r;
}
bool has(const Json& o, const char* k) { return o.get(k) != nullptr; }
int form_int(const Json& form, const char* k, int def = 0) {
    const Json* v = form.get(k);
    return v ? static_cast<int>(v->as_int()) : def;
}
std::string form_str(const Json& form, const char* k) {
    const Json* v = form.get(k);
    return v ? v->string : std::string();
}

std::string h32(u32 v) { char b[16]; std::snprintf(b, sizeof b, "0x%08X", v); return b; }
std::string h64(u64 v) { char b[24]; std::snprintf(b, sizeof b, "0x%016llX", static_cast<unsigned long long>(v)); return b; }
std::string h128(const u128& v) {
    char b[40];
    std::snprintf(b, sizeof b, "0x%016llX%016llX", static_cast<unsigned long long>(v.u64[1]), static_cast<unsigned long long>(v.u64[0]));
    return b;
}

// One replay: the fields we computed, compared against the observed ones.
struct Outcome {
    std::map<std::string, std::string> ours;      // field -> hex text (same formatting as the JSON)
    std::vector<std::string> mismatched;          // fields that differ from `obs`
    std::vector<std::string> notes;               // classification reasons
};

void put32(Outcome& o, const char* k, u32 v) { o.ours[k] = h32(v); }
void put64(Outcome& o, const char* k, u64 v) { o.ours[k] = h64(v); }
void put128(Outcome& o, const char* k, const u128& v) { o.ours[k] = h128(v); }

bool exp255(u32 f) { return (f & 0x7F800000u) == 0x7F800000u; }
u32 clamp_ieee(u32 f) { return exp255(f) ? ((f & 0x80000000u) | 0x7F7FFFFFu) : f; }

// ---------------------------------------------------------------------------------------------------------
// hilo
// ---------------------------------------------------------------------------------------------------------
void replay_hilo(const Json& v, Outcome& o) {
    const Json& in = *v.get("in");
    const Json& form = *v.get("form");
    const std::string op = v.get("op")->string;
    EEContext c;
    c.hi = hx128(in, "hi");
    c.lo = hx128(in, "lo");
    const u64 rs = hx64(in, "rs"), rt = hx64(in, "rt");
    u128 rd = hx128(in, "rd");
    const int pipe = form_int(form, "pipe");
    const bool three = form.get("rd") && form.get("rd")->boolean;
    const u32 s = static_cast<u32>(rs), t = static_cast<u32>(rt);
    const std::string base = (op.back() == '1') ? op.substr(0, op.size() - 1) : op;
    if (base == "mult") mult(c, pipe, s, t);
    else if (base == "multu") multu(c, pipe, s, t);
    else if (base == "div") div(c, pipe, s, t);
    else if (base == "divu") divu(c, pipe, s, t);
    else if (base == "madd") madd(c, pipe, s, t);
    else if (base == "maddu") maddu(c, pipe, s, t);
    else if (base == "mthi") c.hi.u64[pipe] = rs;
    else if (base == "mtlo") c.lo.u64[pipe] = rs;
    else FAIL("unknown hilo op " << op);
    if (three) rd.u64[0] = c.lo.u64[pipe];   // rd <- LO of the pipe (64-bit GPR write)
    put128(o, "rd", rd);
    put128(o, "hi", c.hi);
    put128(o, "lo", c.lo);
    put32(o, "sa", 0);
}

// ---------------------------------------------------------------------------------------------------------
// mmi: lane-parallel ops go through both paths; the result must agree on both.
// ---------------------------------------------------------------------------------------------------------
using Bin = void (*)(u128&, const u128&, const u128&);
using Un = void (*)(u128&, const u128&);
using Sh = void (*)(u128&, const u128&, u32);
#define BIN2(name) {#name, {mmi::scalar::name, mmi::sse2::name}}
#define UN2(name) {#name, {mmi::scalar::name, mmi::sse2::name}}
#define SH2(name) {#name, {mmi::scalar::name, mmi::sse2::name}}
const std::map<std::string, std::pair<Bin, Bin>> kBin = {
    BIN2(paddw), BIN2(psubw), BIN2(paddh), BIN2(psubh), BIN2(paddb), BIN2(psubb), BIN2(paddsw), BIN2(psubsw), BIN2(paddsh),
    BIN2(psubsh), BIN2(paddsb), BIN2(psubsb), BIN2(padduw), BIN2(psubuw), BIN2(padduh), BIN2(psubuh), BIN2(paddub),
    BIN2(psubub), BIN2(pcgtw), BIN2(pcgth), BIN2(pcgtb), BIN2(pceqw), BIN2(pceqh), BIN2(pceqb), BIN2(pmaxw), BIN2(pminw),
    BIN2(pmaxh), BIN2(pminh), BIN2(padsbh), BIN2(pand), BIN2(por), BIN2(pxor), BIN2(pnor), BIN2(pextlw), BIN2(pextuw),
    BIN2(pextlh), BIN2(pextuh), BIN2(pextlb), BIN2(pextub), BIN2(ppacw), BIN2(ppach), BIN2(ppacb), BIN2(pinth), BIN2(pinteh),
    BIN2(pcpyld), BIN2(pcpyud), BIN2(psllvw), BIN2(psrlvw), BIN2(psravw),
};
const std::map<std::string, std::pair<Un, Un>> kUn = {
    UN2(pabsw), UN2(pabsh), UN2(pcpyh), UN2(pexch), UN2(pexcw), UN2(pexeh), UN2(pexew), UN2(prevh), UN2(prot3w), UN2(pext5), UN2(ppac5),
};
const std::map<std::string, std::pair<Sh, Sh>> kSh = {SH2(psllh), SH2(psrlh), SH2(psrah), SH2(psllw), SH2(psrlw), SH2(psraw)};
using HiLoOp = void (*)(EEContext&, u128&, const u128&, const u128&);
const std::map<std::string, HiLoOp> kHiLo = {
    {"pmultw", mmi::pmultw}, {"pmultuw", mmi::pmultuw}, {"pmaddw", mmi::pmaddw}, {"pmsubw", mmi::pmsubw}, {"pmadduw", mmi::pmadduw},
    {"pmulth", mmi::pmulth}, {"pmaddh", mmi::pmaddh}, {"pmsubh", mmi::pmsubh}, {"phmadh", mmi::phmadh}, {"phmsbh", mmi::phmsbh},
};

constexpr u32 kScratch = 0x01100000u;

void replay_mmi(const Json& v, Outcome& o) {
    const Json& in = *v.get("in");
    const Json& form = *v.get("form");
    const std::string op = v.get("op")->string;
    EEContext c;
    c.hi = hx128(in, "hi");
    c.lo = hx128(in, "lo");
    c.sa = 0;
    const u128 s = hx128(in, "rs"), t = hx128(in, "rt");
    u128 rd = hx128(in, "rd");
    u128 rd2 = rd;   // second path
    bool two_paths = false;
    if (auto it = kBin.find(op); it != kBin.end()) {
        // PSLLVW/PSRLVW/PSRAVW assemble as op rd, rt, rs: $8 (JSON "rs") is the value, $9 (JSON "rt") the amount,
        // and mmi.h takes (d, amount, value).
        const bool vshift = op == "psllvw" || op == "psrlvw" || op == "psravw";
        it->second.first(rd, vshift ? t : s, vshift ? s : t);
        it->second.second(rd2, vshift ? t : s, vshift ? s : t);
        two_paths = true;
    } else if (auto it2 = kUn.find(op); it2 != kUn.end()) {
        it2->second.first(rd, t);
        it2->second.second(rd2, t);
        two_paths = true;
    } else if (auto it3 = kSh.find(op); it3 != kSh.end()) {
        const u32 sa = static_cast<u32>(form_int(form, "sa"));
        it3->second.first(rd, t, sa);
        it3->second.second(rd2, t, sa);
        two_paths = true;
    } else if (auto it4 = kHiLo.find(op); it4 != kHiLo.end()) {
        it4->second(c, rd, s, t);
    } else if (op == "plzcw") {
        mmi::plzcw(rd, s);
    } else if (op == "qfsrv") {
        const std::string sf = form_str(form, "sa_form");
        const u32 sa_rs = static_cast<u32>(hx64(in, "sa_rs"));
        const u32 imm = static_cast<u32>(form_int(form, "sa_imm"));
        if (sf == "mtsab") mtsab(c, sa_rs, imm);
        else if (sf == "mtsah") mtsah(c, sa_rs, imm);
        else mtsa(c, sa_rs);
        mmi::qfsrv(c, rd, s, t);
    } else if (op.rfind("pmfhl.", 0) == 0) {
        mmi::pmfhl(c, rd, static_cast<u32>(form_int(form, "fmt")));
    } else if (op == "pmthl.lw") {
        mmi::pmthl(c, s);
    } else if (op == "pmfhi") {
        mmi::pmfhi(c, rd);
    } else if (op == "pmflo") {
        mmi::pmflo(c, rd);
    } else if (op == "pmthi") {
        mmi::pmthi(c, s);
    } else if (op == "pmtlo") {
        mmi::pmtlo(c, s);
    } else if (op == "pdivw") {
        mmi::pdivw(c, s, t);
    } else if (op == "pdivuw") {
        mmi::pdivuw(c, s, t);
    } else if (op == "pdivbw") {
        mmi::pdivbw(c, s, t);
    } else if (op == "lq") {
        EEMemory mem;
        mem.write<u128>(kScratch, s);
        mem.write<u128>(kScratch + 16, t);
        rd = mmi::lq(mem, kScratch + static_cast<u32>(form_int(form, "off")));
    } else if (op == "sq") {
        EEMemory mem;
        mem.write<u128>(kScratch, u128{});
        mem.write<u128>(kScratch + 16, u128{});
        mmi::sq(mem, kScratch + static_cast<u32>(form_int(form, "off")), s);
        rd = mem.read<u128>(kScratch);
        put128(o, "mem0", rd);
        put128(o, "mem1", mem.read<u128>(kScratch + 16));
    } else {
        FAIL("unknown mmi op " << op);
    }
    if (two_paths && rd != rd2) {
        o.notes.push_back("scalar/sse2 paths differ: " + h128(rd) + " vs " + h128(rd2));
        o.mismatched.push_back("paths");
    }
    put128(o, "rd", rd);
    put128(o, "hi", c.hi);
    put128(o, "lo", c.lo);
    put32(o, "sa", mfsa(c));
}

// ---------------------------------------------------------------------------------------------------------
// fpu
// ---------------------------------------------------------------------------------------------------------
void replay_fpu(const Json& v, Outcome& o) {
    const Json& in = *v.get("in");
    const std::string op = v.get("op")->string;
    EEContext c;
    const u32 fs = hx32(in, "fs"), ft = hx32(in, "ft"), acc = hx32(in, "acc"), fcr31 = hx32(in, "fcr31"), fd0 = hx32(in, "fd");
    fpu::set_fpr(c, 1, fs);
    fpu::set_fpr(c, 2, ft);
    fpu::set_fpr(c, 3, acc);
    fpu::set_fpr(c, 4, 0);
    fpu::adda_s(c, 3, 4);                 // ACC = acc_in + 0, as the test program does
    fpu::ctc1(c, 31, fcr31);
    fpu::set_fpr(c, 5, fd0);
    const u32 pre = fpu::cfc1(c, 31);
    if (op == "add.s") fpu::add_s(c, 5, 1, 2);
    else if (op == "sub.s") fpu::sub_s(c, 5, 1, 2);
    else if (op == "mul.s") fpu::mul_s(c, 5, 1, 2);
    else if (op == "div.s") fpu::div_s(c, 5, 1, 2);
    else if (op == "madd.s") fpu::madd_s(c, 5, 1, 2);
    else if (op == "msub.s") fpu::msub_s(c, 5, 1, 2);
    else if (op == "max.s") fpu::max_s(c, 5, 1, 2);
    else if (op == "min.s") fpu::min_s(c, 5, 1, 2);
    else if (op == "sqrt.s") fpu::sqrt_s(c, 5, 2);
    else if (op == "rsqrt.s") fpu::rsqrt_s(c, 5, 1, 2);
    else if (op == "abs.s") fpu::abs_s(c, 5, 1);
    else if (op == "neg.s") fpu::neg_s(c, 5, 1);
    else if (op == "mov.s") fpu::mov_s(c, 5, 1);
    else if (op == "cvt.w.s") fpu::cvt_w_s(c, 5, 1);
    else if (op == "cvt.s.w") fpu::cvt_s_w(c, 5, 1);
    else if (op == "adda.s") fpu::adda_s(c, 1, 2);
    else if (op == "suba.s") fpu::suba_s(c, 1, 2);
    else if (op == "mula.s") fpu::mula_s(c, 1, 2);
    else if (op == "madda.s") fpu::madda_s(c, 1, 2);
    else if (op == "msuba.s") fpu::msuba_s(c, 1, 2);
    else if (op == "c.eq.s") fpu::c_eq_s(c, 1, 2);
    else if (op == "c.lt.s") fpu::c_lt_s(c, 1, 2);
    else if (op == "c.le.s") fpu::c_le_s(c, 1, 2);
    else if (op == "c.f.s") fpu::c_f_s(c);
    else if (op == "ctc1" || op == "cfc1.fcr0") { /* the preset ctc1 is the operation */ }
    else FAIL("unknown fpu op " << op);
    put32(o, "fcr31", fpu::cfc1(c, 31));
    put32(o, "fcr31_pre", pre);
    if (op == "cfc1.fcr0") put32(o, "fcr0", fpu::cfc1(c, 0));   // 0x2E30 = recompiler; interpreter 0x2E00
    put32(o, "fd", fpu::fpr(c, 5));
    put64(o, "fd64", fpu::mfc1(c, 5));
    fpu::set_fpr(c, 6, 0);
    fpu::madd_s(c, 7, 6, 6);              // ACC probe: ACC + 0 * 0
    put32(o, "acc", fpu::fpr(c, 7));
}

// ---------------------------------------------------------------------------------------------------------
// vu0
// ---------------------------------------------------------------------------------------------------------
struct VuForm {
    std::string root;   // vadd, vmadda, vftoi4 ...
    char sfx = 0;       // 0, x/y/z/w (broadcast), q, i
    unsigned dest = 15;
};

VuForm parse_vu(const std::string& op, const Json& form) {
    VuForm f;
    const auto dot = op.find('.');
    const std::string base = op.substr(0, dot);
    f.dest = static_cast<unsigned>(form_int(form, "dest", 15));
    static const char* roots[] = {"vmadda", "vmsuba", "vadda", "vsuba", "vmula", "vmadd", "vmsub", "vmini", "vadd", "vsub", "vmul", "vmax"};
    for (const char* r : roots) {
        const std::string rs = r;
        if (base.rfind(rs, 0) == 0 && (base.size() == rs.size() || (base.size() == rs.size() + 1 && std::string("xyzwqi").find(base.back()) != std::string::npos))) {
            f.root = rs;
            f.sfx = base.size() > rs.size() ? base.back() : 0;
            return f;
        }
    }
    f.root = base;
    return f;
}

void replay_vu0(const Json& v, Outcome& o, bool int_raw_status = false) {
    const Json& in = *v.get("in");
    const Json& form = *v.get("form");
    const std::string op = v.get("op")->string;
    VU0State s;
    vu0::reset(s);
    const u128 fs = hx128(in, "fs"), ft = hx128(in, "ft"), fd = hx128(in, "fd"), acc = hx128(in, "acc");
    vu0::qmtc2(s, 1, fs);
    vu0::qmtc2(s, 2, ft);
    vu0::qmtc2(s, 3, fd);
    vu0::qmtc2(s, 4, acc);
    vu0::adda_bc(s, 15, 4, 0, vu0::kBcX);        // ACC = acc_in + vf0.x (= +0)
    vu0::ctc2(s, vu0::kCtrlI, hx32(in, "i"));
    vu0::ctc2(s, vu0::kCtrlQ, hx32(in, "q"));
    vu0::ctc2(s, vu0::kCtrlStatus, hx32(in, "status"));
    vu0::ctc2(s, vu0::kCtrlMac, hx32(in, "mac"));
    vu0::ctc2(s, vu0::kCtrlClip, hx32(in, "clip"));
    vu0::ctc2(s, 1, hx32(in, "vi1"));
    vu0::ctc2(s, 2, hx32(in, "vi2"));
    // The live I/D bits (STATUS 4..5) persist across vectors on PCSX2 (CTC2 cannot clear them) and the previous
    // vector's Q-pipe op may have left them set; our replay starts from a fresh state, so seed them from the
    // recompiler's observed pre-state (the interpreter's raw CTC2 write cleared them, which is its own class).
    if (int_raw_status) s.status = hx32(in, "status");   // the interpreter's CTC2 $16 writes all 32 bits
    else if (const Json* ob = v.get("obs"); ob && ob->get("status_pre")) s.status |= hx32(*ob, "status_pre") & 0x30u;
    put32(o, "status_pre", vu0::cfc2(s, vu0::kCtrlStatus));
    put32(o, "mac_pre", vu0::cfc2(s, vu0::kCtrlMac));
    put32(o, "clip_pre", vu0::cfc2(s, vu0::kCtrlClip));
    put32(o, "q_pre", vu0::cfc2(s, vu0::kCtrlQ));

    const VuForm f = parse_vu(op, form);
    const unsigned d = f.dest;
    bool int_op = false;
    bool is_ctc2 = false;
    if (f.root == "vadd" || f.root == "vsub" || f.root == "vmul" || f.root == "vmadd" || f.root == "vmsub" || f.root == "vmax" || f.root == "vmini") {
        using Full = void (*)(VU0State&, unsigned, unsigned, unsigned, unsigned);
        using Bc = void (*)(VU0State&, unsigned, unsigned, unsigned, unsigned, unsigned);
        using Qi = void (*)(VU0State&, unsigned, unsigned, unsigned);
        struct Fns { Full full; Bc bc; Qi q; Qi i; };
        static const std::map<std::string, Fns> table = {
            {"vadd", {vu0::add, vu0::add_bc, vu0::add_q, vu0::add_i}},   {"vsub", {vu0::sub, vu0::sub_bc, vu0::sub_q, vu0::sub_i}},
            {"vmul", {vu0::mul, vu0::mul_bc, vu0::mul_q, vu0::mul_i}},   {"vmadd", {vu0::madd, vu0::madd_bc, vu0::madd_q, vu0::madd_i}},
            {"vmsub", {vu0::msub, vu0::msub_bc, vu0::msub_q, vu0::msub_i}}, {"vmax", {vu0::max, vu0::max_bc, vu0::max_q, vu0::max_i}},
            {"vmini", {vu0::mini, vu0::mini_bc, vu0::mini_q, vu0::mini_i}},
        };
        const Fns& fn = table.at(f.root);
        if (f.sfx == 0) fn.full(s, d, 3, 1, 2);
        else if (f.sfx == 'q') fn.q(s, d, 3, 1);
        else if (f.sfx == 'i') fn.i(s, d, 3, 1);
        else fn.bc(s, d, 3, 1, 2, static_cast<unsigned>(std::string("xyzw").find(f.sfx)));
    } else if (f.root == "vadda" || f.root == "vsuba" || f.root == "vmula" || f.root == "vmadda" || f.root == "vmsuba") {
        using Full = void (*)(VU0State&, unsigned, unsigned, unsigned);
        using Bc = void (*)(VU0State&, unsigned, unsigned, unsigned, unsigned);
        using Qi = void (*)(VU0State&, unsigned, unsigned);
        struct Fns { Full full; Bc bc; Qi q; Qi i; };
        static const std::map<std::string, Fns> table = {
            {"vadda", {vu0::adda, vu0::adda_bc, vu0::adda_q, vu0::adda_i}},   {"vsuba", {vu0::suba, vu0::suba_bc, vu0::suba_q, vu0::suba_i}},
            {"vmula", {vu0::mula, vu0::mula_bc, vu0::mula_q, vu0::mula_i}},   {"vmadda", {vu0::madda, vu0::madda_bc, vu0::madda_q, vu0::madda_i}},
            {"vmsuba", {vu0::msuba, vu0::msuba_bc, vu0::msuba_q, vu0::msuba_i}},
        };
        const Fns& fn = table.at(f.root);
        if (f.sfx == 0) fn.full(s, d, 1, 2);
        else if (f.sfx == 'q') fn.q(s, d, 1);
        else if (f.sfx == 'i') fn.i(s, d, 1);
        else fn.bc(s, d, 1, 2, static_cast<unsigned>(std::string("xyzw").find(f.sfx)));
    } else if (f.root == "vopmula") {
        vu0::opmula(s, 1, 2);
    } else if (f.root == "vopmsub") {
        vu0::opmsub(s, 3, 1, 2);
    } else if (f.root == "vabs") {
        vu0::abs(s, d, 3, 1);
    } else if (f.root == "vmove") {
        vu0::move(s, d, 3, 1);
    } else if (f.root == "vmr32") {
        vu0::mr32(s, d, 3, 1);
    } else if (f.root.rfind("vftoi", 0) == 0) {
        vu0::ftoi(s, d, 3, 1, form_int(form, "frac"));
    } else if (f.root.rfind("vitof", 0) == 0) {
        vu0::itof(s, d, 3, 1, form_int(form, "frac"));
    } else if (f.root == "vclipw") {
        vu0::clip(s, 1, 2);
    } else if (f.root == "vdiv") {
        vu0::div(s, 1, static_cast<unsigned>(form_int(form, "fsf")), 2, static_cast<unsigned>(form_int(form, "ftf")));
        vu0::waitq(s);
    } else if (f.root == "vrsqrt") {
        vu0::rsqrt(s, 1, static_cast<unsigned>(form_int(form, "fsf")), 2, static_cast<unsigned>(form_int(form, "ftf")));
        vu0::waitq(s);
    } else if (f.root == "vsqrt") {
        vu0::sqrt(s, 2, static_cast<unsigned>(form_int(form, "ftf")));
        vu0::waitq(s);
    } else if (f.root == "vwaitq") {
        vu0::waitq(s);
    } else if (f.root == "vnop") {
        vu0::nop(s);
    } else if (f.root == "viadd") { vu0::iadd(s, 3, 1, 2); int_op = true; }
    else if (f.root == "visub") { vu0::isub(s, 3, 1, 2); int_op = true; }
    else if (f.root == "viand") { vu0::iand(s, 3, 1, 2); int_op = true; }
    else if (f.root == "vior") { vu0::ior(s, 3, 1, 2); int_op = true; }
    else if (f.root == "viaddi") { vu0::iaddi(s, 3, 1, form_int(form, "imm")); int_op = true; }
    else if (f.root == "vmfir") { vu0::mfir(s, d, 3, 1); }
    else if (f.root == "ctc2") {
        const unsigned reg = static_cast<unsigned>(form_int(form, "reg"));
        vu0::ctc2(s, reg, static_cast<u32>(static_cast<u64>(form.get("val")->number)));   // a JSON number, not hex text
        put32(o, "readback", vu0::cfc2(s, reg));
        is_ctc2 = true;
    } else {
        FAIL("unknown vu0 op " << op);
    }
    put32(o, "status", vu0::cfc2(s, vu0::kCtrlStatus));
    put32(o, "mac", vu0::cfc2(s, vu0::kCtrlMac));
    put32(o, "clip", vu0::cfc2(s, vu0::kCtrlClip));
    if (!is_ctc2) put32(o, "q", vu0::cfc2(s, vu0::kCtrlQ));
    if (int_op) put32(o, "vi3", vu0::cfc2(s, 3));
    else put128(o, "fd", vu0::qmfc2(s, 3));
    vu0::madd_bc(s, 15, 5, 0, 0, vu0::kBcX);     // ACC probe: vf5 = ACC + vf0 * vf0.x
    put128(o, "acc", vu0::qmfc2(s, 5));
    put128(o, "fs_after", vu0::qmfc2(s, 1));
    put128(o, "ft_after", vu0::qmfc2(s, 2));
}

// ---------------------------------------------------------------------------------------------------------
// core
// ---------------------------------------------------------------------------------------------------------
void replay_core(const Json& v, Outcome& o) {
    const Json& in = *v.get("in");
    const Json& form = *v.get("form");
    const std::string op = v.get("op")->string;
    if (has(in, "mem0")) {
        EEMemory mem;
        mem.write<u128>(kScratch, hx128(in, "mem0"));
        mem.write<u128>(kScratch + 16, hx128(in, "mem1"));
        u64 rt = hx64(in, "rt");
        const u32 va = kScratch + static_cast<u32>(form_int(form, "off"));
        const u32 w = mem.read<u32>(va & core::kWordMask);
        const u64 dw = mem.read<u64>(va & core::kDwordMask);
        if (op == "lwl") rt = core::lwl(rt, w, va);
        else if (op == "lwr") rt = core::lwr(rt, w, va);
        else if (op == "ldl") rt = core::ldl(rt, dw, va);
        else if (op == "ldr") rt = core::ldr(rt, dw, va);
        else if (op == "swl") mem.write<u32>(va & core::kWordMask, core::swl(w, rt, va));
        else if (op == "swr") mem.write<u32>(va & core::kWordMask, core::swr(w, rt, va));
        else if (op == "sdl") mem.write<u64>(va & core::kDwordMask, core::sdl(dw, rt, va));
        else if (op == "sdr") mem.write<u64>(va & core::kDwordMask, core::sdr(dw, rt, va));
        else if (op == "lb") rt = core::lb(mem.read<u8>(va));
        else if (op == "lbu") rt = core::lbu(mem.read<u8>(va));
        else if (op == "lh") rt = core::lh(mem.read<u16>(va));
        else if (op == "lhu") rt = core::lhu(mem.read<u16>(va));
        else if (op == "lw") rt = core::lw(mem.read<u32>(va));
        else if (op == "lwu") rt = core::lwu(mem.read<u32>(va));
        else if (op == "ld") rt = mem.read<u64>(va);
        else FAIL("unknown core memory op " << op);
        put64(o, "rt", rt);
        put128(o, "mem0", mem.read<u128>(kScratch));
        put128(o, "mem1", mem.read<u128>(kScratch + 16));
        return;
    }
    const u64 rs = hx64(in, "rs"), rt = hx64(in, "rt");
    const s32 imm = form_int(form, "imm");
    const unsigned sa = static_cast<unsigned>(imm);
    EEContext c;
    u64 rd = 0;
    if (op == "addu") rd = core::add32(rs, rt);
    else if (op == "subu") rd = core::sub32(rs, rt);
    else if (op == "add") rd = core::add32(rs, rt);
    else if (op == "sub") rd = core::sub32(rs, rt);
    else if (op == "and") rd = core::and64(rs, rt);
    else if (op == "or") rd = core::or64(rs, rt);
    else if (op == "xor") rd = core::xor64(rs, rt);
    else if (op == "nor") rd = core::nor64(rs, rt);
    else if (op == "slt") rd = core::slt(rs, rt);
    else if (op == "sltu") rd = core::sltu(rs, rt);
    else if (op == "daddu" || op == "dadd") rd = core::add64(rs, rt);
    else if (op == "dsubu") rd = core::sub64(rs, rt);
    // `op $10, $8, $9` assembles as op rd, rt, rs for the shift-by-register forms: $8 (JSON "rs") is the value,
    // $9 (JSON "rt") the amount.
    else if (op == "sllv") rd = core::sllv(rs, rt);
    else if (op == "srlv") rd = core::srlv(rs, rt);
    else if (op == "srav") rd = core::srav(rs, rt);
    else if (op == "dsllv") rd = core::dsllv(rs, rt);
    else if (op == "dsrlv") rd = core::dsrlv(rs, rt);
    else if (op == "dsrav") rd = static_cast<u64>(static_cast<s64>(rs) >> (static_cast<unsigned>(rt) & 63u));
    else if (op == "movn") rd = core::movn_taken(rt) ? rs : 0u;
    else if (op == "movz") rd = core::movz_taken(rt) ? rs : 0u;
    else if (op == "mult") { mult(c, 0, static_cast<u32>(rs), static_cast<u32>(rt)); rd = c.lo.u64[0]; }
    else if (op == "multu") { multu(c, 0, static_cast<u32>(rs), static_cast<u32>(rt)); rd = c.lo.u64[0]; }
    else if (op == "div") { div(c, 0, static_cast<u32>(rs), static_cast<u32>(rt)); }
    else if (op == "divu") { divu(c, 0, static_cast<u32>(rs), static_cast<u32>(rt)); }
    else if (op == "sll") rd = core::sll(rt, sa);
    else if (op == "srl") rd = core::srl(rt, sa);
    else if (op == "sra") rd = core::sra(rt, sa);
    else if (op == "dsll") rd = core::dsll(rt, sa);
    else if (op == "dsrl") rd = core::dsrl(rt, sa);
    else if (op == "dsra") rd = core::dsra(rt, sa);
    else if (op == "dsll32") rd = core::dsll32(rt, sa);
    else if (op == "dsrl32") rd = core::dsrl32(rt, sa);
    else if (op == "dsra32") rd = core::dsra32(rt, sa);
    else if (op == "addiu" || op == "addi") rd = core::add32i(rs, imm);
    else if (op == "daddiu") rd = core::add64i(rs, imm);
    else if (op == "slti") rd = core::slti(rs, imm);
    else if (op == "sltiu") rd = core::sltiu(rs, imm);
    else if (op == "andi") rd = core::andi(rs, static_cast<u32>(imm));
    else if (op == "ori") rd = core::ori(rs, static_cast<u32>(imm));
    else if (op == "xori") rd = core::xori(rs, static_cast<u32>(imm));
    else if (op == "lui") rd = core::lui(static_cast<u32>(imm));
    else FAIL("unknown core op " << op);
    put64(o, "rd", rd);
    put128(o, "hi", c.hi);
    put128(o, "lo", c.lo);
}

// ---------------------------------------------------------------------------------------------------------
// Classification of mismatches into documented, deliberate disagreements.
// ---------------------------------------------------------------------------------------------------------
bool any_exp255_in(const Json& in, const char* k, int lanes) {
    if (!has(in, k)) return false;
    if (lanes == 1) return exp255(hx32(in, k));
    const u128 q = hx128(in, k);
    for (int i = 0; i < lanes; ++i)
        if (exp255(q.u32[i])) return true;
    return false;
}

u32 lane_of(const std::string& hex128, int i) { return static_cast<u32>(hx(hex128, 8 * i + 7, 8 * i)); }

// Documented, deliberate differences from both PCSX2 engines. Every field in `o.mismatched` (fields that match
// neither engine) must be explained by a class; returns the "+"-joined class names, or "" when something is left.
// `obs` is the oracle view (interpreter where it differs, recompiler otherwise).
std::string classify(const Json& v, const Outcome& o, const std::map<std::string, std::string>& obs) {
    const std::string fam = v.get("family")->string;
    const std::string op = v.get("op")->string;
    const Json& in = *v.get("in");
    const Json& form = *v.get("form");
    std::set<std::string> left(o.mismatched.begin(), o.mismatched.end());
    std::set<std::string> classes;
    auto explain = [&](std::initializer_list<const char*> fields, const char* cls) {
        bool any = false;
        for (const char* f : fields) any = left.erase(f) || any;
        if (any) classes.insert(cls);
    };
    auto obs32 = [&](const char* k) { return static_cast<u32>(hx(obs.at(k), 7, 0)); };
    auto ours32 = [&](const char* k) { return static_cast<u32>(hx(o.ours.at(k), 7, 0)); };
    auto done = [&]() {
        if (!left.empty()) return std::string();
        std::string r;
        for (const auto& c : classes) r += (r.empty() ? "" : "+") + c;
        return r;
    };
    if (fam == "fpu") {
        // FCR31 cause bits: we only ever set them; the interpreter clears O/U (bits 14..15) on ADD/SUB/MUL/MADD
        // and the recompiler clears I/D on DIV/SQRT/RSQRT. The binary never reads FCR31.
        if (left.count("fcr31") && (hx32(in, "fcr31") & 0x3C000u) && (ours32("fcr31") & ~0x3C000u) == (obs32("fcr31") & ~0x3C000u))
            explain({"fcr31"}, "fcr31-cause-clear");
        // PCSX2 computes on host IEEE floats: an operand with exponent 255 is Inf/NaN to it and any result that
        // would land in the EE's exponent-255 range is clamped to +/-0x7F7FFFFF (IEEE FLT_MAX). The EE has no
        // Inf/NaN: exponent 255 is a normal binade and the overflow/divide-by-zero value is +/-0x7FFFFFFF (manual).
        bool in255 = false;
        if (op == "sqrt.s") in255 = any_exp255_in(in, "ft", 1);
        else if (op == "abs.s" || op == "cvt.w.s") in255 = any_exp255_in(in, "fs", 1);
        else if (op != "neg.s" && op != "mov.s" && op != "cvt.s.w") in255 = any_exp255_in(in, "fs", 1) || any_exp255_in(in, "ft", 1);
        if (op == "madd.s" || op == "msub.s" || op == "madda.s" || op == "msuba.s")
            in255 = in255 || any_exp255_in(in, "acc", 1) || exp255(fpu::mul(hx32(in, "fs"), hx32(in, "ft")));   // clamped product
        if (in255) {
            explain({"fd", "fd64", "acc"}, "ee-range-input");
            explain({"fcr31"}, "ee-range-input");   // compares: PCSX2 clamps the operands, so Inf == FLT_MAX
        } else if (left.count("fd") || left.count("acc")) {
            const u32 ours_fd = ours32("fd"), ours_acc = ours32("acc");
            const u32 obs_fd = obs32("fd"), obs_acc = obs32("acc");
            if ((exp255(ours_fd) || exp255(ours_acc)) && obs_fd == clamp_ieee(ours_fd) && obs_acc == clamp_ieee(ours_acc) &&
                hx(obs.at("fd64"), 15, 0) == core::sext32(obs_fd))
                explain({"fd", "fd64", "acc"}, "ee-range-clamp");
            // DIV.S rounds to nearest here (integration decision 1, the recompiler's game state); the interpreter
            // truncates like every other FPU op.
            else if (op == "div.s" && (ours_fd - obs_fd == 1u) && hx(obs.at("fd64"), 15, 0) == core::sext32(obs_fd))
                explain({"fd", "fd64"}, "div-rounding");
            // RSQRT.S by +/-0: the interpreter gives the clamp the sign of ft, we (and the recompiler) the sign of fs.
            else if (op == "rsqrt.s" && !(hx32(in, "ft") & 0x7F800000u) && obs_fd == (clamp_ieee(ours_fd) ^ 0x80000000u) &&
                     hx(obs.at("fd64"), 15, 0) == core::sext32(obs_fd))
                explain({"fd", "fd64"}, "ee-range-clamp+rsqrt-zero-sign");
            // MAX.S/MIN.S: PCSX2 orders -0 below +0 and never flushes; we flush and return fs on ties (unused by the game).
            else if ((op == "max.s" || op == "min.s") && (obs_fd == hx32(in, "fs") || obs_fd == hx32(in, "ft")))
                explain({"fd", "fd64"}, "maxmin-zero-order");
            // SQRT.S of -0 (or a flushed negative denormal): the interpreter keeps the sign (-0), we return +0.
            else if (op == "sqrt.s" && ours_fd == 0u && obs_fd == 0x80000000u)
                explain({"fd", "fd64"}, "sqrt-negative-zero");
            // ADD/SUB alignment: we keep the EE recompiler's 25-binade rule (lead decision, ADR-0012); the exact
            // round-toward-zero value is one ULP lower in magnitude.
            else if ((ours_fd - obs_fd == 1u || ours_acc - obs_acc == 1u) && (ours_fd == obs_fd || ours_fd - obs_fd == 1u) &&
                     (ours_acc == obs_acc || ours_acc - obs_acc == 1u) && hx(obs.at("fd64"), 15, 0) == core::sext32(obs_fd))
                explain({"fd", "fd64", "acc"}, "add-alignment");
        }
        return done();
    }
    if (fam == "vu0") {
        // The preamble writes ACC through VADDAx, so an exponent-255 lane in acc_in affects every vector's flags.
        bool in255 = any_exp255_in(in, "fs", 4) || any_exp255_in(in, "ft", 4) || any_exp255_in(in, "acc", 4);
        // a clamped intermediate product (PCSX2 rounds fs * ft to IEEE before the add/sub)
        if (op.find("mul") != std::string::npos || op.find("madd") != std::string::npos || op.find("msub") != std::string::npos ||
            op.find("opm") != std::string::npos) {
            const u128 fs = hx128(in, "fs"), ft = hx128(in, "ft");
            const VuForm f = parse_vu(op, form);
            const bool opm = op.find("opm") != std::string::npos;
            for (int i = 0; i < (opm ? 3 : 4); ++i) {
                u32 t = ft.u32[i];
                if (f.sfx == 'q') t = hx32(in, "q");
                else if (f.sfx == 'i') t = hx32(in, "i");
                else if (f.sfx) t = ft.u32[std::string("xyzw").find(f.sfx)];
                if (opm) t = ft.u32[(i + 2) % 3];
                const u32 sl = opm ? fs.u32[(i + 1) % 3] : fs.u32[i];
                in255 = in255 || exp255(fpu::mul(sl, t));
            }
        }
        const bool qop = op == "vdiv" || op == "vrsqrt" || op == "vsqrt";
        // VRSQRT with both operands zero: the interpreter raises I and D and leaves Q = +/-0, the recompiler raises
        // I; we raise D with +/-max (manual: ft = 0 -> D).
        if (op == "vrsqrt") {
            const u32 fsl = lane_of(in.get("fs")->string, form_int(form, "fsf")), ftl = lane_of(in.get("ft")->string, form_int(form, "ftf"));
            if (!(fsl & 0x7F800000u) && !(ftl & 0x7F800000u)) explain({"q", "status"}, "rsqrt-zero-operands");
        }
        if (in255) {
            explain({"fd", "acc", "q", "mac", "status", "mac_pre", "status_pre"}, "ee-range-input");
        } else if (left.count("fd") || left.count("acc") || left.count("q")) {
            bool ours255 = false, consistent = true;
            for (const char* k : {"fd", "acc"}) {
                if (!o.ours.count(k)) continue;
                for (int i = 0; i < 4; ++i) {
                    const u32 ov = lane_of(o.ours.at(k), i), pv = lane_of(obs.at(k), i);
                    ours255 = ours255 || exp255(ov);
                    consistent = consistent && pv == clamp_ieee(ov);
                }
            }
            bool sign_flip = false;
            if (qop && o.ours.count("q")) {
                ours255 = ours255 || exp255(ours32("q"));
                const u32 oq = ours32("q"), pq = obs32("q");
                // VRSQRT by -0 (or a negative denormal): the interpreter gives the clamp the sign of ft as well.
                const u32 ftl = lane_of(in.get("ft")->string, form_int(form, "ftf"));
                if (op == "vrsqrt" && (ftl & 0x80000000u) && !(ftl & 0x7F800000u) && pq == (clamp_ieee(oq) ^ 0x80000000u))
                    sign_flip = true;
                else
                    consistent = consistent && pq == clamp_ieee(oq);
            }
            if (ours255 && consistent) {
                explain({"fd", "acc", "q", "mac", "status"}, "ee-range-clamp");
                if (sign_flip) classes.insert("rsqrt-negative-zero-sign");
            }
            // VRSQRT: PCSX2 rounds sqrt(ft) to single precision before dividing; we evaluate fs / sqrt(ft) in double.
            else if (op == "vrsqrt" && (ours32("q") - obs32("q") == 1u || obs32("q") - ours32("q") == 1u))
                explain({"q"}, "rsqrt-intermediate-rounding");
            // VMAX/VMINI: PCSX2 orders -0 below +0 and never flushes; we flush and return fs on ties.
            else if (op.rfind("vmax", 0) == 0 || op.rfind("vmini", 0) == 0) {
                const std::string fs = in.get("fs")->string, ft = in.get("ft")->string;
                bool fits = true;
                for (int i = 0; i < 4; ++i) {
                    const u32 pv = lane_of(obs.at("fd"), i);
                    fits = fits && (pv == lane_of(fs, i) || pv == lane_of(ft, i) || pv == lane_of(o.ours.at("fd"), i));
                }
                if (fits) explain({"fd"}, "maxmin-zero-order");
            }
        }
        // ADD/SUB alignment (see fpu.h `add`): PCSX2's VU path is exact round-toward-zero, every differing lane is
        // one ULP below ours in magnitude; MAC/STATUS follow the lane values.
        if (!qop && (left.count("fd") || left.count("acc"))) {
            bool one_ulp = true, any = false;
            for (const char* k : {"fd", "acc"}) {
                if (!o.ours.count(k)) continue;
                for (int i = 0; i < 4; ++i) {
                    const u32 ov = lane_of(o.ours.at(k), i), pv = lane_of(obs.at(k), i);
                    if (ov == pv) continue;
                    any = true;
                    one_ulp = one_ulp && (ov - pv == 1u);
                }
            }
            if (any && one_ulp) explain({"fd", "acc", "mac", "status"}, "add-alignment");
        }
        if (op == "ctc2") {
            const int reg = form_int(form, "reg");
            if (reg == 18 || reg == 27) explain({"readback", "clip"}, "ctc2-width");   // CLIP / CMSAR0: 24 / 16 bits here, 32 in PCSX2
        }
        return done();
    }
    if (fam == "mmi") {
        if (op == "qfsrv") {
            // SA is held in bits here (manual: MTSAB scales by 8, MTSAH by 16); PCSX2 holds the byte count and
            // masks MTSA to 4 bits. QFSRV results agree for MTSAB/MTSAH; only MFSA and the raw MTSA path differ.
            const std::string sf = form_str(form, "sa_form");
            if (sf != "mtsa" && obs32("sa") == (ours32("sa") >> 3)) explain({"sa"}, "sa-units");
            if (sf == "mtsa") explain({"sa", "rd"}, "sa-units");
        }
        if (op == "pmfhl.raw" && obs.at("rd") == in.get("rd")->string) explain({"rd"}, "pmfhl-reserved");
        if (op == "phmadh" || op == "phmsbh") {
            // The manual leaves the odd words of HI/LO undefined; we leave them unchanged, PCSX2 stores the odd
            // halfword products there (PHMADH: p1, p3, p5, p7; PHMSBH: their one's complements).
            const u128 s = hx128(in, "rs"), t = hx128(in, "rt");
            u32 p[8];
            for (int i = 0; i < 8; ++i) p[i] = static_cast<u32>(static_cast<s32>(s.s16[i]) * t.s16[i]);
            if (op == "phmsbh")
                for (u32& x : p) x = ~x;
            const bool fits = lane_of(obs.at("lo"), 1) == p[1] && lane_of(obs.at("hi"), 1) == p[3] &&
                              lane_of(obs.at("lo"), 3) == p[5] && lane_of(obs.at("hi"), 3) == p[7] &&
                              lane_of(obs.at("lo"), 0) == lane_of(o.ours.at("lo"), 0) && lane_of(obs.at("hi"), 0) == lane_of(o.ours.at("hi"), 0) &&
                              lane_of(obs.at("lo"), 2) == lane_of(o.ours.at("lo"), 2) && lane_of(obs.at("hi"), 2) == lane_of(o.ours.at("hi"), 2);
            if (fits) explain({"hi", "lo"}, "phmadh-odd-words");
        }
        return done();
    }
    return done();
}

// Why a result that matches the recompiler but not the interpreter is accepted: the interpreter's shortcut.
std::string rec_class(const Json& v, const std::vector<std::string>& fields) {
    const std::string fam = v.get("family")->string;
    const std::string op = v.get("op")->string;
    auto only = [&](std::initializer_list<const char*> allowed) {
        for (const std::string& m : fields) {
            bool ok = false;
            for (const char* f : allowed) ok = ok || m == f;
            if (!ok) return false;
        }
        return true;
    };
    if (fam == "mmi" && (op == "pmaddw" || op == "pmsubw")) return "int-drops-64bit-carry";
    if (fam == "mmi" && op == "qfsrv") return "int-raw-mtsa";
    if (fam == "vu0" && only({"status", "status_pre"})) return "int-ctc2-status-writes-live-bits";
    if (fam == "vu0" && op == "ctc2" && only({"readback", "status", "status_pre"})) return "int-ctc2-raw-write";
    if (fam == "vu0" && (op == "vrsqrt" || op == "vdiv") && only({"q", "status", "status_pre"})) return "int-rsqrt-zero-operands";
    if (fam == "vu0" && only({"fd", "acc", "mac", "status", "status_pre", "mac_pre", "q"})) return "int-ee-range";
    if (fam == "fpu" && only({"fd", "fd64", "acc"}) && (op == "add.s" || op == "sub.s" || op == "adda.s" || op == "suba.s" ||
                                                      op.rfind("madd", 0) == 0 || op.rfind("msub", 0) == 0))
        return "int-exact-rz-or-ee-range";
    // SQRT.S rounds to nearest like the recompiler (fpu.h sqrt_nearest, 2026-10-31); the interpreter truncates.
    if (fam == "fpu" && op == "sqrt.s" && only({"fd", "fd64"})) return "int-sqrt-truncates";
    if (fam == "fpu" && only({"fd", "fd64", "acc"})) return "int-ee-range";
    if (fam == "fpu" && only({"fcr0"})) return "int-fcr0";
    if (fam == "fpu" && only({"fcr31", "fcr31_pre"})) return "int-fcr31-cause-clear";
    return "rec";
}

struct Summary {
    int agree = 0, agree_rec = 0, disagree = 0, bad = 0, missing = 0;
    std::map<std::string, int> classes;
};

} // namespace

TEST_CASE("pcsx2 vectors: every observed result is reproduced by the headers (or is a documented disagreement)") {
    const std::string path = std::string(P3FES_REPO_DIR) + "/tests/ee/vectors/pcsx2_vectors.json";
    std::ifstream f(path, std::ios::binary);
    REQUIRE_MESSAGE(f.good(), "cannot open " << path);
    std::stringstream ss;
    ss << f.rdbuf();
    const auto doc = p3fes::test::json::parse(ss.str());
    REQUIRE(doc.has_value());
    const Json* vectors = doc->get("vectors");
    REQUIRE(vectors != nullptr);
    const char* report_path = std::getenv("P3FES_EEVEC_REPORT");
    std::ofstream report;
    if (report_path) report.open(report_path, std::ios::binary);

    std::map<std::string, Summary> per_family;
    int status_mismatch = 0;
    for (const Json& v : vectors->array) {
        const std::string id = v.get("id")->string;
        const std::string fam = v.get("family")->string;
        Summary& sum = per_family[fam];
        const Json* obs = v.get("obs");
        if (!obs || obs->type != Json::Type::Object) {
            ++sum.missing;
            if (report.is_open()) report << "{\"id\":\"" << id << "\",\"status\":\"missing\"}\n";
            continue;
        }
        Outcome o;
        if (fam == "hilo") replay_hilo(v, o);
        else if (fam == "mmi") replay_mmi(v, o);
        else if (fam == "fpu") replay_fpu(v, o);
        else if (fam == "vu0") replay_vu0(v, o);
        else if (fam == "core") replay_core(v, o);
        else FAIL("unknown family " << fam);
        // oracle view: the interpreter's value where it differs from the recompiler's
        const Json* obs_int = v.get("obs_int");
        std::map<std::string, std::string> oracle, rec;
        for (const auto& [k, ob] : obs->object) {
            rec[k] = ob.string;
            const Json* oi = obs_int && obs_int->type == Json::Type::Object ? obs_int->get(k.c_str()) : nullptr;
            oracle[k] = oi ? oi->string : ob.string;
        }
        // The interpreter's CTC2 $16 writes the live STATUS bits too (vu0_3400): its fields are compared against a
        // replay that models that write, so the artefact does not mask (or fake) other differences.
        Outcome o_int;
        const bool have_int = obs_int && obs_int->type == Json::Type::Object;
        if (fam == "vu0" && have_int) replay_vu0(v, o_int, true);
        // per field: accept the interpreter's value, else the recompiler's (noted), else it is a mismatch
        std::vector<std::string> rec_only;
        for (const auto& [k, ours] : o.ours) {
            if (!oracle.count(k)) continue;   // not observed for this op
            const bool from_int = have_int && obs_int->get(k.c_str());
            const std::string& ours_vs_oracle = (from_int && o_int.ours.count(k)) ? o_int.ours.at(k) : ours;
            if (oracle.at(k) == ours_vs_oracle) continue;
            if (rec.at(k) == ours) rec_only.push_back(k);
            else o.mismatched.push_back(k);
        }
        std::string status = "agree";
        if (!o.mismatched.empty()) {
            const std::string cls = classify(v, o, oracle);
            status = cls.empty() ? "mismatch" : "disagree:" + cls;
        } else if (!rec_only.empty()) {
            status = "agree-rec:" + rec_class(v, rec_only);
        }
        if (status == "agree") ++sum.agree;
        else if (status == "mismatch") ++sum.bad;
        else if (status.rfind("agree-rec:", 0) == 0) { ++sum.agree_rec; ++sum.classes[status]; }
        else { ++sum.disagree; ++sum.classes[status]; }
        const Json* stored = v.get("status");
        if (!stored || stored->string != status) ++status_mismatch;
        if (report.is_open()) {
            report << "{\"id\":\"" << id << "\",\"status\":\"" << status << "\",\"ours\":{";
            bool first = true;
            for (const auto& [k, val] : o.ours) {
                report << (first ? "" : ",") << "\"" << k << "\":\"" << val << "\"";
                first = false;
            }
            report << "},\"mismatched\":[";
            first = true;
            for (const auto& m : o.mismatched) {
                report << (first ? "" : ",") << "\"" << m << "\"";
                first = false;
            }
            for (const auto& m : rec_only) {
                report << (first ? "" : ",") << "\"" << m << "\"";
                first = false;
            }
            report << "]}\n";
        }
        if (status == "mismatch") {
            std::string detail = id + " " + v.get("op")->string + ":";
            for (const auto& m : o.mismatched)
                detail += " " + m + " ours=" + (o.ours.count(m) ? o.ours.at(m) : "?") + " oracle=" + oracle.at(m) +
                          (rec.at(m) != oracle.at(m) ? " rec=" + rec.at(m) : "");
            for (const auto& n : o.notes) detail += " [" + n + "]";
            CHECK_MESSAGE(false, detail);
        }
    }
    for (const auto& [fam, s] : per_family) {
        std::string classes;
        for (const auto& [c, n] : s.classes) classes += " " + c + "=" + std::to_string(n);
        MESSAGE(fam << ": agree " << s.agree << ", agree-rec " << s.agree_rec << ", disagree " << s.disagree << " (" << classes
                    << " ), mismatch " << s.bad << ", missing " << s.missing);
    }
    CHECK_MESSAGE(status_mismatch == 0, status_mismatch << " vectors carry a stale or missing `status`; regenerate with "
                                                            "P3FES_EEVEC_REPORT=<file> p3fes_tests -tc=\"pcsx2 vectors*\" then "
                                                            "python -I tools/ours/eevec/annotate.py --report <file>");
}
