// SSE2-vs-scalar equivalence for every lane-parallel MMI operation (runtime/include/p3fes/ee/mmi.h).
// Both namespaces are always compiled; this test feeds the same random and edge-value quadwords through
// p3fes::ee::mmi::scalar::* and p3fes::ee::mmi::sse2::* and requires bit-identical results. Operations that
// the SSE2 namespace re-exports from scalar (pext5, ppac5, plzcw, psllvw, psrlvw, psravw, qfsrv) are included
// so the table stays the complete instruction list; for them the check is trivially true.
#include "ee_test_util.h"

#include "p3fes/ee/mmi.h"

#include <string>

using namespace p3fes;
using namespace p3fes::ee;
using namespace p3fes::ee_test;

namespace {

using BinOp = void (*)(u128&, const u128&, const u128&);
using UnOp = void (*)(u128&, const u128&);
using ShiftOp = void (*)(u128&, const u128&, u32);

struct Rng {
    u64 s = 0x9E3779B97F4A7C15ull;
    u64 next() noexcept {
        s ^= s << 13;
        s ^= s >> 7;
        s ^= s << 17;
        return s;
    }
};

// Mostly random lanes, with saturation / sign boundaries injected often enough to exercise every branch.
u128 random_quad(Rng& rng) {
    u128 q{};
    for (int i = 0; i < 4; ++i) {
        const u64 r = rng.next();
        switch ((r >> 56) % 10u) {
        case 0: q.u32[i] = 0u; break;
        case 1: q.u32[i] = 0xFFFFFFFFu; break;
        case 2: q.u32[i] = 0x80000000u; break;
        case 3: q.u32[i] = 0x7FFFFFFFu; break;
        case 4: q.u32[i] = 0x80008000u; break;
        case 5: q.u32[i] = 0x7FFF7FFFu; break;
        case 6: q.u32[i] = 0x80808080u; break;
        case 7: q.u32[i] = 0x7F7F7F7Fu; break;
        default: q.u32[i] = static_cast<u32>(r); break;
        }
    }
    return q;
}

constexpr int kIterations = 4000;

struct BinCase { const char* name; BinOp scalar; BinOp sse2; };
struct UnCase { const char* name; UnOp scalar; UnOp sse2; };
struct ShiftCase { const char* name; ShiftOp scalar; ShiftOp sse2; };

#define P3FES_BIN(op) BinCase{#op, &mmi::scalar::op, &mmi::sse2::op}
#define P3FES_UN(op) UnCase{#op, &mmi::scalar::op, &mmi::sse2::op}
#define P3FES_SHIFT(op) ShiftCase{#op, &mmi::scalar::op, &mmi::sse2::op}

constexpr BinCase kBinary[] = {
    P3FES_BIN(paddw), P3FES_BIN(psubw), P3FES_BIN(paddh), P3FES_BIN(psubh), P3FES_BIN(paddb), P3FES_BIN(psubb),
    P3FES_BIN(paddsw), P3FES_BIN(psubsw), P3FES_BIN(paddsh), P3FES_BIN(psubsh), P3FES_BIN(paddsb), P3FES_BIN(psubsb),
    P3FES_BIN(padduw), P3FES_BIN(psubuw), P3FES_BIN(padduh), P3FES_BIN(psubuh), P3FES_BIN(paddub), P3FES_BIN(psubub),
    P3FES_BIN(pcgtw), P3FES_BIN(pcgth), P3FES_BIN(pcgtb), P3FES_BIN(pceqw), P3FES_BIN(pceqh), P3FES_BIN(pceqb),
    P3FES_BIN(pmaxw), P3FES_BIN(pminw), P3FES_BIN(pmaxh), P3FES_BIN(pminh), P3FES_BIN(padsbh),
    P3FES_BIN(pand), P3FES_BIN(por), P3FES_BIN(pxor), P3FES_BIN(pnor),
    P3FES_BIN(pextlw), P3FES_BIN(pextuw), P3FES_BIN(pextlh), P3FES_BIN(pextuh), P3FES_BIN(pextlb), P3FES_BIN(pextub),
    P3FES_BIN(ppacw), P3FES_BIN(ppach), P3FES_BIN(ppacb), P3FES_BIN(pinth), P3FES_BIN(pinteh),
    P3FES_BIN(pcpyld), P3FES_BIN(pcpyud), P3FES_BIN(psllvw), P3FES_BIN(psrlvw), P3FES_BIN(psravw),
};

constexpr UnCase kUnary[] = {
    P3FES_UN(pabsw), P3FES_UN(pabsh), P3FES_UN(pcpyh), P3FES_UN(pexch), P3FES_UN(pexcw), P3FES_UN(pexeh),
    P3FES_UN(pexew), P3FES_UN(prevh), P3FES_UN(prot3w), P3FES_UN(pext5), P3FES_UN(ppac5), P3FES_UN(plzcw),
};

constexpr ShiftCase kShift[] = {
    P3FES_SHIFT(psllh), P3FES_SHIFT(psrlh), P3FES_SHIFT(psrah), P3FES_SHIFT(psllw), P3FES_SHIFT(psrlw), P3FES_SHIFT(psraw),
};

#undef P3FES_BIN
#undef P3FES_UN
#undef P3FES_SHIFT

} // namespace

