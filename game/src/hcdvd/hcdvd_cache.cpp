// H_Cdvd request-node state and the sCdvdCache table: lookup, registration and removal
// (game/include/p3fes/game/hcdvd.h), hand-decompiled from SLUS_216.21. The guest::enter/charge/backedge
// lines mirror the recompiled bodies' virtual time (ADR-0013); strcmp and memcpy stay recompiled and
// charge their own cycles through guest::call.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 5 functions here are p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 3, faults only 1, scratch GPRs 1); what this
// header says about guest::call describes those earlier versions. Made readable on 2026-10-22 (slice read_misc):
// role comments, named registers, the sCdvdCache slot fields and the request node's state by name (asserted against
// hcdvd.h), block roles, and no goto left. Every guest statement, frame, link, cycle charge and check point is the
// generated body's, in its order on every path.
#include "p3fes/game/hcdvd.h"

#include "p3fes/game/guest.h"

#include <cstddef>
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_H_Cdvd_BuildPathUppercase_00101010(p3fes::EEContext&);
void fn_H_Cdvd_NormalizePath_001013f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
// An sCdvdCache slot (hcdvd.h HCdvdCacheEntry, 148 bytes; 256 of them at 0x7D6F80).
namespace cache_ent {
inline constexpr s32 kUsed = 0, kOwner = 4, kName = 8, kData = 136, kSize = 140, kZero = 144;
inline constexpr s32 kNameSize = 128, kSlotSize = 148;
static_assert(kOwner == static_cast<s32>(offsetof(HCdvdCacheEntry, owner)) && kName == static_cast<s32>(offsetof(HCdvdCacheEntry, name)));
static_assert(kData == static_cast<s32>(offsetof(HCdvdCacheEntry, data)) && kSize == static_cast<s32>(offsetof(HCdvdCacheEntry, size)));
static_assert(kZero == static_cast<s32>(offsetof(HCdvdCacheEntry, zero)) && kSlotSize == static_cast<s32>(sizeof(HCdvdCacheEntry)));
}  // namespace cache_ent
inline constexpr s32 kCacheSlots = 256;
inline constexpr s32 kNodeState = 12, kStateLoaded = 4;  // the request node's state, 4 = loaded
static_assert(kNodeState == static_cast<s32>(kHCdvdNodeState) && kStateLoaded == static_cast<s32>(kHCdvdStateLoaded));
inline constexpr s32 kPathBuf = 0x30, kQueryNorm = 0x130, kQueryBuilt = 0x230;  // CacheFindFile's frame buffers
}  // namespace

