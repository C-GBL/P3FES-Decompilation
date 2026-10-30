// Slice fcl: the facility ("fcl") task bands -- fclMisc.c 0x3C77A0-0x3CF158 (the facility message window helpers, the
// boot-time "MsgAssist" service, the persona-status ("psStatus") accessors and draw tasks, the persona model
// ("psModel")), the fclBankManager.c slot helpers, the background element handlers of fclShopBGManager.c that the
// shops slice left (0x40CA00-0x417158) and fclCombineEffect.c 0x417160-0x41BE44 (the persona fusion cut-in
// "fclCmbEffCalc" with its draw tasks and command runner); plus the helpers they need that no slice had taken: the
// nmlist object create / remove / clear (sub_3C44D0 / sub_3C49E0 / sub_3C4A90), the g_data colour lookups
// sub_16BC80 / sub_16BDB0 and the frame-translation setter sub_20D650.
//
// What "fcl" is: the facility layer of the field side -- the Velvet Room (fclCombine*.c: fusion, its cut-in), the
// shops (fclShop*.c, fclShopBGManager.c, fclDrawSprite.c), the bank manager and the shared services of fclMisc.c. Its
// tasks are created by the facility sequences that the field starts (the sequence table's shop / fusion steps, field
// events; fusion's root update sub_3D3D20 creates the cut-in), by frFontSystemStart at boot ("MsgAssist", "fclBank")
// and, for the persona-status screen, also by the battle result / panel code (sub_264E30, sub_266F60); none is a
// battle-layer task.
//
// Every function is register-ABI (`void name(EEContext&)`: arguments in $a0.. / $f12.., result in $v0 / $f0) and
// register-faithful (p3fes_handgen bodies). namespace fcl names the record offsets the bodies use (the values are the
// instructions' offsets; names ours, from the instructions -- ADR-0009).
//
// Left recompiled in the bands (each a callee of something below or a band member, with the reason):
//   * stood in by other slices' tests (a replaced callee cannot be stood in; their tests stay as they are):
//     sub_3C77A0 (test_fusion), sub_3C7850 / sub_3C7B90 / sub_3CF3A0 / sub_3CF440 / sub_3CF630 (test_events),
//     sub_3C7C90 [msgWinSetVisible] (test_events2),
//     sub_3C7BC0 / sub_3C7C20 / sub_3C7D80 / sub_3C8230 / sub_3C82E0 / sub_3C83B0 / sub_3C9790 /
//     fclMisc_CreatePsStatusTasks / sub_3C9AB0 / sub_40D640 (test_shops), sub_3C9D00 / sub_40E360 (test_fusion),
//     sub_40CAD0 (test_fusion, test_shops), sub_3CF120 (test_ui4), sub_3CF160 / sub_3CF240 / sub_3CF5D0 (test_script3);
//   * callees outside the slice that are not replaced (sprite handles of ui4's dropped spr* set, itfMesMng request /
//     initialize, the sprite drawers sub_1332F0 / sub_133180 / sub_133A80, RenderWare, sound, model animation):
//     fclMisc_UpdatePsStatusTask (sub_133B80, sub_3C9FE0 -> sprCreateHandleFromData), sub_3CA6B0 (sub_1124B0),
//     sub_3CEA50 (the camera / model calls), fclMisc_CreatePsModelDummyTask (sub_316F70), sub_418230 (sub_41BE50 of the
//     memory-card band, sub_21A1B0), the MsgAssist update and its window helpers (sub_3C8550 sprite release,
//     itfMesMng*), the persona-status drawers sub_3CA780..sub_3CD5A0, fclBank_UpdateTask, the cut-in's loader
//     sub_4178C0 and its 3D / scene commands (sub_418390..sub_41A730, sub_41AE20 voice);
//   * the 0x41BE50.. helpers next to fclCombineEffect.c belong to the memory-card band (savedata).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace fcl {

