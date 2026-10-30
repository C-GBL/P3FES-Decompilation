// R5900 decoder: the non-constexpr diagnostics (mnemonic text). Tables and decode() live in
// r5900_decode.h so tests can static_assert encodings. See the header for scope and
// attribution (layout after ps2-web-recomp recomp/r5900.cpp @ c0f476e, MIT).
#include "r5900_decode.h"

namespace p3fes::recomp {

namespace {

constexpr const char* kMnemonics[] = {
#define P3FES_X(name, text) text,
    P3FES_R5900_OPS(P3FES_X)
#undef P3FES_X
};
static_assert(sizeof(kMnemonics) / sizeof(kMnemonics[0]) == static_cast<std::size_t>(Op::Count));

// Minimal bounded string builder (no <string>, no exceptions).
struct Out {
    char* buf;
    std::size_t cap;
    std::size_t len = 0;
    void put(char c) noexcept {
        if (len + 1 < cap) buf[len] = c;
        ++len;
    }
    void put(const char* s) noexcept {
        for (; *s; ++s) put(*s);
    }
    void finish() noexcept {
        if (cap) buf[len < cap ? len : cap - 1] = '\0';
    }
};

constexpr const char kPmfhlSuffix[5][5] = {".lw", ".uw", ".slw", ".lh", ".sh"};

}  // namespace

const char* mnemonic(Op op) noexcept {
    const auto i = static_cast<std::size_t>(op);
    return i < static_cast<std::size_t>(Op::Count) ? kMnemonics[i] : kMnemonics[0];
}

std::size_t variant_mnemonic(const Insn& insn, char* out, std::size_t cap) noexcept {
    Out o{out, cap};
    const char* base = mnemonic(insn.op);
    switch (unit_of(insn.op)) {
    case Unit::Vu0Macro:
        o.put(base);
        if (insn.vu_bc) o.put("xyzw"[insn.bc & 3]);
        // vnop / vwaitq / vsqrt / vrsqrt carry no dest mask (vsqrt/vrsqrt reuse the bits as fsf/ftf).
        if (insn.op != Op::Vnop && insn.op != Op::Vwaitq && insn.op != Op::Vsqrt && insn.op != Op::Vrsqrt) {
            o.put('.');
            if (insn.dest & 8) o.put('x');
            if (insn.dest & 4) o.put('y');
            if (insn.dest & 2) o.put('z');
            if (insn.dest & 1) o.put('w');
        }
        break;
    case Unit::Cop0:
        o.put(base);
        if (insn.op == Op::Sync) o.put(insn.sync_p() ? ".p" : ".l");
        break;
    case Unit::Mmi:
        o.put(base);
        if (insn.op == Op::Pmfhl) o.put(kPmfhlSuffix[insn.fmt < 5 ? insn.fmt : 0]);
        break;
    case Unit::Cop2Transfer:
        o.put(base);
        if (insn.interlock) o.put(".i");
        break;
    default:
        o.put(base);
        break;
    }
    o.finish();
    return o.len;
}

}  // namespace p3fes::recomp
