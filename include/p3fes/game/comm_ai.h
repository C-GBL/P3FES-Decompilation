// The battle-AI script command handlers (slice comm_ai): the 120 handlers of sScrCommandTable 0x7B92B0 at indices
// 51-117, 139-144, 149-180 and 235-250 (btlAICommand.c, band 0x2C7300-0x2CE090, plus sub_2D13C0), hand-decompiled
// from SLUS_216.21. They are the COMM functions the enemy / party AI scripts (the two FLW0 blobs of AICALC.TBL,
// docs/ANALYSIS/21_battle.md section 3.2, procedures AI_PC_%03X_%03X / AI_EVENT_%03X_*) call to ask about the battle
// and to choose an action; docs/ANALYSIS/18_script_vm.md section 2.4 is the calling convention (arguments read in
// place through scrGetIntPara, the result through scrSetIntReturnVal, return 1 = done).
//
// The acting unit. scrGetUserData() of an AI script is the btlAction object (1200 bytes, 21_battle.md section 1.3)
// of the unit whose turn it is; the handlers read
//   action +48   btlUnit*: +162 u8 side (0 party, 1 enemy; `1 << side` is the side mask of the unit finders),
//                +164 u16 unit id, +2604 DatUnit* (the 60-byte unit record of battle.h)
//   action +56   the command record handed to sub_2C6A00 [btlAISetCommand]; its +52/+54 are action +108 (u16
//                command kind: 1 attack, 2 skill, 3 item, 6/7/8/9/11/12 the other kinds) and +110 (u16 skill id)
//   action +112  u16 item id (item command), +118 / +120 u16 arguments of command kind 9 (skill 341)
//   action +136  the target record (copied from the appointed action by sub_2C08B0)
// gBtl (`*(u32*)($gp - 18692)` = 0x7CE3EC) +328 is the appointed action (or 0), +332 the head of the action list
// (`+1192` = next) that the unit finders walk.
//
// An AI query is one word: `kind << 24 | (param & 0xFFFFFF)`. Two tables decode the kind:
//   kCondTable 0x6971B0, 12-byte rows {fn, name, flag}: the conditions, `fn(action, param)` -> non-zero when true;
//               the handler hands `result != 0` to the script. Kinds 1..71, named by the table's own strings:
//               MYHP MYMP FRHP ENHP ENHP_O MYLV_O FRLV_O ENLV_O FRCNT ENCNT MYBAD FRBAD ENBAD ENBAD_ALL FRID ENID FRHOJO
//               ENHOJO ESCAPE SUMMON SENSEI MYHANSYA MYKYUSYU MYMUKOU MYWEAK FRHANSYA ENHANSYA FRKYUSYU ENKYUSYU
//               FRMUKOU ENMUKOU FRWEAK ENWEAK MYUSEATTR FRUSEATTR ENUSEATTR MYUSESKIL FRUSESKIL ENUSESKIL MYGROUP
//               FRGROUP ENGROUP TURN TURN_O MYHREC MORE FRHANSYA_ST ENHANSYA_ST FRKYUSYU_ST ENKYUSYU_ST FRMUKOU_ST
//               ENMUKOU_ST FRWEAK_ST ENWEAK_ST MYID FRALLHP ENALLHP MYABLESKIL ENWEAK_PAI ENWEAK_ST_PAI ENWEAK_DW_PAI
//               MYATTRSKIL MYNOMAL ENNOMAL ENNOMAL_ST ENNOMAL_DW ANALYZE DOWN SLIP ENOVERLV MYHOJO
//               (MY = the acting unit, FR = its side, EN = the other side; e.g. MYHP sub_2C12F0 is
//               `100 * hp <= max_hp * param`: "my HP is at most param percent").
//   kTargetTable 0x6975E0, 8-byte rows {fn, name}: the target selectors, `fn(action, param)` -> non-zero when a
//               target was chosen (written into the action's target record); 0 AI (the default choice) HPMIN LVMIN
//               MPMAX BAD NOTBAD ID MINE MYAI HANSYA KYUSYU MUKOU WEAK NOTHANSYA NOTKYUSYU NOTMUKOU NOTWEAK AI_REV
//               APPOINT DOWN STAND HANSYA_ST KYUSYU_ST MUKOU_ST WEAK_ST NOTHANSYA_ST ... HOJO. Every selecting
//               handler falls back to row 0 (AI) when its selector finds nothing.
// Both calls go through a function pointer (`jalr`); the hand versions make them through rt::lookup_func with the
// original frame, $ra link and every register the original set (comm_ai.cpp, "Register discipline").
//
// Names are the IDA names of symbols/functions.json (all sub_*). Every handler is referenced only by the COMM table
// (no jal and no other data word in the ELF points at one), so its only caller is CodeFunc_Comm's jalr.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace comm_ai {
inline constexpr u32 kCondTable = 0x6971B0u;    // {u32 fn, u32 name, u32 flag}[72]
inline constexpr u32 kCondRow = 12;
inline constexpr u32 kTargetTable = 0x6975E0u;  // {u32 fn, u32 name}[37]
inline constexpr u32 kTargetRow = 8;
inline constexpr s32 kGBtlGpOffset = -18692;    // gBtl = *(u32*)($gp - 18692) = 0x7CE3EC
inline constexpr u32 kGBtlAppointed = 328;      // gBtl +328: the appointed action, or 0
// btlAction fields (the AI script's user data).
inline constexpr u32 kActUnit = 48;             // btlUnit*
inline constexpr u32 kActCommandRec = 56;       // the record sub_2C6A00 fills (+52 command, +54 skill)
inline constexpr u32 kActCommand = 108;         // u16 command kind (= record +52)
inline constexpr u32 kActSkill = 110;           // u16 skill id (= record +54)
inline constexpr u32 kActItem = 112;            // u16 item id
inline constexpr u32 kActArg0 = 118;            // u16 first argument of command kind 9
inline constexpr u32 kActArg1 = 120;            // u16 second argument
inline constexpr u32 kActTargetRec = 136;       // the target record (sub_2C08B0 copies it)
// btlUnit fields.
inline constexpr u32 kUnitSide = 162;           // u8: 0 party, 1 enemy
inline constexpr u32 kUnitId = 164;             // u16
inline constexpr u32 kUnitDat = 2604;           // DatUnit*
// sub_2C0E30's status filter: skip dead units (bit 19, datCalcIsDead) and units with that status.
inline constexpr u32 kStatusDead = 0x80000u;
// The command codes of sub_2C6A00 (a value below 0x1000 is a skill id).
inline constexpr u32 kCmdAttack = 0x8000u;      // command 1, the held weapon's attack skill
inline constexpr u32 kCmdKind6 = 0x8001u;       // command 6
inline constexpr u32 kCmdKind7 = 0x8002u;       // command 7
inline constexpr u32 kCmdKind8 = 0x8007u;       // command 8
// Command kind 9 with skill 341 (sub_2C7540 / sub_2C75D0).
inline constexpr u32 kSkill341Command = 9;
inline constexpr u32 kSkill341 = 341;
inline constexpr u32 kItemCommand = 3;
}  // namespace comm_ai

