// The battle command menu, bcm_main.c (game/include/p3fes/game/battle_cmd_menu.h has the overview; the bcm work record
// and its fields are named there). Phase 5 slice battle_cmd_menu: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_battle_cmd_menu.cpp runs each against its __recomp body.
//
// Cycle model (ADR-0013): every charge() is one `ctx.cycles += N` block of the recompiled body (recomp/generated
// fn_0010 / fn_0011), in the order the path executes them; a block holding `jal`s is charged in full where it starts.
// A block is the run of instructions from a branch target (or the instruction after a branch's delay slot) to the
// next branch's delay slot, so N is simply its instruction count. backedge() sits on every backward branch: the loop
// tests here come last (`b test; body; test: ...; bnez body`), so the check point is taken after the test block, before
// each further iteration.
//
// Registers: register-faithful (battle_cmd_menu.h). The bodies run on bcm::Cpu; the delay slots are all nops.
// The two jump tables (0x7B7350, 0x7B73B0) are read from guest memory as the originals do ($v1 holds the target) and
// dispatched on that target.
#include "p3fes/game/battle_cmd_menu.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by this or other slices: always through their generated entry points).
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);             // system sound (kind)
void fn_sub_16C970_0016c970(p3fes::EEContext&);             // persona / unit flags of a party member id
void fn_sub_16DAD0_0016dad0(p3fes::EEContext&);             // set a party member's tactic (pc id, tactic)
void fn_sub_16DD80_0016dd80(p3fes::EEContext&);             // a party member's tactic (pc id)
void fn_datGetFlag_0016f190(p3fes::EEContext&);             // (id) (menu_ui)
void fn_sub_16F380_0016f380(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);             // item stock count (owner, item)
void fn_sub_170E90_00170e90(p3fes::EEContext&);             // item record (item)
void fn_sub_171110_00171110(p3fes::EEContext&);             // item name (item, 0)
void fn_sub_173220_00173220(p3fes::EEContext&);             // persona name (persona id)
void fn_sub_173370_00173370(p3fes::EEContext&);             // persona skill list (persona)
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);    // (pc id) (battle_data)
void fn_sub_174A90_00174a90(p3fes::EEContext&);             // stock persona (index)
void fn_sub_1756F0_001756f0(p3fes::EEContext&);             // stock persona count
void fn_sub_176A30_00176a30(p3fes::EEContext&);             // persona skill count (persona)
void fn_sub_1775A0_001775a0(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);             // party member name (pc id)
void fn_sub_17D2E0_0017d2e0(p3fes::EEContext&);             // item kind (item)
void fn_sub_17D800_0017d800(p3fes::EEContext&);             // scenario mode: 1 = The Answer (ui2)
void fn_sub_1FF430_001ff430(p3fes::EEContext&);             // battle panel: the btlUnit of a unit record
void fn_sub_1FF500_001ff500(p3fes::EEContext&);             // battle panel
void fn_sub_1FF740_001ff740(p3fes::EEContext&);             // battle panel: the menu mode
void fn_sub_1FF7F0_001ff7f0(p3fes::EEContext&);             // battle panel: is party member present (pc id)
void fn_sub_2083D0_002083d0(p3fes::EEContext&);             // (this file)
void fn_sub_208860_00208860(p3fes::EEContext&);             // (this file)
void fn_sub_249650_00249650(p3fes::EEContext&);
void fn_btlGetEncounterId_002d5550(p3fes::EEContext&);             // the encounter id
void fn_sub_2DDBA0_002ddba0(p3fes::EEContext&);             // navigator line (message id)
void fn_sub_2DDC10_002ddc10(p3fes::EEContext&);             // navigator: the line was said already (pc id)
void fn_sub_30C0C0_0030c0c0(p3fes::EEContext&);             // (battle_rest)
void fn_sub_3B0170_003b0170(p3fes::EEContext&);             // release a font line
void fn_sub_488F30_00488f30(p3fes::EEContext&);             // RpRandom
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);   // (text, 2, style, 0; t0 0) -> font line
void fn_sub_3B2C60_003b2c60(p3fes::EEContext&);             // font line: depth ($f12)
void fn_frFontLineSetPos_003b0d70(p3fes::EEContext&);       // (line, x, y) (font)
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);      // (line, rgba) (font)
void fn_frFontSetDefaultGlyphFlags_003b0e70(p3fes::EEContext&);    // (bits) (font)
void fn_frFontClearDefaultGlyphFlags_003b0e90(p3fes::EEContext&);  // (bits) (font)
void fn_datGetSkillName_0030bb40(p3fes::EEContext&);        // (skill) (battle_rest)
void fn_itfMesMngDestroyHandle_003a3060(p3fes::EEContext&); // (handle)
void fn_sub_21F0C0_0021f0c0(p3fes::EEContext&);             // command panel: create (panel record)
void fn_sub_21F140_0021f140(p3fes::EEContext&);             // command panel: destroy
void fn_sub_21F3C0_0021f3c0(p3fes::EEContext&);             // command panel: reset
void fn_sub_22C0A0_0022c0a0(p3fes::EEContext&);             // skill window: close
void fn_sub_22C1D0_0022c1d0(p3fes::EEContext&);             // item window: close
void fn_sub_25D710_0025d710(p3fes::EEContext&);             // panel dialog: reset
void fn_sub_2C0A50_002c0a50(p3fes::EEContext&);             // btlUnit: set the assigned target (unit, target)
void fn_sub_2DB2A0_002db2a0(p3fes::EEContext&);             // support (navigator) state of a side: start
void fn_btlSupportClearFlag_002db420(p3fes::EEContext&);             // ... stop
void fn_btlSupportTestFlag_002db450(p3fes::EEContext&);             // ... is on (side)
void fn_sub_2DB480_002db480(p3fes::EEContext&);             // support availability
void fn_sub_2DB650_002db650(p3fes::EEContext&);             // ... (kind)
void fn_sub_2055F0_002055f0(p3fes::EEContext&);             // (this file)
void fn_sub_205650_00205650(p3fes::EEContext&);             // (this file)
void fn_sub_202BC0_00202bc0(p3fes::EEContext&);             // (this file)
void fn_sub_203360_00203360(p3fes::EEContext&);             // (this file)
void fn_sub_203B70_00203b70(p3fes::EEContext&);             // (this file)
void fn_sub_204BE0_00204be0(p3fes::EEContext&);             // (this file)
void fn_sub_206310_00206310(p3fes::EEContext&);             // (this file)
void fn_sub_206EB0_00206eb0(p3fes::EEContext&);             // (this file)
void fn_sub_208360_00208360(p3fes::EEContext&);             // (this file)
void fn_sub_2082C0_002082c0(p3fes::EEContext&);             // (this file)
void fn_sub_3A5540_003a5540(p3fes::EEContext&);             // help message line (x, y, z, 2; t0 6, t1 handle, t2 index; $f12)
void fn_sub_3C7D60_003c7d60(p3fes::EEContext&);             // message handle of a help kind
void fn_sub_2255F0_002255f0(p3fes::EEContext&);             // command panel: open the analyze window
void fn_sub_2518B0_002518b0(p3fes::EEContext&);             // boss tutorial page (index)
void fn_sub_251E10_00251e10(p3fes::EEContext&);             // tutorial page
void fn_sub_20FC40_0020fc40(p3fes::EEContext&);             // panel: hide the command window
void fn_sub_202A10_00202a10(p3fes::EEContext&);             // (this file)
void fn_sub_203410_00203410(p3fes::EEContext&);             // (this file)
void fn_sub_203DE0_00203de0(p3fes::EEContext&);             // (this file)
void fn_sub_205000_00205000(p3fes::EEContext&);             // (this file)
void fn_sub_206170_00206170(p3fes::EEContext&);             // (this file)
void fn_sub_207010_00207010(p3fes::EEContext&);             // (this file)
void fn_sub_207930_00207930(p3fes::EEContext&);             // (this file)
void fn_sub_207960_00207960(p3fes::EEContext&);             // (this file)
void fn_sub_30BC20_0030bc20(p3fes::EEContext&);             // item -> its kind's item id (battle_rest)
void fn_sub_3083F0_003083f0(p3fes::EEContext&);             // skill cost for a unit (unit +2604, skill) (battle_calc)
void fn_sub_3086F0_003086f0(p3fes::EEContext&);             // the unit can pay the skill (unit +2604, skill) (battle_calc)
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);             // (id, value) (ui2)
void fn_sub_222B90_00222b90(p3fes::EEContext&);             // command panel: skill window
void fn_sub_222D60_00222d60(p3fes::EEContext&);             // command panel: item window
void fn_sub_222ED0_00222ed0(p3fes::EEContext&);             // command panel: close the sub window
void fn_sub_2230E0_002230e0(p3fes::EEContext&);             // command panel: target window
void fn_sub_224860_00224860(p3fes::EEContext&);             // command panel: persona window
void fn_sub_225670_00225670(p3fes::EEContext&);             // command panel: tactics / analyze window
void fn_sub_249420_00249420(p3fes::EEContext&);             // item use preview (id, a, b)
void fn_sub_21B670_0021b670(p3fes::EEContext&);             // panel: analyze not available
void fn_sub_21C720_0021c720(p3fes::EEContext&);             // panel: the message handle of the support dialog
void fn_sub_2DBA80_002dba80(p3fes::EEContext&);             // navigator: stop talking
void fn_btlSupportRequestLine_002db9f0(p3fes::EEContext&);             // navigator: say (32, message)
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);             // yes/no dialog: open (handle)
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);             // yes/no dialog: question entry
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);             // yes/no dialog: answer entry
void fn_sub_201880_00201880(p3fes::EEContext&);             // (this file)
void fn_sub_2024B0_002024b0(p3fes::EEContext&);             // (this file)
void fn_sub_2025E0_002025e0(p3fes::EEContext&);             // (this file)
void fn_sub_203030_00203030(p3fes::EEContext&);             // (this file)
void fn_sub_2031C0_002031c0(p3fes::EEContext&);             // (this file)
void fn_sub_203990_00203990(p3fes::EEContext&);             // (this file)
void fn_sub_203C30_00203c30(p3fes::EEContext&);             // (this file)
void fn_sub_204760_00204760(p3fes::EEContext&);             // (this file)
void fn_sub_204CC0_00204cc0(p3fes::EEContext&);             // (this file)
void fn_sub_205D60_00205d60(p3fes::EEContext&);             // (this file)
void fn_sub_208570_00208570(p3fes::EEContext&);             // (this file)
void fn_sub_208790_00208790(p3fes::EEContext&);             // (this file)
void fn_sub_21F150_0021f150(p3fes::EEContext&);             // command panel: back to the top (word +36)
void fn_sub_21F410_0021f410(p3fes::EEContext&);             // command panel: draw the top menu
void fn_sub_221B60_00221b60(p3fes::EEContext&);             // command panel: draw the sub window
void fn_sub_222930_00222930(p3fes::EEContext&);             // command panel: open the item list
void fn_sub_222A60_00222a60(p3fes::EEContext&);             // command panel: open the skill list
void fn_sub_222FA0_00222fa0(p3fes::EEContext&);             // command panel: open the target list
void fn_sub_224660_00224660(p3fes::EEContext&);             // command panel: open the persona list
void fn_sub_2254A0_002254a0(p3fes::EEContext&);             // command panel: open the analyze list
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace gen = ::p3fes::recomp_gen;
using namespace bcm;

// The bodies: one member per replaced function, named after it (functions.json), on the Cpu view.
struct Body : Cpu {
    using Cpu::Cpu;

    // --- the font-line idioms of the builders -------------------------------------------------------------------------
    // `li a0, 1; jal frFontSetDefaultGlyphFlags; li a0, 2; jal frFontClearDefaultGlyphFlags` (jals at pc, pc + 12):
    // glyph flag 1 on, 2 off while the lines are built; glyphs_close() is the mirror image afterwards.
    void glyphs_open(u32 pc) {
        a0 = 1;
        jal(pc, &gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
        a0 = 2;
        jal(pc + 12, &gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    }
    void glyphs_close(u32 pc) {
        a0 = 1;
        jal(pc, &gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
        a0 = 2;
        jal(pc + 12, &gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    }
    // `a1 = 2; a2 = style; a3 = 0; t0 = 0; jal frFontBuildGlyphList` with the text already in $a0; the line in $v0.
    void build_line(u32 pc, u64 style) {
        a1 = 2;
        a2 = style;
        a3 = 0;
        t0 = 0;
        jal(pc, &gen::fn_frFontBuildGlyphList_003b0970);
    }
    // `mtc1 zero, $f12; a0 = line; jal sub_3B2C60; a0 = line; li a1, -1; jal frFontLineSetRgba` (jals at pc, pc + 16):
    // depth 0, opaque white.
    void line_finish(u32 pc, const Gpr& line) {
        mtc1_zero(12);
        a0 = line;
        jal(pc, &gen::fn_sub_3B2C60_003b2c60);
        a0 = line;
        a1 = si(-1);
        jal(pc + 16, &gen::fn_frFontLineSetRgba_003b0e20);
    }
    // `sll v0, i, 3; addu v0, v0, i; sll v0, v0, 1; addiu v0, v0, 280; sll a2, v0, 3; a0 = line; li a1, 1840;
    // jal frFontLineSetPos`: row i of a 4-row list at x 1840, y (280 + 18 i) * 8.
    void line_row_pos(u32 pc, const Gpr& i, const Gpr& line) {
        v0 = sll(i, 3);
        v0 = addu(v0, i);
        v0 = sll(v0, 1);
        v0 = addiu(v0, 280);
        a2 = sll(v0, 3);
        a0 = line;
        a1 = 1840;
        jal(pc, &gen::fn_frFontLineSetPos_003b0d70);
    }
    // `lw r, 0(w); ori/and r, ...; sw r, 0(w)` style updates of a flag word.
    void word_or(Gpr& r, const Gpr& w, s32 off, u32 bits) {
        lw(r, w, off);
        r = ori(r, bits);
        sw(r, w, off);
    }
    // `lw a0, off(w); li v1, ~bit; and v1, a0, v1; sw v1, off(w)`.
    void word_clear(const Gpr& w, s32 off, s32 mask) {
        lw(a0, w, off);
        v1 = si(mask);
        v1 = a0 & v1;
        sw(v1, w, off);
    }

    void sub_201AF0();
    void sub_2053C0();
    void sub_2054C0();
    void sub_205500();
    void sub_205550();
    void sub_2055A0();
    void sub_2055F0();
    void sub_205650();
    void operation_unless_debug(u32 debug_bit, u32 op_bit, u32 assert_pc);  // sub_2056A0 / 205700 / 205760
    void debug_set(u32 bit, u32 assert_pc);    // sub_2079C0 .. sub_207BA0
    void debug_clear(s32 mask, u32 assert_pc); // sub_207BF0 .. sub_207DD0
    void flag_test(u32 hi16, u32 assert_pc);   // sub_207F70 / 207FC0
    void flag_or(u32 hi16, u32 assert_pc);     // sub_2085E0 / 208680
    void flag_and(u32 hi16, u32 assert_pc);    // sub_208630 / 2086D0
    void sub_207930();
    void sub_207960();
    void sub_208010();
    void sub_208050();
    void sub_208130();
    void sub_2082C0();
    void sub_208360();
    void sub_2083D0();
    void sub_208570();
    void sub_208720();
    void sub_208790();
    void sub_208860();
    // the lists
    void sub_2024B0();
    void sub_202BC0();
    void sub_203030();
    void sub_203360();
    void sub_203760();
    void sub_203990();
    void sub_203B70();
    void sub_203DE0();
    void sub_204000();
    void sub_204760();
    void sub_204BE0();
    void sub_205000();
    void sub_206310();
    void sub_206EB0();
    void sub_201EF0();
    void sub_202C90();
    void sub_204AF0();
    void sub_205410();
    // the record's life
    void sub_1FFC60();
    void sub_201730();
    void sub_201780();
    // the help line and the window refreshers
    // `lw v1, 0(w); lui v0, 0x80; and v0, v1, v0; beqz 1f; nop` (5) `jal sub_208360; nop` (2) `1:` -- drop the old help line.
    void drop_help(const Gpr& w, u32 pc) {
        charge(5);
        lw(v1, w, kFlags);
        v0 = lui(0x80);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(2);
            jal(pc, &gen::fn_sub_208360_00208360);
        }
    }
    // `li a0, 100; move a1, a0; li a3, 2; li t0, 6; jal sub_3A5540; move a0, v0; jal sub_2082C0` with $f12, $a2, $t1, $t2
    // set by the caller: the help line at (100, 100, z) from message handle t1, entry t2, made current.
    void new_help(u32 pc_msg, u32 pc_set) {
        a0 = 100;
        a1 = a0;
        a3 = 2;
        t0 = 6;
        jal(pc_msg, &gen::fn_sub_3A5540_003a5540);
        a0 = v0;
        jal(pc_set, &gen::fn_sub_2082C0_002082c0);
    }
    void sub_201880();
    void sub_201AD0();
    void sub_202A10();
    void sub_203410();
    void sub_206170();
    void sub_206E40();
    void sub_207010();
    void sub_207E20();
    void sub_207F10();
    // the panel fillers
    void sub_2025E0();
    void sub_2031C0();
    void sub_203C30();
    void target_row_lines(bool absolute, u32 pc_assert, const u32 (&pcs)[6]);  // the row loop of sub_204CC0 / sub_205D60
    void open_analyze_tail(u32 pc_assert, u32 pc_open, u32 pc_sound, u64 cost);  // sub_207340's "analyze" exits
    void navi_say(u32 pc_stop, u32 message);                                     // sub_2DBA80(); btlSupportRequestLine(32, message)
    void yes_no(u32 pc, u32 question);                                           // msgWinRequestMessage(q); sub_3C74E0(q + 1)
    void sub_204CC0();
    void sub_205D60();
    void sub_2060B0();
    void sub_206F70();
    void sub_207340();
    void sub_2078A0();
    void sub_208460();
    // the list openers
    void reopen_windows(u32 pc_menu);  // sub_201880 + the open windows of every built list (sub_201B50 .. sub_201E00)
    void sub_2016B0();
    void sub_201A50();
    void sub_201B50();
    void sub_201C30();
    void sub_201D10();
    void sub_201E00();
    void sub_202010();
    void sub_202D70();
    void sub_203850();
    void sub_204480();
    void sub_2065A0();
    void sub_206740();
};

// =====================================================================================================================
// Queries on the bcm work
// =====================================================================================================================

// sub_201AF0 [bcmIsActive]: (+0 bit 0) || (+0 bit 29), as 0 / 1.
void Body::sub_201AF0() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x201B10);
    charge(6);
    lw(v0, gp, kGpWork);
    lw(v1, v0, kFlags);
    v0 = sltu(0, andi(v1, 0x1));
    if (v0 == 0) {
        charge(3);
        v0 = lui(0x2000);
        v0 = sltu(0, v1 & v0);
    }
    charge(4);
    pop(16, 0);
}

// sub_2053C0: +0 & 0x20.
void Body::sub_2053C0() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x2053E0);
    charge(7);
    lw(v0, gp, kGpWork);
    lw(v0, v0, kFlags);
    v0 = andi(v0, 0x20);
    pop(16, 0);
}

// sub_2054C0: the word at +36.
void Body::sub_2054C0() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x2054E0);
    charge(6);
    lw(v0, gp, kGpWork);
    lw(v0, v0, kWord36);
    pop(16, 0);
}

// sub_205500 [bcmGetSelectedSkill]: skills[cursor].id with the skill cursor at +30308 (8-byte rows at +44).
void Body::sub_205500() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x205520);
    charge(9);
    lw(v1, gp, kGpWork);
    lw(v0, v1, 30308);
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    lhu(v0, v0, kSkills);
    pop(16, 0);
}

// sub_205550 [bcmGetSelectedItem]: items[cursor] with the item cursor at +30360 (u16 at +156).
void Body::sub_205550() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x205570);
    charge(9);
    lw(v1, gp, kGpWork);
    lw(v0, v1, 30360);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    lhu(v0, v0, kItems);
    pop(16, 0);
}

// sub_2055A0 [bcmGetSelectedPersona]: personas[cursor].id with the persona cursor at +30412 (8-byte rows at +616).
void Body::sub_2055A0() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x2055C0);
    charge(9);
    lw(v1, gp, kGpWork);
    lw(v0, v1, 30412);
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    lhu(v0, v0, kPersonas);
    pop(16, 0);
}

// sub_2055F0 [bcmIsSkillUsableInBattle](skill): 0 for ids >= 464; else bit 1 of byte +1 of the skill's 44-byte row
// (the skill table at $gp-18680), as 0 / 1.
void Body::sub_2055F0() {
    enter(4);
    a0 = andi(a0, 0xFFFF);
    v0 = slti(a0, 464);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(12);
        lw(v1, gp, kGpSkillTable);
        v0 = sll(a0, 2);
        v0 = addu(v0, a0);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        v0 = sll(v0, 2);  // 44 * skill
        v0 = addu(v0, v1);
        lbu(v0, v0, 1);
        v0 = nor(v0, 0);
        v0 = andi(v0, 0x2);
        v0 = sltu(0, v0);
        v0 = xori(v0, 0x1);
    }
    charge(2);
}

// sub_205650 [bcmIsItemUsable](item): the item record's +4 kind is 0 or 1.
void Body::sub_205650() {
    enter(9);
    push(16, 0);
    a0 = sext_h(a0);
    jal(0x205660, &gen::fn_sub_170E90_00170e90);
    lw(v1, v0, 4);
    if (v1 != 0) {
        charge(3);
        v0 = 1;
        if (v1 != v0) {
            charge(3);
            v0 = 0;
            charge(4);
            pop(16, 0);
            return;
        }
    }
    charge(1);
    v0 = 1;
    charge(4);
    pop(16, 0);
}

// sub_2056A0 / sub_205700 / sub_205760: +12 |= op_bit unless the debug word +30624 has debug_bit.
void Body::operation_unless_debug(u32 debug_bit, u32 op_bit, u32 assert_pc) {
    enter(5);
    push(16, 0);
    need_work(v1, assert_pc);
    charge(5);
    lw(a0, gp, kGpWork);
    lw(v1, a0, kDebug);
    v1 = andi(v1, debug_bit);
    if (v1 == 0) {
        charge(3);
        lw(v1, a0, kOperation);
        v1 = ori(v1, op_bit);
        sw(v1, a0, kOperation);
    }
    charge(4);
    pop(16, 0);
}

// sub_2079C0 .. sub_207BA0: +30624 |= bit (the debug "OFF" / "ON" switches).
void Body::debug_set(u32 bit, u32 assert_pc) {
    enter(5);
    push(16, 0);
    need_work(v1, assert_pc);
    charge(8);
    lw(a0, gp, kGpWork);
    lw(v1, a0, kDebug);
    v1 = ori(v1, bit);
    sw(v1, a0, kDebug);
    pop(16, 0);
}

// sub_207BF0 .. sub_207DD0: +30624 &= mask.
void Body::debug_clear(s32 mask, u32 assert_pc) {
    enter(5);
    push(16, 0);
    need_work(v1, assert_pc);
    charge(9);
    lw(a1, gp, kGpWork);
    lw(a0, a1, kDebug);
    v1 = si(mask);
    v1 = a0 & v1;
    sw(v1, a1, kDebug);
    pop(16, 0);
}

// sub_207F70 / sub_207FC0: +0 & (hi16 << 16).
void Body::flag_test(u32 hi16, u32 assert_pc) {
    enter(5);
    push(16, 0);
    need_work(v0, assert_pc);
    charge(8);
    lw(v0, gp, kGpWork);
    lw(v1, v0, kFlags);
    v0 = lui(hi16);
    v0 = v1 & v0;
    pop(16, 0);
}

// sub_2085E0 / sub_208680: +0 |= hi16 << 16.
void Body::flag_or(u32 hi16, u32 assert_pc) {
    enter(5);
    push(16, 0);
    need_work(v1, assert_pc);
    charge(9);
    lw(a1, gp, kGpWork);
    lw(a0, a1, kFlags);
    v1 = lui(hi16);
    v1 = a0 | v1;
    sw(v1, a1, kFlags);
    pop(16, 0);
}

