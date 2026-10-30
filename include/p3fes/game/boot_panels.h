// Phase 5 slice boot, part 2: the H_ band 0x18A3F0-0x18F0E0 that shares the boot band -- the field's party panel
// ("h_party_panel_draw_proc" and its four "h_party_pnl_sub_draw" member panels), the area-name panel
// ("h_area_panel_draw_proc"), their boot-time sprite loaders (camp/ptypnl.pak, camp/areapnl.pak, from kwlnInitMain),
// the tween record's per-frame updates (sub_18B7B0 / sub_18BA60 / sub_18BB20 / sub_18BB80; the stepper sub_18B700 stays
// recompiled: test_ui6 stands it in), the fusion-spell cut-in ("H_PerEfcMixraidDraw",
// h_permixefc.c, and its five word tasks) and the battle member cut-in ("H_BtlEscEfectDraw"). Bodies in
// game/src/boot/boot_panels.cpp (p3fes_handgen's, made readable; boot.h explains the conventions and the boot sequence).
//
// Records (byte offsets; a kwln task's work block is at task +0x3C):
// * tween record (68 bytes; ui5.h: sub_18B6D0 allocates, sub_18BC10 starts, sub_18B700 steps): +0 sprite, +4 active,
//   +8 kind (0 plain, 1 also draws the sprite), +12 motion curve (0 jump, 1 linear, 2 sine, 3 cosine), +16 fade curve
//   (0 none, 1 out, 2 in), +20 sprite frame, +24 frame, +28 first frame, +32 last frame, +36 z, +40 / +44 from x / y,
//   +48 / +52 to x / y, +56 / +60 the current x / y, +64 the current alpha.
// * party panel work (100 bytes): +0 step, +8 shown, +12..+24 the four member panels, +28..+96 the 18 sprite files.
// * member panel work (116 bytes): +0 step, +4 slide state (0 start, 1 sliding in, 2 reset, 3 standing), +8 slot
//   (0 the hero, 1..3 the party), +12 mode (0 normal, 1 simple, 2 flash, 3 mark coming in, 4 mark), +16 the mode to
//   return to after the flash, +20 the unit shown, +24 the mode timer, +28 the party size laid out for, +32 the spark
//   timer, +36 shown, +40..+108 the 18 sprite files (+44 the frame sprite, +48 sparks, +52 / +56 / +60 marks, +60 + 4
//   unit = the unit's portrait), +112 the tween record.
// * area panel work (536 bytes): +4 a node, +8 the current name (256), +264 the previous name (256), +520 shown once,
//   +524 shown, +528 three tween records, +532 the area sprite file.
// * mix-raid cut-in work (2,676 bytes) and battle cut-in work (976 bytes): see sub_18A9F0 / sub_18EB40.
//
// The Answer swaps three portraits (unit 1 -> 11, unit 3 -> 11, unit 9 -> 12: sub_17D800 is the scenario word) in
// every member draw.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace boot_panels {
inline constexpr u32 kPartyPanelSprites = 0x846730u;  // u32[18]: camp/ptypnl.pak's sprite files (sub_18BC80)
inline constexpr u32 kAreaPanelSprite = 0x7CE008u;    // camp/areapnl.pak's file 0 (sub_18E4A0)
inline constexpr u32 kTweenSize = 68;
inline constexpr u32 kPartyPanelWorkSize = 100;
inline constexpr u32 kMemberPanelWorkSize = 116;
inline constexpr u32 kAreaPanelWorkSize = 536;
inline constexpr u32 kMixraidWorkSize = 2676;
inline constexpr u32 kBtlCutinWorkSize = 976;
}  // namespace boot_panels

