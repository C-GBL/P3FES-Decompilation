# The recompiled program's entry points of the replaced functions (recomp/README.md "Replacements", "Forwarders").
#
#   cmake -DREPLACED=<game/replaced.txt> -DLIST=<game/forwarders.txt> -DOUT_GAME=<file> -DOUT_TEST=<file> -P forwarders.cmake
#
# Every row of game/replaced.txt gets a one-line forwarder
#     void p3fes::recomp_gen::fn_<name>_<addr8>(p3fes::EEContext& ctx) { p3fes::game::<name>(ctx); }
# except the rows game/forwarders.txt marks '-' (the game/ source defines that entry point itself: a typed shim or a
# shim macro); a row there with a third word names the game:: body the forwarder calls instead of <name>. A row with
# `@0x<pc>` tokens (a function with mid-body entries; the emitter checks them) gets one more forwarder per entry,
#     void p3fes::recomp_gen::fn_<name>_<addr8>_at_<pc8>(p3fes::EEContext& ctx) { p3fes::game::<name>_at_<pc8>(ctx); }
#
# OUT_GAME: the plain forwarders (p3fes_game_forwarders: p3fes, the link check, the audit). Nothing else: the game's
#   code is a tail call, as it was when each slice wrote the line into its own source.
# OUT_TEST: the same forwarders for p3fes_game_tests, each asking the installed test stand-ins first with the check
#   tests/rt/emit_units.cmake puts at the entry of a hooked generated body
#     if (::p3fes::game_test::g_stand_ins_active && ::p3fes::game_test::stand_in_hook(ctx, 0x<addr8>u)) return;
#   so a test can stand in a replaced callee (tests/game/stand_ins.h). It also registers the forwarders' addresses
#   (tests/game/stand_in_entry.h): the pair runners call the function under test past its own stand-in, so a pair
#   always compares the real hand-written body.
# Each output is rewritten only when its text changes (the custom command's outputs are restat byproducts).
cmake_minimum_required(VERSION 3.20)
foreach(v REPLACED LIST OUT_GAME OUT_TEST)
    if(NOT DEFINED ${v})
        message(FATAL_ERROR "forwarders.cmake: -D${v}= missing")
    endif()
endforeach()

# game/forwarders.txt: '0x<addr> <name> -' (own entry) or '0x<addr> <name> <body>'
file(STRINGS "${LIST}" _exc REGEX "^[ \t]*0[xX][0-9A-Fa-f]+")
foreach(_l IN LISTS _exc)
    string(STRIP "${_l}" _l)
    if(NOT _l MATCHES "^0[xX]([0-9A-Fa-f]+)[ \t]+([^ \t]+)[ \t]+([^ \t#]+)")
        message(FATAL_ERROR "forwarders.cmake: ${LIST}: bad row '${_l}' (want '0x<addr> <name> -|<body>')")
    endif()
    math(EXPR _a "0x${CMAKE_MATCH_1}" OUTPUT_FORMAT HEXADECIMAL)
    string(TOLOWER "${_a}" _a)
    set(_exc_${_a} "${CMAKE_MATCH_3}")
endforeach()

file(STRINGS "${REPLACED}" _rows REGEX "^[ \t]*0[xX][0-9A-Fa-f]+")
# Five texts, built in chunks of 64 rows (string(APPEND) copies the whole variable: appending every row to the full text
# is quadratic, about a minute for 13,000 rows).
set(_parts decl_game decl_gen plain hooked table)
foreach(_p IN LISTS _parts)
    set(_${_p} "")
    set(_c_${_p} "")
