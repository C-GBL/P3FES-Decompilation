// Static Q-pipeline timing model (private to p3fes_vu1).
//
// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/include/ps2/vu_ops.hpp (vf_use, issue, retire, q_delay,
// q_unit_latency, waits_q, reads_q, q_read_kind, branch_delay_exempt), MIT; adapted for p3fes-port (operates on the
// decoder's DecodedPair fields instead of raw words; undefined halves contribute no operands; the branch list is
// built once per micro-memory generation instead of per query).
//
// Upstream models the FMAC/EFU interlocks to decide when a DIV/RSQRT result becomes visible: every vf lane and
// loaded vi register has a ready cycle (+4 after the producing pair issues); each pair issues one cycle after the
// previous one or when its operands are ready. `q_delay` is the number of pairs after the producer until the Q
// latency (7 cycles DIV/SQRT, 13 RSQRT) has elapsed along the straight-line path; `q_read_kind` walks the static
// predecessors of a Q-reading pair (at most 15 pairs back) and classifies the read as always seeing the new Q, always
// the old one, or path-dependent (then resolved at run time by the pair counter). Hardware-unverified.
#pragma once

#include "p3fes/vu1/vu1_decode.h"

#include <span>
#include <utility>
#include <vector>

namespace p3fes::vu1::detail {

using Code = std::span<const DecodedPair, kMicroPairs>; // indexed by byte pc >> 3
using Jump = std::pair<u32, u32>;                         // (target byte pc, delay-slot byte pc)

enum class QRead : u8 { Dynamic, New, Old };

inline const DecodedPair& at(Code code, u32 byte_pc) noexcept { return code[(byte_pc & kMicroMask) >> 3]; }

// 7 for DIV/SQRT, 13 for RSQRT, 0 otherwise (LOI pairs have no lower op).
u32 q_unit_latency(const DecodedPair& d) noexcept;
bool waits_q(const DecodedPair& d) noexcept;
// Upper ops that read Q: MULq ADDq MADDq SUBq MSUBq and the ACC forms MULAq ADDAq MADDAq SUBAq MSUBAq.
bool reads_q(const UpperInsn& u) noexcept;
// Lower ops whose vi result a following conditional branch sees immediately (flag reads, BAL, JALR).
bool branch_delay_exempt(LowerOp op) noexcept;

// Every relative branch (B BAL IB*) in micro memory as (target, delay slot).
std::vector<Jump> collect_jumps(Code code);

// Optional record of what an analysis looked at (the ahead-of-time generator uses it to know which pairs outside a
// program, and which jump targets, a compiled Q decision depends on): `reads` = byte pcs of every pair read,
// `expanded` = byte pcs whose jump-list predecessors were consulted. Recording changes no result.
struct Footprint {
    std::vector<u32> reads;
    std::vector<u32> expanded;
};

u32 q_delay(Code code, u32 pc, u32 latency, Footprint* footprint = nullptr);
QRead q_read_kind(Code code, std::span<const Jump> jumps, u32 pc, Footprint* footprint = nullptr);

} // namespace p3fes::vu1::detail
