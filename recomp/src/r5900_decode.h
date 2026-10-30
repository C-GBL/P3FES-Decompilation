// R5900 (PlayStation 2 Emotion Engine core) instruction decoder for the p3fes recompiler.
//
// Scope and policy (ADR-0011): this table knows exactly the instruction set that
// SLUS_216.21 uses, i.e. the 198 base mnemonics counted in symbols/insn_census.json
// (docs/ANALYSIS/08_instruction_census.md), plus Op::Invalid. Every other word, whether
// it is an EE instruction the game never executes (dadd, tge, pref, vcallms, bc2f...)
// or a generic-MIPS encoding the EE does not implement at all (ll/sc, dmult, ldc1,
// double-precision FPU, TLB ops), decodes to Op::Invalid and the recompiler stops on it.
// Table slots for EE instructions outside the census are marked with the mnemonic they
// would carry so that widening the set after a census re-run is a one-word change.
//
// Decoding is field-oriented: Insn exposes the raw register / immediate / VU0 fields and
// the control-flow flags the emitter needs; no text is produced except mnemonic() for
// diagnostics and the oracle test (census spelling, e.g. "add.s", "pmfhl", "vadd").
//
// Table layout borrowed from ps2-web-recomp recomp/r5900.cpp @ c0f476e (MIT, Samir Nuri;
// see THIRD_PARTY_NOTICES.md and licenses/ps2-web-recomp.LICENSE). The text here is ours;
// the encoding itself follows Sony's "EE Core Instruction Set Manual".
//
// C++20, no exceptions, no dependencies. Everything but mnemonic() is constexpr.
#pragma once

#include <cstddef>
#include <cstdint>

