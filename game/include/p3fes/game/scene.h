// Slice scene: the 0x3B0000 band beyond the fonts (game/src/scene/scene_{res,func,comu,misc}.cpp). Every function keeps
// the name symbols/functions.json gives it; a proposed name is given in [brackets] (and in symbols/deltas/scene.sym).
// Register ABI throughout: arguments in $a0.. ($f12.. for floats), the result in $v0 ($f0 for floats).
//
// What the band holds (obs: the K_Assert file strings, task names, callers; 0x3AE000-0x3B4FC0 are the fonts, font2.h):
//   0x3B4FC0-0x3B5620  resrcManager.c  -- the resource manager: 22 typed, doubly linked lists of resource records
//   0x3B5620-0x3B8210  mt_scene.c      -- the scene record, MT_Scene_Load / unload, the typed creators, delete, the
//                                         transform helpers (pos / rot / scale -> model or EPL), matrix <-> angles
//   0x3B8210-0x3BD280  mt_sceneFunc.c  -- the scene function layer the event scripts drive: move / rotate / fade /
//                                         motion requests on resources (the "SceneManager Task" executes them), the
//                                         icon EPLs over characters ("10ban" icon), bezier camera / actor paths, the
//                                         field-hit value under a point, the icon files icon/ICON1..25.EPL
//   0x3BD280-0x3C0000  comuFunction.c, comuTimerSequence.c -- the social-link ("comu") table comuTable.bin and its
//                                         accessors, link-state rules, event requests, the comu timer sequence steps
//                                         (0x3C0000-0x3C442C continue it: social_map.cpp)
// Left recompiled in the band: what other slices' tests stand in with answers (MT_Scene_Load 0x3B5760 and its unload
// sub_3B5AB0 / try-finish sub_3B5A10, MT_Scene_GetRes sub_3B5D10, the stage getter sub_3B5D00, sub_3B5CF0, the class
// count sub_3B5DF0, the curve rows sub_3B55B0 (and their user sub_3BBED0), sub_3B64C0, sub_3B65D0, the scheduled-event table getter sub_3BD880,
// sub_3BD8B0 / sub_3BD9A0 / sub_3BE8E0, the frFontEx draw-string trio sub_3B2CB0 / sub_3B2F90 / sub_3B32D0) and what
// calls them (most of mt_sceneFunc.c's resource-id wrappers go through sub_3B5D10); fptodp / qsort users; the
// scene manager task bodies sub_3BCCB0 / sub_3BD010 (they call the big executor sub_3B9610 and sub_3BB7A0).
//
// --- The scene and its resources (what an editor places; field4.h and 26_field.md 3.1 have the loader side) --------
// The scene record 0x95AFC0 (gp-0x57B0 holds the pointer; namespace scn::scene): +0 s32 major, +4 s32 minor, +8 the
// resource manager, +12 flags (bit 0 loaded, bit 1 reload the NPC set, bit 2 reload the ENV), +20 s16 the NPC set,
// +22 s16 the ENV sub-id.
// The resource manager: 88 bytes = 22 list heads (u32), one per type. A resource id is u16: type = id >> 10 (6 bits),
// index = id & 0x3FF; the record is found on list `type` by id (resrcMngFindRes) -- ids are unique per manager.
// The resource record (RwMalloc'd, zeroed; namespace scn::res), the common 256 bytes:
//   +0 u16 id           +4 vec3 position        +16 vec3 rotation (degrees, x y z)   +28 vec3 scale (1.0 at creation)
//   +40 u32 flags: bit 0 a move is running, bit 1 visible (the field draw tasks test it), bit 2 a rotation is running,
//       bit 3 shown (set by every creator that takes an object), bit 6 cleared by a new move, 0x2000 a motion request
//       is queued, 0x4000 an alpha fade is running
//   +44 vec3 move from  +56 vec3 move to  +80 u8 move state  +84 a block the manager frees with the record  +88 f32
//       move speed (sub_3B86C0)
//   +100 vec3 rotation from  +112 vec3 rotation to  +124 u8 state  +125 u8 mode  +128 s32 frames  +132 s32 time
//   +180 u8 alpha from  +181 u8 alpha to  +184 s32 frames  +188 s32 time  +192 u8 hold (sub_3B8CE0)
//   +248 next  +252 prev (the type list)
// then by type (record size from the jump table 0x7BB250):
//   1  characters, 496 B: +256 / +260 two icon EPL slots, +264 the "10ban" icon, +268 u8 which slot is current,
//      +272 a queued motion request (5 words + f32), +296 the model, +480 the controller task, +484 its control
//      object, +488 the shadow model
//   2  plain models, 464 B: +256 the motion request, +280 the model
//   3  objects / NPCs (id 0xC00 | n: the FBN NPC records), 544 B: as type 1 up to +296, +488 the task, +492 a second
//      model, +496 the control object, +512 / +520 two owned blocks
//   4 / 5  the character / NPC lights, 432 B          6  effects (EPL at +260), 264 B
//   7  272 B: +256 f32 (35.0 at creation), +264 a word sub_3BB340 clears        8  positions, 256 B
//   10 field object models, 304 B: +260 the model, +300 a second model           11 field EPLs (+260), 264 B
//   12 Tartarus blocks (id 0x3000 + 16 z + x), 368 B: +352 the block data (its collision clump at +8)
//   13 / 21  field hits, 336 B: +256 u8 rgba, +260 vec3 the centre, +272 width, +276 depth, +280 the turn about y,
//      +284 the quad derived from them (4 x vec3: the corners (-w/2, -d/2), (w/2, -d/2), (-w/2, d/2), (w/2, d/2) turned
//      and moved to the centre; triangles {0, 1, 2} and {1, 2, 3}), +332 s32 the hit's value (type 21: sub_3BAA70)
//   14..19 positions / markers (15: enemies 0x3C00 + i), 272 B: +256 vec3, +268 f32 angle
//   20 cameras, 288 B: +256 kind, +260 f32, +264 an RW matrix, +268 vec3 eye, +280 / +284 two floats
//   0 and 9 have no record (resrcMngAddRes returns 0).
//
// --- Bezier paths (mt_sceneFunc.c; namespace scn::path) -------------------------------------------------------------
// u8 count at +0, then 3 count + 1 points of 12 bytes (x, y, z) from +4: segment i is the cubic Bezier of points
// 3i .. 3i+3 (consecutive segments share their end point; stride 36). sub_3BBD40 evaluates the path at t in [0, 1)
// (segment = (int)(t * count), local t = (t mod 1 / count) * count; t >= 1 the end point), sub_3BC0E0 / sub_3BC730
// measure it with 20 chords per segment.
//
// --- comuTable.bin (inside event/comuPack.pak; comuFunction.c) -----------------------------------------------------
// The pak is the usual PAK container (252-byte name + u32 size, data). comuTable.bin: u16 version (must be 1), u8 the
// last section number (143), u8 0, then 144 entries {u32 offset from the file start (0: absent), u32 size}. The loader
// (sub_3BD280, at boot) keeps the section pointers at 0x95B078 + 4 i and the sizes at 0x95B2B4 + 4 i; sections 0..29
// (the rank events of each link: 14-byte rows, 10 per rank), 32..61 (24-byte rows per rank: four event triples) and
// 64..93 are copied to per-link tables; the named tables become {pointer, count} pairs (record sizes in scn::comu):
// 96 (24 B), 99 / 100 (3 B: {month, day, minor} -- month 255 = a weekday), 101 / 102 (5 B: {m0, d0, m1, d1, minor}),
// 104 (5 B), 105 (3 B), 106 (4 B), 107 (6 B), 112 (10 B: {u8, u8, u16, u8, -, u16 value, u16 flag}), 114 (24 B: link
// rank events), 115 (2 B), 116 (16 B), 117 (2 B: {link 6..11, min rank}), 123 (26 B: {u8 link, .., u16 flag per rank}),
// 125 (12 B), 128 (5 B: {month, day, link, min rank, max rank}), 131 (12 B), 135 (6 B), 136 (8 B), 139 (3 B); single
// pointers: 119 / 120 / 121 / 122 (6-byte event triples {u16 major, u16 minor, u16 sub}), 124 (64 x 32-byte link
// records), 126 (u8 per link), 127, 129, 130, 132, 133 (f32), 134, 137, 138, 140. An event triple names an event
// file (major, minor) and its sub-id; the 56-byte event request of sub_3BE2A0 collects up to four of them.
// The comu timer sequence: a chain of steps (kwln task work: +0 state, +4 timer, +8 frames to wait) where a step
// returns 0 (again next frame), -1 (done) or the next step's address; the steps request events 808..811 / 861 through
// adminiChangeSeq(3, {.., +12 event, +16 1, +20 arg}, 28, 0).
//
// --- The icon EPLs ------------------------------------------------------------------------------------------------
// 0x6A3130: 26 slots, "icon/ICON1.EPL" .. "icon/ICON25.EPL" and NULL; all read into the H_Cdvd cache at boot
// (sub_3BD130); sub_3BAC40 puts icon n over a character / object (icon 10 = the "10ban" icon in its own slot).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace scn {
namespace comu {  // comuTable.bin and the comu globals (the table block 0x95B070; lo parts of 0x960000, gp offsets)
inline constexpr s32 kGpPakPath = -22408;  // 0x7CD568: "event/comuPack.pak"
inline constexpr s32 kGpPakRequest = -18056;  // 0x7CE668: the H_Cdvd request of comuPack.pak
inline constexpr s32 kGpPersonaTable = -18640;  // 0x7CE420: PERSONA.TBL section 0 (14-byte records: +0 flags, +2 arcana, +3 level)
inline constexpr s32 kGpScriptPath = -22400;  // 0x7CD570: "event/SiteibiEvent.bf" (inside the pak)
inline constexpr s32 kGpTablePath = -22404;  // 0x7CD56C: "event/comuTable.bin" (inside the pak)
inline constexpr s32 kGpTimerArg = -18052;  // 0x7CE66C: the comu timer word sub_3BF370 clears
inline constexpr s32 kGpTimerEvent = -18040;  // 0x7CE678: the event request of the timer sequence (sub_3BF8E0 / sub_3BF720)
inline constexpr s32 kGpTimerLink = -18044;  // 0x7CE674: s32: the link the timer sequence works on (sub_3BFDB0 / sub_3BFC50)
inline constexpr s32 kLoCallDays = -18824;  // 0x95B678: {section 99, /3}, {100, /3}, {101, /5}, {102, /5}: the dated / ranged call tables (sub_3BFFA0)
inline constexpr s32 kLoDateLinkCount = -18724;  // 0x95B6DC: the row count of section 128
inline constexpr s32 kLoDateLinks = -18728;  // 0x95B6D8: {section 128, size / 5}: {month, day, link, min rank, max rank} (sub_3BECA0)
inline constexpr s32 kLoDatedConds = -18848;  // 0x95B660: {section 106, size / 4}: dated conditions (sub_3BD890)
inline constexpr s32 kLoDatedFlags = -18840;  // 0x95B668: {section 107, size / 6}: dated flags (sub_3BD8A0)
inline constexpr s32 kLoLinks = -18664;  // 0x95B718: section 124: 64 x 32-byte social link records (sub_3BEB10)
inline constexpr s32 kLoMapEventCount = -18828;  // 0x95B674: the row count of section 112
inline constexpr s32 kLoMapEvents = -18832;  // 0x95B670: {section 112, size / 10}: 10-byte event rows (sub_3BDA60)
inline constexpr s32 kLoPartnerCount = -18740;  // 0x95B6CC: the pair count of section 117
inline constexpr s32 kLoPartners = -18744;  // 0x95B6C8: {section 117, size / 2}: {link 6..11, rank} pairs (sub_3BE020)
inline constexpr s32 kLoRankEventCount = -18772;  // 0x95B6AC: the row count of section 114
inline constexpr s32 kLoRankEvents = -18776;  // 0x95B6A8: {section 114, size / 24}: per link, the rank events (sub_3BDD50, sub_3BE2A0 kind 7)
inline constexpr s32 kLoScript = -20364;  // 0x95B074: SiteibiEvent.bf in the pak
inline constexpr s32 kLoSec119 = -18696;  // 0x95B6F8: section 119: 6-byte event triples per link (sub_3BE2A0 kind 3)
inline constexpr s32 kLoSec120 = -18684;  // 0x95B704: section 120: 6-byte event triples per link (kind 4)
inline constexpr s32 kLoSec121 = -18680;  // 0x95B708: section 121: 6-byte event triples, 4 per link 6..11 (kind 6)
inline constexpr s32 kLoSec122 = -18676;  // 0x95B70C: section 122: 6-byte event triples per link 6..11 (sub_3BE020)
inline constexpr s32 kLoSec123 = -18672;  // 0x95B710: {section 123, size / 26}: {u8 link, ..., u16 flag ids +4 + 2k} (sub_3BE1C0)
inline constexpr s32 kLoSec123Count = -18668;  // 0x95B714: the row count of section 123
inline constexpr s32 kLoSec126 = -18688;  // 0x95B700: section 126: u8 per link (sub_3BDFC0)
inline constexpr s32 kLoSec130 = -19840;  // 0x95B280: section 130
inline constexpr s32 kLoSec133 = -18700;  // 0x95B6F4: section 133 (f32 at +0: sub_3BDB80)
inline constexpr s32 kLoSec134 = -18704;  // 0x95B6F0: section 134 (sub_3BDBA0)
inline constexpr s32 kLoSec137 = -19812;  // 0x95B29C: section 137 (u16 at +0: sub_3BDBB0)
inline constexpr s32 kLoSec138 = -19808;  // 0x95B2A0: section 138 (s16 at +0: the rank sub_3BDBD0 sets)
inline constexpr s32 kLoSec140 = -19800;  // 0x95B2A8: section 140 (u8[6]: the ranks ids 6..11 need, sub_3BDBD0)
inline constexpr s32 kLoSec96 = -18856;  // 0x95B658: {section 96, size / 24}
inline constexpr s32 kLoTable = -20368;  // 0x95B070: comuTable.bin in the pak (u16 version 1, u8 last section, 144 x {u32 off, u32 size})
}  // namespace comu
namespace g {  // globals: gp offsets ($gp = 0x7D2CF0) and lo parts of 0x960000 / 0x7C0000 / 0x6A0000 / 0x680000
inline constexpr s32 kGpBankTask = -18032;  // 0x7CE680: the fclBank task (work +36: three 20-byte panel records)
inline constexpr s32 kGpPathZero = -31800;  // 0x7CB0B8: f32 0.0 (the path-length accumulators start from it)
inline constexpr s32 kGpRefPointSet = -18072;  // 0x7CE658: u16: a reference point is set (sub_3BC900)
inline constexpr s32 kGpSceneRecord = -22448;  // 0x7CD540: -> the scene record 0x95AFC0 (MT_Scene)
inline constexpr s32 kLoRefPointX = -20496;  // 0x95AFF0: f32: the reference point x
inline constexpr s32 kLoRefPointZ = -20492;  // 0x95AFF4: f32: the reference point z
inline constexpr s32 kLoRwCalloc = 388;  // 0x960184: the RwCalloc slot (count, size, hint)
inline constexpr s32 kLoRwFree = 380;  // 0x96017C: the RwFree slot
inline constexpr s32 kLoRwMalloc = 376;  // 0x960178: the RwMalloc slot (size, hint)
}  // namespace g
namespace blk {
inline constexpr s32 kBlockData = 352;
}  // namespace blk
namespace cam {
inline constexpr s32 kKind = 256;
inline constexpr s32 kFov = 260;
inline constexpr s32 kMatrix = 264;
inline constexpr s32 kEye = 268;
inline constexpr s32 kEyeY = 272;
inline constexpr s32 kEyeZ = 276;
inline constexpr s32 kNear = 280;
inline constexpr s32 kFar = 284;
}  // namespace cam
namespace chr {
inline constexpr s32 kIcon0 = 256;
inline constexpr s32 kIcon1 = 260;
inline constexpr s32 kIconTen = 264;
inline constexpr s32 kIconSide = 268;
inline constexpr s32 kMotionReq = 272;
inline constexpr s32 kModel = 296;
inline constexpr s32 kTask = 480;
inline constexpr s32 kCtl = 484;
inline constexpr s32 kShadowModel = 488;
}  // namespace chr
namespace creq {
inline constexpr s32 kLink = 0;
inline constexpr s32 kPartner = 1;
inline constexpr s32 kKind = 2;
inline constexpr s32 kResult = 4;
inline constexpr s32 kEvent = 30;
inline constexpr s32 kEventMinor = 32;
inline constexpr s32 kEventSub = 34;
inline constexpr s32 kEventSubHi = 35;
inline constexpr s32 kEvent2 = 36;
inline constexpr s32 kEvent2Minor = 38;
inline constexpr s32 kEvent2Sub = 40;
inline constexpr s32 kEvent3 = 42;
inline constexpr s32 kEvent3Minor = 44;
inline constexpr s32 kEvent3Sub = 46;
inline constexpr s32 kEvent4 = 48;
inline constexpr s32 kEvent4Minor = 50;
inline constexpr s32 kEvent4Sub = 52;
}  // namespace creq
namespace eff {
inline constexpr s32 kEpl = 260;
}  // namespace eff
namespace fmdl {
inline constexpr s32 kModel = 260;
inline constexpr s32 kSubModel = 300;
}  // namespace fmdl
namespace hit {
inline constexpr s32 kRgba = 256;
inline constexpr s32 kRgbaG = 257;
inline constexpr s32 kRgbaB = 258;
inline constexpr s32 kRgbaA = 259;
inline constexpr s32 kPos = 260;
inline constexpr s32 kPosY = 264;
inline constexpr s32 kPosZ = 268;
inline constexpr s32 kWidth = 272;
inline constexpr s32 kDepth = 276;
inline constexpr s32 kTurn = 280;
inline constexpr s32 kQuad = 284;
inline constexpr s32 kQuad1 = 296;
inline constexpr s32 kQuad2 = 308;
inline constexpr s32 kQuad3 = 320;
inline constexpr s32 kValue = 332;
}  // namespace hit
namespace icondel {
inline constexpr s32 kFrames = 0;
inline constexpr s32 kEpl = 4;
}  // namespace icondel
namespace mdl {
inline constexpr s32 kMotionReq = 256;
inline constexpr s32 kModel = 280;
}  // namespace mdl
namespace npc {
inline constexpr s32 kIcon0 = 256;
inline constexpr s32 kIcon1 = 260;
inline constexpr s32 kIconTen = 264;
inline constexpr s32 kIconSide = 268;
inline constexpr s32 kMotionReq = 272;
inline constexpr s32 kModel = 296;
inline constexpr s32 kTask = 488;
inline constexpr s32 kSubModel = 492;
inline constexpr s32 kCtl = 496;
inline constexpr s32 kBlockA = 512;
inline constexpr s32 kBlockB = 520;
}  // namespace npc
namespace path {
inline constexpr s32 kCount = 0;
}  // namespace path
namespace pos {
inline constexpr s32 kPoint = 256;
inline constexpr s32 kPointY = 260;
inline constexpr s32 kPointZ = 264;
inline constexpr s32 kAngle = 268;
}  // namespace pos
namespace res {
inline constexpr s32 kId = 0;
inline constexpr s32 kPos = 4;
inline constexpr s32 kPosY = 8;
inline constexpr s32 kPosZ = 12;
inline constexpr s32 kRot = 16;
inline constexpr s32 kRotY = 20;
inline constexpr s32 kRotZ = 24;
inline constexpr s32 kScale = 28;
inline constexpr s32 kScaleY = 32;
inline constexpr s32 kScaleZ = 36;
inline constexpr s32 kFlags = 40;
inline constexpr s32 kMoveFrom = 44;
inline constexpr s32 kMoveFromY = 48;
inline constexpr s32 kMoveFromZ = 52;
inline constexpr s32 kMoveTo = 56;
inline constexpr s32 kMoveToY = 60;
inline constexpr s32 kMoveToZ = 64;
inline constexpr s32 kMoveState = 80;
inline constexpr s32 kOwnedBlock = 84;
inline constexpr s32 kMoveSpeed = 88;
inline constexpr s32 kRotFrom = 100;
inline constexpr s32 kRotFromY = 104;
inline constexpr s32 kRotFromZ = 108;
inline constexpr s32 kRotTo = 112;
inline constexpr s32 kRotToY = 116;
inline constexpr s32 kRotToZ = 120;
inline constexpr s32 kRotState = 124;
inline constexpr s32 kRotMode = 125;
inline constexpr s32 kRotFrames = 128;
inline constexpr s32 kRotTime = 132;
inline constexpr s32 kFadeFrom = 180;
inline constexpr s32 kFadeTo = 181;
inline constexpr s32 kFadeFrames = 184;
inline constexpr s32 kFadeTime = 188;
inline constexpr s32 kFadeHold = 192;
inline constexpr s32 kNext = 248;
inline constexpr s32 kPrev = 252;
}  // namespace res
namespace scene {
inline constexpr s32 kMajor = 0;
inline constexpr s32 kMinor = 4;
inline constexpr s32 kResMgr = 8;
inline constexpr s32 kFlags = 12;
inline constexpr s32 kNpcSet = 20;
inline constexpr s32 kEnvSub = 22;
}  // namespace scene
namespace seq {
inline constexpr s32 kState = 0;
inline constexpr s32 kTimer = 4;
inline constexpr s32 kWait = 8;
inline constexpr s32 kW12 = 12;
inline constexpr s32 kW16 = 16;
inline constexpr s32 kW20 = 20;
}  // namespace seq
namespace snd {
inline constexpr s32 kRadius = 256;
inline constexpr s32 kState = 264;
}  // namespace snd
namespace task {
inline constexpr s32 kWork = 60;
}  // namespace task
}  // namespace scn

