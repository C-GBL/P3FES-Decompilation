// CRI ROFS directory helpers (game/include/p3fes/game/cri_rofs.h). Phase 5: these replace the
// recompiled bodies of the two functions listed in game/replaced.txt; the recompiled bodies stay in
// the program under the __recomp symbols and tests/game/test_replacements.cpp proves both agree.
//
// The guest::enter/charge/backedge lines are the virtual-time model of the recompiled body (ADR-0013;
// block costs from recomp/generated, where `ctx.cycles += N` marks each basic block). They keep every
// run byte-identical to the fully recompiled program and go away with Phase 6.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 4 of the 5 functions here are p3fes_handgen's register-faithful
// bodies (their hand versions differed from the original: frame/spills 2, scratch GPRs 1, $v0 1); RFMAI_ToUpperStr
// is the register-for-register transliteration of f794284. The 4 were made readable on 2026-10-22 (slice read_misc):
// role comments, named registers, the characters as kDot / kLowerA / kCaseDelta, block roles, and the gotos that
// leave a loop as `break` (rfdirStrcmpFileName keeps the two that re-enter its compare loop: that loop has two
// entries). Every guest statement, frame, link, cycle charge and check point is the generated body's, in its order
// on every path.
#include "p3fes/game/cri_rofs.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_rfdir_toUpperFname_0056bc78(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_strlen_00524388(p3fes::EEContext&);        // still recompiled (recomp/generated/functions.h)
void fn_rfdir_toUpper_0056b980(p3fes::EEContext&);  // still recompiled: plain ASCII toupper of one char
}