TEST_CASE("MMI binary operations: SSE2 path == scalar path on random and edge inputs") {
    static_assert(sizeof(kBinary) / sizeof(kBinary[0]) == 49, "every three-operand MMI lane op must be listed");
    for (const BinCase& op : kBinary) {
        Rng rng;
        int mismatches = 0;
        for (int i = 0; i < kIterations && mismatches < 3; ++i) {
            const u128 s = random_quad(rng), t = random_quad(rng), seed = random_quad(rng);
            u128 a = seed, b = seed; // identical destination seeds so partially-writing ops compare fully
            op.scalar(a, s, t);
            op.sse2(b, s, t);
            if (a != b) {
                ++mismatches;
                INFO(op.name << " rs=" << doctest::StringMaker<u128>::convert(s) << " rt=" << doctest::StringMaker<u128>::convert(t));
                CHECK(a == b);
            }
        }
        CHECK_MESSAGE(mismatches == 0, op.name);
    }
}

TEST_CASE("MMI unary operations: SSE2 path == scalar path") {
    static_assert(sizeof(kUnary) / sizeof(kUnary[0]) == 12, "every two-operand MMI lane op must be listed");
    for (const UnCase& op : kUnary) {
        Rng rng;
        int mismatches = 0;
        for (int i = 0; i < kIterations && mismatches < 3; ++i) {
            const u128 t = random_quad(rng), seed = random_quad(rng);
            u128 a = seed, b = seed;
            op.scalar(a, t);
            op.sse2(b, t);
            if (a != b) {
                ++mismatches;
                INFO(op.name << " rt=" << doctest::StringMaker<u128>::convert(t));
                CHECK(a == b);
            }
        }
        CHECK_MESSAGE(mismatches == 0, op.name);
    }
}

TEST_CASE("MMI immediate shifts: SSE2 path == scalar path for every sa in 0..31") {
    for (const ShiftCase& op : kShift) {
        Rng rng;
        int mismatches = 0;
        for (u32 sa = 0; sa < 32 && mismatches < 3; ++sa) {
            for (int i = 0; i < kIterations / 16; ++i) {
                const u128 t = random_quad(rng);
                u128 a{}, b{};
                op.scalar(a, t, sa);
                op.sse2(b, t, sa);
                if (a != b) {
                    ++mismatches;
                    INFO(op.name << " sa=" << sa << " rt=" << doctest::StringMaker<u128>::convert(t));
                    CHECK(a == b);
                    break;
                }
            }
        }
        CHECK_MESSAGE(mismatches == 0, op.name);
    }
}

TEST_CASE("qfsrv: SSE2 namespace resolves to the same function for every SA byte count") {
    Rng rng;
    for (u32 sa = 0; sa < 16; ++sa) {
        for (int i = 0; i < 64; ++i) {
            const u128 s = random_quad(rng), t = random_quad(rng);
            u128 a{}, b{};
            mmi::scalar::qfsrv(a, s, t, sa);
            mmi::sse2::qfsrv(b, s, t, sa);
            CHECK(a == b);
        }
    }
}

TEST_CASE("the default mmi:: names resolve to the configured path") {
    Rng rng;
    const u128 s = random_quad(rng), t = random_quad(rng);
    u128 a{}, b{};
    mmi::paddsw(a, s, t);
#if P3FES_EE_MMI_USE_SSE2
    mmi::sse2::paddsw(b, s, t);
#else
    mmi::scalar::paddsw(b, s, t);
#endif
    CHECK(a == b);
}
