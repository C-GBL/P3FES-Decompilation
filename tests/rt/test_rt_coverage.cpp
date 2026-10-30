// Declaration coverage of the rt adapter: every function declared in recomp/include/p3fes_recomp_rt.h
// except lookup_func (which the generated dispatch.cpp defines) is listed here by address, so this
// executable links only if runtime/rt/ defines all of them; the test then parses the header and
// requires the table to name exactly the declared functions (a new declaration without an entry
// here, or a stale entry, fails).
#include <doctest.h>

#include "p3fes_recomp_rt.h"

#include <cstdio>
#include <set>
#include <string>

namespace {

using AnyFn = void (*)();
struct Entry {
    const char* name;
    AnyFn fn;
};

#define P3FES_RT_ENTRY(name) {#name, reinterpret_cast<AnyFn>(&p3fes::rt::name)},
const Entry kEntries[] = {
    P3FES_RT_ENTRY(lookup_miss)
    P3FES_RT_ENTRY(bad_entry)
    P3FES_RT_ENTRY(unreachable)
    P3FES_RT_ENTRY(missing_function)
    P3FES_RT_ENTRY(trap)
    P3FES_RT_ENTRY(syscall)
    P3FES_RT_ENTRY(check_events)
    P3FES_RT_ENTRY(jal)
    P3FES_RT_ENTRY(jalr)
    P3FES_RT_ENTRY(reg32)
    P3FES_RT_ENTRY(cmp_eq)
    P3FES_RT_ENTRY(cmp_ne)
    P3FES_RT_ENTRY(cmp_lez)
    P3FES_RT_ENTRY(cmp_gtz)
    P3FES_RT_ENTRY(cmp_ltz)
    P3FES_RT_ENTRY(cmp_gez)
    P3FES_RT_ENTRY(cop1_cond)
    P3FES_RT_ENTRY(cop0_cond)
    P3FES_RT_ENTRY(add)
    P3FES_RT_ENTRY(addu)
    P3FES_RT_ENTRY(sub)
    P3FES_RT_ENTRY(subu)
    P3FES_RT_ENTRY(and_)
    P3FES_RT_ENTRY(or_)
    P3FES_RT_ENTRY(xor_)
    P3FES_RT_ENTRY(nor)
    P3FES_RT_ENTRY(slt)
    P3FES_RT_ENTRY(sltu)
    P3FES_RT_ENTRY(daddu)
    P3FES_RT_ENTRY(dsubu)
    P3FES_RT_ENTRY(movn)
    P3FES_RT_ENTRY(movz)
    P3FES_RT_ENTRY(sllv)
    P3FES_RT_ENTRY(srlv)
    P3FES_RT_ENTRY(srav)
    P3FES_RT_ENTRY(dsllv)
    P3FES_RT_ENTRY(dsrlv)
    P3FES_RT_ENTRY(mult)
    P3FES_RT_ENTRY(multu)
    P3FES_RT_ENTRY(div)
    P3FES_RT_ENTRY(divu)
    P3FES_RT_ENTRY(addi)
    P3FES_RT_ENTRY(addiu)
    P3FES_RT_ENTRY(daddiu)
    P3FES_RT_ENTRY(slti)
    P3FES_RT_ENTRY(sltiu)
    P3FES_RT_ENTRY(andi)
    P3FES_RT_ENTRY(ori)
    P3FES_RT_ENTRY(xori)
    P3FES_RT_ENTRY(lui)
    P3FES_RT_ENTRY(sll)
    P3FES_RT_ENTRY(srl)
    P3FES_RT_ENTRY(sra)
    P3FES_RT_ENTRY(dsll)
    P3FES_RT_ENTRY(dsrl)
    P3FES_RT_ENTRY(dsra)
    P3FES_RT_ENTRY(dsll32)
    P3FES_RT_ENTRY(dsrl32)
    P3FES_RT_ENTRY(dsra32)
    P3FES_RT_ENTRY(mfhi)
    P3FES_RT_ENTRY(mflo)
    P3FES_RT_ENTRY(mthi)
    P3FES_RT_ENTRY(mtlo)
    P3FES_RT_ENTRY(lb)
    P3FES_RT_ENTRY(lbu)
    P3FES_RT_ENTRY(lh)
    P3FES_RT_ENTRY(lhu)
    P3FES_RT_ENTRY(lw)
    P3FES_RT_ENTRY(lwu)
    P3FES_RT_ENTRY(lwl)
    P3FES_RT_ENTRY(lwr)
    P3FES_RT_ENTRY(ld)
    P3FES_RT_ENTRY(ldl)
    P3FES_RT_ENTRY(ldr)
    P3FES_RT_ENTRY(sb)
    P3FES_RT_ENTRY(sh)
    P3FES_RT_ENTRY(sw)
    P3FES_RT_ENTRY(swl)
    P3FES_RT_ENTRY(swr)
    P3FES_RT_ENTRY(sd)
    P3FES_RT_ENTRY(sdl)
    P3FES_RT_ENTRY(sdr)
    P3FES_RT_ENTRY(mfc0)
    P3FES_RT_ENTRY(mtc0)
    P3FES_RT_ENTRY(sync)
    P3FES_RT_ENTRY(ei)
    P3FES_RT_ENTRY(di)
    P3FES_RT_ENTRY(cache)
    P3FES_RT_ENTRY(eret)
    P3FES_RT_ENTRY(abs_s)
    P3FES_RT_ENTRY(add_s)
    P3FES_RT_ENTRY(adda_s)
    P3FES_RT_ENTRY(c_eq_s)
    P3FES_RT_ENTRY(c_le_s)
    P3FES_RT_ENTRY(c_lt_s)
    P3FES_RT_ENTRY(ctc1)
    P3FES_RT_ENTRY(cvt_s_w)
    P3FES_RT_ENTRY(cvt_w_s)
    P3FES_RT_ENTRY(div_s)
    P3FES_RT_ENTRY(lwc1)
    P3FES_RT_ENTRY(madd_s)
    P3FES_RT_ENTRY(madda_s)
    P3FES_RT_ENTRY(mfc1)
    P3FES_RT_ENTRY(mov_s)
    P3FES_RT_ENTRY(msub_s)
    P3FES_RT_ENTRY(msuba_s)
    P3FES_RT_ENTRY(mtc1)
    P3FES_RT_ENTRY(mul_s)
    P3FES_RT_ENTRY(mula_s)
    P3FES_RT_ENTRY(neg_s)
    P3FES_RT_ENTRY(sqrt_s)
    P3FES_RT_ENTRY(sub_s)
    P3FES_RT_ENTRY(suba_s)
    P3FES_RT_ENTRY(swc1)
    P3FES_RT_ENTRY(div1)
    P3FES_RT_ENTRY(lq)
    P3FES_RT_ENTRY(madd)
    P3FES_RT_ENTRY(maddu)
    P3FES_RT_ENTRY(maddu1)
    P3FES_RT_ENTRY(mfhi1)
    P3FES_RT_ENTRY(mflo1)
    P3FES_RT_ENTRY(mfsa)
    P3FES_RT_ENTRY(mthi1)
    P3FES_RT_ENTRY(mtlo1)
    P3FES_RT_ENTRY(mtsa)
    P3FES_RT_ENTRY(mtsab)
    P3FES_RT_ENTRY(mtsah)
    P3FES_RT_ENTRY(mult1)
    P3FES_RT_ENTRY(multu1)
    P3FES_RT_ENTRY(paddh)
    P3FES_RT_ENTRY(paddub)
    P3FES_RT_ENTRY(padduw)
    P3FES_RT_ENTRY(paddw)
    P3FES_RT_ENTRY(pand)
    P3FES_RT_ENTRY(pcgth)
    P3FES_RT_ENTRY(pcpyh)
    P3FES_RT_ENTRY(pcpyld)
    P3FES_RT_ENTRY(pcpyud)
    P3FES_RT_ENTRY(pexew)
    P3FES_RT_ENTRY(pextlb)
    P3FES_RT_ENTRY(pextlh)
    P3FES_RT_ENTRY(pextlw)
    P3FES_RT_ENTRY(pextub)
    P3FES_RT_ENTRY(pextuw)
    P3FES_RT_ENTRY(phmadh)
    P3FES_RT_ENTRY(pmaxh)
    P3FES_RT_ENTRY(pmfhl)
    P3FES_RT_ENTRY(pminh)
    P3FES_RT_ENTRY(pnor)
    P3FES_RT_ENTRY(por)
    P3FES_RT_ENTRY(ppacb)
    P3FES_RT_ENTRY(ppach)
    P3FES_RT_ENTRY(ppacw)
    P3FES_RT_ENTRY(prot3w)
    P3FES_RT_ENTRY(psllh)
    P3FES_RT_ENTRY(psrah)
    P3FES_RT_ENTRY(psraw)
    P3FES_RT_ENTRY(psrlh)
    P3FES_RT_ENTRY(psubb)
    P3FES_RT_ENTRY(psubw)
    P3FES_RT_ENTRY(pxor)
    P3FES_RT_ENTRY(qfsrv)
    P3FES_RT_ENTRY(sq)
    P3FES_RT_ENTRY(cfc2)
    P3FES_RT_ENTRY(ctc2)
    P3FES_RT_ENTRY(lqc2)
    P3FES_RT_ENTRY(qmfc2)
    P3FES_RT_ENTRY(qmtc2)
    P3FES_RT_ENTRY(sqc2)
    P3FES_RT_ENTRY(vabs)
    P3FES_RT_ENTRY(vadd)
    P3FES_RT_ENTRY(vadd_bc)
    P3FES_RT_ENTRY(vadda)
    P3FES_RT_ENTRY(vadda_bc)
    P3FES_RT_ENTRY(vaddi)
    P3FES_RT_ENTRY(vftoi0)
    P3FES_RT_ENTRY(vitof0)
    P3FES_RT_ENTRY(vmadd)
    P3FES_RT_ENTRY(vmadd_bc)
    P3FES_RT_ENTRY(vmadda)
    P3FES_RT_ENTRY(vmadda_bc)
    P3FES_RT_ENTRY(vmax)
    P3FES_RT_ENTRY(vmini)
    P3FES_RT_ENTRY(vmove)
    P3FES_RT_ENTRY(vmsub)
    P3FES_RT_ENTRY(vmsub_bc)
    P3FES_RT_ENTRY(vmsuba)
    P3FES_RT_ENTRY(vmsuba_bc)
    P3FES_RT_ENTRY(vmul)
    P3FES_RT_ENTRY(vmul_bc)
    P3FES_RT_ENTRY(vmula)
    P3FES_RT_ENTRY(vmula_bc)
    P3FES_RT_ENTRY(vmuli)
    P3FES_RT_ENTRY(vmulq)
    P3FES_RT_ENTRY(vnop)
    P3FES_RT_ENTRY(vopmsub)
    P3FES_RT_ENTRY(vopmula)
    P3FES_RT_ENTRY(vrsqrt)
    P3FES_RT_ENTRY(vsqrt)
    P3FES_RT_ENTRY(vsub)
    P3FES_RT_ENTRY(vsub_bc)
    P3FES_RT_ENTRY(vwaitq)
};
#undef P3FES_RT_ENTRY

// Function names declared at namespace scope in the header (one declaration per line).
std::set<std::string> declared_names(const char* path) {
    std::set<std::string> out;
    std::FILE* f = std::fopen(path, "rb");
    if (!f) return out;
    char line[512];
    const char* prefixes[] = {"[[noreturn]] void ", "void ", "bool ", "Fn ", "std::uint32_t "};
    while (std::fgets(line, sizeof line, f)) {
        for (const char* p : prefixes) {
            const std::string s(line);
            if (s.rfind(p, 0) != 0) continue;
            const std::size_t b = std::char_traits<char>::length(p);
            const std::size_t e = s.find('(', b);
            if (e == std::string::npos) break;
            const std::string name = s.substr(b, e - b);
            if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") == std::string::npos) out.insert(name);
            break;
        }
    }
    std::fclose(f);
    return out;
}

} // namespace

TEST_CASE("rt coverage: the adapter defines every declaration of p3fes_recomp_rt.h but lookup_func") {
    std::set<std::string> table;
    for (const Entry& e : kEntries) {
        CHECK(e.fn != nullptr);
        CHECK(table.insert(e.name).second);  // no duplicates
    }
    const std::set<std::string> declared = declared_names(P3FES_RECOMP_RT_HEADER);
    REQUIRE_MESSAGE(!declared.empty(), "cannot read " P3FES_RECOMP_RT_HEADER);
    std::set<std::string> expected = declared;
    CHECK(expected.erase("lookup_func") == 1);
    for (const std::string& n : expected) {
        CAPTURE(n);
        CHECK(table.count(n) == 1);
    }
    for (const std::string& n : table) {
        CAPTURE(n);
        CHECK(expected.count(n) == 1);
    }
    CHECK(declared.size() == 203);  // 202 of the emitter's first cut + check_events (ADR-0013)
    CHECK(table.size() == 202);
    MESSAGE("p3fes_recomp_rt.h declares " << declared.size() << " functions; the adapter defines " << table.size()
            << " (lookup_func is generated)");
}