// sub_208630 / sub_2086D0: +0 &= (hi16 << 16) | 0xFFFF.
void Body::flag_and(u32 hi16, u32 assert_pc) {
    enter(5);
    push(16, 0);
    need_work(v1, assert_pc);
    charge(10);
    lw(a1, gp, kGpWork);
    lw(a0, a1, kFlags);
    v1 = lui(hi16);
    v1 = ori(v1, 0xFFFF);
    v1 = a0 & v1;
    sw(v1, a1, kFlags);
    pop(16, 0);
}

// sub_207930 [bcmIsNotKind12](item): sub_17D2E0(item & 0xFFFF) != 12.
void Body::sub_207930() {
    enter(11);
    push(16, 0);
    a0 = andi(a0, 0xFFFF);
    jal(0x20793C, &gen::fn_sub_17D2E0_0017d2e0);
    v0 = xori(v0, 0xC);
    v0 = sltu(0, v0);
    pop(16, 0);
}

// sub_207960 (item): asserts sub_17D2E0(item) != 12 (line 4850), then returns sub_17D2E0(item).
void Body::sub_207960() {
    enter(11);
    push(32, 1);
    s0 = a0;
    a0 = andi(s0, 0xFFFF);
    jal(0x207974, &gen::fn_sub_17D2E0_0017d2e0);
    v0 = xori(v0, 0xC);
    v0 = sltu(0, v0);
    check(v0 != 0, 0x207998, 4850);
    charge(8);
    a0 = andi(s0, 0xFFFF);
    jal(0x2079A4, &gen::fn_sub_17D2E0_0017d2e0);
    pop(32, 1);
}

// sub_208010: sub_30C0C0() ? sub_249650(*(u16*)result) : 0.
void Body::sub_208010() {
    enter(6);
    push(16, 0);
    jal(0x208018, &gen::fn_sub_30C0C0_0030c0c0);
    if (v0 != 0) {
        charge(6);
        lhu(a0, v0, 0);
        jal(0x20802C, &gen::fn_sub_249650_00249650);
    } else {
        charge(1);
        v0 = 0;
    }
    charge(4);
    pop(16, 0);
}

// sub_208050 [bcmIsBossFirstTime]: encounters 466..469 -> 1 while their flag 4871..4874 is clear, else 0.
void Body::sub_208050() {
    enter(7);
    push(16, 0);
    jal(0x208058, &gen::fn_btlGetEncounterId_002d5550);
    v1 = 469;
    u32 flag = 0, pc = 0;
    if (v0 == v1) {
        flag = 4874, pc = 0x2080FC;
    } else {
        charge(3);
        v1 = 468;
        if (v0 == v1) {
            flag = 4873, pc = 0x2080DC;
        } else {
            charge(3);
            v1 = 467;
            if (v0 == v1) {
                flag = 4872, pc = 0x2080BC;
            } else {
                charge(3);
                v1 = 466;
                if (v0 == v1) flag = 4871, pc = 0x20809C;
                else charge(2);
            }
        }
    }
    bool first = false;
    if (flag != 0) {
        charge(5);
        a0 = flag;
        jal(pc, &gen::fn_datGetFlag_0016f190);
        first = v0 == 0;
    }
    if (first) {
        charge(3);
        v0 = 1;
    } else {
        charge(1);
        v0 = 0;
    }
    charge(4);
    pop(16, 0);
}

// sub_208130 [bcmCanCallSupport]: 1 when the navigator (pc 3, or 9 in The Answer) is present, flag 223 (not in The
// Answer) and flag 4870 are clear, the battle root's +12 has no 0x200000, and the navigator's sub_16C970 flags (low 20
// bits) are none of the single bits 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80000, 0x100000. Otherwise 0.
void Body::sub_208130() {
    enter(6);
    push(16, 0);
    jal(0x208138, &gen::fn_sub_17D800_0017d800);
    bool present;
    if (v0 == 0) {
        charge(5);
        a0 = 3;
        jal(0x20814C, &gen::fn_sub_1FF7F0_001ff7f0);
    } else {
        charge(5);
        a0 = 9;
        jal(0x20816C, &gen::fn_sub_1FF7F0_001ff7f0);
    }
    present = v0 != 0;
    const auto no = [&] {  // `move v0, zero; b epilogue`
        charge(3);
        v0 = 0;
        charge(4);
        pop(16, 0);
    };
    if (!present) return no();
    charge(4);
    jal(0x208188, &gen::fn_sub_17D800_0017d800);
    if (v0 == 0) {
        charge(5);
        a0 = 223;
        jal(0x20819C, &gen::fn_datGetFlag_0016f190);
        if (v0 != 0) return no();
    }
    charge(5);
    a0 = 4870;
    jal(0x2081BC, &gen::fn_datGetFlag_0016f190);
    if (v0 != 0) return no();
    charge(6);
    lw(v0, gp, kGpBattle);
    lw(v1, v0, 12);
    v0 = lui(0x20);
    v0 = v1 & v0;
    if (v0 != 0) return no();
    charge(4);
    jal(0x2081FC, &gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        charge(7);
        a0 = 9;
        jal(0x208210, &gen::fn_sub_16C970_0016c970);
    } else {
        charge(5);
        a0 = 3;
        jal(0x20822C, &gen::fn_sub_16C970_0016c970);
    }
    a0 = core::dsrl32(dsll32(v0, 12), 12);  // the low 20 bits
    charge(3);
    v0 = 1;
    bool single = a0 == v0;
    const u64 bits[] = {2, 4, 8, 16, 32, 64};
    for (std::size_t i = 0; !single && i < 6; ++i) {
        charge(3);
        v1 = bits[i];
        single = a0 == v1;
    }
    if (!single) {
        charge(3);
        v1 = lui(0x8);
        single = a0 == v1;
    }
    if (!single) {
        charge(3);
        v1 = lui(0x10);
        single = a0 == v1;
    }
    if (single) {
        charge(1);
        v0 = 0;
    }
    charge(4);
    pop(16, 0);
}

// sub_2082C0 [bcmSetHelpLine](line): asserts the help line is not built (line 5094), +30620 = +27936 = line,
// +0 |= 0x800000.
void Body::sub_2082C0() {
    enter(8);
    push(48, 2);
    s1 = a0;
    need_work(v1, 0x2082EC);
    charge(7);
    lw(s0, gp, kGpWork);
    lw(v1, s0, kFlags);
    a0 = nor(v1, 0);
    v1 = lui(0x80);
    v1 = a0 & v1;
    check(v1 != 0, 0x20831C, 5094);
    charge(12);
    sw(s1, s0, kHelpLine);
    sw(s1, s0, kHelpText);
    lw(a0, s0, kFlags);
    v1 = lui(0x80);
    v1 = a0 | v1;
    sw(v1, s0, kFlags);
    pop(48, 2);
}

// sub_208360 [bcmReleaseHelpLineChecked]: asserts the help line is built (line 5105), then sub_2083D0.
void Body::sub_208360() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x208380);
    charge(6);
    lw(v0, gp, kGpWork);
    lw(v1, v0, kFlags);
    v0 = lui(0x80);
    v0 = v1 & v0;
    check(v0 != 0, 0x2083AC, 5105);
    charge(6);
    jal(0x2083B4, &gen::fn_sub_2083D0_002083d0);
    pop(16, 0);
}

// sub_2083D0 [bcmReleaseHelpLine]: asserts the help line is built (line 5113), releases it, +0 &= ~0x800000.
void Body::sub_2083D0() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x2083F4);
    charge(6);
    lw(s0, gp, kGpWork);
    lw(v1, s0, kFlags);
    v0 = lui(0x80);
    v0 = v1 & v0;
    check(v0 != 0, 0x208420, 5113);
    charge(13);
    lw(a0, s0, kHelpLine);
    jal(0x20842C, &gen::fn_sub_3B0170_003b0170);
    lw(a0, s0, kFlags);
    v1 = lui(0xFF7F);
    v1 = ori(v1, 0xFFFF);
    v1 = a0 & v1;
    sw(v1, s0, kFlags);
    pop(32, 1);
}

// sub_208570 [bcmInitCursorRecord](rec): a list's cursor record (+30296 skills, +30348 items, +30400 personas,
// +30452 targets, +30556 analyze): rec+0 |= 4; the 8 RGB triples at rec+20 cleared; the alpha bytes
// +23 / +27 / +39 / +43 = 0 and +31 / +35 / +47 / +51 = 5.
void Body::sub_208570() {
    enter(6);
    lw(v1, a0, 0);
    v1 = ori(v1, 0x4);
    sw(v1, a0, 0);
    a1 = 0;
    for (;;) {
        charge(3);
        v1 = slti(a1, 8);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v1 = sll(a1, 2);
        v1 = addu(a0, v1);
        sb(zero, v1, 20);
        sb(zero, v1, 21);
        sb(zero, v1, 22);
        a1 = addiu(a1, 1);
    }
    charge(11);
    sb(zero, a0, 23);
    sb(zero, a0, 27);
    v1 = 5;
    sb(v1, a0, 31);
    sb(v1, a0, 35);
    sb(zero, a0, 43);
    sb(zero, a0, 39);
    sb(v1, a0, 51);
    sb(v1, a0, 47);
}

// sub_208720 [bcmIsTopLevel]: +16 == 0 && !(+0 & 0x20), as 0 / 1.
void Body::sub_208720() {
    enter(5);
    push(16, 0);
    need_work(v0, 0x208740);
    charge(4);
    lw(v1, gp, kGpWork);
    lw(v0, v1, kListKind);
    bool yes = false;
    if (v0 == 0) {
        charge(5);
        lw(v0, v1, kFlags);
        v0 = nor(v0, 0);
        v0 = andi(v0, 0x20);
        yes = v0 != 0;
    }
    if (yes) {
        charge(3);
        v0 = 1;
    } else {
        charge(1);
        v0 = 0;
    }
    charge(4);
    pop(16, 0);
}

// sub_208790 [bcmNaviCommentRandomMember]: the party members among the target rows (kind 1) go into a u32[] at sp+32;
// one is picked with RpRandom() % n and handed to sub_208860. The row walk takes the first +936 rows.
void Body::sub_208790() {
    enter(6);
    push(48, 1);
    need_work(v0, 0x2087B4);
    charge(7);
    lw(a2, gp, kGpWork);
    s0 = 0;
    a3 = 0;
    lw(a1, a2, kTargetCount);
    a0 = 1;
    for (;;) {
        charge(3);
        v0 = slt(a3, a1);
        if (v0 == 0) break;
        backedge();
        charge(8);
        v0 = sll(a3, 1);
        v0 = addu(v0, a3);
        v0 = sll(v0, 3);
        v0 = addu(a2, v0);
        v1 = addiu(v0, kTargets);
        lw(v0, v0, kTargets + kRowKind);
        if (v0 == a0) {
            charge(5);
            lhu(v1, v1, kRowPcId);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            sw(v1, v0, 32);
            s0 = addiu(s0, 1);
        } else {
            charge(2);
        }
        charge(1);
        a3 = addiu(a3, 1);
    }
    charge(14);
    jal(0x208824, &gen::fn_sub_488F30_00488f30);
    rt::divu(c, v0.r, s0.r);
    rt::mfhi(c, v0.r);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    lhu(a0, v0, 32);
    jal(0x208840, &gen::fn_sub_208860_00208860);
    pop(48, 1);
}

// sub_208860 [bcmNaviCommentMember](pc id): unless the member's sub_16C970 flags have any of 0x80371, the navigator
// comments on the member (ids 2..10 through the jump table 0x7B73B0): sub_2DDC10(id) picks the "again" line, the
// message pairs are 162/163, 243/244, 344/345, 417/418, 490/491, 563/564, 701/702; id 6 asserts (line 5274);
// id 9 says 633, or 1131 in The Answer.
void Body::sub_208860() {
    enter(13);
    push(32, 1);
    s0 = a0;
    a0 = sext_h(s0);
    jal(0x208878, &gen::fn_sub_16C970_0016c970);
    v1 = lui(0x8);
    v1 = ori(v1, 0x371);
    v1 = v0 & v1;
    const auto done = [&] {
        charge(5);
        pop(32, 1);
    };
    if (v1 != 0) return done();
    charge(4);
    v1 = andi(s0, 0xFFFF);
    at = sltiu(v1, 11);
    if (at == 0) return done();
    charge(7);
    a0 = sx(0x7B73B0u);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    // A member line: sub_2DDC10(id) ? again : first. Each line block ends `b epilogue` (5), except the last case's
    // "again" block, which falls through into the epilogue (3).
    const auto line = [&](u32 pc_check, u32 first, u32 again, u64 again_cost = 5) {
        charge(5);
        a0 = s0;
        jal(pc_check, &gen::fn_sub_2DDC10_002ddc10);
        charge(v0 == 0 ? 5 : again_cost);
        a0 = v0 == 0 ? first : again;
        jal(v0 == 0 ? pc_check + 0x14 : pc_check + 0x28, &gen::fn_sub_2DDBA0_002ddba0);
    };
    const u32 target = static_cast<u32>(v1);
    switch (target) {
    case 0x208AB0u: break;
    case 0x2088C0u: line(0x2088C4, 162, 163); break;
    case 0x2088FCu: line(0x208900, 243, 244); break;
    case 0x208938u: line(0x20893C, 344, 345); break;
    case 0x208974u: line(0x208978, 417, 418); break;
    case 0x2089B0u:
        charge(7);
        k_assert(0x2089BC, 5274);
        break;
    case 0x2089CCu: line(0x2089D0, 490, 491); break;
    case 0x208A08u: line(0x208A0C, 563, 564); break;
    case 0x208A44u:
        charge(4);
        jal(0x208A44, &gen::fn_sub_17D800_0017d800);
        charge(5);
        a0 = v0 == 0 ? 633 : 1131;
        jal(v0 == 0 ? 0x208A58 : 0x208A6C, &gen::fn_sub_2DDBA0_002ddba0);
        break;
    case 0x208A7Cu: line(0x208A80, 701, 702, 3); break;
    default: rt::lookup_func(target)(c); return;
    }
    done();
}

// =====================================================================================================================
// The lists: builders (font lines + their "built" bit in +0) and releasers
// =====================================================================================================================

// sub_2024B0 [bcmBuildSkillLines]: one line per skill (+112 of them) from datGetSkillName, the first in style 6
// (highlighted), at depth 0 in white; +0 |= 2.
void Body::sub_2024B0() {
    enter(8);
    push(64, 3);
    need_work(v0, 0x2024DC);
    charge(10);
    lw(s0, gp, kGpWork);
    glyphs_open(0x2024EC);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, kSkillCount);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(2);
        if (s1 == 0) {
            charge(3);
            s2 = 6;
        } else {
            charge(1);
            s2 = 0;
        }
        charge(26);
        v0 = sll(s1, 3);
        v0 = addu(s0, v0);
        lhu(a0, v0, kSkills);
        jal(0x202530, &gen::fn_datGetSkillName_0030bb40);
        a0 = v0;
        build_line(0x202550, sext_b(s2));
        s2 = v0;
        line_finish(0x202564, s2);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        sw(s2, v0, kSkillLines);
        s1 = addiu(s1, 1);
    }
    charge(16);
    glyphs_close(0x2025A0);
    word_or(v1, s0, kFlags, 0x2);
    pop(64, 3);
}

// sub_202BC0 [bcmReleaseSkillLines]: asserts bit 2 (line 2320), releases the skill lines and, with bit 0x20, the title
// line +136; +0 &= ~2.
void Body::sub_202BC0() {
    enter(7);
    push(48, 2);
    need_work(v1, 0x202BE8);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(v1, s0, kFlags);
    v1 = andi(v1, 0x2);
    check(v1 != 0, 0x202C10, 2320);
    charge(3);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, kSkillCount);
        v1 = slt(s1, v1);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kSkillLines);
        jal(0x202C30, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    charge(4);
    lw(v1, s0, kFlags);
    v1 = andi(v1, 0x20);
    if (v1 != 0) {
        charge(3);
        lw(a0, s0, kSkillTitle);
        jal(0x202C60, &gen::fn_sub_3B0170_003b0170);
    }
    charge(10);
    word_clear(s0, kFlags, -3);
    pop(48, 2);
}

// sub_203030 [bcmBuildItemLines]: up to 4 rows (and +608) of item names (sub_171110(item, 0)), the first in style 6,
// at row positions; +604 = the rows built; +0 |= 4.
void Body::sub_203030() {
    enter(8);
    push(64, 3);
    need_work(v0, 0x20305C);
    charge(10);
    lw(s1, gp, kGpWork);
    glyphs_open(0x20306C);
    s2 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s2, 4);
        if (v0 == 0) break;
        backedge();
        charge(4);
        lw(v0, s1, kItemCount);
        at = slt(s2, v0);
        if (at == 0) break;
        charge(2);
        const bool first = s2 == 0;
        charge(first ? 16 : 14);
        v0 = sll(s2, 1);
        v0 = addu(s1, v0);
        lh(a0, v0, kItems);
        a1 = 0;
        jal(first ? 0x2030B4 : 0x2030F4, &gen::fn_sub_171110_00171110);
        a0 = v0;
        build_line(first ? 0x2030D0 : 0x203110, first ? 6 : 0);
        s0 = v0;
        charge(21);
        line_row_pos(0x203138, s2, s0);
        line_finish(0x203148, s0);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        sw(s0, v0, kItemLines);
        s2 = addiu(s2, 1);
    }
    charge(17);
    sw(s2, s1, kItemLineCount);
    glyphs_close(0x203184);
    word_or(v1, s1, kFlags, 0x4);
    pop(64, 3);
}

// sub_203360 [bcmReleaseItemLines]: releases the +604 item lines and, with bit 0x20, the title line +612;
// +0 &= ~4.
void Body::sub_203360() {
    enter(7);
    push(48, 2);
    need_work(v1, 0x203388);
    charge(4);
    lw(s0, gp, kGpWork);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, kItemLineCount);
        v1 = slt(s1, v1);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kItemLines);
        jal(0x2033AC, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    charge(4);
    lw(v1, s0, kFlags);
    v1 = andi(v1, 0x20);
    if (v1 != 0) {
        charge(3);
        lw(a0, s0, kItemTitle);
        jal(0x2033DC, &gen::fn_sub_3B0170_003b0170);
    }
    charge(10);
    word_clear(s0, kFlags, -5);
    pop(48, 2);
}

// sub_203760 [bcmCheckPersonaAvailable]: walks the persona stock (sub_1756F0 entries, sub_174A90(i)) for one whose id
// differs from the protagonist's current persona; none -> +0 |= 0x400 (PERSONA greyed out), else the persona operation
// +12 |= 8 unless the debug switch "PERSONA OFF" (+30624 & 8).
void Body::sub_203760() {
    enter(9);
    push(80, 4);
    need_work(v0, 0x203790);
    charge(11);
    lw(s0, gp, kGpWork);
    jal(0x20379C, &gen::fn_sub_1756F0_001756f0);
    s2 = andi(v0, 0xFFFF);
    a0 = 1;
    jal(0x2037AC, &gen::fn_datPersonaGetByPcId_00174800);
    lhu(s1, v0, 2);
    s3 = 0;
    for (;;) {
        charge(3);
        v1 = slt(s3, s2);
        if (v1 == 0) break;
        backedge();
        charge(7);
        a0 = sext_h(s3);
        jal(0x2037CC, &gen::fn_sub_174A90_00174a90);
        lhu(v1, v0, 2);
        if (v1 != s1) break;
        charge(1);
        s3 = addiu(s3, 1);
    }
    charge(2);
    if (s3 == s2) {
        charge(5);
        word_or(v1, s0, kFlags, 0x400);
    } else {
        charge(4);
        lw(v1, s0, kDebug);
        v1 = andi(v1, 0x8);
        if (v1 == 0) {
            charge(3);
            word_or(v1, s0, kOperation, 0x8);
        }
    }
    charge(8);
    pop(80, 4);
}

// sub_203990 [bcmBuildPersonaLines]: the persona list -- the current persona first ({id, level} at +616 / +620), then
// every stock persona with another id; +732 = +728 = the count, +728 capped at 4 rows; one line per row from the
// persona name (sub_173220), style 6, at row positions; +0 |= 8.
void Body::sub_203990() {
    enter(10);
    push(96, 5);
    need_work(v0, 0x2039C4);
    charge(16);
    lw(s2, gp, kGpWork);
    jal(0x2039D0, &gen::fn_sub_1756F0_001756f0);
    s1 = andi(v0, 0xFFFF);
    s3 = 0;
    a0 = 1;
    jal(0x2039E4, &gen::fn_datPersonaGetByPcId_00174800);
    lhu(s0, v0, 2);
    sh(s0, s2, kPersonas);
    lbu(v0, v0, 4);
    sw(v0, s2, kPersonas + 4);
    s3 = addiu(s3, 1);
    s4 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s4, s1);
        if (v0 == 0) break;
        backedge();
        charge(7);
        a0 = sext_h(s4);
        jal(0x203A14, &gen::fn_sub_174A90_00174a90);
        lhu(a0, v0, 2);
        if (a0 != s0) {
            charge(6);
            v1 = sll(s3, 3);
            v1 = addu(s2, v1);
            sh(a0, v1, kPersonas);
            lbu(v0, v0, 4);
            sw(v0, v1, kPersonas + 4);
            s3 = addiu(s3, 1);
        }
        charge(1);
        s4 = addiu(s4, 1);
    }
    charge(5);
    sw(s3, s2, kPersonaCount);
    sw(s3, s2, kPersonaLineCount);
    at = slti(s3, 5);
    if (at == 0) {
        charge(2);
        v0 = 4;
        sw(v0, s2, kPersonaLineCount);
    }
    charge(9);
    glyphs_open(0x203A70);
    s0 = 0;
    for (;;) {
        charge(4);
        lw(v0, s2, kPersonaLineCount);
        v0 = slt(s0, v0);
        if (v0 == 0) break;
        backedge();
        charge(34);
        v0 = sll(s0, 3);
        v0 = addu(s2, v0);
        lhu(a0, v0, kPersonas);
        jal(0x203A9C, &gen::fn_sub_173220_00173220);
        a0 = v0;
        build_line(0x203AB8, 6);
        s1 = v0;
        line_row_pos(0x203AE0, s0, s1);
        line_finish(0x203AF0, s1);
        v0 = sll(s0, 2);
        v0 = addu(s2, v0);
        sw(s1, v0, kPersonaLines);
        s0 = addiu(s0, 1);
    }
    charge(18);
    glyphs_close(0x203B2C);
    word_or(v1, s2, kFlags, 0x8);
    pop(96, 5);
}

// sub_203B70 [bcmReleasePersonaLines]: asserts bit 8 (line 2806), releases the +728 persona lines; +0 &= ~8.
void Body::sub_203B70() {
    enter(7);
    push(48, 2);
    need_work(v1, 0x203B98);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(v1, s0, kFlags);
    v1 = andi(v1, 0x8);
    check(v1 != 0, 0x203BC0, 2806);
    charge(3);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, kPersonaLineCount);
        v1 = slt(s1, v1);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kPersonaLines);
        jal(0x203BE0, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    charge(10);
    word_clear(s0, kFlags, -9);
    pop(48, 2);
}

