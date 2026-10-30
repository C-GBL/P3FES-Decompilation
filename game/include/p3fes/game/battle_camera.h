// The battle camera band 0x2A0050-0x2B7058, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/27_unmapped_bands.md
// "battle camera"): the unit / screen colour packets at its start, the battle camera object (a ring of four position +
// rotation keys, its interpolation, field of view), the camera set / switch layer over the camera table 0x6939F0 (20-byte
// rows {init, update, flag, flag, name}; the current camera id at gBtl+240) and the camera work states the table rows
// point at. Phase 5 slice `battle_camera`; game/src/battle/battle_camera*.cpp, pair tests
// tests/game/test_battle_camera.cpp.
//
// Names: as symbols/functions.json gives them now (all `sub_<addr>` / `nullsub_<n>`); what each does is documented at
// its body. Every function here is register-faithful at each check point, call and return (game/src/battle/
// battle_camera_cpu.h); the arguments are the guest registers ($a0.., $t0, $f12), so the API is the context itself.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle_task.h"

namespace p3fes::game {

namespace btl_cam {
// --- btl packets (battle_actions.h: the queued records sub_27ED20 links at gBtl+372) ---------------------------------
inline constexpr s32 kPktCallback = 108;        // u32: the per-frame callback (data in $a0; non-zero = done)
inline constexpr s32 kPktData = 120;            // u32: the packet's data block (sub_27EC10's second argument = its size)
// the packet kinds of the colour packets (sub_27EC10's first argument)
inline constexpr s32 kPktUnitColour = 1538;     // sub_2A0050: three colours (sub_29FAA0)
inline constexpr s32 kPktScene = 1539;          // sub_2A1080 (sub_2A0440)
inline constexpr s32 kPktScreenFade = 1540;     // sub_2A1280 (sub_2A10E0)
inline constexpr s32 kPktScreenRestore = 1541;  // sub_2A16C0 (sub_2A1400)
inline constexpr s32 kPktUnitFade = 1542;       // sub_2A1B00 (sub_2A1710)
inline constexpr s32 kPktUnitFadeIn = 1543;     // sub_2A1DB0 (sub_2A1B70)
// --- gBtl ------------------------------------------------------------------------------------------------------------
inline constexpr s32 kScreenColour = 564;       // f32[4]: the battle screen colour (RGBA, 0..1)
inline constexpr s32 kSideListB = 336;          // u32[2] (stride 8): the per-side btlUnit lists along +2612
// --- btlAction / btlUnit ---------------------------------------------------------------------------------------------
inline constexpr s32 kActTargets = 56;          // u32[]: the chosen targets (btlActions)
inline constexpr s32 kActTargetCount = 106;     // u16
inline constexpr s32 kUnitNextB = 2612;         // u32: next btlUnit in its side's list
inline constexpr s32 kUnitModelId = 2546;       // u16: the unit's model (0 = none)
// --- $gp constants ---------------------------------------------------------------------------------------------------
inline constexpr s32 kGpInv255 = -32232;        // f32 1/255
inline constexpr s32 kGpBaseColour = -18424;    // u8[4]: the battle's base screen colour
inline constexpr s32 kGpSkillTbl = -18680;      // SKILL.TBL (44-byte records)
inline constexpr s32 kGpSkillAttr = -18672;     // per-skill 28-byte attribute records: +2 u16 flags (0x10 no camera,
                                                //   0x20 skill camera, 0x4000)
inline constexpr s32 kGpPersonaTbl = -18628;    // 88-byte records indexed by a unit sub-object's +164 (+0 bit 0)
inline constexpr s32 kGpOneThird = -32056;      // f32 1/3
inline constexpr s32 kGpTwoThirds = -32676;     // f32 2/3
// --- the camera set / switch layer (gBtl fields; the camera work record / camera object is gBtl+32) -----------------
inline constexpr s32 kBtCamRec = 32;            // the camera work record = the camera object (record+0 flags, +4 the
                                                //   key ring, +116/+118/+120 ring head / count / write, +124, +128,
                                                //   +132 duration, +148, +152 frame; record+156 = gBtl+188 the key)
inline constexpr s32 kBtCamKey = 188;           // the current camera key (position f32[3], rotation f32[4])
inline constexpr s32 kBtCamId = 240;            // u16: the current camera (row of the camera table 0x6939F0)
inline constexpr s32 kBtCamFlags = 244;         // u32: bit 0 (sub_2A4C50), bit 1 the row's +12 flag
inline constexpr s32 kBtCam248 = 248;           // u32: cleared by a switch
inline constexpr s32 kBtCam252 = 252;           // u32: cleared by a switch (record+220)
inline constexpr s32 kBtCamSubject = 256;       // u32: the subject btlAction (record+224)
inline constexpr s32 kBtCamHistory = 258;       // u16[]: +260 the previous camera
inline constexpr s32 kBtCamRepeat = 266;        // u16: switches to the same camera in a row
inline constexpr s32 kBtCamParam = 288;         // u32: the state's parameter word (record+256)
inline constexpr s32 kRcSubject = 224;          // camera work record: the subject btlAction
inline constexpr s32 kPktCameraSet = 512;       // sub_2A3B40 (sub_2A3B00)
inline constexpr s32 kPktCameraMove = 513;      // sub_2A3D70 (sub_2A3BA0)
// --- btlAction / btlUnit fields of the set layer ---------------------------------------------------------------------
inline constexpr s32 kAcMoveKind = 108;         // u16: 3 = (sub_2A3520)
inline constexpr s32 kAcSkill = 110;            // u16: the skill / item of the command
inline constexpr s32 kAcItem = 114;             // u16: sub_308A50's argument
inline constexpr s32 kAcNextInList = 1192;      // u32: next btlAction in gBtl+332's list
inline constexpr s32 kUnPersona = 2560;         // u32: the unit's sub-object (persona)
inline constexpr s32 kUnPersonaIdx = 164;       // u16: (sub-object) its index into *(gp-18628)
inline constexpr s32 kUnSize = 144;             // f32: the unit's size (radius = +144 * +44)
inline constexpr s32 kUnScale = 44;             // f32: the unit's scale
}  // namespace btl_cam

// The replaced functions of battle_camera.cpp: X(name, address as 8 hex digits). (battle_camera_<k>.h list the
// camera work states of battle_camera_<k>.cpp.)
#define P3FES_BCAM_BODIES(X) \
    X(sub_2A0050, 002a0050) \
    X(sub_2A1080, 002a1080) \
    X(sub_2A10E0, 002a10e0) \
    X(sub_2A1280, 002a1280) \
    X(sub_2A1400, 002a1400) \
    X(sub_2A16C0, 002a16c0) \
    X(sub_2A1710, 002a1710) \
    X(sub_2A1B00, 002a1b00) \
    X(sub_2A1B70, 002a1b70) \
    X(sub_2A1DB0, 002a1db0) \
    X(sub_2A32F0, 002a32f0) \
    X(sub_2A3380, 002a3380) \
    X(sub_2A3420, 002a3420) \
    X(sub_2A3520, 002a3520) \
    X(sub_2A3550, 002a3550) \
    X(sub_2A3590, 002a3590) \
    X(sub_2A3750, 002a3750) \
    X(sub_2A3820, 002a3820) \
    X(sub_2A3850, 002a3850) \
    X(sub_2A38F0, 002a38f0) \
    X(sub_2A3A80, 002a3a80) \
    X(sub_2A3A90, 002a3a90) \
    X(sub_2A3B00, 002a3b00) \
    X(sub_2A3B40, 002a3b40) \
    X(sub_2A3BA0, 002a3ba0) \
    X(sub_2A3D70, 002a3d70) \
    X(sub_2A3E80, 002a3e80) \
    X(sub_2A42A0, 002a42a0) \
    X(sub_2A4330, 002a4330) \
    X(sub_2A4470, 002a4470) \
    X(sub_2A44B0, 002a44b0) \
    X(sub_2A44F0, 002a44f0) \
    X(sub_2A4530, 002a4530) \
    X(sub_2A4690, 002a4690) \
    X(sub_2A4C50, 002a4c50)

// Each runs the replaced body on the guest context (arguments in its registers, results left there).
#define P3FES_BCAM_API(name, addr) void name(EEContext& ctx);
P3FES_BCAM_BODIES(P3FES_BCAM_API)
#undef P3FES_BCAM_API

}  // namespace p3fes::game