// --- resrcManager.c / mt_scene.c (scene_res.cpp) ---------------------------------------------------------------------
// [resrcMngCreate] Creates a resource manager: an 88-byte RwMalloc block (hint 0x40000), zeroed -- the 22 list heads,
// one per resource type (MT_Scene_Load stores it at scene +8).
void sub_3B4FC0(EEContext& ctx);  // 0x3B4FC0
// [resrcMngDestroy] (mgr) Deletes every resource of every type (sub_3B5360 on each list head until the list is empty)
// and frees the manager; a NULL manager does nothing.
void sub_3B5020(EEContext& ctx);  // 0x3B5020
// [resrcMngAddRes] (mgr, id) Allocates and links a resource record: type = (id & 0xFC00) >> 10 (>= 22: "warning!! not
// known resrc!!" and 0), the record size from the type (jump table 0x7BB250: 1 496, 2 464, 3 544, 4/5 432, 6 264, 7
// 272, 8 256, 10 304, 11 264, 12 368, 13/21 336, 14..19 272, 20 288; types 0 and 9 have none -> 0), zeroed, +0 = id,
// scale = 1.0; an id already on the list frees the block, prints "warning!! duplicate resID!! not regist!" and
// returns 0 (K_Assert line 168); else it is appended at the list tail (+248 next, +252 prev) and returned.
void sub_3B50D0(EEContext& ctx);  // 0x3B50D0
// [resrcMngDeleteRes] (mgr, res) Unlinks `res` from its type list (the head when it has no prev), frees its owned
// block (+84) and the record (RwFree); a record not on the list is left alone.
void sub_3B5360(EEContext& ctx);  // 0x3B5360
// [resrcMngGetListHead] (mgr, type) The head of the type list (type < 22; else 0).
void sub_3B5430(EEContext& ctx);  // 0x3B5430
// [resrcMngFindRes] (mgr, id) The record with this id on its type list (0 for type 0, type >= 22 or none).
void sub_3B54C0(EEContext& ctx);  // 0x3B54C0
// [resrcMngCountRes] (mgr, type) How many records the type list holds (0 for type >= 22).
void sub_3B5550(EEContext& ctx);  // 0x3B5550
// [MT_Scene_FieldModelExists] (major, minor) 1 when "field/model/fMMM_NNN.rws" exists (H_Cdvd_FileExists), else 0
// (the Tartarus-floor test after it changes nothing: both branches return 1).
void sub_3B5620(EEContext& ctx);  // 0x3B5620
// [MT_Scene_SetNpcSet] (set) Sets the scene's NPC placement set (+20). Scene loaded (flags bit 0): the same set marks
// every type-3 resource visible (flag bit 1); another set sets flags bit 1 (reload the NPCs) and the field loader's
// step (sField +4184) to 30.
void sub_3B58C0(EEContext& ctx);  // 0x3B58C0
// [MT_Scene_SetEnvSub] (sub) Sets the scene's ENV sub-id (+22). Scene loaded and the id changes: flags bit 2 (reload
// the ENV) and, unless an NPC reload is pending (bit 1), the loader step 40.
void sub_3B5980(EEContext& ctx);  // 0x3B5980
// [MT_Scene_GetResListHead] (type) The head of the scene manager's type list (0 without a manager).
void sub_3B5D50(EEContext& ctx);  // 0x3B5D50
// [MT_Scene_CreateResPos] (n) Registers position resource 0x2000 | (n & 0x3FF) (type 8); the id only when it is type
// 8 ("this resId not postion" otherwise, unreachable) and the record was made, else 0. "not found active resmanager"
// without a manager.
void sub_3B5E90(EEContext& ctx);  // 0x3B5E90
// [MT_Scene_CreateRes7] (n) Registers type-7 resource 0x1C00 | n with +256 = 35.0; the id or 0.
void sub_3B5F70(EEContext& ctx);  // 0x3B5F70
// [MT_Scene_CreateResModel] (n, model) Registers type-2 resource 0x800 | n for an existing model (+280) and places
// the model at the origin (sub_318A30 with a zero vector from the stack); 0 for a NULL model.
void sub_3B6180(EEContext& ctx);  // 0x3B6180
// [MT_Scene_CreateResLightChar] (n) Registers type-4 resource 0x1000 | n (MT_Scene_Load: the character light); the id
// or 0.
void sub_3B63C0(EEContext& ctx);  // 0x3B63C0
// [MT_Scene_CreateResLightNpc] (n) Registers type-5 resource 0x1400 | n (the NPC light); the id or 0.
void sub_3B6440(EEContext& ctx);  // 0x3B6440
// [MT_Scene_CreateResFieldEpl] (n, epl) Registers type-11 resource 0x2C00 | n for an EPL handle (+260), shown (flag
// 8); 0 for a NULL handle.
void sub_3B66B0(EEContext& ctx);  // 0x3B66B0
// [MT_Scene_CreateResBlock] (n, data) Registers type-12 resource 0x3000 | n (a Tartarus block: 0x3000 + 16 z + x)
// with its block data (+352), shown; 0 for NULL data.
void sub_3B6790(EEContext& ctx);  // 0x3B6790
// [MT_Scene_CreateResHit] (n, pos, rgba, $f12 width, $f13 depth, $f14 turn) Registers type-13 field hit 0x3400 | n:
// the colour bytes (+256), the position (+260), width / depth / turn (+272 / +276 / +280) and its quad (+284,
// sub_1E6AF0: the width x depth rectangle centred on the origin, turned about y, moved to the position), shown.
void sub_3B6870(EEContext& ctx);  // 0x3B6870
// [MT_Scene_CreateResHit21] (n, pos, rgba, $f12 width, $f13 depth, $f14 turn) As sub_3B6870 for the type-21 hit
// 0x5400 | n.
void sub_3B69A0(EEContext& ctx);  // 0x3B69A0
// [MT_Scene_CreateResPoint14] (n, point, $f12) Registers marker 0x3800 | n (type 14): point (+256), angle (+268),
// shown.
void sub_3B6AD0(EEContext& ctx);  // 0x3B6AD0
// [MT_Scene_CreateResPoint15] (n, point, $f12) Marker 0x3C00 | n (type 15: enemies), as sub_3B6AD0.
void sub_3B6B90(EEContext& ctx);  // 0x3B6B90
// [MT_Scene_CreateResPoint16] (n, point, $f12) Marker 0x4000 | n (type 16), as sub_3B6AD0.
void sub_3B6C50(EEContext& ctx);  // 0x3B6C50
// [MT_Scene_CreateResPoint17] (n, point, $f12) Marker 0x4400 | n (type 17), as sub_3B6AD0.
void sub_3B6D10(EEContext& ctx);  // 0x3B6D10
// [MT_Scene_CreateResPoint18] (n, point, $f12) Marker 0x4800 | n (type 18), as sub_3B6AD0.
void sub_3B6DD0(EEContext& ctx);  // 0x3B6DD0
// [MT_Scene_CreateResPoint19] (n, point, $f12) Marker 0x4C00 | n (type 19), as sub_3B6AD0.
void sub_3B6E90(EEContext& ctx);  // 0x3B6E90
// [MT_Scene_CreateResCamera] (n, kind, matrix, eye, $f12, $f14) Registers camera 0x5000 | n (type 20): kind (+256),
// $f12 (+260), a new RW matrix (sub_4C38C0) filled with the caller's 64 bytes (+264), the eye (+268), $f13 as left
// (+280), $f14 (+284), shown.
void sub_3B6F50(EEContext& ctx);  // 0x3B6F50
// [MT_Scene_DeleteRes] (id) Deletes a scene resource with what it owns, by type: 1 the controller task tree (+480),
// the three icon EPLs, the shadow model (+488, through its clump); 2 the model (+280); 3 the task (+488), the model
// (+296), the icons, blocks +512 / +520, the sub-model (+492); 6 / 11 the EPL (+260); 10 both models; 12 the block
// data (sub_1B3C90); 20 the camera matrix; each with its "delete ... =0x%x" print; then resrcMngDeleteRes. Unknown
// ids do nothing; no manager prints "not found active resmanager".
void sub_3B7090(EEContext& ctx);  // 0x3B7090
// [MT_Scene_ApplyTransform] (res, pos, rot, scale) Copies the non-NULL vectors into the record and applies the
// transform to its object: models (types 1 / 3 +296, 2 +280, 10 +260) are rotated by the record's angles about y
// (replacing), x and z (pre-concatenated; the axes 0x6A2D20 / 0x6A2D30 / 0x6A2D40, sub_318A50), then scaled
// (sub_318A90) and translated (sub_318A30) post-concatenated; effects (type 6) get the matrix of sub_3B79A0
// (sub_34FE80). "mdlHandle not found!" / "effect Handle not found!" for a missing object.
void sub_3B7460(EEContext& ctx);  // 0x3B7460
// [MT_Scene_SetResPosRot] (id, pos, rot) Finds the scene resource and applies a position and rotation (sub_3B7460,
// scale kept).
void sub_3B78B0(EEContext& ctx);  // 0x3B78B0
// [MT_Scene_SetResScale] (id, scale) Finds the scene resource and applies a scale (sub_3B7460).
void sub_3B7930(EEContext& ctx);  // 0x3B7930
// [MT_Scene_RotMatrix] (out, pos, rot) A 64-byte RW matrix: the identity rotated about y by rot.y, x by rot.x, z by
// rot.z (degrees; the axes 0x6A2A70 / 0x6A2A60 / 0x6A2A80, sub_4C31B0 pre-concatenated), translated by pos
// (sub_4C35D0, post-concatenated), copied to `out`.
void sub_3B79A0(EEContext& ctx);  // 0x3B79A0
// [MT_Scene_MatrixToEuler] (matrix, out_angles, out_pos) Splits a matrix into its position (out_pos) and three angles
// in degrees: the rotation about z from the right vector against the projected axes (sign from +4), about y from the
// at vector's xz direction (360 - a when x < 0), about x from the at vector rotated back; asserts (mt_scene.c
// 1525..1645) on zero-length normalisations.
void sub_3B7AC0(EEContext& ctx);  // 0x3B7AC0