// sub_203DE0 [bcmRefreshPersonaLines]: releases the persona lines and rebuilds the visible window (first row +30404):
// the row under the cursor (+30412) and the current persona in style 6; the current persona's row is coloured
// 0xFFE678FF when it is under the cursor, else 0x785A28FF; other rows white.
void Body::sub_203DE0() {
    enter(9);
    push(80, 4);
    need_work(v0, 0x203E10);
    charge(8);
    lw(s1, gp, kGpWork);
    a0 = 1;
    jal(0x203E20, &gen::fn_datPersonaGetByPcId_00174800);
    lhu(s0, v0, 2);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kPersonaLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        lw(a0, v0, kPersonaLines);
        jal(0x203E44, &gen::fn_sub_3B0170_003b0170);
        s2 = addiu(s2, 1);
    }
    charge(10);
    glyphs_open(0x203E64);
    s2 = 0;
    s0 = andi(s0, 0xFFFF);
    for (;;) {
        charge(4);
        lw(v0, s1, kPersonaLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(5);
        lw(v1, s1, 30404);
        lw(v0, s1, 30412);
        v0 = subu(v0, v1);
        if (s2 == v0) {
            charge(3);
            s3 = 6;
        } else {
            charge(1);
            s3 = 0;
        }
        charge(6);
        v0 = addu(s2, v1);
        v0 = sll(v0, 3);
        v0 = addu(s1, v0);
        lhu(a0, v0, kPersonas);
        if (a0 == s0) {
            charge(1);
            s3 = 6;
        }
        charge(31);
        jal(0x203EC8, &gen::fn_sub_173220_00173220);
        a0 = v0;
        build_line(0x203EE8, sext_b(s3));
        s3 = v0;
        line_row_pos(0x203F10, s2, s3);
        mtc1_zero(12);
        a0 = s3;
        jal(0x203F20, &gen::fn_sub_3B2C60_003b2c60);
        lw(v1, s1, 30404);
        v0 = addu(s2, v1);
        v0 = sll(v0, 3);
        v0 = addu(s1, v0);
        lhu(v0, v0, kPersonas);
        if (v0 == s0) {
            charge(4);
            lw(v0, s1, 30412);
            v0 = subu(v0, v1);
            charge(7);
            a0 = s3;
            if (s2 == v0) {
                v0 = lui(0xFFE6);
                a1 = ori(v0, 0x78FF);
                jal(0x203F60, &gen::fn_frFontLineSetRgba_003b0e20);
            } else {
                v0 = lui(0x785A);
                a1 = ori(v0, 0x28FF);
                jal(0x203F7C, &gen::fn_frFontLineSetRgba_003b0e20);
            }
        } else {
            charge(4);
            a0 = s3;
            a1 = si(-1);
            jal(0x203F94, &gen::fn_frFontLineSetRgba_003b0e20);
        }
        charge(4);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        sw(s3, v0, kPersonaLines);
        s2 = addiu(s2, 1);
    }
    charge(14);
    glyphs_close(0x203FC0);
    pop(80, 4);
}

// sub_204000 [bcmBuildTargetRows]: the tactics rows. From the battle root's unit list (+336, next at +2612) every unit
// with bit 3 of +156 except the protagonist (pc id 1, the u16 at +2 of its +2604 record) is noted on the stack frame:
// unit +168 (sp+128), pc id (sp+120), tactic sub_16DD80(id) (sp+112). The members that obey orders are counted through
// the jump table 0x7B7350 by pc id (Orgia Mode, tactic 10, does not count for id 3, nor for id 9 in The Answer; id 1
// asserts, line 2991). Two or more -> row 0 is "All Members" (kind 0). Then one kind-1 row per member {unit, id,
// tactic; bit 1 when in Orgia Mode}. The target bits 0x4000 / 0x8000 / 0x10000 / 0x20000 / 0x40000 / 0x80000 /
// 0x100000 / 0x200000 are cleared; in menu modes 0 / 1 the support side states (btlSupportTestFlag(2 / 1 / 0)), flag 4864 and
// sub_2DB480 set them again and a "Support" row (kind 2) follows, sub_2DB480 & 0xFFFF in +30640. +936 = rows, +940 =
// rows capped at 7. Unless the debug switch 0x40: rows -> +12 |= 4, none -> +0 |= 0x200.
void Body::sub_204000() {
    enter(11);
    push(144, 6);
    need_work(v1, 0x204038);
    charge(7);
    lw(s1, gp, kGpWork);
    lw(s0, gp, kGpBattle);
    lw(v1, s1, kFlags);
    v1 = nor(v1, 0);
    v1 = andi(v1, 0x10);
    check(v1 != 0, 0x204068, 2949);
    charge(4);
    s3 = 0;
    lw(s0, s0, 336);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(5);
        lw(v1, s0, 156);
        v1 = nor(v1, 0);
        v1 = andi(v1, 0x8);
        if (v1 == 0) {
            charge(5);
            lw(v1, s0, 2604);
            lhu(a0, v1, 2);
            v1 = 1;
            if (a0 != v1) {
                charge(14);
                lw(v1, s0, 168);
                v0 = sll(s3, 2);
                v0 = addu(v0, sp);
                sw(v1, v0, 128);
                s2 = sll(s3, 1);
                v0 = addu(s2, sp);
                sh(a0, v0, 120);
                a0 = sext_h(a0);
                jal(0x2040CC, &gen::fn_sub_16DD80_0016dd80);
                v1 = addu(s2, sp);
                sh(v0, v1, 112);
                s3 = addiu(s3, 1);
            }
        }
        charge(1);
        lw(s0, s0, 2612);
    }
    charge(4);
    s2 = 0;
    s4 = 0;
    for (;;) {
        charge(3);
        v1 = slt(s4, s3);
        if (v1 == 0) break;
        backedge();
        charge(7);
        s5 = sll(s4, 1);
        a1 = addu(s5, sp);
        v1 = addiu(a1, 120);
        lhu(s0, v1, 0);
        at = sltiu(s0, 11);
        bool counts = true;  // falls into `s2++`
        if (at != 0) {
            charge(7);
            a0 = sx(0x7B7350u);
            v1 = sll(s0, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            const u32 target = static_cast<u32>(v1);
            switch (target) {
            case 0x204198u: break;
            case 0x204134u:  // ids 2, 4..10: Orgia Mode of id 9 in The Answer does not count
                charge(4);
                jal(0x204134, &gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                    charge(3);
                    v1 = 9;
                    if (s0 == v1) {
                        charge(5);
                        v1 = addu(s5, sp);
                        lhu(a0, v1, 112);
                        v1 = 10;
                        if (a0 == v1) {
                            charge(2);
                            counts = false;
                        }
                    }
                }
                break;
            case 0x20416Cu:  // id 1: the protagonist is never a row
                charge(7);
                k_assert(0x204178, 2991);
                break;
            case 0x204188u:  // id 3: Orgia Mode does not count
                charge(4);
                lhu(a0, a1, 112);
                v1 = 10;
                if (a0 == v1) counts = false;
                break;
            default: rt::lookup_func(target)(c); return;
            }
        }
        if (counts) {
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(1);
        s4 = addiu(s4, 1);
    }
    charge(4);
    s0 = 0;
    v1 = slti(s2, 2);
    if (v1 == 0) {  // "All Members"
        charge(3);
        sw(zero, s1, kTargets + kRowFlags);
        sw(zero, s1, kTargets + kRowKind);
        s0 = addiu(s0, 1);
    }
    charge(5);
    t1 = 0;
    a2 = 1;
    a0 = 10;
    for (;;) {
        charge(3);
        v1 = slt(t1, s3);
        if (v1 == 0) break;
        backedge();
        charge(20);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        v1 = sll(v1, 3);
        t0 = addu(s1, v1);
        a3 = addiu(t0, kTargets);
        sw(zero, t0, kTargets + kRowFlags);
        sw(a2, t0, kTargets + kRowKind);
        v1 = sll(t1, 2);
        v1 = addu(v1, sp);
        lw(v1, v1, 128);
        sw(v1, t0, kTargets + kRowUnit);
        v1 = sll(t1, 1);
        a1 = addu(v1, sp);
        lhu(v1, a1, 120);
        sh(v1, t0, kTargets + kRowPcId);
        v1 = addiu(a1, 112);
        lhu(v1, v1, 0);
        sw(v1, t0, kTargets + kRowTactic);
        if (v1 == a0) {
            charge(3);
            word_or(v1, a3, 0, 0x2);
        }
        charge(2);
        s0 = addiu(s0, 1);
        t1 = addiu(t1, 1);
    }
    charge(28);
    lw(a0, s1, kFlags);
    v1 = si(-16385);
    a0 = a0 & v1;
    sw(a0, s1, kFlags);
    for (u32 hi : {0xFFFFu, 0xFFFEu, 0xFFFDu, 0xFFFBu}) {
        v1 = ori(lui(hi), hi == 0xFFFFu ? 0x7FFF : 0xFFFF);
        a0 = a0 & v1;
        sw(a0, s1, kFlags);
    }
    v1 = ori(lui(0xFFF7), 0xFFFF);
    v1 = a0 & v1;
    sw(v1, s1, kFlags);
    lw(a0, s1, kMode);
    v1 = 2;
    bool support = false;
    if (a0 != v1) {
        charge(3);
        v1 = 1;
        if (a0 == v1) {
            support = true;
        } else {
            charge(2);
            if (a0 == 0) support = true;
            else charge(2);
        }
    }
    if (support) {
        charge(5);
        a0 = 2;
        jal(0x2042DC, &gen::fn_btlSupportTestFlag_002db450);
        if (v0 != 0) {
            charge(6);
            lw(v0, s1, kFlags);
            v1 = ori(v0, 0x4000);
            sw(v1, s1, kFlags);
            v0 = lui(0x2);
            v0 = v1 | v0;
            sw(v0, s1, kFlags);
        }
        charge(5);
        a0 = 1;
        jal(0x204308, &gen::fn_btlSupportTestFlag_002db450);
        if (v0 != 0) {
            charge(6);
            lw(v0, s1, kFlags);
            v1 = ori(v0, 0x8000);
            sw(v1, s1, kFlags);
            v0 = lui(0x4);
            v0 = v1 | v0;
            sw(v0, s1, kFlags);
        }
        charge(5);
        a0 = 0;
        jal(0x204334, &gen::fn_btlSupportTestFlag_002db450);
        if (v0 != 0) {
            charge(7);
            lw(v1, s1, kFlags);
            v0 = lui(0x1);
            v1 = v1 | v0;
            sw(v1, s1, kFlags);
            v0 = lui(0x8);
            v0 = v1 | v0;
            sw(v0, s1, kFlags);
        }
        charge(10);
        lw(v1, s1, kFlags);
        v0 = ori(lui(0xFFEF), 0xFFFF);
        v0 = v1 & v0;
        sw(v0, s1, kFlags);
        a0 = 4864;
        jal(0x204378, &gen::fn_datGetFlag_0016f190);
        if (v0 != 0) {
            charge(4);
            lw(v1, s1, kFlags);
            v0 = lui(0x10);
            v0 = v1 | v0;
            sw(v0, s1, kFlags);
        }
        charge(9);
        lw(v1, s1, kFlags);
        v0 = ori(lui(0xFFDF), 0xFFFF);
        v0 = v1 & v0;
        sw(v0, s1, kFlags);
        jal(0x2043AC, &gen::fn_sub_2DB480_002db480);
        if (v0 != 0) {
            charge(4);
            lw(v1, s1, kFlags);
            v0 = lui(0x20);
            v0 = v1 | v0;
            sw(v0, s1, kFlags);
        }
        charge(12);
        jal(0x2043CC, &gen::fn_sub_2DB480_002db480);
        v1 = andi(v0, 0xFFFF);
        sw(v1, s1, kSupportState);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        v1 = sll(v1, 3);
        a0 = addu(v1, s1);
        sw(zero, a0, kTargets + kRowFlags);
        v1 = 2;
        sw(v1, a0, kTargets + kRowKind);
        s0 = addiu(s0, 1);
    }
    charge(5);
    sw(s0, s1, kTargetCount);
    sw(s0, s1, kTargetLineCount);
    at = slti(s0, 8);
    if (at == 0) {
        charge(2);
        v1 = 7;
        sw(v1, s1, kTargetLineCount);
    }
    charge(4);
    lw(v1, s1, kDebug);
    v1 = andi(v1, 0x40);
    if (v1 == 0) {
        charge(2);
        if (s0 != 0) {
            charge(5);
            word_or(v1, s1, kOperation, 0x4);
        } else {
            charge(3);
            word_or(v1, s1, kFlags, 0x200);
        }
    }
    charge(10);
    pop(144, 6);
}

// sub_204760 [bcmBuildTargetLines]: asserts bit 0x10 is clear (line 3234); for each of the +940 visible rows two lines
// at +880 / +884: kind 0 -> "All Members" (no second line); kind 1 -> the member's name (sub_177790) and the tactic
// name (0x684F00[tactic - 1]); kind 2 -> the navigator's name (sub_177790(4), or 6 in menu mode 1; mode 2 asserts,
// line 3286, and keeps the previous line) and "Support". The row under the cursor (+30464 == +30456 + i) is in style
// 6. +0 |= 0x10.
void Body::sub_204760() {
    enter(11);
    push(112, 6);
    need_work(v0, 0x204798);
    charge(6);
    lw(s2, gp, kGpWork);
    lw(v0, s2, kFlags);
    v0 = nor(v0, 0);
    v0 = andi(v0, 0x10);
    check(v0 != 0, 0x2047C4, 3234);
    charge(9);
    glyphs_open(0x2047D0);
    s4 = 0;
    for (;;) {
        charge(4);
        lw(v0, s2, kTargetLineCount);
        v0 = slt(s4, v0);
        if (v0 == 0) break;
        backedge();
        charge(10);
        v0 = sll(s4, 1);
        v0 = addu(v0, s4);
        v0 = sll(v0, 3);
        v0 = addu(s2, v0);
        s1 = addiu(v0, kTargets);
        lw(v1, s2, 30464);
        lw(v0, s2, 30456);
        v0 = addu(s4, v0);
        if (v1 == v0) {
            charge(3);
            s0 = 6;
        } else {
            charge(1);
            s0 = 0;
        }
        charge(4);
        lw(v1, s1, kRowKind);
        a1 = 2;
        if (v1 == a1) {  // "Support"
            charge(3);
            lw(v0, s2, kMode);
            check(v0 != a1, 0x204984, 3286);
            charge(4);
            lw(v1, s2, kMode);
            v0 = 1;
            if (v1 == v0) {
                charge(12);
                a0 = 6;
                jal(0x2049E8, &gen::fn_sub_177790_00177790);
                a2 = sext_b(s0);
                a0 = v0;
                build_line(0x204A08, a2);
                s3 = v0;
            } else {
                charge(2);
                if (v1 == 0) {
                    charge(14);
                    a0 = 4;
                    jal(0x2049B0, &gen::fn_sub_177790_00177790);
                    a2 = sext_b(s0);
                    a0 = v0;
                    build_line(0x2049D0, a2);
                    s3 = v0;
                } else {
                    charge(2);
                }
            }
            charge(29);
            line_finish(0x204A1C, s3);
            v0 = sll(s4, 3);
            s1 = addu(s2, v0);
            sw(s3, s1, kTargetLines);
            a2 = sext_b(s0);
            lw(a0, gp, kGpStrSupport);
            build_line(0x204A58, a2);
            s3 = v0;
            line_finish(0x204A6C, s3);
            sw(s3, s1, kTargetLines + 4);
        } else {
            charge(3);
            v0 = 1;
            if (v1 == v0) {  // a party member: name + tactic
                charge(48);
                lh(a0, s1, kRowPcId);
                jal(0x2048B0, &gen::fn_sub_177790_00177790);
                a2 = sext_b(s0);
                a0 = v0;
                build_line(0x2048D0, a2);
                s3 = v0;
                line_finish(0x2048E4, s3);
                v0 = sll(s4, 3);
                s5 = addu(s2, v0);
                sw(s3, s5, kTargetLines);
                lw(v0, s1, kRowTactic);
                v1 = sll(v0, 2);
                v0 = sx(kTacticNames);
                v0 = addu(v0, v1);
                a2 = sext_b(s0);
                lw(a0, v0, -4);
                build_line(0x204934, a2);
                s3 = v0;
                line_finish(0x204948, s3);
                sw(s3, s5, kTargetLines + 4);
            } else {
                charge(2);
                if (v1 == 0) {  // "All Members"
                    charge(22);
                    a2 = sext_b(s0);
                    lw(a0, gp, kGpStrAllMembers);
                    a3 = 0;
                    t0 = 0;
                    jal(0x204868, &gen::fn_frFontBuildGlyphList_003b0970);
                    s3 = v0;
                    line_finish(0x20487C, s3);
                    v0 = sll(s4, 3);
                    v0 = addu(s2, v0);
                    sw(s3, v0, kTargetLines);
                    sw(zero, v0, kTargetLines + 4);
                } else {
                    charge(2);
                }
            }
        }
        charge(1);
        s4 = addiu(s4, 1);
    }
    charge(19);
    glyphs_close(0x204AA0);
    word_or(v1, s2, kFlags, 0x10);
    pop(112, 6);
}

// sub_204BE0 [bcmReleaseTargetLines]: asserts bit 0x10 (line 3376), releases the non-null lines of the +940 rows;
// +0 &= ~0x10.
void Body::sub_204BE0() {
    enter(8);
    push(64, 3);
    need_work(v1, 0x204C0C);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(v1, s0, kFlags);
    v1 = andi(v1, 0x10);
    check(v1 != 0, 0x204C34, 3376);
    charge(3);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, kTargetLineCount);
        v1 = slt(s2, v1);
        if (v1 == 0) break;
        backedge();
        charge(5);
        v1 = sll(s2, 3);
        s1 = addu(s0, v1);
        lw(a0, s1, kTargetLines);
        if (a0 != 0) {
            charge(2);
            jal(0x204C5C, &gen::fn_sub_3B0170_003b0170);
        }
        charge(3);
        lw(a0, s1, kTargetLines + 4);
        if (a0 != 0) {
            charge(2);
            jal(0x204C70, &gen::fn_sub_3B0170_003b0170);
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(11);
    word_clear(s0, kFlags, -17);
    pop(64, 3);
}

// sub_205000 [bcmRefreshTargetLines]: releases (and zeroes) the target lines, then rebuilds them for the window that
// starts at row +30456, as sub_204760 (the cursor row +30464 in style 6; "All Members" leaves the second line as it
// is). The built bit is not touched.
void Body::sub_205000() {
    enter(11);
    push(112, 6);
    need_work(v0, 0x205038);
    charge(4);
    lw(s2, gp, kGpWork);
    s0 = 0;
    for (;;) {
        charge(4);
        lw(v0, s2, kTargetLineCount);
        v0 = slt(s0, v0);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s0, 3);
        s3 = addu(s2, v0);
        s1 = addiu(s3, kTargetLines);
        lw(a0, s3, kTargetLines);
        if (a0 != 0) {
            charge(3);
            jal(0x205068, &gen::fn_sub_3B0170_003b0170);
            sw(zero, s1, 0);
        }
        charge(3);
        lw(a0, s3, kTargetLines + 4);
        if (a0 != 0) {
            charge(6);
            v0 = sll(s0, 3);
            v0 = addu(s2, v0);
            s1 = addiu(v0, kTargetLines + 4);
            jal(0x20508C, &gen::fn_sub_3B0170_003b0170);
            sw(zero, s1, 0);
        }
        charge(1);
        s0 = addiu(s0, 1);
    }
    charge(9);
    glyphs_open(0x2050B0);
    s3 = 0;
    for (;;) {
        charge(4);
        lw(v0, s2, kTargetLineCount);
        v0 = slt(s3, v0);
        if (v0 == 0) break;
        backedge();
        charge(10);
        lw(v0, s2, 30456);
        v1 = addu(s3, v0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(s2, v0);
        s1 = addiu(v0, kTargets);
        lw(v0, s2, 30464);
        if (v0 == v1) {
            charge(3);
            s0 = 6;
        } else {
            charge(1);
            s0 = 0;
        }
        charge(4);
        lw(v1, s1, kRowKind);
        a1 = 2;
        if (v1 == a1) {  // "Support"
            charge(3);
            lw(v0, s2, kMode);
            check(v0 != a1, 0x205260, 3554);
            charge(4);
            lw(v1, s2, kMode);
            v0 = 1;
            if (v1 == v0) {
                charge(12);
                a0 = 6;
                jal(0x2052C4, &gen::fn_sub_177790_00177790);
                a2 = sext_b(s0);
                a0 = v0;
                build_line(0x2052E4, a2);
                s4 = v0;
            } else {
                charge(2);
                if (v1 == 0) {
                    charge(14);
                    a0 = 4;
                    jal(0x20528C, &gen::fn_sub_177790_00177790);
                    a2 = sext_b(s0);
                    a0 = v0;
                    build_line(0x2052AC, a2);
                    s4 = v0;
                } else {
                    charge(2);
                }
            }
            charge(29);
            line_finish(0x2052F8, s4);
            v0 = sll(s3, 3);
            s1 = addu(s2, v0);
            sw(s4, s1, kTargetLines);
            a2 = sext_b(s0);
            lw(a0, gp, kGpStrSupport);
            build_line(0x205334, a2);
            s4 = v0;
            line_finish(0x205348, s4);
            sw(s4, s1, kTargetLines + 4);
        } else {
            charge(3);
            v0 = 1;
            if (v1 == v0) {
                charge(48);
                lh(a0, s1, kRowPcId);
                jal(0x20518C, &gen::fn_sub_177790_00177790);
                a2 = sext_b(s0);
                a0 = v0;
                build_line(0x2051AC, a2);
                s4 = v0;
                line_finish(0x2051C0, s4);
                v0 = sll(s3, 3);
                s5 = addu(s2, v0);
                sw(s4, s5, kTargetLines);
                lw(v0, s1, kRowTactic);
                v1 = sll(v0, 2);
                v0 = sx(kTacticNames);
                v0 = addu(v0, v1);
                a2 = sext_b(s0);
                lw(a0, v0, -4);
                build_line(0x205210, a2);
                s4 = v0;
                line_finish(0x205224, s4);
                sw(s4, s5, kTargetLines + 4);
            } else {
                charge(2);
                if (v1 == 0) {
                    charge(21);
                    a2 = sext_b(s0);
                    lw(a0, gp, kGpStrAllMembers);
                    a3 = 0;
                    t0 = 0;
                    jal(0x205148, &gen::fn_frFontBuildGlyphList_003b0970);
                    s4 = v0;
                    line_finish(0x20515C, s4);
                    v0 = sll(s3, 3);
                    v0 = addu(s2, v0);
                    sw(s4, v0, kTargetLines);
                } else {
                    charge(2);
                }
            }
        }
        charge(1);
        s3 = addiu(s3, 1);
    }
    charge(16);
    glyphs_close(0x20537C);
    pop(112, 6);
}

// sub_206310 [bcmReleaseTacticLines]: asserts bit 0x1000 (line 4096), releases the title line +30632, the optional
// +30636 and the +1024 lines at +984; +0 &= ~0x1000.
void Body::sub_206310() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x206338);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(v0, s0, kFlags);
    v0 = andi(v0, 0x1000);
    check(v0 != 0, 0x206360, 4096);
    charge(6);
    lw(a0, s0, kTitleLine);
    jal(0x20636C, &gen::fn_sub_3B0170_003b0170);
    lw(a0, s0, kTitleLine2);
    if (a0 != 0) {
        charge(2);
        jal(0x206380, &gen::fn_sub_3B0170_003b0170);
    }
    charge(3);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, kTacticLineCount);
        v1 = slt(s1, v1);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kTacticLines);
        jal(0x2063A0, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    charge(10);
    word_clear(s0, kFlags, -4097);
    pop(48, 2);
}

// sub_206EB0 [bcmReleaseAnalyzeLines]: asserts bit 0x2000 (line 4498), releases the title line +30632 and the +1060
// lines at +1044; +0 &= ~0x2000.
void Body::sub_206EB0() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x206ED8);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(v0, s0, kFlags);
    v0 = andi(v0, 0x2000);
    check(v0 != 0, 0x206F00, 4498);
    charge(6);
    lw(a0, s0, kTitleLine);
    jal(0x206F0C, &gen::fn_sub_3B0170_003b0170);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, kAnalyzeLineCount);
        v1 = slt(s1, v1);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kAnalyzeLines);
        jal(0x206F2C, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    charge(10);
    word_clear(s0, kFlags, -8193);
    pop(48, 2);
}

