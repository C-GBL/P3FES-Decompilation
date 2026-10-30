// Phase 5 slice `standins_demo`: functions the slices used to skip because their own body allocates or frees, calls
// printf / sprintf or requests a file (docs/PHASE5_AGENT_BRIEF.md step 7 before 2026-10-21). Their pair tests run on
// the test stand-ins (tests/game/stand_ins.h: a deterministic guest heap behind H_Malloc / the RW memory slots, a
// printf / sprintf that formats like newlib, a fake H_Cdvd layer over extracted/). Names are symbols/functions.json's;
// roles in brackets are proposals, not imported. All are register-faithful (frames, spills, $ra, scratch registers at
// every call and check point as the original leaves them) and take their arguments from the guest registers, so each
// shim only calls the function.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// --- file requests (H_Cdvd_Request) -------------------------------------------------------------------------------
// The resource loaders: assert the module work (a gp word) exists and the request is not pending yet, then
// work[off] = H_Cdvd_Request(path, isArchive) and set the pending bit.
void sub_266A20(EEContext& ctx);  // [opRes_RequestTitle] op_res.c: oped/op_title.bin -> work+8, flags |= 1
void sub_266CB0(EEContext& ctx);  // [opRes_RequestLogo] op_res.c: oped/op_logo.bin -> work+72, flags |= 2
void sub_21C7F0(EEContext& ctx);  // [bpRes_RequestTutorial] bp_res.c: battle/panel/bp_tutorial.bin (plain file) -> work+132, flags |= 4
void sub_233B20(EEContext& ctx);  // [brRes_RequestLevel] br_res.c: battle/result/br_level.bin -> work+16, flags |= 2
void sub_2339D0(EEContext& ctx);  // [brRes_RequestBase] br_res.c: br_base.bin / AGS_ / AGS2_ by scenario and flag 752 -> work+12, flags |= 1
void sub_24BE40(EEContext& ctx);  // [brpRes_RequestBirth] brp_res.c: battle/result/brp_birth.bin -> work+8, flags |= 1
void sub_107020(EEContext& ctx);  // [H_Fade_ReadPak] request + H_Cdvd_ReadSync of the fade PAK, node in 0x7E39D0

// --- heap (the RW memory functions through 0x960178 / 0x96017C / 0x960184) ------------------------------------------
void sub_2699A0(EEContext& ctx);  // [RwFree tail] free(a0) through the slot 0x96017C
void sub_266600(EEContext& ctx);  // [gmRoot destroy] gm_root.c: assert gp-18788, clear it, free(task->+60)
void sub_3C4430(EEContext& ctx);  // [nmList_Create](payload) nmlist.c: a 24-byte header + payload from RwMalloc, zeroed
void sub_3C45F0(EEContext& ctx);  // [nmList_Destroy](list) release the items (sub_3C4A90), zero, free
void sub_3C4F30(EEContext& ctx);  // [nmBuffer_Destroy](buf) zero buf->+8 bytes, free
void sub_430150(EEContext& ctx);  // [Y_SMap staire destroy] free(task->+60)
void sub_4310E0(EEContext& ctx);  // [Y_SMap mask destroy] free(task->+60)
void Y_SMap_CreateStaireDispTask(EEContext& ctx);  // calloc(1, 28) work + kwlnTaskCreate("y_staire_disp_proc"...)
void sub_234710(EEContext& ctx);  // [brRes_SetCopy](src, size) RwMalloc + memcpy -> work+44, flags2 |= 0x20

// --- printf / sprintf ---------------------------------------------------------------------------------------------
void sub_2449D0(EEContext& ctx);    // printf(gp-26756, an empty string in the ELF), then sub_244770
void sub_1FA450(EEContext& ctx);    // [brfUpdateFriendEquip] unless The Answer: printf("brfUpdateFriendEquip\n"), sub_1FA4F0 for 2..5, 7..10
void sub_1FBCA0(EEContext& ctx);    // [brData_CountRanges](level) count the rows whose [lo, hi) holds it, printf("%d <= %d < %d\n") each
void sub_21B8B0(EEContext& ctx);    // [bse_SetValue](value) bse_main.c: printf(gp-26796, empty), work+8 = value, flags &= ~1
void kwlnAdxErrorCallback(EEContext& ctx);  // printf(a1): the ADX library's error message
void bpIfontDrawNumber(EEContext& ctx);     // sprintf("%d") into its frame, one bpIfontSetDigitQuad per digit from the right

}  // namespace p3fes::game