void sub_18A3F0(EEContext& ctx);  // 0x18A3F0 (task) -> 0 / -1 [H_MixWord5Draw]
void sub_18A9C0(EEContext& ctx);  // 0x18A9C0 (task) [H_MixDestroyWork]
void sub_18A9F0(EEContext& ctx);  // 0x18A9F0 (task) -> 0 / -1 [H_PerEfcMixraidUpdate]
void sub_18B270(EEContext& ctx);  // 0x18B270 (task) [H_PerEfcMixraidDestroy]
void sub_18B360(EEContext& ctx);  // 0x18B360 (task) -> bool [H_PerEfcMixraidIsReady]
void sub_18B380(EEContext& ctx);  // 0x18B380 (task) [H_PerEfcMixraidStartWords]
void sub_18B5F0(EEContext& ctx);  // 0x18B5F0 (task) -> frame [H_PerEfcMixraidGetFrame]
void sub_18B620(EEContext& ctx);  // 0x18B620 (parent, spell) -> task / 0 [H_PerEfcMixraidCreate]
void sub_18B7B0(EEContext& ctx);  // 0x18B7B0 (tween, out_xy) [H_TweenPosition]
void sub_18BA60(EEContext& ctx);  // 0x18BA60 (tween, out_alpha) [H_TweenAlpha]
void sub_18BB20(EEContext& ctx);  // 0x18BB20 (tween) -> alpha != 255 [H_TweenUpdatePlain]
void sub_18BB80(EEContext& ctx);  // 0x18BB80 (tween) -> alpha != 255 [H_TweenUpdateSprite]
void sub_18BC80(EEContext& ctx);  // 0x18BC80 () [H_PartyPanelLoad]
void sub_18BD90(EEContext& ctx);  // 0x18BD90 (task) -> 0 [H_PartyPanelUpdate]
void sub_18BEE0(EEContext& ctx);  // 0x18BEE0 (panel_task, unit, kind) [H_PartyPanelSetMemberMode]
void sub_18BFA0(EEContext& ctx);  // 0x18BFA0 (task) [H_PartyPanelDestroy]
void sub_18BFF0(EEContext& ctx);  // 0x18BFF0 (parent) -> task / 0 [H_PartyPanelCreate]
void sub_18C0A0(EEContext& ctx);  // 0x18C0A0 (task) -> bool [H_PartyPanelIsReady]
void sub_18C0C0(EEContext& ctx);  // 0x18C0C0 (task, shown) [H_PartyPanelSetShown]
void sub_18C150(EEContext& ctx);  // 0x18C150 (member) [H_PartyMemberDrawNormal]
void sub_18C780(EEContext& ctx);  // 0x18C780 (member) [H_PartyMemberDrawMarkIn]
void sub_18CE50(EEContext& ctx);  // 0x18CE50 (member) [H_PartyMemberDrawMark]
void sub_18D320(EEContext& ctx);  // 0x18D320 (member) [H_PartyMemberDrawFlash]
void sub_18DB20(EEContext& ctx);  // 0x18DB20 (member) [H_PartyMemberDraw]
void sub_18DDE0(EEContext& ctx);  // 0x18DDE0 (member_task, kind) [H_PartyMemberSetMode]
void sub_18DE60(EEContext& ctx);  // 0x18DE60 (task) -> 0 [H_PartyMemberUpdate]
void sub_18E330(EEContext& ctx);  // 0x18E330 (task) [H_PartyMemberDestroy]
void sub_18E390(EEContext& ctx);  // 0x18E390 (parent, slot, files) -> task / 0 [H_PartyMemberCreate]
void sub_18E490(EEContext& ctx);  // 0x18E490 (member_task, shown) [H_PartyMemberSetShown]
void sub_18E4A0(EEContext& ctx);  // 0x18E4A0 () [H_AreaPanelLoad]
void sub_18E540(EEContext& ctx);  // 0x18E540 (task) -> 0 [H_AreaPanelUpdate]
void sub_18E5C0(EEContext& ctx);  // 0x18E5C0 (task, name) [H_AreaPanelSetName]
void sub_18E7A0(EEContext& ctx);  // 0x18E7A0 (task) [H_AreaPanelDestroy]
void sub_18E820(EEContext& ctx);  // 0x18E820 (parent) -> task / 0 [H_AreaPanelCreate]
void sub_18E8E0(EEContext& ctx);  // 0x18E8E0 (work) [H_AreaPanelDraw]
void sub_18EB30(EEContext& ctx);  // 0x18EB30 (task, shown) [H_AreaPanelSetShown]
void sub_18EB40(EEContext& ctx);  // 0x18EB40 (task) -> 0 / -1 [H_BtlEscEffectUpdate]
void sub_18EF60(EEContext& ctx);  // 0x18EF60 (task) [H_BtlEscEffectDestroy]
void sub_18EFB0(EEContext& ctx);  // 0x18EFB0 (parent, unit) -> task / 0 [H_BtlEscEffectCreate]
void sub_18F060(EEContext& ctx);  // 0x18F060 (task) -> bool [H_BtlEscEffectIsWaiting]
void sub_18F080(EEContext& ctx);  // 0x18F080 (task) [H_BtlEscEffectGo]
void sub_18F0A0(EEContext& ctx);  // 0x18F0A0 () -> 63 [H_BtlEscEffectLength]
void sub_18F0B0(EEContext& ctx);  // 0x18F0B0 (task) -> frame [H_BtlEscEffectGetFrame]
void sub_18F0C0(EEContext& ctx);  // 0x18F0C0 (task) -> bool [H_BtlEscEffectPast50]
void sub_18F0E0(EEContext& ctx);  // 0x18F0E0 (task) [H_BtlEscEffectRelease]

}  // namespace p3fes::game