// sub_201EF0 [bcmCheckSkillAvailable]: looks for a battle-usable skill (sub_2055F0) among the current persona's skills
// (sub_173370 list, sub_176A30 entries). None and no sub_30C0C0 entry -> +0 |= 0x80 (SKILL greyed out); else the skill
// operation +12 |= 1 unless the debug switch "SKILL OFF" (+30624 & 2).
void Body::sub_201EF0() {
    enter(10);
    push(96, 5);
    need_work(v0, 0x201F24);
    charge(19);
    lw(s3, gp, kGpWork);
    a0 = 1;
    jal(0x201F34, &gen::fn_datPersonaGetByPcId_00174800);
    s0 = v0;
    a0 = s0;
    jal(0x201F44, &gen::fn_sub_176A30_00176a30);
    s2 = v0;
    jal(0x201F50, &gen::fn_sub_30C0C0_0030c0c0);
    s1 = v0;
    a0 = s0;
    jal(0x201F60, &gen::fn_sub_173370_00173370);
    s0 = v0;
    s4 = 0;
    for (;;) {
        charge(3);
        v1 = slt(s4, s2);
        if (v1 == 0) break;
        backedge();
        charge(7);
        v0 = sll(s4, 1);
        v0 = addu(s0, v0);
        lhu(a0, v0, 0);
        jal(0x201F84, &gen::fn_sub_2055F0_002055f0);
        if (v0 != 0) break;
        charge(1);
        s4 = addiu(s4, 1);
    }
    charge(2);
    bool none = false;
    if (s1 == 0) {
        charge(2);
        none = s4 == s2;
    }
    if (none) {
        charge(5);
        word_or(v1, s3, kFlags, 0x80);
    } else {
        charge(4);
        lw(v1, s3, kDebug);
        v1 = andi(v1, 0x2);
        if (v1 == 0) {
            charge(3);
            word_or(v1, s3, kOperation, 0x1);
        }
    }
    charge(9);
    pop(96, 5);
}

// sub_202C90 [bcmCheckItemAvailable]: looks for a usable item (sub_205650) the party holds (sub_170760(1, item)) among
// items 4000..4222. None -> +0 |= 0x100 (ITEM greyed out); else the item operation +12 |= 2 unless the debug switch
// "ITEM OFF" (+30624 & 4).
void Body::sub_202C90() {
    enter(7);
    push(48, 2);
    need_work(v1, 0x202CB8);
    charge(4);
    lw(s0, gp, kGpWork);
    s1 = 0;
    for (;;) {
        charge(3);
        v1 = slti(s1, 223);
        if (v1 == 0) break;
        backedge();
        charge(6);
        v0 = addiu(s1, 4000);
        a0 = andi(v0, 0xFFFF);
        jal(0x202CD8, &gen::fn_sub_205650_00205650);
        if (v0 != 0) {
            charge(8);
            v0 = addiu(s1, 4000);
            a1 = sext_h(v0);
            a0 = 1;
            jal(0x202CF8, &gen::fn_sub_170760_00170760);
            if (v0 != 0) break;
        }
        charge(1);
        s1 = addiu(s1, 1);
    }
    charge(3);
    v1 = 223;
    if (s1 == v1) {
        charge(5);
        word_or(v1, s0, kFlags, 0x100);
    } else {
        charge(4);
        lw(v1, s0, kDebug);
        v1 = andi(v1, 0x4);
        if (v1 == 0) {
            charge(3);
            word_or(v1, s0, kOperation, 0x2);
        }
    }
    charge(6);
    pop(48, 2);
}

// sub_204AF0 [bcmApplyTactics]: every party-member row (kind 1) of the +936 rows gets its tactic (sub_16DAD0(pc id,
// tactic)); "Assign Target" (7) also sets the member's btlUnit target (sub_2C0A50(sub_1FF430(unit), row +20));
// +4 |= 4.
void Body::sub_204AF0() {
    enter(8);
    push(64, 3);
    need_work(v1, 0x204B1C);
    charge(4);
    lw(s1, gp, kGpWork);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v1, s1, kTargetCount);
        v1 = slt(s2, v1);
        if (v1 == 0) break;
        backedge();
        charge(9);
        v1 = sll(s2, 1);
        v1 = addu(v1, s2);
        v1 = sll(v1, 3);
        v1 = addu(s1, v1);
        s0 = addiu(v1, kTargets);
        lw(a0, v1, kTargets + kRowKind);
        v1 = 1;
        if (a0 == v1) {
            charge(8);
            lh(a0, s0, kRowPcId);
            lh(a1, s0, kRowTactic);
            jal(0x204B68, &gen::fn_sub_16DAD0_0016dad0);
            lw(a0, s0, kRowTactic);
            v1 = 7;
            if (a0 == v1) {
                charge(7);
                lw(a0, s0, kRowUnit);
                jal(0x204B84, &gen::fn_sub_1FF430_001ff430);
                a0 = v0;
                lw(a1, s0, kRowTarget);
                jal(0x204B94, &gen::fn_sub_2C0A50_002c0a50);
            }
        } else {
            charge(2);
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(10);
    word_or(v1, s1, kFlags2, 0x4);
    pop(64, 3);
}

// sub_205410 [bcmCloseSubList]: the open sub list (+16: 1 skill -> its title line +136 and sub_22C0A0; 2 item -> +612
// and sub_22C1D0) is closed; +0 &= ~0x20.
void Body::sub_205410() {
    enter(6);
    push(32, 1);
    need_work(v1, 0x205434);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(a0, s0, kListKind);
    v1 = 2;
    if (a0 == v1) {
        charge(5);
        lw(a0, s0, kItemTitle);
        jal(0x205484, &gen::fn_sub_3B0170_003b0170);
        jal(0x20548C, &gen::fn_sub_22C1D0_0022c1d0);
    } else {
        charge(3);
        v1 = 1;
        if (a0 == v1) {
            charge(7);
            lw(a0, s0, kSkillTitle);
            jal(0x205468, &gen::fn_sub_3B0170_003b0170);
            jal(0x205470, &gen::fn_sub_22C0A0_0022c0a0);
        } else {
            charge(2);
        }
    }
    charge(9);
    word_clear(s0, kFlags, -33);
    pop(32, 1);
}

// =====================================================================================================================
// The record's life
// =====================================================================================================================

// The teardown chain of sub_1FFC60 / sub_201780: the help line (bit 0x800000), then every built list's releaser.
// `w` holds the work; one 4-cycle test block per list and a 2-cycle call block when its bit is set.
static void release_built_lists(Body& b, Gpr& w, const u32 (&pcs)[7]) {
    const struct {
        u32 bit;
        rt::Fn fn;
    } kLists[] = {
        {0x2000, &gen::fn_sub_206EB0_00206eb0}, {0x1000, &gen::fn_sub_206310_00206310}, {0x2, &gen::fn_sub_202BC0_00202bc0},
        {0x4, &gen::fn_sub_203360_00203360},    {0x8, &gen::fn_sub_203B70_00203b70},    {0x10, &gen::fn_sub_204BE0_00204be0},
    };
    b.lw(b.v1, w, kFlags);
    b.v0 = lui(0x80);
    b.v0 = b.v1 & b.v0;
    if (b.v0 != 0) {
        b.charge(2);
        b.jal(pcs[0], &gen::fn_sub_2083D0_002083d0);
    }
    for (std::size_t i = 0; i < 6; ++i) {
        b.charge(4);
        b.lw(b.v0, w, kFlags);
        b.v0 = andi(b.v0, kLists[i].bit);
        if (b.v0 != 0) {
            b.charge(2);
            b.jal(pcs[i + 1], kLists[i].fn);
        }
    }
}

// sub_1FFC60 [bcmTeardown]: applies the tactics of the party-member rows (as sub_204AF0, without +4), stops the
// support sides whose state bits changed (0x20000 / 0x40000 / 0x80000 against 0x4000 / 0x8000 / 0x10000: btlSupportClearFlag
// when turned off, sub_2DB650(+30292) + sub_2DB2A0 or sub_2DB2A0 when turned on), releases every built list, the three
// message handles and resets the command panel (sub_21F3C0) and the panel dialog (sub_25D710).
void Body::sub_1FFC60() {
    enter(8);
    push(64, 3);
    need_work(v0, 0x1FFC8C);
    charge(4);
    lw(s1, gp, kGpWork);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kTargetCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(10);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 3);
        v0 = addu(s1, v0);
        s0 = addiu(v0, kTargets);
        lw(v0, v0, kTargets + kRowFlags);
        v0 = nor(v0, 0);
        v0 = andi(v0, 0x1);
        if (v0 == 0) {  // the row was used
            charge(4);
            lw(v1, s0, kRowKind);
            v0 = 1;
            if (v1 == v0) {
                charge(8);
                lh(a0, s0, kRowPcId);
                lh(a1, s0, kRowTactic);
                jal(0x1FFCEC, &gen::fn_sub_16DAD0_0016dad0);
                lw(v1, s0, kRowTactic);
                v0 = 7;
                if (v1 == v0) {
                    charge(7);
                    lw(a0, s0, kRowUnit);
                    jal(0x1FFD08, &gen::fn_sub_1FF430_001ff430);
                    a0 = v0;
                    lw(a1, s0, kRowTarget);
                    jal(0x1FFD18, &gen::fn_sub_2C0A50_002c0a50);
                }
            } else {
                charge(2);
            }
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    // The three support sides: (changed bit, on bit, side, the jal pcs of "stop" / "start").
    charge(5);
    lw(v1, s1, kFlags);
    v0 = lui(0x2);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(4);
        v0 = nor(v1, 0);
        v0 = andi(v0, 0x4000);
        if (v0 != 0) {
            charge(5);
            a0 = 2;
            jal(0x1FFD5C, &gen::fn_btlSupportClearFlag_002db420);
        }
    } else {
        charge(3);
        v0 = andi(v1, 0x4000);
        if (v0 != 0) {
            charge(6);
            lw(a0, s1, 30292);
            jal(0x1FFD7C, &gen::fn_sub_2DB650_002db650);
            a0 = 2;
            jal(0x1FFD88, &gen::fn_sub_2DB2A0_002db2a0);
        }
    }
    charge(5);
    lw(v1, s1, kFlags);
    v0 = lui(0x4);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(4);
        v0 = nor(v1, 0);
        v0 = andi(v0, 0x8000);
        if (v0 != 0) {
            charge(5);
            a0 = 1;
            jal(0x1FFDB8, &gen::fn_btlSupportClearFlag_002db420);
        }
    } else {
        charge(3);
        v0 = andi(v1, 0x8000);
        if (v0 != 0) {
            charge(3);
            a0 = 1;
            jal(0x1FFDD8, &gen::fn_sub_2DB2A0_002db2a0);
        }
    }
    charge(5);
    lw(v1, s1, kFlags);
    v0 = lui(0x8);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(5);
        v1 = nor(v1, 0);
        v0 = lui(0x1);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(5);
            a0 = 0;
            jal(0x1FFE0C, &gen::fn_btlSupportClearFlag_002db420);
        }
    } else {
        charge(4);
        v0 = lui(0x1);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(3);
            a0 = 0;
            jal(0x1FFE30, &gen::fn_sub_2DB2A0_002db2a0);
        }
    }
    charge(5);
    release_built_lists(*this, s1, {0x1FFE4C, 0x1FFE64, 0x1FFE7C, 0x1FFE94, 0x1FFEAC, 0x1FFEC4, 0x1FFEDC});
    charge(20);
    lw(a0, s1, kMsgHandles);
    jal(0x1FFEE8, &gen::fn_itfMesMngDestroyHandle_003a3060);
    lw(a0, s1, kMsgHandles + 4);
    jal(0x1FFEF4, &gen::fn_itfMesMngDestroyHandle_003a3060);
    lw(a0, s1, kMsgHandles + 8);
    jal(0x1FFF00, &gen::fn_itfMesMngDestroyHandle_003a3060);
    jal(0x1FFF08, &gen::fn_sub_21F3C0_0021f3c0);
    jal(0x1FFF10, &gen::fn_sub_25D710_0025d710);
    pop(64, 3);
}

// sub_201730 [bcmCreate](work): +0 = +30624 = +8 = 0, the menu mode +32 = sub_1FF740(), the command panel at +1072
// (sub_21F0C0), and $gp-18952 = work.
void Body::sub_201730() {
    enter(19);
    push(32, 1);
    s0 = a0;
    sw(zero, a0, kFlags);
    sw(zero, a0, kDebug);
    sw(zero, a0, kSelState);
    jal(0x20174C, &gen::fn_sub_1FF740_001ff740);
    sw(v0, s0, kMode);
    a0 = addiu(s0, kPanel);
    jal(0x20175C, &gen::fn_sub_21F0C0_0021f0c0);
    sw(s0, gp, kGpWork);
    pop(32, 1);
}

// sub_201780 [bcmDestroy]: releases every built list, destroys the command panel (sub_21F140), $gp-18952 = 0.
void Body::sub_201780() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x2017A4);
    charge(6);
    lw(s0, gp, kGpWork);
    release_built_lists(*this, s0, {0x2017C4, 0x2017DC, 0x2017F4, 0x20180C, 0x201824, 0x20183C, 0x201854});
    charge(8);
    jal(0x20185C, &gen::fn_sub_21F140_0021f140);
    sw(zero, gp, kGpWork);
    pop(32, 1);
}

// =====================================================================================================================
// The top menu's icons, the help line and the window refreshers
// =====================================================================================================================

// sub_201880 [bcmRefreshTopMenu]: the seven top commands' icon words (+5696 + 4 i) get bit 0 from the operation bits
// +12 (jump table 0x7B7330: ATTACK 0x20, SKILL 1, ITEM 2, PERSONA 4, 8, 0x10, 0x40); then the help line is replaced by
// entry +36 of message handle +30608 (sub_3A5540 at z -78) and +27944 = 0.
void Body::sub_201880() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x2018A4);
    charge(8);
    lw(s0, gp, kGpWork);
    a2 = 0;
    t0 = 1;
    v0 = sx(0x7B7330u);
    v1 = si(-2);
    for (;;) {
        charge(3);
        a0 = slti(a2, 7);
        if (a0 == 0) break;
        backedge();
        charge(10);
        a1 = 0;
        t2 = sll(a2, 2);
        t1 = addu(s0, t2);
        a0 = addiu(t1, 5696);
        lw(a3, t1, 5696);
        a3 = a3 & v1;
        sw(a3, t1, 5696);
        at = sltiu(a2, 7);
        if (at != 0) {
            charge(4);
            a3 = addu(t2, v0);
            lw(a3, a3, 0);
            const u32 target = static_cast<u32>(a3);
            u32 bit = 0;
            switch (target) {
            case 0x201904u: bit = 0x20; break;
            case 0x201920u: bit = 0x1; break;
            case 0x20193Cu: bit = 0x2; break;
            case 0x201958u: bit = 0x4; break;
            case 0x201974u: bit = 0x8; break;
            case 0x201990u: bit = 0x10; break;
            case 0x2019ACu: bit = 0x40; break;
            default: rt::lookup_func(target)(c); return;
            }
            charge(4);
            lw(a3, s0, kOperation);
            a3 = andi(a3, bit);
            if (a3 != 0) {
                charge(bit == 0x40 ? 1 : 3);  // the last case falls through, the others `b`
                a1 = t0;
            }
        }
        charge(2);
        if (a1 != 0) {
            charge(3);
            word_or(a1, a0, 0, 0x1);
        }
        charge(1);
        a2 = addiu(a2, 1);
    }
    drop_help(s0, 0x2019F8);
    charge(19);
    mtc1_zero(12);
    a2 = si(-78);
    lw(t1, s0, kMsgHandles);
    lw(t2, s0, kWord36);
    new_help(0x201A20, 0x201A2C);
    sw(zero, s0, 27944);
    pop(32, 1);
}

// sub_201AD0: sub_208360 (drop the help line, asserting it exists).
void Body::sub_201AD0() {
    enter(8);
    push(16, 0);
    jal(0x201AD8, &gen::fn_sub_208360_00208360);
    pop(16, 0);
}

// sub_202A10 [bcmRefreshSkillLines]: releases the skill lines, replaces the help line by the selected skill's entry of
// sub_3C7D60(7), and rebuilds the visible skill names from the window start +30300 (the cursor row +30308 in style 6).
void Body::sub_202A10() {
    enter(8);
    push(64, 3);
    need_work(v0, 0x202A3C);
    charge(4);
    lw(s0, gp, kGpWork);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, kSkillCount);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kSkillLines);
        jal(0x202A60, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    drop_help(s0, 0x202A90);
    charge(28);
    a0 = 7;
    jal(0x202A9C, &gen::fn_sub_3C7D60_003c7d60);
    mtc1_zero(12);
    lw(v1, s0, 30308);
    v1 = sll(v1, 3);
    v1 = addu(v1, s0);
    lhu(t2, v1, kSkills);
    a2 = si(-1);
    t1 = v0;
    new_help(0x202AD0, 0x202ADC);
    glyphs_open(0x202AE8);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, kSkillCount);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(9);
        lw(a0, s0, 30300);
        v0 = addu(s1, a0);
        v0 = sll(v0, 3);
        v0 = addu(s0, v0);
        v1 = addiu(v0, 40);
        lw(v0, s0, 30308);
        v0 = subu(v0, a0);
        if (s1 == v0) {
            charge(3);
            s2 = 6;
        } else {
            charge(1);
            s2 = 0;
        }
        charge(15);
        lhu(a0, v1, 4);
        jal(0x202B40, &gen::fn_datGetSkillName_0030bb40);
        a0 = v0;
        build_line(0x202B60, sext_b(s2));
        v1 = sll(s1, 2);
        v1 = addu(s0, v1);
        sw(v0, v1, kSkillLines);
        s1 = addiu(s1, 1);
    }
    charge(13);
    glyphs_close(0x202B8C);
    pop(64, 3);
}

// sub_203410 [bcmRefreshItemLines]: as sub_202A10 for the items -- the help entry is the selected item - 4000 of
// sub_3C7D60(5); the visible rows from +30352 (cursor +30360) at row positions, white.
void Body::sub_203410() {
    enter(8);
    push(64, 3);
    need_work(v0, 0x20343C);
    charge(4);
    lw(s1, gp, kGpWork);
    s0 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kItemLineCount);
        v0 = slt(s0, v0);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        lw(a0, v0, kItemLines);
        jal(0x203460, &gen::fn_sub_3B0170_003b0170);
        s0 = addiu(s0, 1);
    }
    drop_help(s1, 0x203490);
    charge(29);
    a0 = 5;
    jal(0x20349C, &gen::fn_sub_3C7D60_003c7d60);
    mtc1_zero(12);
    lw(v1, s1, 30360);
    v1 = sll(v1, 1);
    v1 = addu(v1, s1);
    lhu(v1, v1, kItems);
    t2 = addiu(v1, -4000);
    a2 = si(-1);
    t1 = v0;
    new_help(0x2034D4, 0x2034E0);
    glyphs_open(0x2034EC);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kItemLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(5);
        lw(v0, s1, 30352);
        v1 = addu(s2, v0);
        lw(v0, s1, 30360);
        const bool cursor = v0 == v1;
        charge(cursor ? 16 : 14);
        v0 = sll(v1, 1);
        v0 = addu(s1, v0);
        lh(a0, v0, kItems);
        a1 = 0;
        jal(cursor ? 0x203530 : 0x203570, &gen::fn_sub_171110_00171110);
        a0 = v0;
        build_line(cursor ? 0x20354C : 0x20358C, cursor ? 6 : 0);
        s0 = v0;
        charge(21);
        line_row_pos(0x2035B4, s2, s0);
        line_finish(0x2035C4, s0);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        sw(s0, v0, kItemLines);
        s2 = addiu(s2, 1);
    }
    charge(13);
    glyphs_close(0x203600);
    pop(64, 3);
}

// sub_206170 [bcmRefreshTacticLines]: releases the tactic lines (+984), replaces the help line by the tactic under the
// cursor (+30516: word +944 + 4 cursor, minus 1) of message handle +30612, and rebuilds the visible tactic names
// (0x684F00[tactic - 1]) from the window start +30508, the cursor row in style 6.
void Body::sub_206170() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x206198);
    charge(4);
    lw(s0, gp, kGpWork);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, kTacticLineCount);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kTacticLines);
        jal(0x2061BC, &gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    drop_help(s0, 0x2061EC);
    charge(26);
    mtc1_zero(12);
    lw(v0, s0, 30516);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, 944);
    t2 = addiu(v0, -1);
    a2 = si(-1);
    lw(t1, s0, kMsgHandles + 4);
    new_help(0x206224, 0x206230);
    glyphs_open(0x20623C);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, kTacticLineCount);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(12);
        lw(v0, s0, 30508);
        a0 = addu(s1, v0);
        v0 = sll(a0, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, 944);
        v1 = sll(v0, 2);
        v0 = sx(kTacticNames);
        v1 = addu(v0, v1);
        lw(v0, s0, 30516);
        if (a0 == v0) {
            charge(3);
            v0 = 6;
        } else {
            charge(1);
            v0 = 0;
        }
        charge(12);
        a2 = sext_b(v0);
        lw(a0, v1, -4);
        build_line(0x2062B4, a2);
        v1 = sll(s1, 2);
        v1 = addu(s0, v1);
        sw(v0, v1, kTacticLines);
        s1 = addiu(s1, 1);
    }
    charge(12);
    glyphs_close(0x2062E0);
    pop(48, 2);
}

// sub_206E40 [bcmOpenAnalyze]: opens the analyze window (sub_2255F0), plays system sound 4, +24 = 9.
void Body::sub_206E40() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x206E64);
    charge(16);
    lw(s0, gp, kGpWork);
    jal(0x206E70, &gen::fn_sub_2255F0_002255f0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 4;
    jal(0x206E88, &gen::fn_sub_10A4E0_0010a4e0);
    v1 = 9;
    sw(v1, s0, 24);
    pop(32, 1);
}

// sub_207010 [bcmRefreshAnalyzeLines]: releases the analyze lines (+1044), replaces the help line by the kind of the
// row under the cursor (+1032 + 4 (+30568 + +30560): 2 -> 3, 1 -> 2, 0 -> the menu mode 0 / 1 -> 0 / 1) of message
// handle +30616, and rebuilds the visible rows from the window start +30560 (cursor +30568 in style 6): kind 0 ->
// skill name 324 (mode 0) or 326 (mode 1), kind 1 -> the $gp-26840 string, kind 2 -> skill name 325 (asserting mode
// 1, line 4617); other kinds keep the previous line.
void Body::sub_207010() {
    enter(9);
    push(80, 4);
    need_work(v0, 0x207040);
    charge(4);
    lw(s1, gp, kGpWork);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kAnalyzeLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        lw(a0, v0, kAnalyzeLines);
        jal(0x207064, &gen::fn_sub_3B0170_003b0170);
        s2 = addiu(s2, 1);
    }
    drop_help(s1, 0x207094);
    charge(9);
    lw(v1, s1, 30568);
    lw(v0, s1, 30560);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    v0 = addu(s1, v0);
    lw(a0, v0, 1032);
    v0 = 2;
    if (a0 == v0) {
        charge(1);
        s0 = 3;
    } else {
        charge(3);
        v1 = 1;
        if (a0 == v1) {
            charge(3);
            s0 = v0;
        } else {
            charge(2);
            if (a0 == 0) {
                charge(3);
                lw(v0, s1, kMode);
                if (v0 == v1) {
                    charge(3);
                    s0 = v1;
                } else {
                    charge(2);
                    if (v0 == 0) {
                        charge(3);
                        s0 = 0;
                    } else {
                        charge(2);
                    }
                }
            } else {
                charge(2);
            }
        }
    }
    charge(23);
    mtc1_zero(12);
    a2 = si(-1);
    lw(t1, s1, kMsgHandles + 8);
    t2 = s0;
    a0 = 100;
    a1 = a0;
    a3 = 2;
    t0 = 6;
    jal(0x207140, &gen::fn_sub_3A5540_003a5540);
    s3 = v0;
    a0 = s3;
    jal(0x207150, &gen::fn_sub_2082C0_002082c0);
    glyphs_open(0x20715C);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kAnalyzeLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(9);
        lw(a0, s1, 30560);
        v0 = addu(s2, a0);
        v0 = sll(v0, 2);
        v0 = addu(s1, v0);
        v1 = addiu(v0, 1032);
        lw(v0, s1, 30568);
        v0 = subu(v0, a0);
        if (s2 == v0) {
            charge(3);
            s0 = 6;
        } else {
            charge(1);
            s0 = 0;
        }
        charge(4);
        lw(v0, v1, 0);
        a1 = 2;
        const auto skill_line = [&](u32 skill, u32 pc_name, u32 pc_build) {
            a0 = skill;
            jal(pc_name, &gen::fn_datGetSkillName_0030bb40);
            a2 = sext_b(s0);
            a0 = v0;
            build_line(pc_build, a2);
            s3 = v0;
        };
        if (v0 == a1) {
            charge(4);
            lw(v1, s1, kMode);
            v0 = 1;
            check(v1 == v0, 0x2072AC, 4617);
            charge(12);
            skill_line(325, 0x2072B8, 0x2072D8);
        } else {
            charge(3);
            v1 = 1;
            if (v0 == v1) {
                charge(10);
                a2 = sext_b(s0);
                lw(a0, gp, -26840);
                a3 = 0;
                t0 = 0;
                jal(0x20727C, &gen::fn_frFontBuildGlyphList_003b0970);
                s3 = v0;
            } else {
                charge(2);
                if (v0 == 0) {
                    charge(3);
                    lw(v0, s1, kMode);
                    if (v0 == v1) {
                        charge(14);
                        skill_line(326, 0x207234, 0x207254);
                    } else {
                        charge(2);
                        if (v0 == 0) {
                            charge(14);
                            skill_line(324, 0x2071FC, 0x20721C);
                        } else {
                            charge(2);
                        }
                    }
                } else {
                    charge(2);
                }
            }
        }
        charge(4);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        sw(s3, v0, kAnalyzeLines);
        s2 = addiu(s2, 1);
    }
    charge(14);
    glyphs_close(0x207308);
    pop(80, 4);
}