// --- nmlist (nm_message.h documents it): a list object, its embedded list header at +4, the nodes ------------------
inline constexpr s32 kNmObjList = 4;        // the embedded list header (passed as the second argument of the list ops)
inline constexpr s32 kNmObjHead = 4;        // ptr: first node (list header +0)
inline constexpr s32 kNmObjCursor = 12;     // ptr: the cursor (list header +8); the runner walks its lists from here
inline constexpr s32 kNmObjCount = 16;      // u16: node count (list header +12); new keys are count + 1
inline constexpr s32 kNmObjOnInsert = 20;   // fnptr (obj, node)
inline constexpr s32 kNmObjOnRemove = 24;   // fnptr (obj, node)
inline constexpr s32 kNmObjFilter = 28;     // fnptr (obj, node) -> bool
inline constexpr s32 kNmObjSize = 32;       // the payload size given at creation
inline constexpr s32 kNmObjPayload = 36;    // ptr: the object's own payload (obj + 40) or 0
inline constexpr s32 kNmObjHeaderSize = 40;
inline constexpr s32 kNmListHead = 0;       // on the embedded header
inline constexpr s32 kNmListTail = 4;
inline constexpr s32 kNmListCursor = 8;
inline constexpr s32 kNmListCount = 12;     // u16
inline constexpr s32 kNmNodeSize = 8;       // the node's allocation size (cleared before the free)
inline constexpr s32 kNmNodeNext = 16;
inline constexpr s32 kNmNodePayload = 20;

// --- the facility message window 0x95BE90 (sub_3C7D50) ----------------------------------------------------------------
inline constexpr u32 kMsgWin = 0x95BE90u;
inline constexpr u32 kMsgRecord = 0x95BE80u;   // the second record fclMisc_CreateMsgAssistTask resets
inline constexpr s32 kMsgWinHandle = 0;        // s32: itfMesMng handle (< 0: none)
inline constexpr s32 kMsgWinState = 4;         // s8
inline constexpr s32 kMsgWinHidden = 5;        // s8: 1 hidden (sub_3C7C90)
inline constexpr s32 kMsgWinSelection = 13;    // s8: the last selection (sub_3C78D0)

// --- MsgAssist (fclMisc_CreateMsgAssistTask): the payload of a 160-byte nm list object, gp slot 0x7CE67C -----------
inline constexpr s32 kGpMsgAssist = -18036;    // $gp offset of the work pointer (0x7CE67C)
inline constexpr u32 kMsgAssistSlot = 0x7CE67Cu;
inline constexpr s32 kMaRequests = 0;          // ptr: the object itself; its nodes are the 48-byte requests
inline constexpr s32 kMaFlags = 4;             // 1 created, 2 set by sub_3C8F20
inline constexpr s32 kMaOwner = 12;            // the owner recorded in new requests (sub_3C8DD0)
inline constexpr s32 kMaMask = 20;             // a mask word (sub_3C8DA0 / sub_3C8DC0)
inline constexpr s32 kMaSlotList = 24;         // ptr: list object of queued slots (12-byte payloads)
inline constexpr s32 kMaSlots = 28;            // 12 slots of 12 bytes
inline constexpr s32 kMaSlotSize = 12;
inline constexpr s32 kMaSlotCount = 12;
inline constexpr s32 kMaSlotFlags = 0;         // on a slot: 2 running, 4 stop requested
inline constexpr s32 kMaSlotIndex = 4;         // on a slot (and a slot-list payload): the slot's index
inline constexpr s32 kMaSlotWord8 = 8;         // on a slot-list payload: 0 = finished (purged by sub_3C8810)
inline constexpr s32 kMaReqNode = 0;           // on a request (48 bytes): back pointer to its node
inline constexpr s32 kMaReqFlags = 4;          // 2 = keep on purge
inline constexpr s32 kMaReqC = 14;             // s16
inline constexpr s32 kMaReqA = 32;
inline constexpr s32 kMaReqB = 36;
inline constexpr s32 kMaReqOwner = 40;
inline constexpr s32 kMaReqKey = 44;
inline constexpr s32 kMaReqSize = 48;