// The handler table as X-macros, one family per list: X(name, addr8, index, k) where addr8 is the start address in
// eight hex digits (the generated symbol fn_<name>_<addr8>), index the COMM index and k the family's parameter.
//
// ASK (argc 1): scrSetIntReturnVal(condition k of the acting unit, param = arg0 & 0xFFFFFF). k = kCondTable row.
#define P3FES_COMM_AI_ASK(X)                                                                                         \
    X(sub_2C76B0, 002c76b0, 51, 1)  /* MYHP */                                                                       \
    X(sub_2C7760, 002c7760, 52, 2)  /* MYMP */                                                                       \
    X(sub_2C7810, 002c7810, 53, 3)  /* FRHP */                                                                       \
    X(sub_2C78C0, 002c78c0, 54, 4)  /* ENHP */                                                                       \
    X(sub_2C7970, 002c7970, 55, 5)  /* ENHP_O */                                                                     \
    X(sub_2C7A20, 002c7a20, 56, 6)  /* MYLV_O */                                                                     \
    X(sub_2C7AD0, 002c7ad0, 57, 7)  /* FRLV_O */                                                                     \
    X(sub_2C7B80, 002c7b80, 58, 8)  /* ENLV_O */                                                                     \
    X(sub_2C7C30, 002c7c30, 59, 9)  /* FRCNT */                                                                      \
    X(sub_2C7CE0, 002c7ce0, 60, 10) /* ENCNT */                                                                      \
    X(sub_2C7D90, 002c7d90, 61, 11) /* MYBAD */                                                                      \
    X(sub_2C7E40, 002c7e40, 62, 12) /* FRBAD */                                                                      \
    X(sub_2C7EF0, 002c7ef0, 63, 13) /* ENBAD */                                                                      \
    X(sub_2C7FA0, 002c7fa0, 64, 14) /* ENBAD_ALL */                                                                  \
    X(sub_2C8050, 002c8050, 65, 15) /* FRID */                                                                       \
    X(sub_2C8100, 002c8100, 66, 16) /* ENID */                                                                       \
    X(sub_2C81B0, 002c81b0, 67, 17) /* FRHOJO */                                                                     \
    X(sub_2C8260, 002c8260, 68, 18) /* ENHOJO */                                                                     \
    X(sub_2C8400, 002c8400, 72, 22) /* MYHANSYA */                                                                   \
    X(sub_2C84B0, 002c84b0, 73, 23) /* MYKYUSYU */                                                                   \
    X(sub_2C8560, 002c8560, 74, 24) /* MYMUKOU */                                                                    \
    X(sub_2C8610, 002c8610, 75, 25) /* MYWEAK */                                                                     \
    X(sub_2C86C0, 002c86c0, 76, 26) /* FRHANSYA */                                                                   \
    X(sub_2C8770, 002c8770, 77, 27) /* ENHANSYA */                                                                   \
    X(sub_2C8820, 002c8820, 78, 28) /* FRKYUSYU */                                                                   \
    X(sub_2C88D0, 002c88d0, 79, 29) /* ENKYUSYU */                                                                   \
    X(sub_2C8980, 002c8980, 80, 30) /* FRMUKOU */                                                                    \
    X(sub_2C8A30, 002c8a30, 81, 31) /* ENMUKOU */                                                                    \
    X(sub_2C8AE0, 002c8ae0, 82, 32) /* FRWEAK */                                                                     \
    X(sub_2C8B90, 002c8b90, 83, 33) /* ENWEAK */                                                                     \
    X(sub_2C8C40, 002c8c40, 84, 34) /* MYUSEATTR */                                                                  \
    X(sub_2C8CF0, 002c8cf0, 85, 35) /* FRUSEATTR */                                                                  \
    X(sub_2C8DA0, 002c8da0, 86, 36) /* ENUSEATTR */                                                                  \
    X(sub_2C8E50, 002c8e50, 87, 37) /* MYUSESKIL */                                                                  \
    X(sub_2C8F00, 002c8f00, 88, 38) /* FRUSESKIL */                                                                  \
    X(sub_2C8FB0, 002c8fb0, 89, 39) /* ENUSESKIL */                                                                  \
    X(sub_2C9150, 002c9150, 93, 43) /* TURN */                                                                       \
    X(sub_2C9200, 002c9200, 94, 44) /* TURN_O */                                                                     \
    X(sub_2C9350, 002c9350, 157, 47) /* FRHANSYA_ST */                                                               \
    X(sub_2C9400, 002c9400, 158, 48) /* ENHANSYA_ST */                                                               \
    X(sub_2C94B0, 002c94b0, 159, 49) /* FRKYUSYU_ST */                                                               \
    X(sub_2C9560, 002c9560, 160, 50) /* ENKYUSYU_ST */                                                               \
    X(sub_2C9610, 002c9610, 161, 51) /* FRMUKOU_ST */                                                                \
    X(sub_2C96C0, 002c96c0, 162, 52) /* ENMUKOU_ST */                                                                \
    X(sub_2C9770, 002c9770, 163, 53) /* FRWEAK_ST */                                                                 \
    X(sub_2C9820, 002c9820, 164, 54) /* ENWEAK_ST */                                                                 \
    X(sub_2CB270, 002cb270, 237, 56) /* FRALLHP */                                                                   \
    X(sub_2CB320, 002cb320, 238, 57) /* ENALLHP */                                                                   \
    X(sub_2CB3D0, 002cb3d0, 239, 58) /* MYABLESKIL */                                                                \
    X(sub_2CB480, 002cb480, 240, 59) /* ENWEAK_PAI */                                                                \
    X(sub_2CB530, 002cb530, 241, 60) /* ENWEAK_ST_PAI */                                                             \
    X(sub_2CB5E0, 002cb5e0, 242, 61) /* ENWEAK_DW_PAI */                                                             \
    X(sub_2CB690, 002cb690, 243, 62) /* MYATTRSKIL */                                                                \
    X(sub_2CB740, 002cb740, 244, 63) /* MYNOMAL */                                                                   \
    X(sub_2CB7F0, 002cb7f0, 245, 64) /* ENNOMAL */                                                                   \
    X(sub_2CB8A0, 002cb8a0, 246, 65) /* ENNOMAL_ST */                                                                \
    X(sub_2CB950, 002cb950, 247, 66) /* ENNOMAL_DW */