// 0x00102650 H_Cdvd_CacheAdd -- 196 bytes; frame 0x10: ra sp+0x0
// H_Cdvd_CacheAdd(owner, data, size, name): registers a file in the first free sCdvdCache slot (nothing when the
// table is full).
// The body of H_Cdvd_CacheAdd 0x102650 and H_Cdvd_AddFileCacheEntry 0x102030 (identical code, frame 16
// for $ra). Cycles: prologue 7; loop test 3, checked as a back-edge before every slot including the
// first; 9 per slot, 1 to pass a used one, 25 to take a free one (memcpy charges its own); epilogue 4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_CacheAdd(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00102650
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t3 = 0;  // the slot index
    mview::la(t1, kHCdvdCache);  // &sCdvdCache
    for (;;) {
        // 0x001026f8: for (i = 0; i < 256; i++)
        charge(ctx, 3);
        v1 = slti(t3, kCacheSlots);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010266c: t2 = i * 148, t0 = &sCdvdCache[i]; a free slot takes the file
        charge(ctx, 9);
        v1 = sll(t3, 3);
        v1 = addu(v1, t3);
        v1 = sll(v1, 2);
        v1 = addu(v1, t3);
        t2 = sll(v1, 2);
        t0 = addu(t1, t2);
        lw(v1, t0, cache_ent::kUsed);
        if (v1 == 0) {
            // 0x00102690: a free slot: used = 1, owner, data, size, zero, then memcpy(slot->name, name, 128)
            charge(ctx, 25);
            v0 = 1;
            sw(v0, t0, cache_ent::kUsed);
            mview::la(v0, kHCdvdCache + cache_ent::kOwner);
            v0 = addu(v0, t2);
            sw(a0, v0, 0);
            mview::la(v0, kHCdvdCache + cache_ent::kData);
            v0 = addu(v0, t2);
            sw(a1, v0, 0);
            mview::la(v0, kHCdvdCache + cache_ent::kSize);
            v0 = addu(v0, t2);
            sw(a2, v0, 0);
            mview::la(v0, kHCdvdCache + cache_ent::kZero);
            v0 = addu(v0, t2);
            sw(zero, v0, 0);
            a0 = addiu(t0, cache_ent::kName);
            a1 = a3;
            a2 = cache_ent::kNameSize;
            jal(ctx, 0x1026E4u, gen::fn_memcpy_00521250);
            // 0x00102704 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x001026f4
        charge(ctx, 1);
        t3 = addiu(t3, 1);
    }
    // 0x00102704: the table is full
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00102030 H_Cdvd_AddFileCacheEntry -- 196 bytes; frame 0x10: ra sp+0x0
// H_Cdvd_AddFileCacheEntry(owner, data, size, name): the same code as H_Cdvd_CacheAdd at its own address.
// Cycles: prologue 7; loop test 3, checked as a back-edge before every slot including the first; 9 per slot,
// 1 to pass a used one, 25 to take a free one (memcpy charges its own); epilogue 4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_AddFileCacheEntry(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00102030
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t3 = 0;  // the slot index
    mview::la(t1, kHCdvdCache);  // &sCdvdCache
    for (;;) {
        // 0x001020d8: for (i = 0; i < 256; i++)
        charge(ctx, 3);
        v1 = slti(t3, kCacheSlots);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0010204c: t2 = i * 148, t0 = &sCdvdCache[i]; a free slot takes the file
        charge(ctx, 9);
        v1 = sll(t3, 3);
        v1 = addu(v1, t3);
        v1 = sll(v1, 2);
        v1 = addu(v1, t3);
        t2 = sll(v1, 2);
        t0 = addu(t1, t2);
        lw(v1, t0, cache_ent::kUsed);
        if (v1 == 0) {
            // 0x00102070: a free slot: used = 1, owner, data, size, zero, then memcpy(slot->name, name, 128)
            charge(ctx, 25);
            v0 = 1;
            sw(v0, t0, cache_ent::kUsed);
            mview::la(v0, kHCdvdCache + cache_ent::kOwner);
            v0 = addu(v0, t2);
            sw(a0, v0, 0);
            mview::la(v0, kHCdvdCache + cache_ent::kData);
            v0 = addu(v0, t2);
            sw(a1, v0, 0);
            mview::la(v0, kHCdvdCache + cache_ent::kSize);
            v0 = addu(v0, t2);
            sw(a2, v0, 0);
            mview::la(v0, kHCdvdCache + cache_ent::kZero);
            v0 = addu(v0, t2);
            sw(zero, v0, 0);
            a0 = addiu(t0, cache_ent::kName);
            a1 = a3;
            a2 = cache_ent::kNameSize;
            jal(ctx, 0x1020C4u, gen::fn_memcpy_00521250);
            // 0x001020e4 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x001020d4
        charge(ctx, 1);
        t3 = addiu(t3, 1);
    }
    // 0x001020e4: the table is full
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00102870 H_Cdvd_CacheRemove -- 96 bytes; leaf frame (no stack)
// H_Cdvd_CacheRemove(owner): frees every used slot of that owner.
// 0x102870, no frame. Cycles: entry 5; loop test 3, checked as a back-edge before every slot
// including the first; 9 per slot, +3 for a used one, +1 when its owner matches; 1 to advance; exit 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_CacheRemove(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00102870
    enter(ctx, 5);  // entry check point + this block's cycles
    a3 = 0;  // the slot index
    mview::la(a2, kHCdvdCache);  // &sCdvdCache
    for (;;) {
        // 0x001028bc: for (i = 0; i < 256; i++)
        charge(ctx, 3);
        v1 = slti(a3, kCacheSlots);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00102884
        charge(ctx, 9);
        v1 = sll(a3, 3);
        v1 = addu(v1, a3);
        v1 = sll(v1, 2);
        v1 = addu(v1, a3);
        v1 = sll(v1, 2);
        a1 = addu(a2, v1);
        lw(v1, a1, cache_ent::kUsed);
        if (v1 != 0) {
            // 0x001028a8: used: the owner's?
            charge(ctx, 3);
            lw(v1, a1, cache_ent::kOwner);
            if (v1 == a0) {
                // 0x001028b4: used = 0
                charge(ctx, 1);
                sw(zero, a1, cache_ent::kUsed);
            }
        }
        // 0x001028b8
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x001028c8
    charge(ctx, 2);
}

// 0x001016B0 H_Cdvd_IsFileLoaded -- 20 bytes; leaf frame (no stack)
// H_Cdvd_IsFileLoaded(node): node->state == 4 (the whole file is in memory).
// 0x1016B0: one block of 5 (lw, xori 4, sltiu 1).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_IsFileLoaded(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001016b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, kNodeState);
    v0 = v0 ^ kStateLoaded;
    v0 = sltiu(v0, 1);
}

// 0x001021C0 H_Cdvd_CacheFindFile -- 276 bytes; frame 0x330: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// H_Cdvd_CacheFindFile(sentinel, out_size, path): the data of the sCdvdCache slot whose normalized name equals the
// normalized query (*out_size = its size), 0 when none or when the first argument is 1.
// 0x1021C0, frame 816: saved registers at +0..+32, three 256-byte path buffers at +48 (a slot's
// normalized name), +304 (the normalized query) and +560 (the query as H_Cdvd_BuildPathUppercase
// builds it). Cycles: prologue 8; 3 for the sentinel; setup 10 (the two path helpers charge their
// own); loop test 3, checked as a back-edge before every slot including the first; per slot 11,
// +10 for a used slot (H_Cdvd_NormalizePath, strcmp), +16 on a hit; 1 to advance; 1 after the last
// slot; epilogue 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Cdvd_CacheFindFile(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001021c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x330);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    v0 = 1;
    if (a0 != v0) {
        // 0x001021ec: built = H_Cdvd_BuildPathUppercase(path); query = H_Cdvd_NormalizePath(built)
        charge(ctx, 10);
        a1 = addiu(sp, kQueryBuilt);
        jal(ctx, 0x1021F0u, gen::fn_H_Cdvd_BuildPathUppercase_00101010);
        a0 = addiu(sp, kQueryBuilt);
        a1 = addiu(sp, kQueryNorm);
        jal(ctx, 0x102200u, gen::fn_H_Cdvd_NormalizePath_001013f0);
        s0 = 0;  // the slot index
        for (;;) {
            // 0x001022ac: for (i = 0; i < 256; i++)
            charge(ctx, 3);
            v0 = slti(s0, kCacheSlots);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00102214: v1 = &sCdvdCache[i]
            charge(ctx, 11);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            mview::la(v0, kHCdvdCache);
            v1 = addu(v0, v1);
            lw(v0, v1, cache_ent::kUsed);
            if (v0 != 0) {
                // 0x00102240: a used slot: strcmp(H_Cdvd_NormalizePath(slot->name), query)
                charge(ctx, 10);
                a0 = addiu(v1, cache_ent::kName);
                a1 = addiu(sp, kPathBuf);
                jal(ctx, 0x102248u, gen::fn_H_Cdvd_NormalizePath_001013f0);
                a0 = addiu(sp, kPathBuf);
                a1 = addiu(sp, kQueryNorm);
                jal(ctx, 0x102258u, gen::fn_strcmp_00524128);
                if (v0 == 0) {
                    // 0x00102268: a hit: *out_size = slot->size, return slot->data
                    charge(ctx, 16);
                    v0 = sll(s0, 3);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s0);
                    v1 = sll(v0, 2);
                    mview::la(v0, kHCdvdCache + cache_ent::kSize);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    sw(v0, s1, 0);
                    mview::la(v0, kHCdvdCache + cache_ent::kData);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    // 0x001022bc (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x330);
                    return;
                }
            }
            // 0x001022a8
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x001022b8: none: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001021e0: the sentinel 1: 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001022bc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x330);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------
namespace p3fes::recomp_gen {

// The two registrations leave $v0 as memcpy set it (its destination) when a slot was taken, and
// untouched when the table was full: nothing to write here.

}  // namespace p3fes::recomp_gen