// --- mt_sceneFunc.c (scene_func.cpp) ---------------------------------------------------------------------------------
// Update of the "IconEplDestroyDell" task: counts the work's frames down; below zero destroys its EPL (sub_34FCF0),
// clears it and returns -1 (task done), else 0.
void sub_3B8210(EEContext& ctx);  // 0x3B8210
// Destroy of the "IconEplDestroyDell" task: destroys a remaining EPL and frees the work (RwFree).
void sub_3B8270(EEContext& ctx);  // 0x3B8270
// [MT_SceneFunc_SetShown] (res, on) Sets (on == 1) or clears flag bit 3 (shown / drawn); 1, or 0 for a NULL record.
void sub_3B82C0(EEContext& ctx);  // 0x3B82C0
// [MT_SceneFunc_IsShown] (res) Flag bit 3 of a non-NULL record (0 / 1).
void sub_3B83A0(EEContext& ctx);  // 0x3B83A0
// [MT_SceneFunc_RequestMove] (res, to, $f12 speed) Starts a move: flag bit 0 on, bit 6 off, from = the current
// position, to, speed, state 0; 1, or 0 for NULL.
void sub_3B86C0(EEContext& ctx);  // 0x3B86C0
// [MT_SceneFunc_RequestRotate] (res, to, frames, mode) Starts a rotation: the current and target angles normalised to
// [0, 360) (sub_3BBA70 / sub_3BB9B0), flag bit 2, from / to, state 0, mode byte, frames, time 0; 1, or 0 for NULL.
void sub_3B8A60(EEContext& ctx);  // 0x3B8A60
// [MT_SceneFunc_RequestFade] (res, alpha, frames, hold) Starts an alpha fade of an effect (type 6: the start alpha
// from the EPL, sub_350040) or an object (type 3: from its model's colour, sub_318B00; +192 = hold == 1): flag
// 0x4000, from / to alpha, frames, time 0; 1, or 0 for other types.
void sub_3B8CE0(EEContext& ctx);  // 0x3B8CE0
// [MT_SceneFunc_ChangeMotion] (res, group, minor, blend, loop, wait) Switches the object's motion (types 1 / 3 +296,
// 2 +280, 10 +260) unless it already plays it (sub_3186E0): sub_3189F0, sub_3182D0 with the loop flag (loop == 1),
// sub_318770 when wait > 0, the "motion change" print; clears flag 0x2000; 1, or 0 for other types.
void sub_3B8FF0(EEContext& ctx);  // 0x3B8FF0
// [MT_SceneFunc_QueueMotion] (res, a1..a5, $f12) Queues a motion request (types 1 / 3 at +272, 2 at +256: five words
// and a float) and sets flag 0x2000; 1, or 0 for other types.
void sub_3B9260(EEContext& ctx);  // 0x3B9260
// [MT_SceneFunc_SetVisible] (res, on) Sets (on == 1) or clears flag bit 1 (the bit the field draw tasks test); 1, or
// 0 for NULL.
void sub_3B9500(EEContext& ctx);  // 0x3B9500
// [MT_SceneFunc_GetHitValue] (pos) The value of the field hit under a point: the default from 0x67EF00[major][minor]
// (minor - 49 on random floors 20..28 with minor >= 50; 0 when the major has no row), replaced by the +332 of the
// first type-21 hit whose two triangles (quad +284..+320) contain the point (K_FldFrame_IsPointInTriangle, normal
// 0x6A2DA0) within 100 units in height.
void sub_3BAA70(EEContext& ctx);  // 0x3BAA70
// [MT_SceneFunc_SetIcon] (res, icon) The icon EPL over a character (type 1) or object (type 3): icon 10 (the "10ban"
// icon) is created once in +264 ("10ban icon create") and a second call resets it ("10ban icon reset"); any other
// icon swaps the two slots +256 / +260 (+268 toggles): the old EPL is handed to an "IconEplDestroyDell" task
// (sub_3B8210 / sub_3B8270, two frames) and the new one created from the icon file (sub_3BD1C0, sub_34FCD0; asserts
// mt_sceneFunc.c 1690 .. 1763 on failure); 1, or 0 for other types.
void sub_3BAC40(EEContext& ctx);  // 0x3BAC40
// [MT_SceneFunc_SetCtlMode] (res, on) Sets the controller of a character (+484) or object (+496) to mode 3 (on == 1)
// or 0 (sub_19C310); 1, or 0 without one.
void sub_3BB0C0(EEContext& ctx);  // 0x3BB0C0
// [MT_SceneFunc_ResetRes7] Clears +264 of every type-7 resource; returns the list head.
void sub_3BB340(EEContext& ctx);  // 0x3BB340
// [MT_SceneFunc_OffsetAlongDir] (pos, out, $f12 dist) out = pos - dist * d, d = the direction 0x6A2EF8 rotated by the
// matrix of the three axes 0x6A2EE8.. (sub_4C31B0 / sub_4C6C60); ACC-fused multiply-subtract per component.
void sub_3BB450(EEContext& ctx);  // 0x3BB450
// [MT_SceneFunc_NormAngles] (angles) Wraps each of the three angles into [0, 360) by repeated -360 / +360.
void sub_3BB9B0(EEContext& ctx);  // 0x3BB9B0
// (res) sub_3BB9B0 on the record's rotation (+16).
void sub_3BBA70(EEContext& ctx);  // 0x3BBA70
// [MT_SceneFunc_AngleDelta] (from, to, out) The per-axis turn from `from` to `to`: (to - from) wrapped to [0, 360),
// then values above 180 become negative (the shorter way).
void sub_3BBAA0(EEContext& ctx);  // 0x3BBAA0
// [MT_SceneFunc_Bezier] (xs, ys, zs, out_x, out_y, out_z, $f12 t) A cubic Bezier point: each coordinate = (1-t)^3 c0
// + 3t(1-t)^2 c1 + 3t^2(1-t) c2 + t^3 c3 (the four control values at +0..+12 of each array), through ACC (mula /
// madda / madd).
void sub_3BBC90(EEContext& ctx);  // 0x3BBC90
// [MT_SceneFunc_PathPoint] (path, out, $f12 t) The point of a bezier path: t < 1 picks segment (int)(t / (1 / count))
// and evaluates it at (t minus whole steps of 1 / count while above one step) * count -- at an exact segment boundary
// that is the end (1.0) of the segment the division picked; t >= 1 gives the last segment's end point (local t 1.0).
// Nothing for an empty path.
void sub_3BBD40(EEContext& ctx);  // 0x3BBD40
// (xs, ys, zs, a, b) Two Bezier points (sub_3BBC90 at $f12 / $f13) into a and b and their distance (sub_4C6AC0) in
// $f0.
void sub_3BBFD0(EEContext& ctx);  // 0x3BBFD0
// [MT_SceneFunc_PathLength] (path) The path length: per segment 20 chords (sub_3BBFD0); the total stays in $f21 for
// the caller.
void sub_3BC0E0(EEContext& ctx);  // 0x3BC0E0
// [MT_SceneFunc_PathLengthTo] (path, n) The length of the first n segments (20 chords each), in $f20.
void sub_3BC730(EEContext& ctx);  // 0x3BC730
// [MT_SceneFunc_PathLastSeg] (path) The path's segment count - 1.
void sub_3BC8F0(EEContext& ctx);  // 0x3BC8F0
// (out) The reference point (0x95AFF0 / 0x95AFF4) when one is set (u16 0x7CE658): 1, else 0.
void sub_3BC900(EEContext& ctx);  // 0x3BC900
// [MT_SceneFunc_CreateManagerTasks] Creates "SceneManager Task" (priority 110; update sub_3BCCB0, destroy sub_3BCD80)
// and its child "SceneManager Draw" (2109; sub_3BD010); returns the parent.
void sub_3BD0B0(EEContext& ctx);  // 0x3BD0B0
// [MT_SceneFunc_LoadIcons] Requests and reads the 25 icon EPL files of 0x6A3130 ("icon/ICON1.EPL" ..) into the H_Cdvd
// cache, keeping each request at 0x95B000 + 4 i (kwlnInitMain).
void sub_3BD130(EEContext& ctx);  // 0x3BD130
// [MT_SceneFunc_GetIconFile] (icon) The cached data of icon file `icon` (< 26 and named; H_Cdvd_CacheFindFile), else
// 0.
void sub_3BD1C0(EEContext& ctx);  // 0x3BD1C0