// --- psStatus: the work of a "psStatus" task (fclMisc_CreatePsStatusTasks) --------------------------------------------
inline constexpr s32 kPsState = 8;             // bit 0 visible (the draw tasks), 0x40 compare set (sub_3C9C10)
inline constexpr s32 kPsSpeedA = 12;           // u16, >= 1
inline constexpr s32 kPsSpeedB = 14;           // u16, >= 1
inline constexpr s32 kPsPageHeight = 20;       // s16 (15)
inline constexpr s32 kPsScroll = 22;           // s16: page * page height
inline constexpr s32 kPsWord24 = 24;
inline constexpr s32 kPsBlock84 = 28;          // 84 bytes: a header word + the persona record
inline constexpr s32 kPsPersona = 32;          // 52-byte persona record (the current persona)
inline constexpr s32 kPsPersonaId = 34;        // u16 inside it: 0 = nothing to draw
inline constexpr s32 kPsPersonaNext = 116;     // 52-byte persona record (the compared one)
inline constexpr s32 kPsDrawLow = 224;         // fnptr: "psStatusDrawLow"'s drawer
inline constexpr s32 kPsDrawHigh = 228;        // fnptr: "psStatusDrawHigh"'s drawer
inline constexpr s32 kPsPage = 232;            // s8
inline constexpr s32 kPsPageCount = 233;       // s8
inline constexpr s32 kPsWord234 = 234;         // s16

// --- psModel: the 256-byte work of a "psModel" task (sub_3CDA60) -------------------------------------------------------
inline constexpr s32 kPmWord0 = 0;             // u16 (sub_3CDEE0)
inline constexpr s32 kPmFlags = 4;             // bit 0 model ready; bits 16.. set / cleared by sub_3CDE00 / sub_3CDE70
inline constexpr s32 kPmState = 8;             // 1 created, 2 reload requested
inline constexpr s32 kPmPersona = 12;          // s16 persona id
inline constexpr s32 kPmPending = 14;          // s16 queued id while not ready
inline constexpr s32 kPmModel = 24;            // ptr: the model (sub_3182D0 animations, sub_3174E0 destroy)
inline constexpr s32 kPmMatrix = 64;           // 64-byte frame matrix
inline constexpr s32 kPmColour = 128;          // RGBA bytes
inline constexpr s32 kPmColourA = 132;         // f32[4] (sub_16BC80)
inline constexpr s32 kPmColourB = 148;         // f32[4] (sub_16BDB0)
inline constexpr s32 kPmFadeTarget = 164;      // RGBA the colour fades to (sub_3CDF40)
inline constexpr s32 kPmFadeStart = 168;       // RGBA it starts from
inline constexpr s32 kPmFadeTimer = 172;       // u16
inline constexpr s32 kPmFadeFrames = 174;      // u16 duration (0 = set at once)
inline constexpr s32 kPmFadeATarget = 176;     // f32[4] (sub_3CE060)
inline constexpr s32 kPmFadeAStart = 192;
inline constexpr s32 kPmFadeATimer = 208;
inline constexpr s32 kPmFadeAFrames = 210;
inline constexpr s32 kPmFadeBTarget = 212;     // f32[4] (sub_3CE180)
inline constexpr s32 kPmFadeBStart = 228;
inline constexpr s32 kPmFadeBTimer = 244;
inline constexpr s32 kPmFadeBFrames = 246;
inline constexpr s32 kModelAnimState = 238;    // u8 on the model: 1 = the animation finished

// --- fclBank: the bank manager work (gp slot 0x7CE680 -> +36) ----------------------------------------------------------
inline constexpr u32 kBankSlot = 0x7CE680u;
inline constexpr s32 kGpBankManager = -18032;  // $gp offset of the bank manager pointer (0x7CE680)
inline constexpr s32 kBankSlots = 36;          // ptr: the slot block; three 20-byte slots from its +4
inline constexpr s32 kBankSlotStride = 20;
inline constexpr s32 kBankSlotFlags = 0;       // u16: 1 active, 2 loading, 4 stopped, 8 playing, 0x100 group, 0x400
                                               // blocked, 0x800 flag 5145 clear; high byte = request flags