// sub_207E20 [bcmOpenBossTutorial]: the boss encounters 466 / 467 / 468 / 469 show tutorial page 0 / 1 / 2 / 3
// (sub_2518B0; any other encounter asserts, line 4965, with $s1 as the caller left it), hide the command window
// (sub_20FC40); +16 = 10.
void Body::sub_207E20() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x207E48);
    charge(6);
    lw(s0, gp, kGpWork);
    jal(0x207E54, &gen::fn_btlGetEncounterId_002d5550);
    v1 = 469;
    if (v0 == v1) {
        charge(3);
        s1 = 3;
    } else {
        charge(3);
        v1 = 468;
        if (v0 == v1) {
            charge(3);
            s1 = 2;
        } else {
            charge(3);
            v1 = 467;
            if (v0 == v1) {
                charge(3);
                s1 = 1;
            } else {
                charge(3);
                v1 = 466;
                if (v0 == v1) {
                    charge(3);
                    s1 = 0;
                } else {
                    charge(2);
                    charge(5);
                    k_assert(0x207ED0, 4965);
                }
            }
        }
    }
    charge(13);
    a0 = s1;
    jal(0x207EDC, &gen::fn_sub_2518B0_002518b0);
    jal(0x207EE4, &gen::fn_sub_20FC40_0020fc40);
    v1 = 10;
    sw(v1, s0, kListKind);
    pop(48, 2);
}

// sub_207F10 [bcmOpenTutorial]: tutorial page (sub_251E10), hide the command window (sub_20FC40); +16 = 11.
void Body::sub_207F10() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x207F34);
    charge(12);
    lw(s0, gp, kGpWork);
    jal(0x207F40, &gen::fn_sub_251E10_00251e10);
    jal(0x207F48, &gen::fn_sub_20FC40_0020fc40);
    v1 = 11;
    sw(v1, s0, kListKind);
    pop(32, 1);
}

// =====================================================================================================================
// The panel fillers: copy a list's state into the command panel record (+19088 on) and open its window
// =====================================================================================================================

// The panel's list summary words (+25752 cursor, +25756 window start, +25760 rows, +25764 entries) and +30272.
inline constexpr s32 kPanelRows = 19088;     // the panel's per-row records
inline constexpr s32 kPanelCursor = 25752;
inline constexpr s32 kPanelWindow = 25756;
inline constexpr s32 kPanelCount = 25760;
inline constexpr s32 kPanelTotal = 25764;

// sub_2025E0 [bcmOpenSkillWindow]: asserts the skill lines exist (line 2172), refreshes them (sub_202A10) and fills a
// 144-byte panel row per skill: +0 flags (the entry's bits 0 / 1), +4 the line, +8 the target kind (skill table byte
// 3: 1 -> 0, 2 -> 1), +12 the cost sub_3083F0(actor +2604, skill) for the actor sub_1FF500(1); the summary words, and
// +27944 / +27940 from the item kind tests sub_207930 / sub_207960 of the selected skill; opens the skill window.
void Body::sub_2025E0() {
    enter(10);
    push(96, 5);
    need_work(v0, 0x202614);
    charge(6);
    lw(s3, gp, kGpWork);
    s2 = addiu(s3, kPanelRows);
    lw(v0, s3, kFlags);
    v0 = andi(v0, 0x2);
    check(v0 != 0, 0x202640, 2172);
    charge(9);
    a0 = 1;
    jal(0x20264C, &gen::fn_sub_1FF500_001ff500);
    s1 = v0;
    jal(0x202658, &gen::fn_sub_202A10_00202a10);
    s4 = 0;
    // `lw v0, 30300(s3); addu v0, s4, v0; sll v0, v0, 3; addu v0, s3, v0`: the entry of visible row s4.
    const auto entry = [&] {
        lw(v0, s3, 30300);
        v0 = addu(s4, v0);
        v0 = sll(v0, 3);
        v0 = addu(s3, v0);
    };
    for (;;) {
        charge(4);
        lw(v0, s3, kSkillCount);
        v0 = slt(s4, v0);
        if (v0 == 0) break;
        backedge();
        charge(19);
        v0 = sll(s4, 3);
        v1 = addu(v0, s4);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v0 = sll(v0, 4);
        s0 = addu(s2, v0);  // 144 * row
        sw(zero, s0, 0);
        v0 = sll(s4, 2);
        v0 = addu(s3, v0);
        lw(v0, v0, kSkillLines);
        sw(v0, s0, 4);
        entry();
        lw(v0, v0, kSkills - 4);
        v0 = andi(v0, 0x1);
        if (v0 != 0) {
            charge(3);
            word_or(v0, s0, 0, 0x1);
        }
        charge(8);
        entry();
        lw(v0, v0, kSkills - 4);
        v0 = andi(v0, 0x2);
        if (v0 != 0) {
            charge(3);
            word_or(v0, s0, 0, 0x2);
        }
        charge(16);
        entry();
        lhu(v1, v0, kSkills);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);  // 44 * skill
        lw(v0, gp, kGpSkillTable);
        v0 = addu(v0, v1);
        lbu(v1, v0, 3);
        v0 = 2;
        if (v1 == v0) {
            charge(2);
            v0 = 1;
            sw(v0, s0, 8);
        } else {
            charge(3);
            v0 = 1;
            if (v1 == v0) {
                charge(3);
                sw(zero, s0, 8);
            } else {
                charge(2);
            }
        }
        charge(10);
        entry();
        lw(a0, s1, 2604);
        lhu(a1, v0, kSkills);
        jal(0x202770, &gen::fn_sub_3083F0_003083f0);
        sw(v0, s0, 12);
        s4 = addiu(s4, 1);
    }
    charge(18);
    sw(zero, s3, 30272);
    lw(v0, s3, kSkillCount);
    sw(v0, s3, kPanelCount);
    lw(v0, s3, 30308);
    sw(v0, s3, kPanelCursor);
    lw(v0, s3, 30300);
    sw(v0, s3, kPanelWindow);
    lw(v0, s3, 116);
    sw(v0, s3, kPanelTotal);
    sw(zero, s3, 27944);
    lw(v0, s3, 30308);
    v0 = sll(v0, 3);
    v0 = addu(v0, s3);
    lhu(a0, v0, kSkills);
    jal(0x2027C8, &gen::fn_sub_207930_00207930);
    if (v0 != 0) {
        charge(9);
        v0 = 1;
        sw(v0, s3, 27944);
        lw(v0, s3, 30308);
        v0 = sll(v0, 3);
        v0 = addu(v0, s3);
        lhu(a0, v0, kSkills);
        jal(0x2027F0, &gen::fn_sub_207960_00207960);
        sw(v0, s3, 27940);
    }
    charge(11);
    jal(0x2027FC, &gen::fn_sub_222B90_00222b90);
    pop(96, 5);
}

// sub_2031C0 [bcmOpenItemWindow]: asserts the item lines exist (line 2528), refreshes them (sub_203410) and fills a
// 1040-byte panel row per visible item (at most 4): +0 the line, +4 the party's stock sub_170760(1, item) & 0xFFFF;
// the summary words, +27944 / +27940 from sub_207930 / sub_207960 of the selected item's kind item sub_30BC20; opens
// the item window.
void Body::sub_2031C0() {
    enter(10);
    push(96, 5);
    need_work(v0, 0x2031F4);
    charge(6);
    lw(s2, gp, kGpWork);
    s1 = addiu(s2, kPanelRows);
    lw(v0, s2, kFlags);
    v0 = andi(v0, 0x4);
    check(v0 != 0, 0x203220, 2528);
    charge(6);
    jal(0x203228, &gen::fn_sub_203410_00203410);
    lw(s3, s2, kItemCount);
    at = slti(s3, 5);
    if (at == 0) {
        charge(1);
        s3 = 4;
    }
    charge(3);
    s4 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s4, s3);
        if (v0 == 0) break;
        backedge();
        charge(19);
        v0 = sll(s4, 6);
        v0 = addu(v0, s4);
        v0 = sll(v0, 4);
        s0 = addu(s1, v0);  // 1040 * row
        v0 = sll(s4, 2);
        v0 = addu(s2, v0);
        lw(v0, v0, kItemLines);
        sw(v0, s0, 0);
        lw(v0, s2, 30352);
        v0 = addu(v0, s4);
        v0 = sll(v0, 1);
        v0 = addu(s2, v0);
        lh(a1, v0, kItems);
        a0 = 1;
        jal(0x203288, &gen::fn_sub_170760_00170760);
        v0 = andi(v0, 0xFFFF);
        sw(v0, s0, 4);
        s4 = addiu(s4, 1);
    }
    charge(20);
    sw(zero, s2, 30272);
    sw(s3, s2, kPanelCount);
    lw(v0, s2, 30360);
    sw(v0, s2, kPanelCursor);
    lw(v0, s2, 30352);
    sw(v0, s2, kPanelWindow);
    lw(v0, s2, kItemCount);
    sw(v0, s2, kPanelTotal);
    sw(zero, s2, 27944);
    lw(v0, s2, 30360);
    v0 = sll(v0, 1);
    v0 = addu(v0, s2);
    lhu(a0, v0, kItems);
    jal(0x2032DC, &gen::fn_sub_30BC20_0030bc20);
    a0 = andi(v0, 0xFFFF);
    jal(0x2032E8, &gen::fn_sub_207930_00207930);
    if (v0 != 0) {
        charge(12);
        v0 = 1;
        sw(v0, s2, 27944);
        lw(v0, s2, 30360);
        v0 = sll(v0, 1);
        v0 = addu(v0, s2);
        lhu(a0, v0, kItems);
        jal(0x203310, &gen::fn_sub_30BC20_0030bc20);
        a0 = andi(v0, 0xFFFF);
        jal(0x20331C, &gen::fn_sub_207960_00207960);
        sw(v0, s2, 27940);
    }
    charge(11);
    jal(0x203328, &gen::fn_sub_222D60_00222d60);
    pop(96, 5);
}

// sub_203C30 [bcmOpenPersonaWindow]: asserts the persona lines exist (line 2823), refreshes them (sub_203DE0; a
// leftover "work != NULL" check runs for the cursor row), places each line at its row position, fills 784-byte panel
// rows (+768 the line, +772 the persona's level), the summary words, and opens the persona window.
void Body::sub_203C30() {
    enter(8);
    push(64, 3);
    need_work(v0, 0x203C5C);
    charge(6);
    lw(s1, gp, kGpWork);
    s0 = addiu(s1, kPanelRows);
    lw(v0, s1, kFlags);
    v0 = andi(v0, 0x8);
    check(v0 != 0, 0x203C88, 2823);
    charge(5);
    jal(0x203C90, &gen::fn_sub_203DE0_00203de0);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kPersonaLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(5);
        lw(v1, s1, 30412);
        lw(v0, s1, 30404);
        v0 = subu(v1, v0);
        if (s2 == v0) {
            charge(3);
            need_work(v0, 0x203CD0);
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(3);
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kPersonaLineCount);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(12);
        v0 = sll(s2, 2);
        v1 = addu(s1, v0);
        v0 = sll(s2, 3);
        v0 = addu(v0, s2);
        v0 = sll(v0, 1);
        v0 = addiu(v0, 280);
        a2 = sll(v0, 3);
        lw(a0, v1, kPersonaLines);
        a1 = 1840;
        jal(0x203D1C, &gen::fn_frFontLineSetPos_003b0d70);
        s2 = addiu(s2, 1);
    }
    charge(3);
    a0 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kPersonaLineCount);
        v0 = slt(a0, v0);
        if (v0 == 0) break;
        backedge();
        charge(17);
        v0 = sll(a0, 3);
        v1 = subu(v0, a0);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        v1 = addu(s0, v0);  // 784 * row
        v0 = sll(a0, 2);
        v0 = addu(s1, v0);
        lw(v0, v0, kPersonaLines);
        sw(v0, v1, 768);
        lw(v0, s1, 30404);
        v0 = addu(a0, v0);
        v0 = sll(v0, 3);
        v0 = addu(s1, v0);
        lw(v0, v0, kPersonas + 4);
        sw(v0, v1, 772);
        a0 = addiu(a0, 1);
    }
    charge(18);
    sw(zero, s1, 30272);
    lw(v0, s1, kPersonaLineCount);
    sw(v0, s1, kPanelCount);
    lw(v0, s1, 30412);
    sw(v0, s1, kPanelCursor);
    lw(v0, s1, 30404);
    sw(v0, s1, kPanelWindow);
    lw(v0, s1, kPersonaCount);
    sw(v0, s1, kPanelTotal);
    jal(0x203DBC, &gen::fn_sub_224860_00224860);
    pop(64, 3);
}

// The visible target rows of sub_204CC0 / sub_205D60: the lines of row i (absolute row +30456 + i) placed at their row
// position (the second line at x 3920) and coloured -- the cursor row (+30464 against i, or against the absolute row)
// 0x0000FFFF while the menu is active (the inlined sub_201AF0), else 0x8080FFFF; other rows white. pcs: SetPos / Rgba
// of a one-line row, then SetPos / Rgba / SetPos / Rgba of a two-line row.
void Body::target_row_lines(bool absolute, u32 pc_assert, const u32 (&pcs)[6]) {
    for (;;) {
        charge(4);
        lw(v0, s0, kTargetLineCount);
        v0 = slt(s3, v0);
        if (v0 == 0) break;
        backedge();
        charge(10);
        lw(v0, s0, 30456);
        v1 = addu(s3, v0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(s0, v0);
        s1 = addiu(v0, kTargets);
        lw(v0, s0, 30464);
        if (absolute ? v0 == v1 : s3 == v0) {
            charge(3);
            need_work(v0, pc_assert);
            charge(6);
            lw(v0, gp, kGpWork);
            lw(v1, v0, kFlags);
            v0 = sltu(0, andi(v1, 0x1));
            if (v0 == 0) {
                charge(3);
                v0 = lui(0x2000);
                v0 = sltu(0, v1 & v0);
            }
            charge(2);
            if (v0 != 0) {
                charge(3);
                s4 = 0xFFFF;
            } else {
                charge(4);
                v0 = lui(0x8080);
                s4 = ori(v0, 0xFFFF);
            }
        } else {
            charge(1);
            s4 = si(-1);
        }
        charge(4);
        lw(v1, s1, kRowKind);
        v0 = 2;
        bool two = v1 == v0;
        bool one = false;
        if (!two) {
            charge(3);
            v0 = 1;
            two = v1 == v0;
            if (!two) {
                charge(2);
                one = v1 == 0;
                if (!one) charge(2);
            }
        }
        if (one) {
            charge(17);
            v1 = sll(s3, 3);
            v0 = addu(s0, v1);
            lw(s1, v0, kTargetLines);
            v0 = addu(v1, s3);
            v0 = sll(v0, 1);
            v0 = addiu(v0, 280);
            a2 = sll(v0, 3);
            a0 = s1;
            a1 = 1840;
            jal(pcs[0], &gen::fn_frFontLineSetPos_003b0d70);
            a0 = s1;
            a1 = s4;
            jal(pcs[1], &gen::fn_frFontLineSetRgba_003b0e20);
        } else if (two) {
            charge(26);
            v0 = sll(s3, 3);
            s5 = addu(s0, v0);
            lw(s1, s5, kTargetLines);
            v0 = addu(v0, s3);
            v0 = sll(v0, 1);
            v0 = addiu(v0, 280);
            s2 = sll(v0, 3);
            a0 = s1;
            a1 = 1840;
            a2 = s2;
            jal(pcs[2], &gen::fn_frFontLineSetPos_003b0d70);
            a0 = s1;
            a1 = s4;
            jal(pcs[3], &gen::fn_frFontLineSetRgba_003b0e20);
            lw(s1, s5, kTargetLines + 4);
            a0 = s1;
            a1 = 3920;
            a2 = s2;
            jal(pcs[4], &gen::fn_frFontLineSetPos_003b0d70);
            a0 = s1;
            a1 = s4;
            jal(pcs[5], &gen::fn_frFontLineSetRgba_003b0e20);
        }
        charge(1);
        s3 = addiu(s3, 1);
    }
}

// sub_204CC0 [bcmOpenTargetWindow]: asserts the target lines exist (line 3399), refreshes them (sub_205000), places
// and colours the visible rows, fills 1056-byte panel rows (+0 kind: 1 "All Members", 0 member, 2 "Support"; +8 / +12
// the lines; +1040 = 1 for an Orgia-mode member), the summary words, and opens the target window (sub_2230E0).
void Body::sub_204CC0() {
    enter(12);
    push(128, 7);
    need_work(v0, 0x204CFC);
    charge(6);
    lw(s0, gp, kGpWork);
    s6 = addiu(s0, kPanelRows);
    lw(v0, s0, kFlags);
    v0 = andi(v0, 0x10);
    check(v0 != 0, 0x204D28, 3399);
    charge(5);
    jal(0x204D30, &gen::fn_sub_205000_00205000);
    s3 = 0;
    target_row_lines(false, 0x204D84, {0x204E28, 0x204E38, 0x204E70, 0x204E80, 0x204E98, 0x204EA8});
    charge(5);
    v1 = 0;
    a2 = 1;
    a3 = 2;
    for (;;) {
        charge(4);
        lw(a0, s0, kTargetLineCount);
        v0 = slt(v1, a0);
        if (v0 == 0) break;
        backedge();
        charge(15);
        v0 = sll(v1, 5);
        v0 = addu(v0, v1);
        v0 = sll(v0, 5);
        v0 = addu(s6, v0);  // 1056 * row
        lw(a0, s0, 30456);
        a1 = addu(v1, a0);
        a0 = sll(a1, 1);
        a0 = addu(a0, a1);
        a0 = sll(a0, 3);
        a0 = addu(s0, a0);
        t0 = addiu(a0, kTargets);
        sw(zero, v0, 1040);
        lw(a0, a0, kTargets + kRowKind);
        if (a0 == a3) {  // "Support"
            charge(7);
            sw(a3, v0, 0);
            a0 = sll(v1, 3);
            a1 = addu(s0, a0);
            lw(a0, a1, kTargetLines);
            sw(a0, v0, 8);
            lw(a0, a1, kTargetLines + 4);
            sw(a0, v0, 12);
        } else {
            charge(2);
            if (a0 == a2) {  // a member
                charge(9);
                sw(zero, v0, 0);
                a0 = sll(v1, 3);
                a1 = addu(s0, a0);
                lw(a0, a1, kTargetLines);
                sw(a0, v0, 8);
                lw(a0, a1, kTargetLines + 4);
                sw(a0, v0, 12);
            } else {
                charge(2);
                if (a0 == 0) {  // "All Members"
                    charge(7);
                    sw(a2, v0, 0);
                    a0 = sll(v1, 3);
                    a0 = addu(s0, a0);
                    lw(a0, a0, kTargetLines);
                    sw(a0, v0, 8);
                } else {
                    charge(2);
                }
            }
        }
        charge(4);
        lw(a0, t0, kRowFlags);
        a0 = andi(a0, 0x2);
        if (a0 != 0) {
            charge(1);
            sw(a2, v0, 1040);
        }
        charge(1);
        v1 = addiu(v1, 1);
    }
    charge(20);
    sw(a0, s0, kPanelCount);
    lw(v0, s0, 30464);
    sw(v0, s0, kPanelCursor);
    lw(v0, s0, 30456);
    sw(v0, s0, kPanelWindow);
    lw(v0, s0, kTargetCount);
    sw(v0, s0, kPanelTotal);
    jal(0x204FCC, &gen::fn_sub_2230E0_002230e0);
    pop(128, 7);
}

// sub_205D60 [bcmOpenTargetWindowAnalyze]: as sub_204CC0 without the refresh (the cursor compared with the absolute
// row; the first row's second line also lands in panel +6368), then the analyze window (sub_2255F0), system sound 4
// and +28 = 2.
void Body::sub_205D60() {
    enter(12);
    push(128, 7);
    need_work(v0, 0x205D9C);
    charge(5);
    lw(s0, gp, kGpWork);
    s6 = addiu(s0, kPanelRows);
    s3 = 0;
    target_row_lines(true, 0x205DF8, {0x205E9C, 0x205EAC, 0x205EE4, 0x205EF4, 0x205F0C, 0x205F1C});
    charge(5);
    v1 = 0;
    a3 = 1;
    t0 = 2;
    for (;;) {
        charge(4);
        lw(a0, s0, kTargetLineCount);
        v0 = slt(v1, a0);
        if (v0 == 0) break;
        backedge();
        charge(15);
        v0 = sll(v1, 5);
        v0 = addu(v0, v1);
        v0 = sll(v0, 5);
        v0 = addu(s6, v0);
        lw(a0, s0, 30456);
        t2 = addu(v1, a0);
        a0 = sll(t2, 1);
        a0 = addu(a0, t2);
        a0 = sll(a0, 3);
        a0 = addu(s0, a0);
        t1 = addiu(a0, kTargets);
        sw(zero, v0, 1040);
        lw(a0, a0, kTargets + kRowKind);
        if (a0 == t0) {
            charge(7);
            sw(t0, v0, 0);
            a0 = sll(v1, 3);
            a1 = addu(s0, a0);
            lw(a0, a1, kTargetLines);
            sw(a0, v0, 8);
            lw(a0, a1, kTargetLines + 4);
            sw(a0, v0, 12);
        } else {
            charge(2);
            if (a0 == a3) {
                charge(10);
                sw(zero, v0, 0);
                a0 = sll(v1, 3);
                a2 = addu(s0, a0);
                lw(a0, a2, kTargetLines);
                sw(a0, v0, 8);
                a1 = addiu(a2, kTargetLines + 4);
                lw(a0, a2, kTargetLines + 4);
                sw(a0, v0, 12);
                if (t2 == 0) {
                    charge(4);
                    lw(a0, a1, 0);
                    sw(a0, s6, 6368);
                }
            } else {
                charge(2);
                if (a0 == 0) {
                    charge(7);
                    sw(a3, v0, 0);
                    a0 = sll(v1, 3);
                    a0 = addu(s0, a0);
                    lw(a0, a0, kTargetLines);
                    sw(a0, v0, 8);
                } else {
                    charge(2);
                }
            }
        }
        charge(4);
        lw(a0, t1, kRowFlags);
        a0 = andi(a0, 0x2);
        if (a0 != 0) {
            charge(1);
            sw(a3, v0, 1040);
        }
        charge(1);
        v1 = addiu(v1, 1);
    }
    charge(30);
    sw(a0, s0, kPanelCount);
    lw(v0, s0, 30464);
    sw(v0, s0, kPanelCursor);
    lw(v0, s0, 30456);
    sw(v0, s0, kPanelWindow);
    lw(v0, s0, kTargetCount);
    sw(v0, s0, kPanelTotal);
    jal(0x206054, &gen::fn_sub_2230E0_002230e0);
    jal(0x20605C, &gen::fn_sub_2255F0_002255f0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 4;
    jal(0x206074, &gen::fn_sub_10A4E0_0010a4e0);
    v1 = 2;
    sw(v1, s0, 28);
    pop(128, 7);
}

// sub_2060B0 [bcmOpenTacticWindow]: refreshes the tactic lines (sub_206170), fills 272-byte panel rows (+25776 = 0,
// +25780 the line), the tactics summary words (+27136 .. +27148 from +1028 / +30516 / +30508 / +1024), +27944 = 0, and
// opens the window (sub_225670).
void Body::sub_2060B0() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x2060D4);
    charge(6);
    lw(s0, gp, kGpWork);
    jal(0x2060E0, &gen::fn_sub_206170_00206170);
    a0 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, kTacticLineCount);
        v0 = slt(a0, v0);
        if (v0 == 0) break;
        backedge();
        charge(10);
        v0 = sll(a0, 4);
        v0 = addu(v0, a0);
        v0 = sll(v0, 4);
        v1 = addu(s0, v0);  // 272 * row
        sw(zero, v1, 25776);
        v0 = sll(a0, 2);
        v0 = addu(s0, v0);
        lw(v0, v0, kTacticLines);
        sw(v0, v1, 25780);
        a0 = addiu(a0, 1);
    }
    charge(16);
    lw(v0, s0, 1028);
    sw(v0, s0, 27136);
    lw(v0, s0, 30516);
    sw(v0, s0, 27140);
    lw(v0, s0, 30508);
    sw(v0, s0, 27144);
    lw(v0, s0, kTacticLineCount);
    sw(v0, s0, 27148);
    sw(zero, s0, 27944);
    jal(0x206150, &gen::fn_sub_225670_00225670);
    pop(32, 1);
}