// ASK_FIXED (argc 0): scrSetIntReturnVal(condition k of the acting unit, param 0).
#define P3FES_COMM_AI_ASK_FIXED(X)                                                                                   \
    X(sub_2C8310, 002c8310, 69, 19)  /* ESCAPE */                                                                    \
    X(sub_2C8360, 002c8360, 70, 20)  /* SUMMON */                                                                    \
    X(sub_2C83B0, 002c83b0, 71, 21)  /* SENSEI */                                                                    \
    X(sub_2C9060, 002c9060, 90, 40)  /* MYGROUP */                                                                   \
    X(sub_2C90B0, 002c90b0, 91, 41)  /* FRGROUP */                                                                   \
    X(sub_2C9100, 002c9100, 92, 42)  /* ENGROUP */                                                                   \
    X(sub_2C92B0, 002c92b0, 142, 45) /* MYHREC */                                                                    \
    X(sub_2C9300, 002c9300, 143, 46) /* MORE */

// TARGET_FIXED (argc 0): choose a target with selector k (param 0), else with AI. No script result.
#define P3FES_COMM_AI_TARGET_FIXED(X)                                                                                \
    X(sub_2CC3E0, 002cc3e0, 95, 0)   /* AI (twice) */                                                                \
    X(sub_2CC450, 002cc450, 96, 1)   /* HPMIN */                                                                     \
    X(sub_2CC4C0, 002cc4c0, 97, 2)   /* LVMIN */                                                                     \
    X(sub_2CC530, 002cc530, 98, 3)   /* MPMAX */                                                                     \
    X(sub_2CC7B0, 002cc7b0, 102, 7)  /* MINE */                                                                      \
    X(sub_2CC820, 002cc820, 103, 8)  /* MYAI */                                                                      \
    X(sub_2CCE10, 002cce10, 139, 18) /* APPOINT */                                                                   \
    X(sub_2CCE80, 002cce80, 140, 19) /* DOWN */                                                                      \
    X(sub_2CCEF0, 002ccef0, 141, 20) /* STAND */

