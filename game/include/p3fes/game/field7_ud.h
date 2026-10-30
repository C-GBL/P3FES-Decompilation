// Phase 5 slice field7, part 4 (game/src/field/field7_ud.cpp): the RpUserData frame searches of the 0x1A0000 band.
// A clump's frames carry user-data arrays (RpUserData, render_rw7: count sub_48EDE0, n-th array sub_48EE30, name
// sub_48EF10, format sub_48EF20 -- 1 = int --, entries sub_48EF30, n-th int sub_48EF40); these find an int entry by
// array name -- by value (sub_1A69A0: the models' "per3HelperId" helpers) or as the n-th one in walk order
// (sub_1A6E90: the field objects' "per3FieldObjectResid / Type / Collis / Id / Anim") -- the root frame first, then
// the descendants through RwFrameForAllChildren (sub_4CB6E0) with the callbacks sub_1A6860 (left recompiled: test_models
// stands it in), sub_1A6D20 and the counting sub_1A6AF0. Register-ABI bodies; proposed names in brackets (ADR-0009).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f7::ud {
// the search record on the caller's stack (84 bytes for sub_1A6E90 / sub_1A6D20; sub_1A69A0 keeps name, result, id)
inline constexpr int kRecName = 0;     // char[64]: the array name
inline constexpr int kRecWanted = 64;  // sub_1A6D20: n (sub_1A69A0: the frame found)
inline constexpr int kRecTotal = 64;   // sub_1A6AF0: the count it adds to
inline constexpr int kRecCount = 68;   // sub_1A6D20: entries seen so far (sub_1A69A0: the id)
inline constexpr int kRecFound = 72;
inline constexpr int kRecValue = 76;
inline constexpr int kRecFrame = 80;
inline constexpr int kRecSize = 84;
}  // namespace f7::ud

void sub_1A69A0(EEContext& ctx);  // [K_Clump_FindFrameByUserId](clump, name, id) -> frame / 0
void sub_1A6AF0(EEContext& ctx);  // [K_Frame_CountUserInts](frame, record) -> frame
void sub_1A6D20(EEContext& ctx);  // [K_Frame_FindNthUserInt](frame, record) -> frame, or 0 to stop
void sub_1A6E90(EEContext& ctx);  // [K_Clump_GetNthUserInt](out, clump, name, n)

}  // namespace p3fes::game
