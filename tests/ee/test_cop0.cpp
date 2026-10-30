// COP0 semantics (runtime/include/p3fes/ee/cop0.h). (hand: manual) unless stated.
#include "ee_test_util.h"

#include "p3fes/ee/cop0.h"

using namespace p3fes;
namespace cop0 = p3fes::ee::cop0;

TEST_CASE("cop0: EI/DI toggle Status.EIE (bit 16) and nothing else") {
    EEContext c;
    c.cop0[cop0::kStatus] = cop0::kStatusExl | cop0::kStatusIe;
    cop0::ei(c);
    CHECK(c.cop0[cop0::kStatus] == (cop0::kStatusExl | cop0::kStatusIe | 0x10000u));
    CHECK(cop0::interrupts_enabled(c));
    cop0::di(c);
    CHECK(c.cop0[cop0::kStatus] == (cop0::kStatusExl | cop0::kStatusIe));
    CHECK_FALSE(cop0::interrupts_enabled(c));
}

TEST_CASE("cop0: MFC0/MTC0 are plain storage; ERET clears ERL first, else EXL") {
    EEContext c;
    cop0::mtc0(c, cop0::kEpc, 0x00123450u);
    cop0::mtc0(c, cop0::kErrorEpc, 0x00ABCDE0u);
    CHECK(cop0::mfc0(c, cop0::kEpc) == 0x00123450u);
    c.cop0[cop0::kStatus] = cop0::kStatusErl | cop0::kStatusExl;
    CHECK(cop0::eret(c) == 0x00ABCDE0u);
    CHECK(c.cop0[cop0::kStatus] == cop0::kStatusExl);
    CHECK(cop0::eret(c) == 0x00123450u);
    CHECK(c.cop0[cop0::kStatus] == 0u);
}

TEST_CASE("cop0: CPCOND0 = every channel selected in D_PCR.CPC has D_STAT.CIS set") {
    CHECK(cop0::cpcond0(0u, 0u));                    // nothing selected: asserted
    CHECK_FALSE(cop0::cpcond0(0x4u, 0u));            // channel 2 selected, not complete
    CHECK(cop0::cpcond0(0x4u, 0x4u));
    CHECK_FALSE(cop0::cpcond0(0x6u, 0x4u));          // channels 1+2 selected, only 2 complete
    CHECK(cop0::cpcond0(0x6u, 0x3FFu));
    CHECK(cop0::cpcond0(0xFFFF0000u, 0u));           // bits above CPC[9:0] are not channels
    CHECK(cop0::cpcond0(0x4u, 0x00000004u | 0x03FF0000u));  // CIM bits of D_STAT do not matter
}