namespace p3fes::recomp {

// X(enumerator, census_spelling). Grouped by execution unit as in insn_census.json#units;
// alphabetical inside a unit. Invalid is first so a zero-initialised Op is Invalid.
#define P3FES_R5900_OPS(X) \
    X(Invalid, "<invalid>") \
    /* integer core (64) */ \
    X(Add, "add") X(Addi, "addi") X(Addiu, "addiu") X(Addu, "addu") X(And, "and") X(Andi, "andi") \
    X(Daddiu, "daddiu") X(Daddu, "daddu") X(Div, "div") X(Divu, "divu") X(Dsll, "dsll") \
    X(Dsll32, "dsll32") X(Dsllv, "dsllv") X(Dsra, "dsra") X(Dsra32, "dsra32") X(Dsrl, "dsrl") \
    X(Dsrl32, "dsrl32") X(Dsrlv, "dsrlv") X(Dsubu, "dsubu") X(Lb, "lb") X(Lbu, "lbu") X(Ld, "ld") \
    X(Ldl, "ldl") X(Ldr, "ldr") X(Lh, "lh") X(Lhu, "lhu") X(Lui, "lui") X(Lw, "lw") X(Lwl, "lwl") \
    X(Lwr, "lwr") X(Lwu, "lwu") X(Mfhi, "mfhi") X(Mflo, "mflo") X(Movn, "movn") X(Movz, "movz") \
    X(Mthi, "mthi") X(Mtlo, "mtlo") X(Mult, "mult") X(Multu, "multu") X(Nor, "nor") X(Or, "or") \
    X(Ori, "ori") X(Sb, "sb") X(Sd, "sd") X(Sdl, "sdl") X(Sdr, "sdr") X(Sh, "sh") X(Sll, "sll") \
    X(Sllv, "sllv") X(Slt, "slt") X(Slti, "slti") X(Sltiu, "sltiu") X(Sltu, "sltu") X(Sra, "sra") \
    X(Srav, "srav") X(Srl, "srl") X(Srlv, "srlv") X(Sub, "sub") X(Subu, "subu") X(Sw, "sw") \
    X(Swl, "swl") X(Swr, "swr") X(Xor, "xor") X(Xori, "xori") \
    /* branch (7) */ \
    X(Bc0f, "bc0f") X(Beq, "beq") X(Bgez, "bgez") X(Bgtz, "bgtz") X(Blez, "blez") X(Bltz, "bltz") \
    X(Bne, "bne") \
    /* branch, likely (6) */ \
    X(Beql, "beql") X(Bgezl, "bgezl") X(Bgtzl, "bgtzl") X(Blezl, "blezl") X(Bltzl, "bltzl") \
    X(Bnel, "bnel") \
    /* jump (4) */ \
    X(J, "j") X(Jal, "jal") X(Jalr, "jalr") X(Jr, "jr") \
    /* trap (2) */ \
    X(Break, "break") X(Syscall, "syscall") \
    /* COP0 (7) */ \
    X(Cache, "cache") X(Di, "di") X(Ei, "ei") X(Eret, "eret") X(Mfc0, "mfc0") X(Mtc0, "mtc0") \
    X(Sync, "sync") \
    /* COP1 FPU (29) */ \
    X(AbsS, "abs.s") X(AddS, "add.s") X(AddaS, "adda.s") X(Bc1f, "bc1f") X(Bc1fl, "bc1fl") \
    X(Bc1t, "bc1t") X(Bc1tl, "bc1tl") X(CEqS, "c.eq.s") X(CLeS, "c.le.s") X(CLtS, "c.lt.s") \
    X(Ctc1, "ctc1") X(CvtSW, "cvt.s.w") X(CvtWS, "cvt.w.s") X(DivS, "div.s") X(Lwc1, "lwc1") \
    X(MaddS, "madd.s") X(MaddaS, "madda.s") X(Mfc1, "mfc1") X(MovS, "mov.s") X(MsubS, "msub.s") \
    X(MsubaS, "msuba.s") X(Mtc1, "mtc1") X(MulS, "mul.s") X(MulaS, "mula.s") X(NegS, "neg.s") \
    X(SqrtS, "sqrt.s") X(SubS, "sub.s") X(SubaS, "suba.s") X(Swc1, "swc1") \
    /* MMI (49) */ \
    X(Div1, "div1") X(Lq, "lq") X(Madd, "madd") X(Maddu, "maddu") X(Maddu1, "maddu1") \
    X(Mfhi1, "mfhi1") X(Mflo1, "mflo1") X(Mfsa, "mfsa") X(Mthi1, "mthi1") X(Mtlo1, "mtlo1") \
    X(Mtsa, "mtsa") X(Mtsab, "mtsab") X(Mtsah, "mtsah") X(Mult1, "mult1") X(Multu1, "multu1") \
    X(Paddh, "paddh") X(Paddub, "paddub") X(Padduw, "padduw") X(Paddw, "paddw") X(Pand, "pand") \
    X(Pcgth, "pcgth") X(Pcpyh, "pcpyh") X(Pcpyld, "pcpyld") X(Pcpyud, "pcpyud") X(Pexew, "pexew") \
    X(Pextlb, "pextlb") X(Pextlh, "pextlh") X(Pextlw, "pextlw") X(Pextub, "pextub") \
    X(Pextuw, "pextuw") X(Phmadh, "phmadh") X(Pmaxh, "pmaxh") X(Pmfhl, "pmfhl") X(Pminh, "pminh") \
    X(Pnor, "pnor") X(Por, "por") X(Ppacb, "ppacb") X(Ppach, "ppach") X(Ppacw, "ppacw") \
    X(Prot3w, "prot3w") X(Psllh, "psllh") X(Psrah, "psrah") X(Psraw, "psraw") X(Psrlh, "psrlh") \
    X(Psubb, "psubb") X(Psubw, "psubw") X(Pxor, "pxor") X(Qfsrv, "qfsrv") X(Sq, "sq") \
    /* COP2 transfer (6) */ \
    X(Cfc2, "cfc2") X(Ctc2, "ctc2") X(Lqc2, "lqc2") X(Qmfc2, "qmfc2") X(Qmtc2, "qmtc2") \
    X(Sqc2, "sqc2") \
    /* COP2 VU0 macro (24); broadcast forms (vaddx...) fold into the base, see Insn::vu_bc */ \
    X(Vabs, "vabs") X(Vadd, "vadd") X(Vadda, "vadda") X(Vaddi, "vaddi") X(Vftoi0, "vftoi0") \
    X(Vitof0, "vitof0") X(Vmadd, "vmadd") X(Vmadda, "vmadda") X(Vmax, "vmax") X(Vmini, "vmini") \
    X(Vmove, "vmove") X(Vmsub, "vmsub") X(Vmsuba, "vmsuba") X(Vmul, "vmul") X(Vmula, "vmula") \
    X(Vmuli, "vmuli") X(Vmulq, "vmulq") X(Vnop, "vnop") X(Vopmsub, "vopmsub") X(Vopmula, "vopmula") \
    X(Vrsqrt, "vrsqrt") X(Vsqrt, "vsqrt") X(Vsub, "vsub") X(Vwaitq, "vwaitq")

enum class Op : std::uint16_t {
#define P3FES_X(name, text) name,
    P3FES_R5900_OPS(P3FES_X)
#undef P3FES_X
    Count  // 198 mnemonics + Invalid = 199
};

// Which hardware unit executes an op; mirrors the unit grouping of the census.
enum class Unit : std::uint8_t {
    Invalid, Integer, Branch, BranchLikely, Jump, Trap, Cop0, Cop1, Mmi, Cop2Transfer, Vu0Macro
};

// Formats of Op::Pmfhl (the `sa` field). Only Lw occurs in the game; the others are
// listed because the decoder accepts all five encodings the EE defines.
enum class PmfhlFmt : std::uint8_t { Lw = 0, Uw = 1, Slw = 2, Lh = 3, Sh = 4 };

struct Insn {
    std::uint32_t word = 0;  // raw little-endian instruction word
    std::uint32_t pc = 0;    // virtual address of the word
    Op op = Op::Invalid;