endforeach()
set(_n 0)
set(_own 0)
foreach(_l IN LISTS _rows)
    string(STRIP "${_l}" _l)
    if(NOT _l MATCHES "^0[xX]([0-9A-Fa-f]+)[ \t]+([^ \t#]+)(.*)$")
        message(FATAL_ERROR "forwarders.cmake: ${REPLACED}: bad row '${_l}'")
    endif()
    set(_name "${CMAKE_MATCH_2}")
    set(_addr "${CMAKE_MATCH_1}")
    set(_rest "${CMAKE_MATCH_3}")
    # a function with mid-body entries lists them as `@0x<pc>` tokens (the emitter checks them against the program):
    # each gets its own forwarder fn_<name>_<addr8>_at_<pc8> -> game::<body>_at_<pc8> (MATCHALL resets CMAKE_MATCH_n)
    string(REGEX MATCHALL "@0[xX][0-9A-Fa-f]+" _ents "${_rest}")
    math(EXPR _a "0x${_addr}" OUTPUT_FORMAT HEXADECIMAL)
    string(TOLOWER "${_a}" _a)
    set(_body "${_name}")
    if(DEFINED _exc_${_a})
        if(_exc_${_a} STREQUAL "-")
            math(EXPR _own "${_own} + 1")
            continue()
        endif()
        set(_body "${_exc_${_a}}")
    endif()
    # the emitter's symbol: fn_<name, non-identifier characters as '_'>_<start, 8 lower-case hex digits>
    string(REGEX REPLACE "[^A-Za-z0-9_]" "_" _sym "${_name}")
    string(REGEX REPLACE "^0x" "" _h "${_a}")
    string(LENGTH "${_h}" _len)
    while(_len LESS 8)
        set(_h "0${_h}")
        math(EXPR _len "${_len} + 1")
    endwhile()
    set(_sym "fn_${_sym}_${_h}")
    # the function's own forwarder, then one per mid-body entry (the same shape at the entry's address)
    set(_fwd "${_sym};${_body};${_h}")
    foreach(_e IN LISTS _ents)
        string(REGEX REPLACE "^@0[xX]" "" _p "${_e}")
        string(TOLOWER "${_p}" _p)
        string(LENGTH "${_p}" _len)
        while(_len LESS 8)
            set(_p "0${_p}")
            math(EXPR _len "${_len} + 1")
        endwhile()
        list(APPEND _fwd "${_sym}_at_${_p};${_body}_at_${_p};${_p}")
    endforeach()
    list(LENGTH _fwd _k)
    set(_i 0)
    while(_i LESS _k)
        list(GET _fwd ${_i} _s)
        math(EXPR _i "${_i} + 1")
        list(GET _fwd ${_i} _bd)
        math(EXPR _i "${_i} + 1")
        list(GET _fwd ${_i} _va)
        math(EXPR _i "${_i} + 1")
        string(APPEND _c_decl_game "void ${_bd}(::p3fes::EEContext&);\n")
        string(APPEND _c_decl_gen "void ${_s}(::p3fes::EEContext&);\n")
        string(APPEND _c_plain "void p3fes::recomp_gen::${_s}(p3fes::EEContext& ctx) { p3fes::game::${_bd}(ctx); }\n")
        string(APPEND _c_hooked "void p3fes::recomp_gen::${_s}(p3fes::EEContext& ctx) {\n"
            "    if (::p3fes::game_test::g_stand_ins_active && ::p3fes::game_test::stand_in_hook(ctx, 0x${_va}u)) return;\n"
            "    p3fes::game::${_bd}(ctx);\n}\n")
        string(APPEND _c_table "    {&::p3fes::recomp_gen::${_s}, 0x${_va}u},\n")
        math(EXPR _n "${_n} + 1")
    endwhile()
    math(EXPR _k "${_n} % 64")
    if(_k EQUAL 0)
        foreach(_p IN LISTS _parts)
            string(APPEND _${_p} "${_c_${_p}}")
            set(_c_${_p} "")
        endforeach()
    endif()
endforeach()
foreach(_p IN LISTS _parts)
    string(APPEND _${_p} "${_c_${_p}}")
endforeach()

string(CONCAT _head
    "// Generated by game/forwarders.cmake from game/replaced.txt and game/forwarders.txt: do not edit.\n"
    "// ${_n} forwarders (${_own} replaced functions define their entry point in game/ themselves).\n"
    "namespace p3fes {\nstruct EEContext;\n}  // namespace p3fes\n\n"
    "namespace p3fes::game {\n${_decl_game}}  // namespace p3fes::game\n\n"
    "namespace p3fes::recomp_gen {\n${_decl_gen}}  // namespace p3fes::recomp_gen\n\n")
string(CONCAT _game_text "${_head}" "${_plain}")
string(CONCAT _test_text "${_head}"
    "#include \"stand_in_entry.h\"\n\n"
    "namespace p3fes::game_test {\n"
    "extern bool g_stand_ins_active;\n"
    "bool stand_in_hook(::p3fes::EEContext& ctx, std::uint32_t va);\n"
    "}  // namespace p3fes::game_test\n\n"
    "${_hooked}\n"
    "namespace {\n"
    "const ::p3fes::game_test::ForwarderRow kForwarders[] = {\n${_table}};\n"
    "[[maybe_unused]] const bool kRegistered =::p3fes::game_test::register_forwarders(kForwarders, sizeof kForwarders / sizeof kForwarders[0]);\n"
    "}  // namespace\n")

foreach(_pair "OUT_GAME;_game_text" "OUT_TEST;_test_text")
    list(GET _pair 0 _ov)
    list(GET _pair 1 _tv)
    set(_old "")
    if(EXISTS "${${_ov}}")
        file(READ "${${_ov}}" _old)
    endif()
    if(NOT _old STREQUAL "${${_tv}}")
        file(WRITE "${${_ov}}" "${${_tv}}")
    endif()
endforeach()