// TARGET (argc 1): choose a target with selector k, param = arg0 & 0xFFFFFF, else with AI.
#define P3FES_COMM_AI_TARGET(X)                                                                                      \
    X(sub_2CC5A0, 002cc5a0, 99, 4)   /* BAD */                                                                       \
    X(sub_2CC650, 002cc650, 100, 5)  /* NOTBAD */                                                                    \
    X(sub_2CC700, 002cc700, 101, 6)  /* ID */                                                                        \
    X(sub_2CC890, 002cc890, 104, 9)  /* HANSYA */                                                                    \
    X(sub_2CC940, 002cc940, 105, 10) /* KYUSYU */                                                                    \
    X(sub_2CC9F0, 002cc9f0, 106, 11) /* MUKOU */                                                                     \
    X(sub_2CCAA0, 002ccaa0, 107, 12) /* WEAK */                                                                      \
    X(sub_2CCB50, 002ccb50, 108, 13) /* NOTHANSYA */                                                                 \
    X(sub_2CCC00, 002ccc00, 109, 14) /* NOTKYUSYU */                                                                 \
    X(sub_2CCCB0, 002cccb0, 110, 15) /* NOTMUKOU */                                                                  \
    X(sub_2CCD60, 002ccd60, 111, 16) /* NOTWEAK */                                                                   \
    X(sub_2CCF60, 002ccf60, 149, 21) /* HANSYA_ST */                                                                 \
    X(sub_2CD010, 002cd010, 150, 22) /* KYUSYU_ST */                                                                 \
    X(sub_2CD0C0, 002cd0c0, 151, 23) /* MUKOU_ST */                                                                  \
    X(sub_2CD170, 002cd170, 152, 24) /* WEAK_ST */                                                                   \
    X(sub_2CD220, 002cd220, 153, 25) /* NOTHANSYA_ST */                                                              \
    X(sub_2CD2D0, 002cd2d0, 154, 26) /* NOTKYUSYU_ST */                                                              \
    X(sub_2CD380, 002cd380, 155, 27) /* NOTMUKOU_ST */                                                               \
    X(sub_2CD430, 002cd430, 156, 28) /* NOTWEAK_ST */

// COMMAND (argc 0): sub_2C6A00(action, action + 56, k): set the command code k.
#define P3FES_COMM_AI_COMMAND(X)                                                                                     \
    X(sub_2C7300, 002c7300, 112, 0x8000) /* attack */                                                                \
    X(sub_2C7460, 002c7460, 114, 0x8001) /* command 6 */                                                             \
    X(sub_2C74A0, 002c74a0, 115, 0x8002) /* command 7 */                                                             \
    X(sub_2C7670, 002c7670, 144, 0x8007) /* command 8 */