// sub_206F70 [bcmOpenAnalyzeWindow]: refreshes the analyze lines (sub_207010), copies the first +27148 of them into the
// panel rows (+25780), +27140 = the cursor +30568, +27144 = 0, and opens the window (sub_225670).
void Body::sub_206F70() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x206F94);
    charge(6);
    lw(s0, gp, kGpWork);
    jal(0x206FA0, &gen::fn_sub_207010_00207010);
    a0 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, 27148);
        v0 = slt(a0, v0);
        if (v0 == 0) break;
        backedge();
        charge(9);
        v0 = sll(a0, 2);
        v0 = addu(s0, v0);
        lw(v1, v0, kAnalyzeLines);
        v0 = sll(a0, 4);
        v0 = addu(v0, a0);
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        sw(v1, v0, 25780);
        a0 = addiu(a0, 1);
    }
    charge(10);
    lw(v0, s0, 30568);
    sw(v0, s0, 27140);
    sw(zero, s0, 27144);
    jal(0x206FF4, &gen::fn_sub_225670_00225670);
    pop(32, 1);
}

// `lw v0, -18952(gp); bnez; <assert>` (3 + 5) then `lw s1, -18952(gp); jal sub_2255F0; a0 = a1 = a2 = 0; a3 = 4; jal
// sub_10A4E0; li v0, 9; sw v0, 24(s1)`: the analyze window opens with system sound 4, state 9 (13 cycles with the
// closing `b`, 11 without).
void Body::open_analyze_tail(u32 pc_assert, u32 pc_open, u32 pc_sound, u64 cost) {
    need_work(v0, pc_assert);
    charge(cost);
    lw(s1, gp, kGpWork);
    jal(pc_open, &gen::fn_sub_2255F0_002255f0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 4;
    jal(pc_sound, &gen::fn_sub_10A4E0_0010a4e0);
    v0 = 9;
    sw(v0, s1, 24);
}
// `jal sub_2DBA80; li a0, 32; li a1, message; jal btlSupportRequestLine`.
void Body::navi_say(u32 pc_stop, u32 message) {
    jal(pc_stop, &gen::fn_sub_2DBA80_002dba80);
    a0 = 32;
    a1 = message;
    jal(pc_stop + 16, &gen::fn_btlSupportRequestLine_002db9f0);
}
// `li a0, q; jal msgWinRequestMessage; li a0, q + 1; jal sub_3C74E0`.
void Body::yes_no(u32 pc, u32 question) {
    a0 = question;
    jal(pc, &gen::fn_msgWinRequestMessage_003c7430);
    a0 = question + 1;
    jal(pc + 12, &gen::fn_sub_3C74E0_003c74e0);
}

// sub_207340 [bcmConfirmAnalyzeRow]: the analyze row under the cursor (+1032 + 4 +30568) is acted on:
//   kind 0 (the boss / enemy scan): with +0 bit 0x4000 the navigator stops and the yes/no dialog (sub_21C720 ->
//     sub_3C72D0) asks question 0 (menu mode 0), 6 (mode 1 in encounter 417) or 3 (mode 1), state 3; without it
//     sub_21B670, state 1;
//   kind 1 (support): with bit 0x200000 the navigator says 188 / 189 / 190 by the support state +30640 (1 / 2 / 3)
//     and the analyze window opens (state 9); else with bit 0x10000 the dialog asks 9 (mode 0) or 12 (mode 1),
//     state 5; else the navigator says 184, +0 |= 0x10000 and the analyze window opens;
//   kind 2: with bit 0x100000 the navigator says 176 and the analyze window opens; else with bit 0x8000 the dialog
//     asks 15 (mode 1), state 7; else the navigator says 175, +0 |= 0x8000 and the analyze window opens.
// Unknown kinds / modes / states assert (lines 4678, 4718, 4744, 4787). Finally sub_16F3E0(52, row kind).
void Body::sub_207340() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x207368);
    charge(9);
    lw(s1, gp, kGpWork);
    lw(v0, s1, 30568);
    v0 = sll(v0, 2);
    v0 = addu(s1, v0);
    s0 = addiu(v0, 1032);
    lw(v0, v0, 1032);
    a1 = 2;
    // `jal sub_2DBA80; jal sub_21C720; move a0, v0; jal sub_3C72D0; jal sub_1FF740` at pc: the dialog opens, $v0 = mode.
    const auto dialog = [&](u32 pc) {
        jal(pc, &gen::fn_sub_2DBA80_002dba80);
        jal(pc + 8, &gen::fn_sub_21C720_0021c720);
        a0 = v0;
        jal(pc + 20, &gen::fn_sub_3C72D0_003c72d0);
        jal(pc + 28, &gen::fn_sub_1FF740_001ff740);
    };
    const auto state = [&](u32 s) {
        charge(4);
        v0 = s;
        sw(v0, s1, 24);
    };
    if (v0 == a1) {  // kind 2
        charge(5);
        lw(v1, s1, kFlags);
        v0 = lui(0x10);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(9);
            navi_say(0x207700, 176);
            open_analyze_tail(0x207730, 0x20773C, 0x207754, 13);
        } else {
            charge(3);
            v0 = andi(v1, 0x8000);
            if (v0 != 0) {
                charge(11);
                dialog(0x207778);
                bool ok = false;
                if (v0 != 0) {
                    charge(3);
                    v1 = 1;
                    if (v0 == v1) ok = true;
                    else charge(2);
                }
                if (ok) {
                    charge(8);
                    yes_no(0x2077BC, 15);
                } else {
                    charge(5);
                    k_assert(0x2077E4, 4787);
                }
                state(7);
            } else {
                charge(12);
                navi_say(0x2077FC, 175);
                word_or(v0, s1, kFlags, 0x8000);
                open_analyze_tail(0x207838, 0x207844, 0x20785C, 11);
            }
        }
    } else {
        charge(3);
        a0 = 1;
        if (v0 == a0) {  // kind 1
            charge(5);
            lw(v1, s1, kFlags);
            v0 = lui(0x20);
            v0 = v1 & v0;
            if (v0 != 0) {
                charge(4);
                lw(v1, s1, kSupportState);
                v0 = 3;
                if (v1 == v0) {
                    charge(8);
                    navi_say(0x207534, 190);
                } else {
                    charge(2);
                    if (v1 == a1) {
                        charge(8);
                        navi_say(0x207514, 189);
                    } else {
                        charge(2);
                        if (v1 == a0) {
                            charge(8);
                            navi_say(0x2074F4, 188);
                        } else {
                            charge(2);
                            charge(5);
                            k_assert(0x207560, 4718);
                        }
                    }
                }
                charge(3);
                open_analyze_tail(0x207580, 0x20758C, 0x2075A4, 13);
            } else {
                charge(4);
                v0 = lui(0x1);
                v0 = v1 & v0;
                if (v0 != 0) {
                    charge(12);
                    dialog(0x2075CC);
                    v1 = 1;
                    if (v0 == v1) {
                        charge(8);
                        yes_no(0x207630, 12);
                    } else {
                        charge(2);
                        if (v0 == 0) {
                            charge(8);
                            yes_no(0x207610, 9);
                        } else {
                            charge(2);
                            charge(5);
                            k_assert(0x207658, 4744);
                        }
                    }
                    state(5);
                } else {
                    charge(13);
                    navi_say(0x207670, 184);
                    lw(v1, s1, kFlags);
                    v0 = lui(0x1);
                    v0 = v1 | v0;
                    sw(v0, s1, kFlags);
                    open_analyze_tail(0x2076B0, 0x2076BC, 0x2076D4, 13);
                }
            }
        } else {
            charge(2);
            if (v0 == 0) {  // kind 0
                charge(4);
                lw(v0, s1, kFlags);
                v0 = andi(v0, 0x4000);
                if (v0 != 0) {
                    charge(12);
                    dialog(0x2073C0);
                    v1 = 1;
                    if (v0 == v1) {
                        charge(5);
                        jal(0x207420, &gen::fn_btlGetEncounterId_002d5550);
                        v1 = 417;
                        if (v0 == v1) {
                            charge(8);
                            yes_no(0x207440, 6);
                        } else {
                            charge(2);
                            charge(8);
                            yes_no(0x207460, 3);
                        }
                    } else {
                        charge(2);
                        if (v0 == 0) {
                            charge(8);
                            yes_no(0x207404, 0);
                        } else {
                            charge(2);
                            charge(5);
                            k_assert(0x207488, 4678);
                        }
                    }
                    state(3);
                } else {
                    charge(6);
                    jal(0x2074A0, &gen::fn_sub_21B670_0021b670);
                    v0 = 1;
                    sw(v0, s1, 24);
                }
            } else {
                charge(2);
            }
        }
    }
    charge(10);
    a0 = 52;
    lw(a1, s0, 0);
    jal(0x207874, &gen::fn_sub_16F3E0_0016f3e0);
    pop(48, 2);
}

// sub_2078A0 [bcmPreviewItem]: asserts sub_30C0C0() (line 4816) and previews its item (sub_249420(+0, +2, +4)); +16 = 9.
void Body::sub_2078A0() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x2078C8);
    charge(6);
    lw(s1, gp, kGpWork);
    jal(0x2078D4, &gen::fn_sub_30C0C0_0030c0c0);
    s0 = v0;
    check(s0 != 0, 0x2078F4, 4816);
    charge(13);
    lhu(a0, s0, 0);
    lhu(a1, s0, 2);
    lhu(a2, s0, 4);
    jal(0x207908, &gen::fn_sub_249420_00249420);
    v1 = 9;
    sw(v1, s1, kListKind);
    pop(48, 2);
}

// sub_208460 [bcmCloseSubWindow]: the open sub list +16 (1 -> +4 |= 1, 2 -> +4 |= 2, 3, 4; else assert, line 5140)
// closes its window (sub_222ED0); system sound 4; +16 = 0.
void Body::sub_208460() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x208484);
    charge(5);
    lw(s0, gp, kGpWork);
    lw(v1, s0, kListKind);
    v0 = 4;
    if (v1 == v0) {
        charge(4);
        jal(0x208514, &gen::fn_sub_222ED0_00222ed0);
    } else {
        charge(3);
        v0 = 3;
        if (v1 == v0) {
            charge(4);
            jal(0x208504, &gen::fn_sub_222ED0_00222ed0);
        } else {
            charge(3);
            v0 = 2;
            if (v1 == v0) {
                charge(7);
                word_or(v0, s0, kFlags2, 0x2);
                jal(0x2084F4, &gen::fn_sub_222ED0_00222ed0);
            } else {
                charge(3);
                v0 = 1;
                if (v1 == v0) {
                    charge(7);
                    word_or(v0, s0, kFlags2, 0x1);
                    jal(0x2084D8, &gen::fn_sub_222ED0_00222ed0);
                } else {
                    charge(2);
                    charge(5);
                    k_assert(0x208530, 5140);
                }
            }
        }
    }
    charge(12);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 4;
    jal(0x208548, &gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, kListKind);
    pop(32, 1);
}

// =====================================================================================================================
// The list openers and the menu's top-level transitions
// =====================================================================================================================

// sub_2016B0 [bcmDraw]: unless a tutorial / item preview is up (+16 = 9, 10, 11), draws the top menu (sub_21F410) and
// the sub window (sub_221B60).
void Body::sub_2016B0() {
    enter(5);
    push(16, 0);
    need_work(v1, 0x2016D0);
    charge(5);
    lw(v1, gp, kGpWork);
    lw(a0, v1, kListKind);
    v1 = 11;
    if (a0 != v1) {
        charge(3);
        v1 = 10;
        if (a0 != v1) {
            charge(3);
            v1 = 9;
            if (a0 != v1) {
                charge(4);
                jal(0x201704, &gen::fn_sub_21F410_0021f410);
                jal(0x20170C, &gen::fn_sub_221B60_00221b60);
            }
        }
    }
    charge(4);
    pop(16, 0);
}

// sub_201A50 [bcmBackToTop]: refreshes the top menu (sub_201880), +0 |= 0x40, the panel goes back to the top
// (sub_21F150(+36)), system sound (1, 15, 2, 17); +16 = 0.
void Body::sub_201A50() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x201A74);
    charge(21);
    lw(s0, gp, kGpWork);
    jal(0x201A80, &gen::fn_sub_201880_00201880);
    word_or(v0, s0, kFlags, 0x40);
    lw(a0, s0, kWord36);
    jal(0x201A98, &gen::fn_sub_21F150_0021f150);
    a0 = 1;
    a1 = 15;
    a2 = 2;
    a3 = 17;
    jal(0x201AB0, &gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, kListKind);
    pop(32, 1);
}

// The tail of sub_201B50 .. sub_201E00 (the second "work != NULL" check is the caller's): refresh the top menu
// (sub_201880, jal at pc_menu), then reopen the window of every built list -- skills (bit 2, sub_2025E0), items (4,
// sub_2031C0), personas (8, sub_203C30), targets (0x10, sub_204CC0); the jals are 0x18 apart.
void Body::reopen_windows(u32 pc_menu) {
    charge(7);
    lw(s0, gp, kGpWork);
    jal(pc_menu, &gen::fn_sub_201880_00201880);
    const struct {
        u32 bit;
        rt::Fn fn;
    } kLists[] = {{0x2, &gen::fn_sub_2025E0_002025e0}, {0x4, &gen::fn_sub_2031C0_002031c0},
                  {0x8, &gen::fn_sub_203C30_00203c30}, {0x10, &gen::fn_sub_204CC0_00204cc0}};
    for (std::size_t i = 0; i < 4; ++i) {
        if (i != 0) charge(4);
        lw(v1, s0, kFlags);
        v1 = andi(v1, kLists[i].bit);
        if (v1 != 0) {
            charge(2);
            jal(pc_menu + 0x18 * static_cast<u32>(i + 1), kLists[i].fn);
        }
    }
    charge(5);
    pop(32, 1);
}

// sub_201B50 [bcmResume]: +0 |= 1 (menu active), then reopen_windows.
void Body::sub_201B50() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x201B74);
    charge(7);
    lw(v1, gp, kGpWork);
    word_or(v0, v1, kFlags, 0x1);
    need_work(v0, 0x201BA4);
    reopen_windows(0x201BB0);
}

// sub_201C30 [bcmSuspend]: +0 |= 0x20000000 (a dialog is over the menu), then reopen_windows.
void Body::sub_201C30() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x201C54);
    charge(8);
    lw(a0, gp, kGpWork);
    lw(v1, a0, kFlags);
    v0 = lui(0x2000);
    v0 = v1 | v0;
    sw(v0, a0, kFlags);
    need_work(v0, 0x201C88);
    reopen_windows(0x201C94);
}

// sub_201D10 [bcmDeactivate]: +0 = (+0 & ~1) | 0x40, then reopen_windows.
void Body::sub_201D10() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x201D34);
    charge(10);
    lw(a0, gp, kGpWork);
    lw(v1, a0, kFlags);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, a0, kFlags);
    v0 = ori(v0, 0x40);
    sw(v0, a0, kFlags);
    need_work(v0, 0x201D70);
    reopen_windows(0x201D7C);
}

// sub_201E00 [bcmUnsuspend]: +0 = (+0 & ~0x20000000) | 0x40, then reopen_windows.
void Body::sub_201E00() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x201E24);
    charge(11);
    lw(a0, gp, kGpWork);
    lw(v1, a0, kFlags);
    v0 = lui(0xDFFF);
    v0 = ori(v0, 0xFFFF);
    v0 = v1 & v0;
    sw(v0, a0, kFlags);
    v0 = ori(v0, 0x40);
    sw(v0, a0, kFlags);
    need_work(v0, 0x201E64);
    reopen_windows(0x201E70);
}

// sub_202010 [bcmOpenSkillList]: asserts the skill lines are not built (line 1984); the skill list: the sub_30C0C0
// entry first (bit 1; bit 0 when the actor sub_1FF500(1) can pay it, sub_3086F0(actor +2604, skill)), then every
// battle-usable skill (sub_2055F0) of the current persona (bit 0 by cost); asserts 1..9 entries (lines 2019 / 2020);
// +116 = entries, +112 = rows (at most 4); the cursor record +30296 (sub_208570); with flag 390 the remembered skill
// (sub_16F380(49)) is placed in the window, else the cursor starts at 0; builds the lines (sub_2024B0), fills the
// panel rows as sub_2025E0, +27940 = 0, +27944 = 1, opens the skill list (sub_222A60), system sound 3; +16 = 1.
void Body::sub_202010() {
    enter(13);
    push(144, 8);
    need_work(v0, 0x202050);
    charge(11);
    lw(s1, gp, kGpWork);
    s7 = addiu(s1, kPanelRows);
    a0 = 1;
    jal(0x202064, &gen::fn_sub_1FF500_001ff500);
    s0 = v0;
    lw(v0, s1, kFlags);
    v0 = nor(v0, 0);
    v0 = andi(v0, 0x2);
    check(v0 != 0, 0x202090, 1984);
    charge(17);
    a0 = 1;
    jal(0x20209C, &gen::fn_datPersonaGetByPcId_00174800);
    s2 = v0;
    a0 = s2;
    jal(0x2020AC, &gen::fn_sub_176A30_00176a30);
    s5 = v0;
    a0 = s2;
    jal(0x2020BC, &gen::fn_sub_173370_00173370);
    s6 = v0;
    s2 = 0;
    jal(0x2020CC, &gen::fn_sub_30C0C0_0030c0c0);
    if (v0 != 0) {
        charge(12);
        sw(zero, s1, kSkills - 4);
        lhu(v0, v0, 0);
        sh(v0, s1, kSkills);
        word_or(v0, s1, kSkills - 4, 0x2);
        lw(a0, s0, 2604);
        lhu(a1, s1, kSkills);
        jal(0x2020FC, &gen::fn_sub_3086F0_003086f0);
        if (v0 != 0) {
            charge(3);
            word_or(v0, s1, kSkills - 4, 0x1);
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(3);
    s3 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s3, s5);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = sll(s3, 1);
        s4 = addu(s6, v0);
        lhu(a0, s4, 0);
        jal(0x202134, &gen::fn_sub_2055F0_002055f0);
        if (v0 != 0) {
            charge(12);
            v0 = sll(s2, 3);
            v1 = addu(s1, v0);
            lhu(v0, s4, 0);
            sh(v0, v1, kSkills);
            s4 = addiu(v1, kSkills - 4);
            sw(zero, v1, kSkills - 4);
            lw(a0, s0, 2604);
            lhu(a1, v1, kSkills);
            jal(0x202164, &gen::fn_sub_3086F0_003086f0);
            if (v0 != 0) {
                charge(3);
                word_or(v0, s4, 0, 0x1);
            }
            charge(1);
            s2 = addiu(s2, 1);
        }
        charge(1);
        s3 = addiu(s3, 1);
    }
    charge(2);
    check(s2 != 0, 0x2021A8, 2019);
    charge(3);
    at = slti(s2, 10);
    check(at != 0, 0x2021C8, 2020);
    charge(5);
    sw(s2, s1, 116);
    sw(s2, s1, kSkillCount);
    at = slti(s2, 5);
    if (at == 0) {
        charge(2);
        v0 = 4;
        sw(v0, s1, kSkillCount);
    }
    charge(17);
    a0 = 1;
    jal(0x2021F0, &gen::fn_sub_1FF500_001ff500);
    s2 = v0;
    sw(zero, s1, 30296);
    lw(v0, s1, kSkillCount);
    sw(v0, s1, 30304);
    lw(v0, s1, 116);
    sw(v0, s1, 30312);
    a0 = addiu(s1, 30296);
    jal(0x202214, &gen::fn_sub_208570_00208570);
    a0 = 390;
    jal(0x202220, &gen::fn_datGetFlag_0016f190);
    // the remembered skill: not found -> 0 / 0; the last entry -> window idx - (rows - 1); beyond rows - 2 -> window
    // idx - (rows - 2); else window 0; the cursor on it.
    const auto reset = [&](u64 cost) {
        charge(cost);
        sw(zero, s1, 30308);
        sw(zero, s1, 30300);
    };
    if (v0 == 0) {
        reset(2);
    } else {
        charge(5);
        a0 = 49;
        jal(0x202234, &gen::fn_sub_16F380_0016f380);
        if (v0 == 0) {
            reset(4);
        } else {
            charge(5);
            a0 = andi(v0, 0xFFFF);
            a1 = 0;
            lw(v1, s1, 116);
            for (;;) {
                charge(3);
                v0 = slt(a1, v1);
                if (v0 == 0) break;
                backedge();
                charge(5);
                v0 = sll(a1, 3);
                v0 = addu(s1, v0);
                lhu(v0, v0, kSkills);
                if (v0 == a0) break;
                charge(1);
                a1 = addiu(a1, 1);
            }
            charge(2);
            if (a1 == v1) {
                reset(4);
            } else {
                charge(3);
                v0 = addiu(v1, -1);
                if (a1 == v0) {
                    charge(7);
                    lw(v0, s1, kSkillCount);
                    v0 = addiu(v0, -1);
                    v0 = subu(a1, v0);
                    sw(v0, s1, 30300);
                    sw(a1, s1, 30308);
                } else {
                    charge(5);
                    lw(v0, s1, kSkillCount);
                    v0 = addiu(v0, -2);
                    at = slt(v0, a1);
                    if (at != 0) {
                        charge(5);
                        v0 = subu(a1, v0);
                        sw(v0, s1, 30300);
                        sw(a1, s1, 30308);
                    } else {
                        charge(4);
                        sw(zero, s1, 30300);
                        sw(a1, s1, 30308);
                    }
                }
            }
        }
    }
    charge(6);
    jal(0x20230C, &gen::fn_sub_2024B0_002024b0);
    lw(s4, s1, 116);
    at = slti(s4, 5);
    if (at == 0) {
        charge(1);
        s4 = 4;
    }
    charge(3);
    s3 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s3, s4);
        if (v0 == 0) break;
        backedge();
        charge(13);
        a0 = sll(s3, 3);
        v1 = addu(a0, s3);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v0 = sll(v0, 4);
        s0 = addu(s7, v0);  // 144 * row
        sw(zero, s0, 0);
        a0 = addu(s1, a0);
        v1 = addiu(a0, kSkills - 4);
        lw(v0, a0, kSkills - 4);
        v0 = andi(v0, 0x1);
        if (v0 != 0) {
            charge(3);
            word_or(v0, s0, 0, 0x1);
        }
        charge(4);
        lw(v0, v1, 0);
        v0 = andi(v0, 0x2);
        if (v0 != 0) {
            charge(3);
            word_or(v0, s0, 0, 0x2);
        }
        charge(17);
        v0 = sll(s3, 2);
        v0 = addu(s1, v0);
        lw(v0, v0, kSkillLines);
        sw(v0, s0, 4);
        a1 = addiu(a0, kSkills);
        lhu(v1, a0, kSkills);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, gp, kGpSkillTable);
        v0 = addu(v0, v1);
        lbu(v1, v0, 3);
        v0 = 2;
        if (v1 == v0) {
            charge(2);
            v0 = 1;
            sw(v0, s0, 8);
        } else {
            charge(3);
            v0 = 1;
            if (v1 == v0) {
                charge(3);
                sw(zero, s0, 8);
            } else {
                charge(2);
            }
        }
        charge(6);
        lw(a0, s2, 2604);
        lhu(a1, a1, 0);
        jal(0x202404, &gen::fn_sub_3083F0_003083f0);
        sw(v0, s0, 12);
        s3 = addiu(s3, 1);
    }
    charge(33);
    sw(zero, s1, 30272);
    sw(s4, s1, kPanelCount);
    lw(v0, s1, 30308);
    sw(v0, s1, kPanelCursor);
    lw(v0, s1, 30300);
    sw(v0, s1, kPanelWindow);
    lw(v0, s1, 116);
    sw(v0, s1, kPanelTotal);
    sw(zero, s1, 27940);
    v0 = 1;
    sw(v0, s1, 27944);
    jal(0x20244C, &gen::fn_sub_222A60_00222a60);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 3;
    jal(0x202464, &gen::fn_sub_10A4E0_0010a4e0);
    v1 = 1;
    sw(v1, s1, kListKind);
    pop(144, 8);
}