// --- comuFunction.c / comuTimerSequence.c (scene_comu.cpp) -----------------------------------------------------------
// (link) 1 for the social links 6..11 (the ones with partner events, sub_3BE020), else 0.
void sub_172A50(EEContext& ctx);  // 0x172A50
// [comuLoadTableBin] Loads "event/comuPack.pak" (request kept at 0x7CE668, read synchronously), finds
// "event/comuTable.bin" and "event/SiteibiEvent.bf" in it; version 1 (u16 +0): the 144 sections (+4: {u32 offset, u32
// size}) become pointers (0 when the offset is 0) and sizes, sections 0..29 / 32..61 / 64..93 are copied to the
// per-link tables (0x95B4F0 / 0x95B568 / 0x95B5E0), and the named tables {pointer, count} are derived with their
// record sizes (comu namespace). Another version: "error!! comuTableBinFile Version Invalid" and the table pointer
// cleared.
void sub_3BD280(EEContext& ctx);  // 0x3BD280
// [comuGetTables] The loaded table block (0x95B070).
void sub_3BD870(EEContext& ctx);  // 0x3BD870
// The {pointer, count} pair of the dated conditions (0x95B660).
void sub_3BD890(EEContext& ctx);  // 0x3BD890
// The {pointer, count} pair of the dated flags (0x95B668).
void sub_3BD8A0(EEContext& ctx);  // 0x3BD8A0
// (a, b, c, d) Looks up section 112 for the row {u8 a, u8 b, u16 c, u8 d}: its u16 +6 when the row has no flag (+8 ==
// 0) or the flag is clear (MT_Misc_BitChk != 1), else the next match; -1 when none.
void sub_3BDA60(EEContext& ctx);  // 0x3BDA60
// The f32 at the start of section 133 (in $f0).
void sub_3BDB80(EEContext& ctx);  // 0x3BDB80
// Section 134's pointer.
void sub_3BDBA0(EEContext& ctx);  // 0x3BDBA0
// The u16 at the start of section 137.
void sub_3BDBB0(EEContext& ctx);  // 0x3BDBB0
// (link) For a link 6..11 that is active: every other active link 6..11 whose rank reaches its threshold (section
// 140) is set to the rank of section 138 (sub_171960).
void sub_3BDBD0(EEContext& ctx);  // 0x3BDBD0
// The call tables (0x95B678: four {pointer, count} pairs).
void sub_3BDD40(EEContext& ctx);  // 0x3BDD40
// The rank-event table pair (0x95B6A8).
void sub_3BDD50(EEContext& ctx);  // 0x3BDD50
// (a0, a2) Starts a script procedure of SiteibiEvent.bf (scrCreateTaskFromHeader(a0, the .bf, a1)).
void sub_3BDD60(EEContext& ctx);  // 0x3BDD60
// (link) The per-link table of sections 64..93 (link < 31, else 0).
void sub_3BDD90(EEContext& ctx);  // 0x3BDD90
// Section 130's pointer.
void sub_3BDDD0(EEContext& ctx);  // 0x3BDDD0
// [comuRefreshAvailability] For the 30 links: an active link (sub_16E100) that is not reversed / broken (sub_1717C0,
// sub_172160) and below rank 10 is marked available (sub_171960(i, 1)); one whose counter (sub_171AC0) is <= 0 is
// also flagged (sub_171C40(i, 1)).
void sub_3BDDE0(EEContext& ctx);  // 0x3BDDE0
// [comuGetLinkState] (link) 5 at rank 10 (max), 4 broken (sub_172160), 3 reversed (sub_1717C0), else when available
// (sub_172660) 2 if a partner flag of the next rank is pending (sub_3BE1C0) or 1, else 0.
void sub_3BDED0(EEContext& ctx);  // 0x3BDED0
// (link) The link's byte of section 126 (asserts comuFunction.c 657 on an invalid link).
void sub_3BDFC0(EEContext& ctx);  // 0x3BDFC0
// (rank, req, link) For links 6..11: the first row {link, min rank} of section 117 for this link that the link's rank
// reaches (rank 0 when inactive), when the link is neither reversed nor broken (or rank 0): the partner event triple
// of section 122 into req +42 and req +1 = link; 1, else 0.
void sub_3BE020(EEContext& ctx);  // 0x3BE020
// (req) req +4 == 3.
void sub_3BE1A0(EEContext& ctx);  // 0x3BE1A0
// (link, rank) 1 when a row of section 123 for this link has a non-zero flag id for `rank` (rank >= 2; +4 + 2 rank)
// whose flag is clear (datGetFlag), else 0.
void sub_3BE1C0(EEContext& ctx);  // 0x3BE1C0
// [comuMakeEventRequest] (mode, choice, link, kind, req) Fills the 56-byte event request for a link of rank > 0
// (asserts on invalid links): +0 link, +2 kind, by kind: 0 the rank event of sections 0..29 (14-byte rows, 10 per
// rank, the sub-step min 9) + the partner event (sub_3BE020; result 3) else result 2; 1 the 24-byte row of sections
// 32..61 for the rank (four triples, result 3; mode 1 also raises the rank, sub_16E410); 2 section 123's triple; 3 /
// 4 the per-link triples of sections 119 / 120; 5 the triple at +1268 of the link's rank table; 6 section 121's
// triple for links 6..11 (sub_3C2570); 7 one of the link's rank-event rows of section 114 (mode 1: `choice`, else the
// rank's; asserts 947 / 970); +4 = the result (number of triples). 1, or 0 for rank 0.
void sub_3BE2A0(EEContext& ctx);  // 0x3BE2A0
// (row, col) The byte at 30 + 6 row + col (row < 4, the value < 42; asserts comuFunction.c 1017 / 1019).
void sub_3BEA20(EEContext& ctx);  // 0x3BEA20
// [comuFindLink] (a, b, out) The index of the first of the 64 link records with bytes {a, b} at +0 / +1 into *out: 1,
// else 0.
void sub_3BEAB0(EEContext& ctx);  // 0x3BEAB0
// [comuGetLinkRecord] (i) The 32-byte link record i (asserts comuFunction.c 1046 for i >= 64).
void sub_3BEB10(EEContext& ctx);  // 0x3BEB10
// (link) Sets flag 2512 + link (the link's "met today" flag; asserts on an invalid link).
void sub_3BEB70(EEContext& ctx);  // 0x3BEB70
// (link) Flag 2512 + link == 1.
void sub_3BEBD0(EEContext& ctx);  // 0x3BEBD0
// Clears the flags 2512..2541 (all 30 links).
void sub_3BEC50(EEContext& ctx);  // 0x3BEC50
// [comuListDateLinks] (out) Lists today's links of section 128 ({month, day, link, min rank, max rank} == the
// calendar date, the rank in range, rank 9 only while available, flag 2512 + link clear and sub_3C2C50 agreeing) into
// out[]; the count, or 0 when sub_3C2B40 refuses.
void sub_3BECA0(EEContext& ctx);  // 0x3BECA0
// (link, out_count) The personas of the link's arcana (PERSONA.TBL, not flagged 0x10 / 0x08, 0x40 only at rank 10) at
// or below the hero's level, then the lowest-level one above it, sorted by level, into 0x95B730 (max 15; asserts 1202
// / 1220 / 1245); returns 0x95B730.
void sub_3BEE80(EEContext& ctx);  // 0x3BEE80
// 1 when no sequence change is pending (sub_27C2B0 == 0) and sub_27C330 == -1.
void sub_3BF130(EEContext& ctx);  // 0x3BF130
// (a, b, c) Requests sequence 3 (adminiChangeSeq) with the 28-byte packet {.., +12 a, +16 b, +20 c}.
void sub_3BF180(EEContext& ctx);  // 0x3BF180
// (month, day, m2, d2) The date (m2, d2) matches: m2 == 255 means "weekday d2" (sub_17E050), else both equal.
void sub_3BF200(EEContext& ctx);  // 0x3BF200
// [comuDateInRange] (month, day, m0, d0, m1, d1) 1 when (month, day) lies in the range (m0, d0) .. (m1, d1), the
// range wrapping over the year end when it ends before it starts; else 0. Quirks of the original: a range inside one
// month (m0 == m1, d0 <= d1) accepts every day from d0 to the month's end, and a wrapping range that starts and ends
// in the same month rejects that month's days before d0.
void sub_3BF270(EEContext& ctx);  // 0x3BF270
// A timer-sequence step: 0 starts (clears 0x7CE66C), 1 waits for sub_3C3E80 on the hero record +484, 2 arms a 2-frame
// wait, 3 waits it out and requests event 861 (sequence 3), 4 returns -1 when the change is done; 0 otherwise.
void sub_3BF370(EEContext& ctx);  // 0x3BF370
// A timer-sequence step: 1 waits for sub_3C3E80 on the hero record +584, 2 returns -1, 3 returns -1 once the sequence
// change is done; 0 otherwise.
void sub_3BF510(EEContext& ctx);  // 0x3BF510
// Update of "comuTimerProcess": 0 arms, 1 requests sequence 2 with {7, 1, 0, .., 0}, 2 returns -1 once the change is
// done.
void sub_3BF610(EEContext& ctx);  // 0x3BF610
// A timer-sequence step: 1 waits 2 frames, then plays the event of 0x7CE678 (sub_16E920, sequence 3 with event 809);
// 2 waits for the change; 3 returns -1 (asserting sub_3C30B0 unless sub_38D6F0(0)).
void sub_3BF720(EEContext& ctx);  // 0x3BF720
// A timer-sequence step: when sub_3C3190 prepares the request at 0x7CE678, clears the work and returns the next step
// sub_3BF720, else -1.
void sub_3BF8E0(EEContext& ctx);  // 0x3BF8E0
// A timer-sequence step: waits 2 frames, requests event 811 (sequence 3), waits for the change, then clears the work
// and returns the next step sub_3BF8E0.
void sub_3BF950(EEContext& ctx);  // 0x3BF950
// A timer-sequence step: waits 2 frames, requests event 808, waits for the change; -1 at the end.
void sub_3BFAE0(EEContext& ctx);  // 0x3BFAE0
// A timer-sequence step: requests event 810 with the link of 0x7CE674, waits for the change (sub_172B20 after it),
// then clears the work and returns the next step sub_3BF950.
void sub_3BFC50(EEContext& ctx);  // 0x3BFC50
// A timer-sequence step: picks the link (sub_172C50): at rank 10 (0x7CE674 = link + 30) or reversed / broken
// (0x7CE674 = link) -> sub_3BFC50; otherwise prepares its events (sub_3C3050, sub_3C3120; asserts 585 / 587) ->
// sub_3BFAE0; no link -> sub_3BF950. Clears the work.
void sub_3BFDB0(EEContext& ctx);  // 0x3BFDB0
// The first timer-sequence step: refreshes the links (sub_3BDDE0), clears the work, next step sub_3BFDB0.
void sub_3BFF40(EEContext& ctx);  // 0x3BFF40
// [comuPickDatedCall] (out_event, out_flag, out_minor) Today's call: an exact-date row of the first / second dated
// table (3-byte {month, day, minor}; month 255 = weekday) gives event 802 / 803; else up to 10 range rows (5-byte
// {m0, d0, m1, d1, minor}) of the first / second ranged table, one picked at random (sub_395200) with a 20 % chance
// (sub_395230(20)) -> 802 / 803. 1 when one is chosen, else 0.
void sub_3BFFA0(EEContext& ctx);  // 0x3BFFA0

// --- 0x3C0000 leftovers (scene_misc.cpp) -----------------------------------------------------------------------------
// [nmListAllocNode] (?, owner, size) A list node of size + 24 bytes (RwMalloc, asserts nmlist.c 96), zeroed: +0 the
// owner (or itself), +8 the size, +20 -> the payload at +24 when size != 0.
void sub_3C4650(EEContext& ctx);  // 0x3C4650
// (sprite) The slide animation of a facility panel sprite: with flag 0x40, the in and out halves of the frame counter
// (+22 of +20, the fractions 0x7CAD7C / 0x7CADD0) move it by 80 * (sin(...) + 1) and scale its alpha (+18); flag 2
// picks the draw sub_1332F0, else sub_133180; the position is +28 or +112 by the side byte +232.
void sub_3CA960(EEContext& ctx);  // 0x3CA960
// The fclBank panels (three 20-byte records at the bank task's work +36 + 4): state 1/2 slide in over 5 frames (x
// from 256 / -126, alpha 255 * t / 5), 3 holds, 4/5 fade out over 5 frames; through the sprite setters sub_106FB0 /
// sub_106E90 / sub_106F60.
void sub_3CFB50(EEContext& ctx);  // 0x3CFB50

}  // namespace p3fes::game