// ASK_ALLY (argc 2): the living unit of the acting unit's side with id arg0 (sub_2C0E30); 0 when there is none,
// else condition k of that unit with param = arg1 & 0xFFFFFF.
#define P3FES_COMM_AI_ASK_ALLY(X)                                                                                    \
    X(sub_2C98D0, 002c98d0, 167, 1)  /* MYHP */                                                                      \
    X(sub_2C99C0, 002c99c0, 168, 2)  /* MYMP */                                                                      \
    X(sub_2C9AB0, 002c9ab0, 169, 6)  /* MYLV_O */                                                                    \
    X(sub_2C9DA0, 002c9da0, 172, 22) /* MYHANSYA */                                                                  \
    X(sub_2C9E90, 002c9e90, 173, 23) /* MYKYUSYU */                                                                  \
    X(sub_2C9F80, 002c9f80, 174, 24) /* MYMUKOU */                                                                   \
    X(sub_2CA070, 002ca070, 175, 25) /* MYWEAK */                                                                    \
    X(sub_2CA160, 002ca160, 176, 34) /* MYUSEATTR */                                                                 \
    X(sub_2CA250, 002ca250, 177, 37) /* MYUSESKIL */

// ALLY_FIXED (argc 1): the living unit of the acting unit's side with id arg0; 0 when none, else condition k (param 0).
#define P3FES_COMM_AI_ALLY_FIXED(X)                                                                                  \
    X(sub_2CA340, 002ca340, 178, 40) /* MYGROUP */                                                                   \
    X(sub_2CA3E0, 002ca3e0, 179, 45) /* MYHREC */

#define P3FES_COMM_AI_DECLARE(name, addr8, index, k) u32 name(EEContext& ctx);
P3FES_COMM_AI_ASK(P3FES_COMM_AI_DECLARE)
P3FES_COMM_AI_ASK_FIXED(P3FES_COMM_AI_DECLARE)
P3FES_COMM_AI_TARGET_FIXED(P3FES_COMM_AI_DECLARE)
P3FES_COMM_AI_TARGET(P3FES_COMM_AI_DECLARE)
P3FES_COMM_AI_COMMAND(P3FES_COMM_AI_DECLARE)
P3FES_COMM_AI_ASK_ALLY(P3FES_COMM_AI_DECLARE)
P3FES_COMM_AI_ALLY_FIXED(P3FES_COMM_AI_DECLARE)
#undef P3FES_COMM_AI_DECLARE

// The handlers of their own shape. [index] argc.
u32 sub_2C7340(EEContext& ctx);  // [113] 1: arg0 == 0 -> attack; > 0 -> skill (u16)arg0; < 0 -> command 7
u32 sub_2C7540(EEContext& ctx);  // [116] 1: command 9 / skill 341 with +118 = arg0; target MYAI, else AI
u32 sub_2C75D0(EEContext& ctx);  // [165] 2: the same with +118 = arg0, +120 = arg1
u32 sub_2D13C0(EEContext& ctx);  // [117] 0: the table-driven AI: the unit's AICALC row (sub_2C6BA0 / sub_2C6E30) gives
                                 //        the command (row +2) and the target query (row +4), else AI
u32 sub_2C9BA0(EEContext& ctx);  // [170] 2: ally arg0 (dead ones too when arg1 has bit 19) has status bits arg1 (MYBAD)
u32 sub_2C9CE0(EEContext& ctx);  // [171] 2: living ally arg0 has effect mask arg1 (sub_301CA0)
u32 sub_2CD4E0(EEContext& ctx);  // [180] 0: with an appointed action: copy its target record, target APPOINT, else AI
u32 sub_2C73E0(EEContext& ctx);  // [235] 1: arg0 >= 0 -> item command for item arg0 (+110 = sub_30BC20(item)); else 7
u32 sub_2CB190(EEContext& ctx);  // [236] 2: the acting unit is on side arg0 (0 or 1; other values pass) and has id arg1
u32 sub_2CDF40(EEContext& ctx);  // [248] 2: condition MYHP(arg1) of the action with id arg0 (sub_29A210)
u32 sub_2CE010(EEContext& ctx);  // [249] 2: the action with id arg0 has effect mask arg1 (sub_301CA0)
u32 sub_2CE090(EEContext& ctx);  // [250] 1: a normal attack (datCalcDamage(0, me, it, 1, 1, 1, 0, 1)) would leave the
                                 //        unit of action arg0 at hp <= 0 (both units' +0x18 word cleared after)

}  // namespace p3fes::game