// sub_202D70 [bcmOpenItemList]: the item list -- every usable item 4000..4222 (sub_205650) the party holds
// (sub_170760(1, item) & 0xFFFF) into +156, +608 = their count; builds the lines (sub_203030), the cursor record
// +30348 (sub_208570); with flag 390 the remembered item (sub_16F380(50)) is placed in the window, else the cursor
// starts at 0; fills 1040-byte panel rows (line, stock) for the visible rows, opens the item list (sub_222930), system
// sound 3; +16 = 2.
void Body::sub_202D70() {
    enter(10);
    push(96, 5);
    need_work(v0, 0x202DA4);
    charge(6);
    lw(s2, gp, kGpWork);
    s1 = addiu(s2, kPanelRows);
    s0 = 0;
    s3 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s3, 223);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = addiu(s3, 4000);
        a0 = andi(v0, 0xFFFF);
        jal(0x202DCC, &gen::fn_sub_205650_00205650);
        if (v0 != 0) {
            charge(9);
            v0 = addiu(s3, 4000);
            a1 = sext_h(v0);
            a0 = 1;
            jal(0x202DEC, &gen::fn_sub_170760_00170760);
            v0 = andi(v0, 0xFFFF);
            if (v0 != 0) {
                charge(5);
                v1 = addiu(s3, 4000);
                v0 = sll(s0, 1);
                v0 = addu(s2, v0);
                sh(v1, v0, kItems);
                s0 = addiu(s0, 1);
            }
        }
        charge(1);
        s3 = addiu(s3, 1);
    }
    charge(16);
    sw(s0, s2, kItemCount);
    jal(0x202E28, &gen::fn_sub_203030_00203030);
    sw(zero, s2, 30348);
    lw(v0, s2, kItemLineCount);
    sw(v0, s2, 30356);
    lw(v0, s2, kItemCount);
    sw(v0, s2, 30364);
    a0 = addiu(s2, 30348);
    jal(0x202E48, &gen::fn_sub_208570_00208570);
    a0 = 390;
    jal(0x202E54, &gen::fn_datGetFlag_0016f190);
    const auto reset = [&](u64 cost) {
        charge(cost);
        sw(zero, s2, 30360);
        sw(zero, s2, 30352);
    };
    if (v0 == 0) {
        reset(2);
    } else {
        charge(5);
        a0 = 50;
        jal(0x202E68, &gen::fn_sub_16F380_0016f380);
        if (v0 == 0) {
            reset(4);
        } else {
            charge(4);
            a1 = 0;
            lw(a0, s2, kItemCount);
            for (;;) {
                charge(3);
                v1 = slt(a1, a0);
                if (v1 == 0) break;
                backedge();
                charge(5);
                v1 = sll(a1, 1);
                v1 = addu(s2, v1);
                lhu(v1, v1, kItems);
                if (v1 == v0) break;
                charge(1);
                a1 = addiu(a1, 1);
            }
            charge(2);
            if (a1 == a0) {
                reset(4);
            } else {
                charge(3);
                v0 = addiu(a0, -1);
                if (a1 == v0) {
                    charge(7);
                    lw(v0, s2, kItemLineCount);
                    v0 = addiu(v0, -1);
                    v0 = subu(a1, v0);
                    sw(v0, s2, 30352);
                    sw(a1, s2, 30360);
                } else {
                    charge(5);
                    lw(v0, s2, kItemLineCount);
                    v0 = addiu(v0, -2);
                    at = slt(v0, a1);
                    if (at != 0) {
                        charge(5);
                        v0 = subu(a1, v0);
                        sw(v0, s2, 30352);
                        sw(a1, s2, 30360);
                    } else {
                        charge(4);
                        sw(zero, s2, 30352);
                        sw(a1, s2, 30360);
                    }
                }
            }
        }
    }
    charge(4);
    lw(s3, s2, kItemCount);
    at = slti(s3, 5);
    if (at == 0) {
        charge(1);
        s3 = 4;
    }
    charge(3);
    s4 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s4, s3);
        if (v0 == 0) break;
        backedge();
        charge(19);
        v0 = sll(s4, 6);
        v0 = addu(v0, s4);
        v0 = sll(v0, 4);
        s0 = addu(s1, v0);  // 1040 * row
        v0 = sll(s4, 2);
        v0 = addu(s2, v0);
        lw(v0, v0, kItemLines);
        sw(v0, s0, 0);
        lw(v0, s2, 30352);
        v0 = addu(v0, s4);
        v0 = sll(v0, 1);
        v0 = addu(s2, v0);
        lh(a1, v0, kItems);
        a0 = 1;
        jal(0x202F94, &gen::fn_sub_170760_00170760);
        v0 = andi(v0, 0xFFFF);
        sw(v0, s0, 4);
        s4 = addiu(s4, 1);
    }
    charge(28);
    sw(zero, s2, 30272);
    sw(s3, s2, kPanelCount);
    lw(v0, s2, 30360);
    sw(v0, s2, kPanelCursor);
    lw(v0, s2, 30352);
    sw(v0, s2, kPanelWindow);
    lw(v0, s2, kItemCount);
    sw(v0, s2, kPanelTotal);
    sw(zero, s2, 27944);
    jal(0x202FD8, &gen::fn_sub_222930_00222930);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 3;
    jal(0x202FF0, &gen::fn_sub_10A4E0_0010a4e0);
    v1 = 2;
    sw(v1, s2, kListKind);
    pop(96, 5);
}

// sub_203850 [bcmOpenPersonaList]: builds the persona lines (sub_203990), the cursor record +30400 (sub_208570; window
// and cursor 0, +30408 rows, +30416 entries), fills the 784-byte panel rows for the visible rows (at most 4), opens the
// persona list (sub_224660), system sound 3; +20 = 0, +16 = 3.
void Body::sub_203850() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x203878);
    charge(18);
    lw(s1, gp, kGpWork);
    s0 = addiu(s1, kPanelRows);
    jal(0x203888, &gen::fn_sub_203990_00203990);
    sw(zero, s1, 30400);
    sw(zero, s1, 30404);
    sw(zero, s1, 30412);
    lw(v0, s1, kPersonaLineCount);
    sw(v0, s1, 30408);
    lw(v0, s1, kPersonaCount);
    sw(v0, s1, 30416);
    a0 = addiu(s1, 30400);
    jal(0x2038B0, &gen::fn_sub_208570_00208570);
    lw(a0, s1, kPersonaCount);
    at = slti(a0, 5);
    if (at == 0) {
        charge(1);
        a0 = 4;
    }
    charge(3);
    a1 = 0;
    for (;;) {
        charge(3);
        v0 = slt(a1, a0);
        if (v0 == 0) break;
        backedge();
        charge(17);
        v0 = sll(a1, 3);
        v1 = subu(v0, a1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        v1 = addu(s0, v0);  // 784 * row
        v0 = sll(a1, 2);
        v0 = addu(s1, v0);
        lw(v0, v0, kPersonaLines);
        sw(v0, v1, 768);
        lw(v0, s1, 30404);
        v0 = addu(a1, v0);
        v0 = sll(v0, 3);
        v0 = addu(s1, v0);
        lw(v0, v0, kPersonas + 4);
        sw(v0, v1, 772);
        a1 = addiu(a1, 1);
    }
    charge(25);
    sw(zero, s1, 30272);
    sw(a0, s1, kPanelCount);
    lw(v0, s1, 30412);
    sw(v0, s1, kPanelCursor);
    lw(v0, s1, 30404);
    sw(v0, s1, kPanelWindow);
    lw(v0, s1, kPersonaCount);
    sw(v0, s1, kPanelTotal);
    jal(0x203948, &gen::fn_sub_224660_00224660);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 3;
    jal(0x203960, &gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s1, 20);
    v1 = 3;
    sw(v1, s1, kListKind);
    pop(48, 2);
}

// sub_204480 [bcmOpenTargetList]: the cursor record +30452 (sub_208570; +30460 rows, +30468 entries); with flag 390 the
// remembered target sub_16F380(51) -- a member's pc id, 12 "All Members", 11 "Support" -- puts the cursor on its row,
// else row 0; builds the lines (sub_204760), fills the 1056-byte panel rows (kind, lines, Orgia flag), +30272 = rows
// beyond 4, opens the target list (sub_222FA0), system sound 3; +16 = 4.
void Body::sub_204480() {
    enter(7);
    push(48, 2);
    need_work(v0, 0x2044A8);
    charge(15);
    lw(s1, gp, kGpWork);
    s0 = addiu(s1, kPanelRows);
    sw(zero, s1, 30452);
    lw(v0, s1, kTargetLineCount);
    sw(v0, s1, 30460);
    lw(v0, s1, kTargetCount);
    sw(v0, s1, 30468);
    a0 = addiu(s1, 30452);
    jal(0x2044D0, &gen::fn_sub_208570_00208570);
    a0 = 390;
    jal(0x2044DC, &gen::fn_datGetFlag_0016f190);
    const auto reset = [&](u64 cost) {
        charge(cost);
        sw(zero, s1, 30464);
        sw(zero, s1, 30456);
    };
    if (v0 == 0) {
        reset(2);
    } else {
        charge(5);
        a0 = 51;
        jal(0x2044F0, &gen::fn_sub_16F380_0016f380);
        if (v0 == 0) {
            reset(4);
        } else {
            charge(9);
            t2 = 0;
            t3 = 0;
            lw(t1, s1, kTargetCount);
            a2 = 1;
            a3 = 2;
            a0 = 11;
            a1 = 12;
            for (;;) {
                charge(3);
                v1 = slt(t3, t1);
                if (v1 == 0) break;
                backedge();
                charge(8);
                v1 = sll(t3, 1);
                v1 = addu(v1, t3);
                v1 = sll(v1, 3);
                v1 = addu(s1, v1);
                t0 = addiu(v1, kTargets);
                lw(v1, v1, kTargets + kRowKind);
                if (v1 == a3) {  // "Support": 11
                    charge(2);
                    if (v0 == a0) {
                        charge(1);
                        t2 = a2;
                    }
                } else {
                    charge(2);
                    if (v1 == 0) {  // "All Members": 12
                        charge(2);
                        if (v0 == a1) {
                            charge(3);
                            t2 = a2;
                        }
                    } else {
                        charge(2);
                        if (v1 == a2) {  // a member: its pc id
                            charge(3);
                            lhu(v1, t0, kRowPcId);
                            if (v0 == v1) {
                                charge(3);
                                t2 = a2;
                            }
                        } else {
                            charge(2);
                        }
                    }
                }
                charge(2);
                if (t2 != 0) break;
                charge(1);
                t3 = addiu(t3, 1);
            }
            charge(2);
            if (t3 == t1) {
                reset(4);
            } else {
                charge(4);
                sw(t3, s1, 30464);
                sw(zero, s1, 30456);
            }
        }
    }
    charge(7);
    jal(0x2045EC, &gen::fn_sub_204760_00204760);
    v0 = 0;
    a1 = 1;
    a2 = 2;
    for (;;) {
        charge(4);
        lw(a0, s1, kTargetLineCount);
        v1 = slt(v0, a0);
        if (v1 == 0) break;
        backedge();
        charge(13);
        v1 = sll(v0, 1);
        v1 = addu(v1, v0);
        v1 = sll(v1, 3);
        a0 = addu(s1, v1);
        t0 = addiu(a0, kTargets);
        v1 = sll(v0, 5);
        v1 = addu(v1, v0);
        v1 = sll(v1, 5);
        a3 = addu(s0, v1);  // 1056 * row
        sw(zero, a3, 1040);
        lw(v1, a0, kTargets + kRowKind);
        if (v1 == a2) {
            charge(7);
            sw(a2, a3, 0);
            v1 = sll(v0, 3);
            a0 = addu(s1, v1);
            lw(v1, a0, kTargetLines);
            sw(v1, a3, 8);
            lw(v1, a0, kTargetLines + 4);
            sw(v1, a3, 12);
        } else {
            charge(2);
            if (v1 == 0) {
                charge(7);
                sw(a1, a3, 0);
                v1 = sll(v0, 3);
                v1 = addu(s1, v1);
                lw(v1, v1, kTargetLines);
                sw(v1, a3, 8);
            } else {
                charge(2);
                if (v1 == a1) {
                    charge(9);
                    sw(zero, a3, 0);
                    v1 = sll(v0, 3);
                    a0 = addu(s1, v1);
                    lw(v1, a0, kTargetLines);
                    sw(v1, a3, 8);
                    lw(v1, a0, kTargetLines + 4);
                    sw(v1, a3, 12);
                } else {
                    charge(2);
                }
            }
        }
        charge(4);
        lw(v1, t0, kRowFlags);
        v1 = andi(v1, 0x2);
        if (v1 != 0) {
            charge(1);
            sw(a1, a3, 1040);
        }
        charge(1);
        v0 = addiu(v0, 1);
    }
    charge(3);
    at = slti(a0, 5);
    if (at != 0) {
        charge(3);
        sw(zero, s1, 30272);
    } else {
        charge(2);
        v0 = addiu(a0, -4);
        sw(v0, s1, 30272);
    }
    charge(24);
    lw(v0, s1, kTargetLineCount);
    sw(v0, s1, kPanelCount);
    lw(v0, s1, 30464);
    sw(v0, s1, kPanelCursor);
    lw(v0, s1, 30456);
    sw(v0, s1, kPanelWindow);
    lw(v0, s1, kTargetCount);
    sw(v0, s1, kPanelTotal);
    jal(0x204718, &gen::fn_sub_222FA0_00222fa0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 3;
    jal(0x204730, &gen::fn_sub_10A4E0_0010a4e0);
    v1 = 4;
    sw(v1, s1, kListKind);
    pop(48, 2);
}

// sub_2065A0 [bcmConfirmTactic]: asserts the tactic under the cursor (+944 + 4 +30516) is "Assign Target" (line 4191);
// gives it, with the target +1064, to the target row under the cursor (+30464): a member row gets {tactic, target}, bit
// 0 and a navigator comment (sub_208860); "All Members" gives it to every unused member row and comments on a random
// member (sub_208790); "Support" asserts (line 4235). Then the analyze window over the targets (sub_205D60).
void Body::sub_2065A0() {
    enter(6);
    push(32, 1);
    need_work(v0, 0x2065C4);
    charge(8);
    lw(s0, gp, kGpWork);
    lw(v0, s0, 30516);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    lw(v1, v0, 944);
    v0 = 7;
    check(v1 == v0, 0x2065F8, 4191);
    charge(10);
    lw(v1, s0, 30464);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    v0 = addu(s0, v0);
    a1 = addiu(v0, kTargets);
    lw(v1, v0, kTargets + kRowKind);
    v0 = 2;
    if (v1 == v0) {
        charge(5);
        k_assert(0x20671C, 4235);
    } else {
        charge(3);
        a0 = 1;
        if (v1 == a0) {
            charge(15);
            lw(v0, s0, 30516);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lw(v0, v0, 944);
            sw(v0, a1, kRowTactic);
            lw(v0, s0, 1064);
            sw(v0, a1, kRowTarget);
            word_or(v0, a1, kRowFlags, 0x1);
            lhu(a0, a1, kRowPcId);
            jal(0x206700, &gen::fn_sub_208860_00208860);
        } else {
            charge(2);
            if (v1 == 0) {
                charge(3);
                a1 = 0;
                for (;;) {
                    charge(4);
                    lw(v0, s0, kTargetCount);
                    v0 = slt(a1, v0);
                    if (v0 == 0) break;
                    backedge();
                    charge(9);
                    v0 = sll(a1, 1);
                    v0 = addu(v0, a1);
                    v0 = sll(v0, 3);
                    v0 = addu(s0, v0);
                    v1 = addiu(v0, kTargets);
                    lw(v0, v0, kTargets + kRowFlags);
                    v0 = andi(v0, 0x2);
                    if (v0 == 0) {
                        charge(3);
                        lw(v0, v1, kRowKind);
                        if (v0 == a0) {
                            charge(10);
                            lw(v0, s0, 30516);
                            v0 = sll(v0, 2);
                            v0 = addu(s0, v0);
                            lw(v0, v0, 944);
                            sw(v0, v1, kRowTactic);
                            lw(v0, s0, 1064);
                            sw(v0, v1, kRowTarget);
                            word_or(v0, v1, kRowFlags, 0x1);
                        } else {
                            charge(2);
                        }
                    }
                    charge(1);
                    a1 = addiu(a1, 1);
                }
                charge(4);
                jal(0x2066C4, &gen::fn_sub_208790_00208790);
            } else {
                charge(2);
            }
        }
    }
    charge(7);
    jal(0x206724, &gen::fn_sub_205D60_00205d60);
    pop(32, 1);
}

// sub_206740 [bcmOpenAnalyzeList]: asserts the analyze lines are not built (line 4255) and the menu mode is not 2
// (line 4256); the analyze rows (+1032): kind 0, kind 1, and kind 2 in mode 1 when persona 6 has skill 325; +1056 =
// rows, +1060 = rows capped at 4; the cursor record +30556 (sub_208570); with flag 390 the remembered kind
// (sub_16F380(52)) puts the cursor on its row, else row 0; builds the row lines as sub_207010 and the title line
// (+30632: the navigator's name sub_1775A0(4), or 6 in mode 1; else line 4413); +0 |= 0x2000; the 272-byte panel rows
// (+25776: kind 0 -> 2 with the scan bit 0x4000; kind 1 -> 1 with 0x200000, 2 with 0x10000; kind 2 -> 1 with
// 0x100000, 2 with 0x8000; else 0; +25780 the line) and summary words, opens the analyze list (sub_2254A0), system
// sound 3; +24 = 0, +16 = 6.
void Body::sub_206740() {
    enter(12);
    push(128, 7);
    need_work(v0, 0x20677C);
    charge(6);
    lw(s1, gp, kGpWork);
    lw(v0, s1, kFlags);
    v0 = nor(v0, 0);
    v0 = andi(v0, 0x2000);
    check(v0 != 0, 0x2067A8, 4255);
    charge(4);
    lw(v1, s1, kMode);
    v0 = 2;
    check(v1 != v0, 0x2067CC, 4256);
    charge(4);
    s3 = 0;
    s4 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s4, 3);
        if (v0 == 0) break;
        backedge();
        charge(6);
        v0 = sll(s3, 2);
        v0 = addu(s1, v0);
        s0 = addiu(v0, 1032);
        v0 = 2;
        if (s4 == v0) {  // kind 2: mode 1, persona 6 knows skill 325
            charge(4);
            lw(v1, s1, kMode);
            v0 = 1;
            if (v1 == v0) {
                charge(15);
                a0 = 6;
                jal(0x20685C, &gen::fn_datPersonaGetByPcId_00174800);
                s5 = v0;
                a0 = s5;
                jal(0x20686C, &gen::fn_sub_173370_00173370);
                s6 = v0;
                a0 = s5;
                jal(0x20687C, &gen::fn_sub_176A30_00176a30);
                a1 = 0;
                a0 = 325;
                for (;;) {
                    charge(3);
                    v1 = slt(a1, v0);
                    if (v1 == 0) break;
                    backedge();
                    charge(5);
                    v1 = sll(a1, 1);
                    v1 = addu(s6, v1);
                    lhu(v1, v1, 0);
                    if (v1 == a0) break;
                    charge(1);
                    a1 = addiu(a1, 1);
                }
                charge(2);
                if (a1 != v0) {
                    charge(3);
                    v0 = 2;
                    sw(v0, s0, 0);
                    s3 = addiu(s3, 1);
                }
            } else {
                charge(2);
                if (v1 != 0) charge(2);
            }
        } else {
            charge(3);
            v0 = 1;
            if (s4 == v0) {
                charge(4);
                sw(v0, s0, 0);
                s3 = addiu(s3, 1);
            } else {
                charge(2);
                if (s4 == 0) {
                    charge(4);
                    sw(zero, s0, 0);
                    s3 = addiu(s3, 1);
                } else {
                    charge(2);
                }
            }
        }
        charge(1);
        s4 = addiu(s4, 1);
    }
    charge(5);
    sw(s3, s1, 1056);
    sw(s3, s1, kAnalyzeLineCount);
    at = slti(s3, 5);
    if (at == 0) {
        charge(2);
        v0 = 4;
        sw(v0, s1, kAnalyzeLineCount);
    }
    charge(13);
    sw(zero, s1, 30556);
    lw(v0, s1, 1056);
    sw(v0, s1, 30572);
    lw(v0, s1, kAnalyzeLineCount);
    sw(v0, s1, 30564);
    a0 = addiu(s1, 30556);
    jal(0x206910, &gen::fn_sub_208570_00208570);
    a0 = 390;
    jal(0x20691C, &gen::fn_datGetFlag_0016f190);
    const auto reset = [&](u64 cost) {
        charge(cost);
        sw(zero, s1, 30568);
        sw(zero, s1, 30560);
    };
    if (v0 == 0) {
        reset(2);
    } else {
        charge(5);
        a0 = 52;
        jal(0x206930, &gen::fn_sub_16F380_0016f380);
        if (v0 == 0) {
            reset(4);
        } else {
            charge(4);
            a1 = 0;
            lw(a0, s1, 1056);
            for (;;) {
                charge(3);
                v1 = slt(a1, a0);
                if (v1 == 0) break;
                backedge();
                charge(5);
                v1 = sll(a1, 2);
                v1 = addu(s1, v1);
                lw(v1, v1, 1032);
                if (v0 == v1) break;
                charge(1);
                a1 = addiu(a1, 1);
            }
            charge(2);
            if (a1 == a0) {
                reset(4);
            } else {
                charge(4);
                sw(a1, s1, 30568);
                sw(zero, s1, 30560);
            }
        }
    }
    charge(9);
    glyphs_open(0x2069B8);
    s3 = 0;
    for (;;) {
        charge(4);
        lw(v0, s1, kAnalyzeLineCount);
        v0 = slt(s3, v0);
        if (v0 == 0) break;
        backedge();
        charge(9);
        lw(a0, s1, 30560);
        v0 = addu(s3, a0);
        v0 = sll(v0, 2);
        v0 = addu(s1, v0);
        v1 = addiu(v0, 1032);
        lw(v0, s1, 30568);
        v0 = subu(v0, a0);
        if (s3 == v0) {
            charge(3);
            s0 = 6;
        } else {
            charge(1);
            s0 = 0;
        }
        charge(4);
        lw(v0, v1, 0);
        a1 = 2;
        const auto skill_line = [&](u32 skill, u32 pc_name, u32 pc_build) {
            a0 = skill;
            jal(pc_name, &gen::fn_datGetSkillName_0030bb40);
            a2 = sext_b(s0);
            a0 = v0;
            build_line(pc_build, a2);
            s2 = v0;
        };
        if (v0 == a1) {
            charge(4);
            lw(v1, s1, kMode);
            v0 = 1;
            check(v1 == v0, 0x206B08, 4388);
            charge(12);
            skill_line(325, 0x206B14, 0x206B34);
        } else {
            charge(3);
            v1 = 1;
            if (v0 == v1) {
                charge(10);
                a2 = sext_b(s0);
                lw(a0, gp, -26840);
                a3 = 0;
                t0 = 0;
                jal(0x206AD8, &gen::fn_frFontBuildGlyphList_003b0970);
                s2 = v0;
            } else {
                charge(2);
                if (v0 == 0) {
                    charge(3);
                    lw(v0, s1, kMode);
                    if (v0 == v1) {
                        charge(14);
                        skill_line(326, 0x206A90, 0x206AB0);
                    } else {
                        charge(2);
                        if (v0 == 0) {
                            charge(14);
                            skill_line(324, 0x206A58, 0x206A78);
                        } else {
                            charge(2);
                        }
                    }
                } else {
                    charge(2);
                }
            }
        }
        charge(4);
        v0 = sll(s3, 2);
        v0 = addu(s1, v0);
        sw(s2, v0, kAnalyzeLines);
        s3 = addiu(s3, 1);
    }
    charge(4);
    lw(v1, s1, kMode);
    v0 = 1;
    if (v1 == v0) {
        charge(13);
        a0 = 6;
        jal(0x206BB8, &gen::fn_sub_1775A0_001775a0);
        a0 = v0;
        build_line(0x206BD4, 6);
        s2 = v0;
    } else {
        charge(2);
        if (v1 == 0) {
            charge(13);
            a0 = 4;
            jal(0x206B84, &gen::fn_sub_1775A0_001775a0);
            a0 = v0;
            build_line(0x206BA0, 6);
            s2 = v0;
        } else {
            charge(2);
            charge(5);
            k_assert(0x206BF4, 4413);
        }
    }
    charge(22);
    sw(s2, s1, kTitleLine);
    glyphs_close(0x206C04);
    word_or(v0, s1, kFlags, 0x2000);
    lw(v0, s1, 1056);
    sw(v0, s1, 27136);
    lw(v0, s1, kAnalyzeLineCount);
    sw(v0, s1, 27148);
    t0 = 0;
    a1 = 1;
    a0 = lui(0x20);
    v1 = lui(0x1);
    a2 = 2;
    v0 = lui(0x10);
    // `sll t1, t0, 4; addu t1, t1, t0; sll t1, t1, 4; addu t1, s1, t1; sw value, 25776(t1)`: the panel row's state.
    const auto row_state = [&](const Gpr& value, u64 cost) {
        charge(cost);
        t1 = sll(t0, 4);
        t1 = addu(t1, t0);
        t1 = sll(t1, 4);
        t1 = addu(s1, t1);
        sw(value, t1, 25776);
    };
    for (;;) {
        charge(4);
        lw(a3, s1, 27148);
        a3 = slt(t0, a3);
        if (a3 == 0) break;
        backedge();
        charge(5);
        a3 = sll(t0, 2);
        a3 = addu(s1, a3);
        lw(t1, a3, 1032);
        if (t1 == a2) {  // kind 2
            charge(4);
            lw(t2, s1, kFlags);
            t1 = t2 & v0;
            if (t1 != 0) {
                row_state(a1, 7);
            } else {
                charge(3);
                t1 = andi(t2, 0x8000);
                if (t1 != 0) row_state(a2, 7);
                else row_state(zero, 5);
            }
        } else {
            charge(2);
            if (t1 == a1) {  // kind 1
                charge(4);
                lw(t2, s1, kFlags);
                t1 = t2 & a0;
                if (t1 != 0) {
                    row_state(a1, 7);
                } else {
                    charge(3);
                    t1 = t2 & v1;
                    if (t1 != 0) row_state(a2, 7);
                    else row_state(zero, 7);
                }
            } else {
                charge(2);
                if (t1 == 0) {  // kind 0
                    charge(4);
                    lw(t1, s1, kFlags);
                    t1 = andi(t1, 0x4000);
                    if (t1 != 0) row_state(a2, 7);
                    else row_state(zero, 7);
                } else {
                    charge(2);
                }
            }
        }
        charge(7);
        lw(t1, a3, kAnalyzeLines);
        a3 = sll(t0, 4);
        a3 = addu(a3, t0);
        a3 = sll(a3, 4);
        a3 = addu(s1, a3);
        sw(t1, a3, 25780);
        t0 = addiu(t0, 1);
    }
    charge(29);
    lw(v0, s1, 30568);
    sw(v0, s1, 27140);
    lw(v0, s1, 30560);
    sw(v0, s1, 27144);
    lw(v0, s1, kTitleLine);
    sw(v0, s1, 27152);
    sw(zero, s1, 27156);
    jal(0x206DE8, &gen::fn_sub_2254A0_002254a0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 3;
    jal(0x206E00, &gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s1, 24);
    v1 = 6;
    sw(v1, s1, kListKind);
    pop(128, 7);
}

}  // namespace