namespace p3fes::game {

namespace {
// The characters the ROFS name helpers test, as the instructions' immediates.
inline constexpr s32 kDot = 46;         // '.'
inline constexpr s32 kLowerA = 97;      // 'a': `addiu v0, a0, -97; sltiu v0, v0, 26` = 'a' <= c <= 'z'
inline constexpr s32 kLetters = 26;
inline constexpr s32 kCaseDelta = 32;   // 'a' - 'A'
inline constexpr s32 kSearchIdSeed = 218;  // rfdir_getSearchID: the sum starts at 218
}  // namespace

// 0x0056C2E0 rfdir_isContainPeriod -- 64 bytes; leaf frame (no stack)
// rfdir_isContainPeriod(name): 1 when the name has a '.', else 0.
// 0x56C2E0: entry 3 (first byte tested); 1 for the '.' constant; per character 5 (compare) + 4
// (load and test the next byte); the "no" tail 1 + 2, the "yes" tail 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_isContainPeriod(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lb, hg::lbu, hg::sll, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& name = a0;  // the cursor
    Gpr& c = v1;     // the character (sign-extended byte)
    // 0x0056c2e0
    enter(ctx, 3);  // entry check point + this block's cycles
    lb(v0, name, 0);
    lbu(c, name, 0);
    if (v0 != 0) {
        // 0x0056c2ec
        charge(ctx, 1);
        a1 = kDot;
        for (;;) {
            // 0x0056c2f0: '.' -> 1
            charge(ctx, 5);
            c = sll(c, 24);
            name = addiu(name, 1);
            c = sra(c, 24);
            v0 = 1;
            if (c == a1) {
                break;
            }
            // 0x0056c304: the next character; the end -> 0
            charge(ctx, 4);
            lb(v0, name, 0);
            lbu(c, name, 0);
            if (v0 == 0) {
                // 0x0056c314
                charge(ctx, 1);
                v0 = 0;
                break;
            }
            backedge(ctx);
        }
    } else {
        // 0x0056c314: an empty name: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0056c318
    charge(ctx, 2);
}

// 0x0056BAC8 rfdirStrcmpFileName -- 212 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// rfdirStrcmpFileName(a, b): 1 when the two file names are equal ignoring case up to a's extension dot (a '.'
// followed by the end counts as the end), else 0; b may end there or with a lone '.'.
// 0x56BAC8: prologue 10 (tests *a); 3 for the '.' test of *a; 1 to enter the loop plainly, 2 for the
// "a is '.' + next" test (L_56BB48); per character 9 (two rfdir_toUpper calls, each charging its own
// cycles) then 6 to load the next byte of a, 2 for its '.' test, 1 before re-testing the byte after
// it; the mismatch exit 1; the "a ended" block 1 (L_56BB50); the b tail (L_56BB54) 2 / 3 / 3 / 2 by
// outcome; epilogue 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdirStrcmpFileName(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::lbu, hg::ld, hg::sd, hg::sll,
          hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, a{ctx, 17}, b{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // a, b: the two names ($a0, $a1), walked
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056bac8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(a, sp, 0x8);
    a = a0;
    sd(b, sp, 0x10);
    b = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    lb(v1, a, 0);
    lbu(a0, a, 0);
    if (v1 != 0) {
        // 0x0056baf0: a starts with '.'?
        charge(ctx, 3);
        v0 = kDot;
        if (v1 == v0) {
            lb(v0, a, 1);
        } else {
            // 0x0056bafc
            charge(ctx, 1);
            a0 = sll(a0, 24);
            for (;;) {
            L_0056bb00:  // toupper(*a++) == toupper(*b++)? (entered again from 0x56bb48)
                charge(ctx, 9);
                a = addiu(a, 1);
                a0 = sra(a0, 24);
                jal(ctx, 0x56BB04u, gen::fn_rfdir_toUpper_0056b980);
                lb(a0, b, 0);
                s0 = v0;
                b = addiu(b, 1);
                jal(ctx, 0x56BB14u, gen::fn_rfdir_toUpper_0056b980);
                a1 = kDot;
                if (s0 != v0) {
                    // 0x0056bb80: the characters differ: 0
                    charge(ctx, 1);
                    v0 = 0;
                    // 0x0056bb84 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(s0, sp, 0x0);
                    ld(a, sp, 0x8);
                    ld(b, sp, 0x10);
                    ld(ra, sp, 0x18);
                    sp = addiu(sp, 0x20);
                    return;
                }
                // 0x0056bb24: the next character of a; its end -> the b tail with *b
                charge(ctx, 6);
                lbu(v0, a, 0);
                a0 = v0;
                v1 = sll(a0, 24);
                v1 = sra(v1, 24);
                if (v1 == 0) {
                    lb(v1, b, 0);
                    goto L_0056bb54;
                }
                // 0x0056bb3c: a '.' leaves the loop
                charge(ctx, 2);
                if (v1 == a1) {
                    break;
                }
                a0 = sll(a0, 24);
                backedge(ctx);
            }
            // 0x0056bb44
            charge(ctx, 1);
            lb(v0, a, 1);
        }
        // 0x0056bb48: a '.' followed by the end ends a; otherwise the dot is compared like any character
        charge(ctx, 2);
        if (v0 == 0) {
            goto L_0056bb50;
        }
        a0 = sll(a0, 24);
        backedge(ctx);
        goto L_0056bb00;
    }
L_0056bb50:  // a ended: *b
    charge(ctx, 1);
    lb(v1, b, 0);
L_0056bb54:  // b must end too, or be a lone '.' (then 1)
    charge(ctx, 2);
    v0 = 1;
    if (v1 != 0) {
        // 0x0056bb5c
        charge(ctx, 3);
        v0 = kDot;
        cc = v1 != v0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0056bb68
            charge(ctx, 3);
            lb(v0, b, 1);
            if (v0 != 0) {
                v0 = 0;
            } else {
                // 0x0056bb74
                charge(ctx, 2);
                v0 = 1;
            }
        }
    }
    // 0x0056bb84 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(a, sp, 0x8);
    ld(b, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0056BC78 rfdir_toUpperFname -- 56 bytes; leaf frame (no stack)
// rfdir_toUpperFname(c): toupper for a file-name character: 'a'..'z' -> 'A'..'Z', '.' -> 0, others unchanged.
// 0x56BC78: sll/sra 24 (the argument is a byte), then either branch costs 2 + the shared tail 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_toUpperFname(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::sll, hg::sltiu, hg::sra;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    Gpr& c = a0;
    // 0x0056bc78
    enter(ctx, 7);  // entry check point + this block's cycles
    c = sll(c, 24);
    c = sra(c, 24);
    v0 = addiu(c, -kLowerA);
    v1 = addiu(c, -kCaseDelta);
    v0 = sltiu(v0, kLetters);
    v1 = sll(v1, 24);
    if (v0 == 0) {
        // 0x0056bca0: not lowercase: '.' becomes 0 (`movz`)
        charge(ctx, 2);
        v0 = c ^ 0x2E;
        if (v0 == 0) c = 0;
    } else {
        // 0x0056bc94: lowercase: c - 32
        charge(ctx, 2);
        c = sra(v1, 24);
    }
    // 0x0056bca8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
char rfdir_toUpperFname(EEContext& ctx, char c) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(c)));
    rfdir_toUpperFname(ctx);
    return static_cast<char>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0056BC10 rfdir_getSearchID -- 104 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// rfdir_getSearchID(name): the directory search hash: (218 + the sum of toUpperFname(c) as bytes) >> 2, a byte.