    // Register fields (always filled from the word, meaningful per op).
    std::uint8_t rs = 0;  // bits 25..21: base / source; COP2 special: dest field overlaps bits 24..21
    std::uint8_t rt = 0;  // bits 20..16: target / source 2 / branch condition; cache: op code
    std::uint8_t rd = 0;  // bits 15..11: destination; COP0 register for mfc0/mtc0
    std::uint8_t sa = 0;  // bits 10..6:  shift amount; sync stype; pmfhl fmt; mtsab/mtsah unused
    std::uint8_t fs = 0;  // == rd  (COP1 fs; COP2 vfs)
    std::uint8_t ft = 0;  // == rt  (COP1 ft; COP2 vft; qmfc2/qmtc2 vf register)
    std::uint8_t fd = 0;  // == sa  (COP1 fd; COP2 vfd)

    std::int32_t imm = 0;       // bits 15..0 sign-extended (andi/ori/xori/lui: use uimm())
    std::uint32_t target = 0;   // absolute branch (pc+4+imm*4) or jump (region | index*4) target; 0 otherwise

    // VU0 macro-mode fields.
    std::uint8_t dest = 0;  // bits 24..21 as a mask: bit3 = x, bit2 = y, bit1 = z, bit0 = w
                            // (vsqrt/vrsqrt reuse these bits as ftf = bits 24..23, fsf = bits 22..21)
    std::uint8_t bc = 0;    // bits 1..0 broadcast component (0 x, 1 y, 2 z, 3 w); valid when vu_bc
    bool vu_bc = false;     // true for the broadcast form (vaddx/vaddy/... rather than vadd)

    // Per-op format fields.
    std::uint8_t fmt = 0;   // pmfhl: PmfhlFmt (sa); sync: stype (sa; 0x10 = sync.p, else sync.l)
    bool interlock = false; // qmfc2/qmtc2/cfc2/ctc2: bit 0 (".i" form when set)

    // Control flow.
    bool is_branch = false;      // conditional branch (incl. bc0f/bc1f/bc1t and likely forms)
    bool is_likely = false;      // likely branch: the delay slot executes only when taken
    bool is_jump = false;        // j / jal / jr / jalr
    bool is_call = false;        // jal / jalr (link register written)
    bool has_delay_slot = false; // is_branch || is_jump