inline constexpr s32 kBankSlotBank = 4;        // the bank number (also on a request payload)

// --- background element handlers (fclShopBGManager.c) ------------------------------------------------------------------
inline constexpr s32 kBgNodeArea = 12;         // on the element's node data: ptr to the element's own area
inline constexpr s32 kBgEventId = 6;           // s16 on an event record
inline constexpr s32 kBgMgrShopType = 28;      // on the manager (shops.h kBgShopType)

// --- the fusion cut-in (fclCombineEffect.c) ---------------------------------------------------------------------------
// The 96-byte work of "fclCmbEffCalc":
inline constexpr s32 kCeFlags = 4;             // 1 running (the draw tasks draw), 2 loading, 4 finishing
inline constexpr s32 kCeDrawTask = 8;          // "fclCmbEffDraw"
inline constexpr s32 kCeDraw3DTask = 12;       // "fclCmbEffDraw3D"
inline constexpr s32 kCeDraw2DTask = 16;       // "fclCmbEffDraw2DLow"
inline constexpr s32 kCeDrawSPTask = 20;       // "fclCmbEffDrawSP"
inline constexpr s32 kCePsModel = 24;          // the psModel task (sub_3CDA60)
inline constexpr s32 kCeParams = 28;           // 24-byte parameters from the caller
inline constexpr s32 kCeObjAnimArg = 32;       // s16 inside them: the animation argument of sub_41A2C0
inline constexpr s32 kCeResources = 52;        // ptr: the resource list's payload (+20 its object)
inline constexpr s32 kCeResObj = 20;           // on that payload: the list object (nodes from sub_4176F0)
inline constexpr s32 kCeCamera = 56;           // the main camera's +4 (sub_198590)
inline constexpr s32 kCeRunner = 60;           // ptr: the command runner (sub_418030)
inline constexpr s32 kCeRequests = 64;         // ptr: list object of 4-byte script requests
inline constexpr s32 kCeScript = 68;           // ptr: the running script entry (0x6B2AA0 + 8 id), 0 when done
inline constexpr u32 kCeScriptTable = 0x6B2AA0u;   // 8-byte entries {commands, count}
inline constexpr u32 kCeHandlerTable = 0x6B30A0u;  // 29 command handlers
inline constexpr u32 kCeResourceTable = 0x6B2CF0u; // 16 {s16 kind, file name} resources
// The command runner (the payload of a 20-byte list object):
inline constexpr s32 kRunResList = 0;          // ptr: the runner's own object (resource nodes, on-insert sub_418130)
inline constexpr s32 kRunActive = 4;           // ptr: list object of active commands (140-byte payloads)
inline constexpr s32 kRunFrame = 8;            // the script frame (clamped to 0x1FFFFFFF)
inline constexpr s32 kRunStarted = 12;         // commands started
inline constexpr s32 kRunFlags = 16;           // 1 end of script, 2 restart
// A script {commands, count} and its 28-byte commands:
inline constexpr s32 kScriptCommands = 0;
inline constexpr s32 kScriptCount = 4;
inline constexpr s32 kCmdFrame = 0;            // the frame the command starts on
inline constexpr s32 kCmdOp = 4;               // s8 opcode (>= 64: the resource key is the unsigned byte), s16 key
inline constexpr s32 kCmdSubOp = 5;
inline constexpr s32 kCmdHandler = 6;          // s16 index into the handler table
inline constexpr s32 kCmdArg12 = 12;
inline constexpr s32 kCmdArg16 = 16;
inline constexpr s32 kCmdArg20 = 20;
inline constexpr s32 kCmdSize = 28;
// An active command (payload of the runner's active list):
inline constexpr s32 kActCommand = 0;          // ptr: the command copy (+112 of the payload)
inline constexpr s32 kActResource = 4;         // ptr: the resource payload the command acts on
inline constexpr s32 kActHandler = 8;          // fnptr (work, active) -> 1 when done
inline constexpr s32 kActTimer = 12;           // a handler's frame counter (sub_41A900)
inline constexpr s32 kActCommandCopy = 112;
// A resource payload (runner resource list):
inline constexpr s32 kResKind = 2;             // s8 (2 = a 2D resource, sub_41BA60)
inline constexpr s32 kResBuffer = 8;           // ptr: the kind's buffer (sub_418130) / objects {-, count, objects...}

}  // namespace fcl