// 0x56BC10: prologue block 9 (saves s0/s1/ra, seeds the sum with 218, tests the first byte), the
// per-character block 9 (call + accumulate + test of the next byte), epilogue 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void rfdir_getSearchID(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lb, hg::lbu, hg::ld,
          hg::sd, hg::sll, hg::sra, hg::srl;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, name{ctx, 16}, sum{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056bc10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(name, sp, 0x0);
    name = a0;
    sd(sum, sp, 0x8);
    sum = kSearchIdSeed;
    sd(ra, sp, 0x10);
    lb(v0, name, 0);
    lbu(a0, name, 0);
    if (v0 != 0) {
        // 0x0056bc34
        charge(ctx, 1);
        for (;;) {
            // 0x0056bc38: sum += (u8)rfdir_toUpperFname(*name++)
            charge(ctx, 9);
            a0 = sll(a0, 24);
            name = addiu(name, 1);
            a0 = sra(a0, 24);
            jal(ctx, 0x56BC40u, gen::fn_rfdir_toUpperFname_0056bc78);
            lbu(a0, name, 0);
            lb(v1, name, 0);
            v0 = v0 & 0xFF;
            sum = addu(sum, v0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0056bc5c: (sum >> 2) & 0xFF
    charge(ctx, 7);
    v0 = srl(sum, 2);
    ld(sum, sp, 0x8);
    ld(name, sp, 0x0);
    v0 = v0 & 0xFF;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

u8 rfdir_getSearchID(EEContext& ctx, const char* name) {
    // 0x56BC10: prologue block 9 (saves s0/s1/ra, seeds the sum with 218, tests the first byte), the
    // per-character block 9 (call + accumulate + test of the next byte), epilogue 7.
    guest::enter(ctx, 9);
    u32 sum = 218;
    if (*name != 0) {
        guest::charge(ctx, 1);
        for (;;) {
            guest::charge(ctx, 9);
            sum += static_cast<u8>(rfdir_toUpperFname(ctx, *name++));
            if (*name == 0) break;
            guest::backedge(ctx);
        }
    }
    guest::charge(ctx, 7);
    return static_cast<u8>(sum >> 2);
}

void RFMAI_ToUpperStr(EEContext& ctx, u32 str_va) {
    // 0x569848, register for register (the climb and shop replay routes caught the earlier host-variable
    // version: it never opened the 16-byte frame, so the $ra spill at sp+8 -- 0x56C3B8 from
    // rfdir_nameBinarySearch -- was missing from a CRI thread's live stack 30,000 vblanks later).
    // Frame 16: $s0 at +0, $ra at +8; $s0 = the string, $a2 = i, $a3 = count, $a0 = &str[i], and $v0 / $v1 /
    // $a1 as the loop's compares leave them. Callers set $ra (hand callers: rt::jal at the original site).
    // Cycles: prologue 5; strlen block 5 (count = len + 1, tested <= 0); setup 2; per byte 7, +1 when a
    // lowercase letter is stored back, +2 for the loop test; epilogue 4. strlen stays recompiled.
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(str_va));
    rt::check_events(ctx);
    ctx.cycles += 5;
    rt::addiu(ctx, 29, 29, -16);
    rt::sd(ctx, 16, 29, 0);
    rt::daddu(ctx, 16, 4, 0);
    rt::sd(ctx, 31, 29, 8);
    if (str_va != 0) {
        ctx.cycles += 5;
        rt::jal(ctx, 0x56985cu);
        recomp_gen::fn_strlen_00524388(ctx);
        rt::addiu(ctx, 2, 2, 1);  // count = strlen + 1 (the terminator is visited too)
        rt::daddu(ctx, 6, 0, 0);  // i = 0
        if (!rt::cmp_lez(ctx, 2)) {
            ctx.cycles += 2;
            rt::daddu(ctx, 7, 2, 0);
            rt::addu(ctx, 4, 16, 6);
            for (;;) {
                ctx.cycles += 7;
                rt::addiu(ctx, 6, 6, 1);
                rt::lbu(ctx, 2, 4, 0);        // c = str[i]
                rt::addiu(ctx, 3, 2, -32);    // c - 32: the uppercase letter, if c is lowercase
                rt::addiu(ctx, 2, 2, -97);
                rt::sltiu(ctx, 2, 2, 26);     // 'a' <= c <= 'z'
                const bool lower = !rt::cmp_eq(ctx, 2, 0);
                rt::slt(ctx, 5, 6, 7);        // more to go
                if (lower) {
                    ctx.cycles += 1;
                    rt::sb(ctx, 3, 4, 0);
                }
                ctx.cycles += 2;
                const bool more = rt::cmp_ne(ctx, 5, 0);
                rt::addu(ctx, 4, 16, 6);
                if (!more) break;
                rt::check_events(ctx);
            }
        }
    }
    ctx.cycles += 4;
    rt::ld(ctx, 16, 29, 0);
    rt::ld(ctx, 31, 29, 8);
    rt::addiu(ctx, 29, 29, 16);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
namespace p3fes::recomp_gen {

void fn_RFMAI_ToUpperStr_00569848(p3fes::EEContext& ctx) {
    using namespace p3fes::game;
    RFMAI_ToUpperStr(ctx, guest::arg32(ctx, 0));  // void: $v0 is whatever strlen left (callers never read it)
}

}  // namespace p3fes::recomp_gen