    constexpr std::uint32_t uimm() const { return word & 0xFFFFu; }
    constexpr std::uint32_t code() const { return (word >> 6) & 0xFFFFFu; }  // break / syscall code field
    constexpr std::uint32_t jump_index() const { return word & 0x03FFFFFFu; }
    constexpr std::uint8_t cop0_reg() const { return rd; }
    constexpr std::uint8_t vftf() const { return static_cast<std::uint8_t>(dest >> 2); }  // vsqrt/vrsqrt ft component
    constexpr std::uint8_t vfsf() const { return static_cast<std::uint8_t>(dest & 3); }   // vrsqrt fs component
    constexpr bool sync_p() const { return (fmt & 0x10u) != 0; }
    constexpr PmfhlFmt pmfhl_fmt() const { return static_cast<PmfhlFmt>(fmt); }
};

// Decode one word at `pc`. Never fails: unknown words yield op == Op::Invalid with the raw
// fields still filled.
constexpr Insn decode(std::uint32_t word, std::uint32_t pc) noexcept;

// Opcode-only decode (what decode() stores in Insn::op).
constexpr Op decode_op(std::uint32_t word) noexcept;

constexpr Unit unit_of(Op op) noexcept;

// Census spelling of the base mnemonic ("add.s", "pmfhl", "vadd"); "<invalid>" for Invalid.
const char* mnemonic(Op op) noexcept;

// Full variant spelling used by the census and the oracle test: VU0 ops get the broadcast
// letter and ".dest" suffix (vmulx.xyzw, vopmula.xyz), pmfhl gets ".lw"... , sync becomes
// sync.l / sync.p, COP2 transfers get ".i" when the interlock bit is set. Writes at most
// `cap` bytes including the terminator; returns the number of characters written (excluding
// the terminator) or the length that would have been needed if `cap` was too small.
std::size_t variant_mnemonic(const Insn& insn, char* out, std::size_t cap) noexcept;

// ---------------------------------------------------------------------------------------------
// Implementation of the constexpr parts (tables live in r5900_decode.cpp's companion header
// section below so that tests can static_assert encodings).

namespace detail {

using enum Op;

// Primary opcode (bits 31..26). '-' slots name the EE instruction that would live there.
inline constexpr Op kPrimary[64] = {
    /*00 SPECIAL*/ Invalid, /*01 REGIMM*/ Invalid, J, Jal, Beq, Bne, Blez, Bgtz,
    Addi, Addiu, Slti, Sltiu, Andi, Ori, Xori, Lui,
    /*10 COP0*/ Invalid, /*11 COP1*/ Invalid, /*12 COP2*/ Invalid, /*13*/ Invalid, Beql, Bnel, Blezl, Bgtzl,
    /*daddi*/ Invalid, Daddiu, Ldl, Ldr, /*1C MMI*/ Invalid, /*1D*/ Invalid, Lq, Sq,
    Lb, Lh, Lwl, Lw, Lbu, Lhu, Lwr, Lwu,
    Sb, Sh, Swl, Sw, Sdl, Sdr, Swr, Cache,
    /*30 ll*/ Invalid, Lwc1, /*32*/ Invalid, /*pref*/ Invalid, /*34 lld*/ Invalid, /*35 ldc1*/ Invalid, Lqc2, Ld,
    /*38 sc*/ Invalid, Swc1, /*3A*/ Invalid, /*3B*/ Invalid, /*3C scd*/ Invalid, /*3D sdc1*/ Invalid, Sqc2, Sd,
};

// SPECIAL (opcode 0), indexed by funct (bits 5..0).
inline constexpr Op kSpecial[64] = {
    Sll, /*01*/ Invalid, Srl, Sra, Sllv, /*05*/ Invalid, Srlv, Srav,
    Jr, Jalr, Movz, Movn, Syscall, Break, /*0E*/ Invalid, Sync,
    Mfhi, Mthi, Mflo, Mtlo, Dsllv, /*15*/ Invalid, Dsrlv, /*dsrav*/ Invalid,
    Mult, Multu, Div, Divu, /*1C dmult*/ Invalid, /*1D dmultu*/ Invalid, /*1E ddiv*/ Invalid, /*1F ddivu*/ Invalid,
    Add, Addu, Sub, Subu, And, Or, Xor, Nor,
    Mfsa, Mtsa, Slt, Sltu, /*dadd*/ Invalid, Daddu, /*dsub*/ Invalid, Dsubu,
    /*tge*/ Invalid, /*tgeu*/ Invalid, /*tlt*/ Invalid, /*tltu*/ Invalid, /*teq*/ Invalid, /*35*/ Invalid, /*tne*/ Invalid, /*37*/ Invalid,
    Dsll, /*39*/ Invalid, Dsrl, Dsra, Dsll32, /*3D*/ Invalid, Dsrl32, Dsra32,
};

// REGIMM (opcode 1), indexed by rt (bits 20..16).
inline constexpr Op kRegimm[32] = {
    Bltz, Bgez, Bltzl, Bgezl, Invalid, Invalid, Invalid, Invalid,
    /*tgei*/ Invalid, /*tgeiu*/ Invalid, /*tlti*/ Invalid, /*tltiu*/ Invalid, /*teqi*/ Invalid, Invalid, /*tnei*/ Invalid, Invalid,
    /*bltzal*/ Invalid, /*bgezal*/ Invalid, /*bltzall*/ Invalid, /*bgezall*/ Invalid, Invalid, Invalid, Invalid, Invalid,
    Mtsab, Mtsah, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
};

// MMI (opcode 0x1C), indexed by funct; functs 8/9/40/41/48/49 select the sub-tables.
inline constexpr Op kMmi[64] = {
    Madd, Maddu, Invalid, Invalid, /*plzcw*/ Invalid, Invalid, Invalid, Invalid,
    /*08 MMI0*/ Invalid, /*09 MMI2*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    Mfhi1, Mthi1, Mflo1, Mtlo1, Invalid, Invalid, Invalid, Invalid,
    Mult1, Multu1, Div1, /*divu1*/ Invalid, Invalid, Invalid, Invalid, Invalid,
    /*madd1*/ Invalid, Maddu1, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    /*28 MMI1*/ Invalid, /*29 MMI3*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    /*30 pmfhl*/ Invalid, /*31 pmthl*/ Invalid, Invalid, Invalid, Psllh, Invalid, Psrlh, Psrah,
    Invalid, Invalid, Invalid, Invalid, /*psllw*/ Invalid, Invalid, /*psrlw*/ Invalid, Psraw,
};

// MMI0 (funct 8), MMI1 (funct 40), MMI2 (funct 9), MMI3 (funct 41): indexed by sa (bits 10..6).
inline constexpr Op kMmi0[32] = {
    Paddw, Psubw, /*pcgtw*/ Invalid, /*pmaxw*/ Invalid, Paddh, /*psubh*/ Invalid, Pcgth, Pmaxh,
    /*paddb*/ Invalid, Psubb, /*pcgtb*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    /*paddsw*/ Invalid, /*psubsw*/ Invalid, Pextlw, Ppacw, /*paddsh*/ Invalid, /*psubsh*/ Invalid, Pextlh, Ppach,
    /*paddsb*/ Invalid, /*psubsb*/ Invalid, Pextlb, Ppacb, Invalid, Invalid, /*pext5*/ Invalid, /*ppac5*/ Invalid,
};
inline constexpr Op kMmi1[32] = {
    Invalid, /*pabsw*/ Invalid, /*pceqw*/ Invalid, /*pminw*/ Invalid, /*padsbh*/ Invalid, /*pabsh*/ Invalid, /*pceqh*/ Invalid, Pminh,
    Invalid, Invalid, /*pceqb*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    Padduw, /*psubuw*/ Invalid, Pextuw, Invalid, /*padduh*/ Invalid, /*psubuh*/ Invalid, /*pextuh*/ Invalid, Invalid,
    Paddub, /*psubub*/ Invalid, Pextub, Qfsrv, Invalid, Invalid, Invalid, Invalid,
};
inline constexpr Op kMmi2[32] = {
    /*pmaddw*/ Invalid, Invalid, /*psllvw*/ Invalid, /*psrlvw*/ Invalid, /*pmsubw*/ Invalid, Invalid, Invalid, Invalid,
    /*pmfhi*/ Invalid, /*pmflo*/ Invalid, /*pinth*/ Invalid, Invalid, /*pmultw*/ Invalid, /*pdivw*/ Invalid, Pcpyld, Invalid,
    /*pmaddh*/ Invalid, Phmadh, Pand, Pxor, /*pmsubh*/ Invalid, /*phmsbh*/ Invalid, Invalid, Invalid,
    Invalid, Invalid, /*pexeh*/ Invalid, /*prevh*/ Invalid, /*pmulth*/ Invalid, /*pdivbw*/ Invalid, Pexew, Prot3w,
};
inline constexpr Op kMmi3[32] = {
    /*pmadduw*/ Invalid, Invalid, Invalid, /*psravw*/ Invalid, Invalid, Invalid, Invalid, Invalid,
    /*pmthi*/ Invalid, /*pmtlo*/ Invalid, /*pinteh*/ Invalid, Invalid, /*pmultuw*/ Invalid, /*pdivuw*/ Invalid, Pcpyud, Invalid,
    Invalid, Invalid, Por, Pnor, Invalid, Invalid, Invalid, Invalid,
    Invalid, Invalid, /*pexch*/ Invalid, Pcpyh, Invalid, Invalid, /*pexcw*/ Invalid, Invalid,
};

// COP1 with rs == 16 (fmt S), indexed by funct. The EE has no D or L formats.
inline constexpr Op kCop1S[64] = {
    AddS, SubS, MulS, DivS, SqrtS, AbsS, MovS, NegS,
    Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, /*rsqrt.s*/ Invalid, Invalid,
    AddaS, SubaS, MulaS, Invalid, MaddS, MsubS, MaddaS, MsubaS,
    Invalid, Invalid, Invalid, Invalid, CvtWS, Invalid, Invalid, Invalid,
    /*max.s*/ Invalid, /*min.s*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
    /*c.f.s*/ Invalid, Invalid, CEqS, Invalid, CLtS, Invalid, CLeS, Invalid,
    Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
};

// COP2 special1 (rs >= 16, funct < 60), indexed by funct. Entries 0..27 are broadcast forms.
inline constexpr Op kVu[64] = {
    Vadd, Vadd, Vadd, Vadd, Vsub, Vsub, Vsub, Vsub,
    Vmadd, Vmadd, Vmadd, Vmadd, Vmsub, Vmsub, Vmsub, Vmsub,
    /*vmaxbc*/ Invalid, Invalid, Invalid, Invalid, /*vminibc*/ Invalid, Invalid, Invalid, Invalid,
    Vmul, Vmul, Vmul, Vmul, Vmulq, /*vmaxi*/ Invalid, Vmuli, /*vminii*/ Invalid,
    /*vaddq*/ Invalid, /*vmaddq*/ Invalid, Vaddi, /*vmaddi*/ Invalid, /*vsubq*/ Invalid, /*vmsubq*/ Invalid, /*vsubi*/ Invalid, /*vmsubi*/ Invalid,
    Vadd, Vmadd, Vmul, Vmax, Vsub, Vmsub, Vopmsub, Vmini,
    /*viadd*/ Invalid, /*visub*/ Invalid, /*viaddi*/ Invalid, Invalid, /*viand*/ Invalid, /*vior*/ Invalid, Invalid, Invalid,
    /*vcallms*/ Invalid, /*vcallmsr*/ Invalid, Invalid, Invalid, /*3C..3F -> special2*/ Invalid, Invalid, Invalid, Invalid,
};
inline constexpr bool kVuBroadcast[64] = {
    true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, true, true, true, true, true,
    true, true, true, true, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
};

// COP2 special2 (funct >= 60): row = funct & 3, column = sa (bits 10..6). Columns 0..3 and 6
// are broadcast forms.
inline constexpr Op kVuX[4][32] = {
    {Vadda, /*vsubabc*/ Invalid, Vmadda, Vmsuba, Vitof0, Vftoi0, Vmula, /*vmulaq*/ Invalid,
     /*vaddaq*/ Invalid, /*vsubaq*/ Invalid, Vadda, /*vsuba*/ Invalid, Vmove, /*vlqi*/ Invalid, /*vdiv*/ Invalid, /*vmtir*/ Invalid,
     /*vrnext*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
     Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid},
    {Vadda, /*vsubabc*/ Invalid, Vmadda, Vmsuba, /*vitof4*/ Invalid, /*vftoi4*/ Invalid, Vmula, Vabs,
     /*vmaddaq*/ Invalid, /*vmsubaq*/ Invalid, Vmadda, Vmsuba, /*vmr32*/ Invalid, /*vsqi*/ Invalid, Vsqrt, /*vmfir*/ Invalid,
     /*vrget*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
     Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid},
    {Vadda, /*vsubabc*/ Invalid, Vmadda, Vmsuba, /*vitof12*/ Invalid, /*vftoi12*/ Invalid, Vmula, /*vmulai*/ Invalid,
     /*vaddai*/ Invalid, /*vsubai*/ Invalid, Vmula, Vopmula, Invalid, /*vlqd*/ Invalid, Vrsqrt, /*vilwr*/ Invalid,
     /*vrinit*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
     Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid},
    {Vadda, /*vsubabc*/ Invalid, Vmadda, Vmsuba, /*vitof15*/ Invalid, /*vftoi15*/ Invalid, Vmula, /*vclip*/ Invalid,
     /*vmaddai*/ Invalid, /*vmsubai*/ Invalid, Invalid, Vnop, Invalid, /*vsqd*/ Invalid, Vwaitq, /*viswr*/ Invalid,
     /*vrxor*/ Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid,
     Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid, Invalid},
};
inline constexpr bool kVuXBroadcastCol[32] = {
    true, true, true, true, false, false, true, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false,
};

constexpr Op decode_mmi(std::uint32_t word) noexcept {
    const std::uint32_t funct = word & 63u, sub = (word >> 6) & 31u;
    switch (funct) {
    case 8: return kMmi0[sub];
    case 40: return kMmi1[sub];
    case 9: return kMmi2[sub];
    case 41: return kMmi3[sub];
    case 48: return sub <= 4 ? Pmfhl : Invalid;   // pmfhl.lw/.uw/.slw/.lh/.sh
    case 49: return Invalid;                       // pmthl.lw: not in the census
    default: return kMmi[funct];
    }
}

constexpr Op decode_cop0(std::uint32_t word) noexcept {
    const std::uint32_t rs = (word >> 21) & 31u, rt = (word >> 16) & 31u;
    switch (rs) {
    case 0: return Mfc0;
    case 4: return Mtc0;
    case 8: return rt == 0 ? Bc0f : Invalid;      // bc0t / bc0fl / bc0tl: not in the census
    case 16:
        switch (word & 63u) {
        case 24: return Eret;
        case 56: return Ei;
        case 57: return Di;
        default: return Invalid;                   // tlbr/tlbwi/tlbwr/tlbp: not in the census
        }
    default: return Invalid;
    }
}

constexpr Op decode_cop1(std::uint32_t word) noexcept {
    const std::uint32_t rt = (word >> 16) & 31u;
    switch ((word >> 21) & 31u) {
    case 0: return Mfc1;
    case 2: return Invalid;                        // cfc1: not in the census
    case 4: return Mtc1;
    case 6: return Ctc1;
    case 8:
        switch (rt) {
        case 0: return Bc1f;
        case 1: return Bc1t;
        case 2: return Bc1fl;
        case 3: return Bc1tl;
        default: return Invalid;
        }
    case 16: return kCop1S[word & 63u];
    case 20: return (word & 63u) == 32u ? CvtSW : Invalid;
    default: return Invalid;
    }
}

constexpr Op decode_cop2(std::uint32_t word) noexcept {
    const std::uint32_t rs = (word >> 21) & 31u;
    if (rs >= 16) {
        const std::uint32_t funct = word & 63u;
        if (funct >= 60) return kVuX[funct & 3u][(word >> 6) & 31u];
        return kVu[funct];
    }
    switch (rs) {
    case 1: return Qmfc2;
    case 2: return Cfc2;
    case 5: return Qmtc2;
    case 6: return Ctc2;
    default: return Invalid;                       // bc2f/bc2t/bc2fl/bc2tl (rs 8): not in the census
    }
}

constexpr bool vu_is_broadcast(std::uint32_t word) noexcept {
    const std::uint32_t funct = word & 63u;
    if (funct >= 60) return kVuXBroadcastCol[(word >> 6) & 31u];
    return kVuBroadcast[funct];
}

}  // namespace detail

constexpr Op decode_op(std::uint32_t word) noexcept {
    switch (word >> 26) {
    case 0x00: return detail::kSpecial[word & 63u];
    case 0x01: return detail::kRegimm[(word >> 16) & 31u];
    case 0x10: return detail::decode_cop0(word);
    case 0x11: return detail::decode_cop1(word);
    case 0x12: return detail::decode_cop2(word);
    case 0x1C: return detail::decode_mmi(word);
    default: return detail::kPrimary[word >> 26];
    }
}

constexpr Unit unit_of(Op op) noexcept {
    using enum Op;
    switch (op) {
    case Invalid: return Unit::Invalid;
    case Beq: case Bne: case Blez: case Bgtz: case Bltz: case Bgez: case Bc0f:
        return Unit::Branch;
    case Beql: case Bnel: case Blezl: case Bgtzl: case Bltzl: case Bgezl:
        return Unit::BranchLikely;
    case J: case Jal: case Jr: case Jalr:
        return Unit::Jump;
    case Break: case Syscall:
        return Unit::Trap;
    case Cache: case Di: case Ei: case Eret: case Mfc0: case Mtc0: case Sync:
        return Unit::Cop0;
    case AbsS: case AddS: case AddaS: case Bc1f: case Bc1fl: case Bc1t: case Bc1tl: case CEqS: case CLeS:
    case CLtS: case Ctc1: case CvtSW: case CvtWS: case DivS: case Lwc1: case MaddS: case MaddaS: case Mfc1:
    case MovS: case MsubS: case MsubaS: case Mtc1: case MulS: case MulaS: case NegS: case SqrtS: case SubS:
    case SubaS: case Swc1:
        return Unit::Cop1;
    case Div1: case Lq: case Madd: case Maddu: case Maddu1: case Mfhi1: case Mflo1: case Mfsa: case Mthi1:
    case Mtlo1: case Mtsa: case Mtsab: case Mtsah: case Mult1: case Multu1: case Paddh: case Paddub:
    case Padduw: case Paddw: case Pand: case Pcgth: case Pcpyh: case Pcpyld: case Pcpyud: case Pexew:
    case Pextlb: case Pextlh: case Pextlw: case Pextub: case Pextuw: case Phmadh: case Pmaxh: case Pmfhl:
    case Pminh: case Pnor: case Por: case Ppacb: case Ppach: case Ppacw: case Prot3w: case Psllh: case Psrah:
    case Psraw: case Psrlh: case Psubb: case Psubw: case Pxor: case Qfsrv: case Sq:
        return Unit::Mmi;
    case Cfc2: case Ctc2: case Lqc2: case Qmfc2: case Qmtc2: case Sqc2:
        return Unit::Cop2Transfer;
    case Vabs: case Vadd: case Vadda: case Vaddi: case Vftoi0: case Vitof0: case Vmadd: case Vmadda: case Vmax:
    case Vmini: case Vmove: case Vmsub: case Vmsuba: case Vmul: case Vmula: case Vmuli: case Vmulq: case Vnop:
    case Vopmsub: case Vopmula: case Vrsqrt: case Vsqrt: case Vsub: case Vwaitq:
        return Unit::Vu0Macro;
    default:
        return Unit::Integer;
    }
}

constexpr Insn decode(std::uint32_t word, std::uint32_t pc) noexcept {
    Insn i;
    i.word = word;
    i.pc = pc;
    i.op = decode_op(word);
    i.rs = static_cast<std::uint8_t>((word >> 21) & 31u);
    i.rt = static_cast<std::uint8_t>((word >> 16) & 31u);
    i.rd = static_cast<std::uint8_t>((word >> 11) & 31u);
    i.sa = static_cast<std::uint8_t>((word >> 6) & 31u);
    i.fs = i.rd;
    i.ft = i.rt;
    i.fd = i.sa;
    i.imm = static_cast<std::int16_t>(word & 0xFFFFu);

    const Unit u = unit_of(i.op);
    switch (u) {
    case Unit::Branch:
    case Unit::BranchLikely:
        i.is_branch = true;
        i.is_likely = (u == Unit::BranchLikely);
        i.target = pc + 4u + (static_cast<std::uint32_t>(i.imm) << 2);
        break;
    case Unit::Cop1:
        if (i.op == Op::Bc1f || i.op == Op::Bc1t || i.op == Op::Bc1fl || i.op == Op::Bc1tl) {
            i.is_branch = true;
            i.is_likely = (i.op == Op::Bc1fl || i.op == Op::Bc1tl);
            i.target = pc + 4u + (static_cast<std::uint32_t>(i.imm) << 2);
        }
        break;
    case Unit::Jump:
        i.is_jump = true;
        i.is_call = (i.op == Op::Jal || i.op == Op::Jalr);
        if (i.op == Op::J || i.op == Op::Jal)
            i.target = ((pc + 4u) & 0xF0000000u) | ((word & 0x03FFFFFFu) << 2);
        break;
    case Unit::Cop0:
        if (i.op == Op::Sync) i.fmt = i.sa;
        break;
    case Unit::Mmi:
        if (i.op == Op::Pmfhl) i.fmt = i.sa;
        break;
    case Unit::Cop2Transfer:
        if (i.op != Op::Lqc2 && i.op != Op::Sqc2) i.interlock = (word & 1u) != 0;
        break;
    case Unit::Vu0Macro:
        i.dest = static_cast<std::uint8_t>((word >> 21) & 15u);
        i.bc = static_cast<std::uint8_t>(word & 3u);
        i.vu_bc = detail::vu_is_broadcast(word);
        break;
    default:
        break;
    }
    i.has_delay_slot = i.is_branch || i.is_jump;
    return i;
}

}  // namespace p3fes::recomp