// The bodies (register ABI: arguments in $a0.., the result in $v0).
void sub_16BC80(EEContext& ctx);  // 0x16BC80 (register ABI: arguments in $a0.., the result in $v0)
void sub_16BDB0(EEContext& ctx);  // 0x16BDB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_20D650(EEContext& ctx);  // 0x20D650 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C44D0(EEContext& ctx);  // 0x3C44D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C49E0(EEContext& ctx);  // 0x3C49E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C4A90(EEContext& ctx);  // 0x3C4A90 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C78D0(EEContext& ctx);  // 0x3C78D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C7D50(EEContext& ctx);  // 0x3C7D50 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C7D60(EEContext& ctx);  // 0x3C7D60 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8400(EEContext& ctx);  // 0x3C8400 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8770(EEContext& ctx);  // 0x3C8770 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8810(EEContext& ctx);  // 0x3C8810 (register ABI: arguments in $a0.., the result in $v0)
void fclMisc_CreateMsgAssistTask(EEContext& ctx);  // 0x3C88D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8D80(EEContext& ctx);  // 0x3C8D80 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8DA0(EEContext& ctx);  // 0x3C8DA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8DC0(EEContext& ctx);  // 0x3C8DC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8DD0(EEContext& ctx);  // 0x3C8DD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8DE0(EEContext& ctx);  // 0x3C8DE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8EA0(EEContext& ctx);  // 0x3C8EA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8EC0(EEContext& ctx);  // 0x3C8EC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8F20(EEContext& ctx);  // 0x3C8F20 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C8F40(EEContext& ctx);  // 0x3C8F40 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9340(EEContext& ctx);  // 0x3C9340 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9570(EEContext& ctx);  // 0x3C9570 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9840(EEContext& ctx);  // 0x3C9840 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9B00(EEContext& ctx);  // 0x3C9B00 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9BA0(EEContext& ctx);  // 0x3C9BA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9C10(EEContext& ctx);  // 0x3C9C10 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9CD0(EEContext& ctx);  // 0x3C9CD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9D80(EEContext& ctx);  // 0x3C9D80 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9E00(EEContext& ctx);  // 0x3C9E00 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9E30(EEContext& ctx);  // 0x3C9E30 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9E70(EEContext& ctx);  // 0x3C9E70 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9EE0(EEContext& ctx);  // 0x3C9EE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9F10(EEContext& ctx);  // 0x3C9F10 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9F60(EEContext& ctx);  // 0x3C9F60 (register ABI: arguments in $a0.., the result in $v0)
void sub_3C9FB0(EEContext& ctx);  // 0x3C9FB0 (register ABI: arguments in $a0.., the result in $v0)
void fclMisc_UpdatePsStatusDrawLowTask(EEContext& ctx);  // 0x3CA610 (register ABI: arguments in $a0.., the result in $v0)
void fclMisc_UpdatePsStatusDrawHighTask(EEContext& ctx);  // 0x3CA660 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_122(EEContext& ctx);  // 0x3CCC30 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_123(EEContext& ctx);  // 0x3CD0A0 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_124(EEContext& ctx);  // 0x3CD590 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDA60(EEContext& ctx);  // 0x3CDA60 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDBA0(EEContext& ctx);  // 0x3CDBA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDC80(EEContext& ctx);  // 0x3CDC80 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDCD0(EEContext& ctx);  // 0x3CDCD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDD80(EEContext& ctx);  // 0x3CDD80 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDE00(EEContext& ctx);  // 0x3CDE00 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDE70(EEContext& ctx);  // 0x3CDE70 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDEE0(EEContext& ctx);  // 0x3CDEE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CDF40(EEContext& ctx);  // 0x3CDF40 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CE060(EEContext& ctx);  // 0x3CE060 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CE180(EEContext& ctx);  // 0x3CE180 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF520(EEContext& ctx);  // 0x3CF520 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF8F0(EEContext& ctx);  // 0x3CF8F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CF960(EEContext& ctx);  // 0x3CF960 (register ABI: arguments in $a0.., the result in $v0)
void sub_3CFAC0(EEContext& ctx);  // 0x3CFAC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_40D3B0(EEContext& ctx);  // 0x40D3B0 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_67(EEContext& ctx);  // 0x40D400 (register ABI: arguments in $a0.., the result in $v0)
void sub_40D5B0(EEContext& ctx);  // 0x40D5B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_40DCC0(EEContext& ctx);  // 0x40DCC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_40EBC0(EEContext& ctx);  // 0x40EBC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_40F030(EEContext& ctx);  // 0x40F030 (register ABI: arguments in $a0.., the result in $v0)
void sub_40F430(EEContext& ctx);  // 0x40F430 (register ABI: arguments in $a0.., the result in $v0)
void sub_40F5D0(EEContext& ctx);  // 0x40F5D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_40FAB0(EEContext& ctx);  // 0x40FAB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_40FB90(EEContext& ctx);  // 0x40FB90 (register ABI: arguments in $a0.., the result in $v0)
void sub_4101B0(EEContext& ctx);  // 0x4101B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4105E0(EEContext& ctx);  // 0x4105E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_410A10(EEContext& ctx);  // 0x410A10 (register ABI: arguments in $a0.., the result in $v0)
void sub_4110E0(EEContext& ctx);  // 0x4110E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4113F0(EEContext& ctx);  // 0x4113F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_411710(EEContext& ctx);  // 0x411710 (register ABI: arguments in $a0.., the result in $v0)
void sub_411790(EEContext& ctx);  // 0x411790 (register ABI: arguments in $a0.., the result in $v0)
void sub_4120A0(EEContext& ctx);  // 0x4120A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_412610(EEContext& ctx);  // 0x412610 (register ABI: arguments in $a0.., the result in $v0)
void sub_412AF0(EEContext& ctx);  // 0x412AF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_412BC0(EEContext& ctx);  // 0x412BC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_413010(EEContext& ctx);  // 0x413010 (register ABI: arguments in $a0.., the result in $v0)
void sub_4131A0(EEContext& ctx);  // 0x4131A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_413680(EEContext& ctx);  // 0x413680 (register ABI: arguments in $a0.., the result in $v0)
void sub_4138E0(EEContext& ctx);  // 0x4138E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_413B10(EEContext& ctx);  // 0x413B10 (register ABI: arguments in $a0.., the result in $v0)
void sub_414100(EEContext& ctx);  // 0x414100 (register ABI: arguments in $a0.., the result in $v0)
void sub_4141E0(EEContext& ctx);  // 0x4141E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_414280(EEContext& ctx);  // 0x414280 (register ABI: arguments in $a0.., the result in $v0)
void sub_414320(EEContext& ctx);  // 0x414320 (register ABI: arguments in $a0.., the result in $v0)
void sub_414500(EEContext& ctx);  // 0x414500 (register ABI: arguments in $a0.., the result in $v0)
void sub_4145F0(EEContext& ctx);  // 0x4145F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4146B0(EEContext& ctx);  // 0x4146B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4148B0(EEContext& ctx);  // 0x4148B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_414950(EEContext& ctx);  // 0x414950 (register ABI: arguments in $a0.., the result in $v0)
void sub_4149F0(EEContext& ctx);  // 0x4149F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_414AD0(EEContext& ctx);  // 0x414AD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_414BD0(EEContext& ctx);  // 0x414BD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_414C70(EEContext& ctx);  // 0x414C70 (register ABI: arguments in $a0.., the result in $v0)
void sub_414D70(EEContext& ctx);  // 0x414D70 (register ABI: arguments in $a0.., the result in $v0)
void sub_414E10(EEContext& ctx);  // 0x414E10 (register ABI: arguments in $a0.., the result in $v0)
void sub_414FE0(EEContext& ctx);  // 0x414FE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4154E0(EEContext& ctx);  // 0x4154E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_415650(EEContext& ctx);  // 0x415650 (register ABI: arguments in $a0.., the result in $v0)
void sub_4157C0(EEContext& ctx);  // 0x4157C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_415880(EEContext& ctx);  // 0x415880 (register ABI: arguments in $a0.., the result in $v0)
void sub_415A70(EEContext& ctx);  // 0x415A70 (register ABI: arguments in $a0.., the result in $v0)
void sub_415B30(EEContext& ctx);  // 0x415B30 (register ABI: arguments in $a0.., the result in $v0)
void sub_415B70(EEContext& ctx);  // 0x415B70 (register ABI: arguments in $a0.., the result in $v0)
void sub_415C30(EEContext& ctx);  // 0x415C30 (register ABI: arguments in $a0.., the result in $v0)
void sub_4167D0(EEContext& ctx);  // 0x4167D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_416D20(EEContext& ctx);  // 0x416D20 (register ABI: arguments in $a0.., the result in $v0)
void sub_417030(EEContext& ctx);  // 0x417030 (register ABI: arguments in $a0.., the result in $v0)
void fclCmbEff_CreateCmbEffCalcTasks(EEContext& ctx);  // 0x417160 (register ABI: arguments in $a0.., the result in $v0)
void sub_417330(EEContext& ctx);  // 0x417330 (register ABI: arguments in $a0.., the result in $v0)
void sub_417380(EEContext& ctx);  // 0x417380 (register ABI: arguments in $a0.., the result in $v0)
void sub_4173E0(EEContext& ctx);  // 0x4173E0 (register ABI: arguments in $a0.., the result in $v0)
void fclCmbEff_UpdateCmbEffDraw2DLowTask(EEContext& ctx);  // 0x4175E0 (register ABI: arguments in $a0.., the result in $v0)
void fclCmbEff_UpdateCmbEffDrawSPTask(EEContext& ctx);  // 0x417630 (register ABI: arguments in $a0.., the result in $v0)
void sub_417680(EEContext& ctx);  // 0x417680 (register ABI: arguments in $a0.., the result in $v0)
void sub_4176F0(EEContext& ctx);  // 0x4176F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4177E0(EEContext& ctx);  // 0x4177E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_418030(EEContext& ctx);  // 0x418030 (register ABI: arguments in $a0.., the result in $v0)
void sub_4180A0(EEContext& ctx);  // 0x4180A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_4180E0(EEContext& ctx);  // 0x4180E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_418130(EEContext& ctx);  // 0x418130 (register ABI: arguments in $a0.., the result in $v0)
void sub_418340(EEContext& ctx);  // 0x418340 (register ABI: arguments in $a0.., the result in $v0)
void sub_419B00(EEContext& ctx);  // 0x419B00 (register ABI: arguments in $a0.., the result in $v0)
void sub_419B20(EEContext& ctx);  // 0x419B20 (register ABI: arguments in $a0.., the result in $v0)
void sub_419B40(EEContext& ctx);  // 0x419B40 (register ABI: arguments in $a0.., the result in $v0)
void sub_419C10(EEContext& ctx);  // 0x419C10 (register ABI: arguments in $a0.., the result in $v0)
void sub_41A2C0(EEContext& ctx);  // 0x41A2C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_41A900(EEContext& ctx);  // 0x41A900 (register ABI: arguments in $a0.., the result in $v0)
void sub_41ADD0(EEContext& ctx);  // 0x41ADD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_41B530(EEContext& ctx);  // 0x41B530 (register ABI: arguments in $a0.., the result in $v0)
void sub_41B550(EEContext& ctx);  // 0x41B550 (register ABI: arguments in $a0.., the result in $v0)
void sub_41B5C0(EEContext& ctx);  // 0x41B5C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_41BA60(EEContext& ctx);  // 0x41BA60 (register ABI: arguments in $a0.., the result in $v0)
void sub_41BC90(EEContext& ctx);  // 0x41BC90 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