// =====================================================================================================================
// The replaced functions and their entry points
// =====================================================================================================================

void sub_201AF0(EEContext& ctx) { Body(ctx).sub_201AF0(); }
void sub_2053C0(EEContext& ctx) { Body(ctx).sub_2053C0(); }
void sub_2054C0(EEContext& ctx) { Body(ctx).sub_2054C0(); }
void sub_205500(EEContext& ctx) { Body(ctx).sub_205500(); }
void sub_205550(EEContext& ctx) { Body(ctx).sub_205550(); }
void sub_2055A0(EEContext& ctx) { Body(ctx).sub_2055A0(); }
void sub_2055F0(EEContext& ctx) { Body(ctx).sub_2055F0(); }
void sub_205650(EEContext& ctx) { Body(ctx).sub_205650(); }
void sub_2056A0(EEContext& ctx) { Body(ctx).operation_unless_debug(0x1, 0x20, 0x2056C0); }
void sub_205700(EEContext& ctx) { Body(ctx).operation_unless_debug(0x10, 0x10, 0x205720); }
void sub_205760(EEContext& ctx) { Body(ctx).operation_unless_debug(0x20, 0x40, 0x205780); }
void sub_2079C0(EEContext& ctx) { Body(ctx).debug_set(0x1, 0x2079E0); }
void sub_207A10(EEContext& ctx) { Body(ctx).debug_set(0x2, 0x207A30); }
void sub_207A60(EEContext& ctx) { Body(ctx).debug_set(0x4, 0x207A80); }
void sub_207AB0(EEContext& ctx) { Body(ctx).debug_set(0x8, 0x207AD0); }
void sub_207B00(EEContext& ctx) { Body(ctx).debug_set(0x10, 0x207B20); }
void sub_207B50(EEContext& ctx) { Body(ctx).debug_set(0x20, 0x207B70); }
void sub_207BA0(EEContext& ctx) { Body(ctx).debug_set(0x40, 0x207BC0); }
void sub_207BF0(EEContext& ctx) { Body(ctx).debug_clear(-2, 0x207C10); }
void sub_207C40(EEContext& ctx) { Body(ctx).debug_clear(-3, 0x207C60); }
void sub_207C90(EEContext& ctx) { Body(ctx).debug_clear(-5, 0x207CB0); }
void sub_207CE0(EEContext& ctx) { Body(ctx).debug_clear(-9, 0x207D00); }
void sub_207D30(EEContext& ctx) { Body(ctx).debug_clear(-17, 0x207D50); }
void sub_207D80(EEContext& ctx) { Body(ctx).debug_clear(-33, 0x207DA0); }
void sub_207DD0(EEContext& ctx) { Body(ctx).debug_clear(-65, 0x207DF0); }
void sub_207F70(EEContext& ctx) { Body(ctx).flag_test(0x200, 0x207F90); }
void sub_207FC0(EEContext& ctx) { Body(ctx).flag_test(0x400, 0x207FE0); }
void sub_2085E0(EEContext& ctx) { Body(ctx).flag_or(0x800, 0x208600); }
void sub_208630(EEContext& ctx) { Body(ctx).flag_and(0xF7FF, 0x208650); }
void sub_208680(EEContext& ctx) { Body(ctx).flag_or(0x1000, 0x2086A0); }
void sub_2086D0(EEContext& ctx) { Body(ctx).flag_and(0xEFFF, 0x2086F0); }
void sub_207930(EEContext& ctx) { Body(ctx).sub_207930(); }
void sub_207960(EEContext& ctx) { Body(ctx).sub_207960(); }
void sub_208010(EEContext& ctx) { Body(ctx).sub_208010(); }
void sub_208050(EEContext& ctx) { Body(ctx).sub_208050(); }
void sub_208130(EEContext& ctx) { Body(ctx).sub_208130(); }
void sub_2082C0(EEContext& ctx) { Body(ctx).sub_2082C0(); }
void sub_208360(EEContext& ctx) { Body(ctx).sub_208360(); }
void sub_2083D0(EEContext& ctx) { Body(ctx).sub_2083D0(); }
void sub_208570(EEContext& ctx) { Body(ctx).sub_208570(); }
void sub_208720(EEContext& ctx) { Body(ctx).sub_208720(); }
void sub_208790(EEContext& ctx) { Body(ctx).sub_208790(); }
void sub_208860(EEContext& ctx) { Body(ctx).sub_208860(); }
void sub_1FFC60(EEContext& ctx) { Body(ctx).sub_1FFC60(); }
void sub_201730(EEContext& ctx) { Body(ctx).sub_201730(); }
void sub_201780(EEContext& ctx) { Body(ctx).sub_201780(); }
void sub_201EF0(EEContext& ctx) { Body(ctx).sub_201EF0(); }
void sub_2024B0(EEContext& ctx) { Body(ctx).sub_2024B0(); }
void sub_202BC0(EEContext& ctx) { Body(ctx).sub_202BC0(); }
void sub_202C90(EEContext& ctx) { Body(ctx).sub_202C90(); }
void sub_203030(EEContext& ctx) { Body(ctx).sub_203030(); }
void sub_203360(EEContext& ctx) { Body(ctx).sub_203360(); }
void sub_203760(EEContext& ctx) { Body(ctx).sub_203760(); }
void sub_203990(EEContext& ctx) { Body(ctx).sub_203990(); }
void sub_203B70(EEContext& ctx) { Body(ctx).sub_203B70(); }
void sub_203DE0(EEContext& ctx) { Body(ctx).sub_203DE0(); }
void sub_204000(EEContext& ctx) { Body(ctx).sub_204000(); }
void sub_204760(EEContext& ctx) { Body(ctx).sub_204760(); }
void sub_204AF0(EEContext& ctx) { Body(ctx).sub_204AF0(); }
void sub_204BE0(EEContext& ctx) { Body(ctx).sub_204BE0(); }
void sub_205000(EEContext& ctx) { Body(ctx).sub_205000(); }
void sub_205410(EEContext& ctx) { Body(ctx).sub_205410(); }
void sub_206310(EEContext& ctx) { Body(ctx).sub_206310(); }
void sub_206EB0(EEContext& ctx) { Body(ctx).sub_206EB0(); }
void sub_201880(EEContext& ctx) { Body(ctx).sub_201880(); }
void sub_201AD0(EEContext& ctx) { Body(ctx).sub_201AD0(); }
void sub_202A10(EEContext& ctx) { Body(ctx).sub_202A10(); }
void sub_203410(EEContext& ctx) { Body(ctx).sub_203410(); }
void sub_206170(EEContext& ctx) { Body(ctx).sub_206170(); }
void sub_206E40(EEContext& ctx) { Body(ctx).sub_206E40(); }
void sub_207010(EEContext& ctx) { Body(ctx).sub_207010(); }
void sub_207E20(EEContext& ctx) { Body(ctx).sub_207E20(); }
void sub_207F10(EEContext& ctx) { Body(ctx).sub_207F10(); }
void sub_2025E0(EEContext& ctx) { Body(ctx).sub_2025E0(); }
void sub_2031C0(EEContext& ctx) { Body(ctx).sub_2031C0(); }
void sub_203C30(EEContext& ctx) { Body(ctx).sub_203C30(); }
void sub_204CC0(EEContext& ctx) { Body(ctx).sub_204CC0(); }
void sub_205D60(EEContext& ctx) { Body(ctx).sub_205D60(); }
void sub_2060B0(EEContext& ctx) { Body(ctx).sub_2060B0(); }
void sub_206F70(EEContext& ctx) { Body(ctx).sub_206F70(); }
void sub_207340(EEContext& ctx) { Body(ctx).sub_207340(); }
void sub_2078A0(EEContext& ctx) { Body(ctx).sub_2078A0(); }
void sub_208460(EEContext& ctx) { Body(ctx).sub_208460(); }
void sub_2016B0(EEContext& ctx) { Body(ctx).sub_2016B0(); }
void sub_201A50(EEContext& ctx) { Body(ctx).sub_201A50(); }
void sub_201B50(EEContext& ctx) { Body(ctx).sub_201B50(); }
void sub_201C30(EEContext& ctx) { Body(ctx).sub_201C30(); }
void sub_201D10(EEContext& ctx) { Body(ctx).sub_201D10(); }
void sub_201E00(EEContext& ctx) { Body(ctx).sub_201E00(); }
void sub_202010(EEContext& ctx) { Body(ctx).sub_202010(); }
void sub_202D70(EEContext& ctx) { Body(ctx).sub_202D70(); }
void sub_203850(EEContext& ctx) { Body(ctx).sub_203850(); }
void sub_204480(EEContext& ctx) { Body(ctx).sub_204480(); }
void sub_2065A0(EEContext& ctx) { Body(ctx).sub_2065A0(); }
void sub_206740(EEContext& ctx) { Body(ctx).sub_206740(); }

}  // namespace p3fes::game

namespace p3fes::recomp_gen {
namespace g = ::p3fes::game;

void fn_sub_201AF0_00201af0(p3fes::EEContext& ctx) { g::sub_201AF0(ctx); }
void fn_sub_2053C0_002053c0(p3fes::EEContext& ctx) { g::sub_2053C0(ctx); }
void fn_sub_2054C0_002054c0(p3fes::EEContext& ctx) { g::sub_2054C0(ctx); }
void fn_sub_205500_00205500(p3fes::EEContext& ctx) { g::sub_205500(ctx); }
void fn_sub_205550_00205550(p3fes::EEContext& ctx) { g::sub_205550(ctx); }
void fn_sub_2055A0_002055a0(p3fes::EEContext& ctx) { g::sub_2055A0(ctx); }
void fn_sub_2055F0_002055f0(p3fes::EEContext& ctx) { g::sub_2055F0(ctx); }
void fn_sub_205650_00205650(p3fes::EEContext& ctx) { g::sub_205650(ctx); }
void fn_sub_2056A0_002056a0(p3fes::EEContext& ctx) { g::sub_2056A0(ctx); }
void fn_sub_205700_00205700(p3fes::EEContext& ctx) { g::sub_205700(ctx); }
void fn_sub_205760_00205760(p3fes::EEContext& ctx) { g::sub_205760(ctx); }
void fn_sub_2079C0_002079c0(p3fes::EEContext& ctx) { g::sub_2079C0(ctx); }
void fn_sub_207A10_00207a10(p3fes::EEContext& ctx) { g::sub_207A10(ctx); }
void fn_sub_207A60_00207a60(p3fes::EEContext& ctx) { g::sub_207A60(ctx); }
void fn_sub_207AB0_00207ab0(p3fes::EEContext& ctx) { g::sub_207AB0(ctx); }
void fn_sub_207B00_00207b00(p3fes::EEContext& ctx) { g::sub_207B00(ctx); }
void fn_sub_207B50_00207b50(p3fes::EEContext& ctx) { g::sub_207B50(ctx); }
void fn_sub_207BA0_00207ba0(p3fes::EEContext& ctx) { g::sub_207BA0(ctx); }
void fn_sub_207BF0_00207bf0(p3fes::EEContext& ctx) { g::sub_207BF0(ctx); }
void fn_sub_207C40_00207c40(p3fes::EEContext& ctx) { g::sub_207C40(ctx); }
void fn_sub_207C90_00207c90(p3fes::EEContext& ctx) { g::sub_207C90(ctx); }
void fn_sub_207CE0_00207ce0(p3fes::EEContext& ctx) { g::sub_207CE0(ctx); }
void fn_sub_207D30_00207d30(p3fes::EEContext& ctx) { g::sub_207D30(ctx); }
void fn_sub_207D80_00207d80(p3fes::EEContext& ctx) { g::sub_207D80(ctx); }
void fn_sub_207DD0_00207dd0(p3fes::EEContext& ctx) { g::sub_207DD0(ctx); }
void fn_sub_207F70_00207f70(p3fes::EEContext& ctx) { g::sub_207F70(ctx); }
void fn_sub_207FC0_00207fc0(p3fes::EEContext& ctx) { g::sub_207FC0(ctx); }
void fn_sub_2085E0_002085e0(p3fes::EEContext& ctx) { g::sub_2085E0(ctx); }
void fn_sub_208630_00208630(p3fes::EEContext& ctx) { g::sub_208630(ctx); }
void fn_sub_208680_00208680(p3fes::EEContext& ctx) { g::sub_208680(ctx); }
void fn_sub_2086D0_002086d0(p3fes::EEContext& ctx) { g::sub_2086D0(ctx); }
void fn_sub_207930_00207930(p3fes::EEContext& ctx) { g::sub_207930(ctx); }
void fn_sub_207960_00207960(p3fes::EEContext& ctx) { g::sub_207960(ctx); }
void fn_sub_208010_00208010(p3fes::EEContext& ctx) { g::sub_208010(ctx); }
void fn_sub_208050_00208050(p3fes::EEContext& ctx) { g::sub_208050(ctx); }
void fn_sub_208130_00208130(p3fes::EEContext& ctx) { g::sub_208130(ctx); }
void fn_sub_2082C0_002082c0(p3fes::EEContext& ctx) { g::sub_2082C0(ctx); }
void fn_sub_208360_00208360(p3fes::EEContext& ctx) { g::sub_208360(ctx); }
void fn_sub_2083D0_002083d0(p3fes::EEContext& ctx) { g::sub_2083D0(ctx); }
void fn_sub_208570_00208570(p3fes::EEContext& ctx) { g::sub_208570(ctx); }
void fn_sub_208720_00208720(p3fes::EEContext& ctx) { g::sub_208720(ctx); }
void fn_sub_208790_00208790(p3fes::EEContext& ctx) { g::sub_208790(ctx); }
void fn_sub_208860_00208860(p3fes::EEContext& ctx) { g::sub_208860(ctx); }
void fn_sub_1FFC60_001ffc60(p3fes::EEContext& ctx) { g::sub_1FFC60(ctx); }
void fn_sub_201730_00201730(p3fes::EEContext& ctx) { g::sub_201730(ctx); }
void fn_sub_201780_00201780(p3fes::EEContext& ctx) { g::sub_201780(ctx); }
void fn_sub_201EF0_00201ef0(p3fes::EEContext& ctx) { g::sub_201EF0(ctx); }
void fn_sub_2024B0_002024b0(p3fes::EEContext& ctx) { g::sub_2024B0(ctx); }
void fn_sub_202BC0_00202bc0(p3fes::EEContext& ctx) { g::sub_202BC0(ctx); }
void fn_sub_202C90_00202c90(p3fes::EEContext& ctx) { g::sub_202C90(ctx); }
void fn_sub_203030_00203030(p3fes::EEContext& ctx) { g::sub_203030(ctx); }
void fn_sub_203360_00203360(p3fes::EEContext& ctx) { g::sub_203360(ctx); }
void fn_sub_203760_00203760(p3fes::EEContext& ctx) { g::sub_203760(ctx); }
void fn_sub_203990_00203990(p3fes::EEContext& ctx) { g::sub_203990(ctx); }
void fn_sub_203B70_00203b70(p3fes::EEContext& ctx) { g::sub_203B70(ctx); }
void fn_sub_203DE0_00203de0(p3fes::EEContext& ctx) { g::sub_203DE0(ctx); }
void fn_sub_204000_00204000(p3fes::EEContext& ctx) { g::sub_204000(ctx); }
void fn_sub_204760_00204760(p3fes::EEContext& ctx) { g::sub_204760(ctx); }
void fn_sub_204AF0_00204af0(p3fes::EEContext& ctx) { g::sub_204AF0(ctx); }
void fn_sub_204BE0_00204be0(p3fes::EEContext& ctx) { g::sub_204BE0(ctx); }
void fn_sub_205000_00205000(p3fes::EEContext& ctx) { g::sub_205000(ctx); }
void fn_sub_205410_00205410(p3fes::EEContext& ctx) { g::sub_205410(ctx); }
void fn_sub_206310_00206310(p3fes::EEContext& ctx) { g::sub_206310(ctx); }
void fn_sub_206EB0_00206eb0(p3fes::EEContext& ctx) { g::sub_206EB0(ctx); }
void fn_sub_201880_00201880(p3fes::EEContext& ctx) { g::sub_201880(ctx); }
void fn_sub_201AD0_00201ad0(p3fes::EEContext& ctx) { g::sub_201AD0(ctx); }
void fn_sub_202A10_00202a10(p3fes::EEContext& ctx) { g::sub_202A10(ctx); }
void fn_sub_203410_00203410(p3fes::EEContext& ctx) { g::sub_203410(ctx); }
void fn_sub_206170_00206170(p3fes::EEContext& ctx) { g::sub_206170(ctx); }
void fn_sub_206E40_00206e40(p3fes::EEContext& ctx) { g::sub_206E40(ctx); }
void fn_sub_207010_00207010(p3fes::EEContext& ctx) { g::sub_207010(ctx); }
void fn_sub_207E20_00207e20(p3fes::EEContext& ctx) { g::sub_207E20(ctx); }
void fn_sub_207F10_00207f10(p3fes::EEContext& ctx) { g::sub_207F10(ctx); }
void fn_sub_2025E0_002025e0(p3fes::EEContext& ctx) { g::sub_2025E0(ctx); }
void fn_sub_2031C0_002031c0(p3fes::EEContext& ctx) { g::sub_2031C0(ctx); }
void fn_sub_203C30_00203c30(p3fes::EEContext& ctx) { g::sub_203C30(ctx); }
void fn_sub_204CC0_00204cc0(p3fes::EEContext& ctx) { g::sub_204CC0(ctx); }
void fn_sub_205D60_00205d60(p3fes::EEContext& ctx) { g::sub_205D60(ctx); }
void fn_sub_2060B0_002060b0(p3fes::EEContext& ctx) { g::sub_2060B0(ctx); }
void fn_sub_206F70_00206f70(p3fes::EEContext& ctx) { g::sub_206F70(ctx); }
void fn_sub_207340_00207340(p3fes::EEContext& ctx) { g::sub_207340(ctx); }
void fn_sub_2078A0_002078a0(p3fes::EEContext& ctx) { g::sub_2078A0(ctx); }
void fn_sub_208460_00208460(p3fes::EEContext& ctx) { g::sub_208460(ctx); }
void fn_sub_2016B0_002016b0(p3fes::EEContext& ctx) { g::sub_2016B0(ctx); }
void fn_sub_201A50_00201a50(p3fes::EEContext& ctx) { g::sub_201A50(ctx); }
void fn_sub_201B50_00201b50(p3fes::EEContext& ctx) { g::sub_201B50(ctx); }
void fn_sub_201C30_00201c30(p3fes::EEContext& ctx) { g::sub_201C30(ctx); }
void fn_sub_201D10_00201d10(p3fes::EEContext& ctx) { g::sub_201D10(ctx); }
void fn_sub_201E00_00201e00(p3fes::EEContext& ctx) { g::sub_201E00(ctx); }
void fn_sub_202010_00202010(p3fes::EEContext& ctx) { g::sub_202010(ctx); }
void fn_sub_202D70_00202d70(p3fes::EEContext& ctx) { g::sub_202D70(ctx); }
void fn_sub_203850_00203850(p3fes::EEContext& ctx) { g::sub_203850(ctx); }
void fn_sub_204480_00204480(p3fes::EEContext& ctx) { g::sub_204480(ctx); }
void fn_sub_2065A0_002065a0(p3fes::EEContext& ctx) { g::sub_2065A0(ctx); }
void fn_sub_206740_00206740(p3fes::EEContext& ctx) { g::sub_206740(ctx); }

}  // namespace p3fes::recomp_gen
