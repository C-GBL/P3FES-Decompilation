# Build-time emission of a recompiled subset for tests/rt (custom command, see CMakeLists.txt).
#
#   cmake -DRECOMP=<p3fes_recomp.exe> -DELF=<SLUS_216.21> -DSRC=<repo> -DOUT=<dir> (-DONLY=<a,b,...> | -DONLY_FILE=<file>)
#         [-DNO_ADR13=1] [-DREPLACE=<game/replaced.txt>] [-DSTAND_INS=on|<a,b,...>] [-DBUCKETS=<n>] -P emit_units.cmake
#
# Runs p3fes_recomp --out into OUT (a build directory, never recomp/generated/) and writes
# OUT/gen_units.cpp, which #includes every emitted fn_*.cpp, so the build sees fixed file names
# whatever addresses the unit names carry. NO_ADR13=1 adds --no-cycles --no-check-events (the
# performance comparison build).
# BUCKETS=n (big subsets, tests/game): --stable-units --group-size 200 (units = the whole program's bands of 200
# functions, each holding the selected ones), emitted and post-processed (stand-ins) in OUT/_emit and copied into OUT
# only where the final text changed (stale units removed), and n files OUT/gen_units_NN.cpp, bucket b #including the
# units of bands [b*K/n, (b+1)*K/n) (K = the program's band count) with each unit's SHA-1, rewritten only when that
# list changes (a unit's text changed, one appeared or went). Nothing is deleted first, so an unchanged bucket keeps
# its timestamp and its object.
# Always touches OUT/emit.stamp (the custom command's output; the sources are restat byproducts).
set(extra)
if(ONLY_FILE)
    set(ONLY "@${ONLY_FILE}")
endif()
if(NO_ADR13)
    list(APPEND extra --no-cycles --no-check-events)
endif()
if(REPLACE)
    list(APPEND extra --replace "${REPLACE}")
endif()
set(group 100000)
if(BUCKETS)
    set(group 200)
    list(APPEND extra --stable-units)
    set(EMIT "${OUT}/_emit")
else()
    file(REMOVE_RECURSE "${OUT}")
    set(EMIT "${OUT}")
endif()
file(MAKE_DIRECTORY "${EMIT}")
execute_process(
    COMMAND "${RECOMP}" --elf "${ELF}" --functions "${SRC}/symbols/functions.json"
            --chunks "${SRC}/symbols/function_chunks.txt" --jumptables "${SRC}/symbols/jumptables.json"
            --out "${EMIT}" --only "${ONLY}" --group-size ${group} ${extra}
    RESULT_VARIABLE rc OUTPUT_VARIABLE so ERROR_VARIABLE se)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "p3fes_recomp --out failed (${rc}):\n${se}")
endif()
file(GLOB units RELATIVE "${EMIT}" "${EMIT}/fn_*.cpp")
if(NOT units)
    message(FATAL_ERROR "p3fes_recomp wrote no units into ${EMIT}")
endif()
list(SORT units)

# Test stand-ins (tests/game/stand_ins.h; -DSTAND_INS=on or a comma list of emitted function starts). Every stub of a
# function this subset does not emit asks the installed stand-ins first (stand_in_or_missing: no stand-in for that
# address -> the same rt::missing_function stop as before), and each listed emitted function asks them at its entry
# (stand_in_hook; g_stand_ins_active is false unless a test installed a set). A replaced function (plain symbol in
# game/) is never hooked: only `_<addr8>(p3fes::EEContext& ctx) {` heads of generated bodies match.
if(STAND_INS)
    file(APPEND "${EMIT}/gen_prelude.h"
        "namespace p3fes::game_test {\n"
        "extern bool g_stand_ins_active;\n"
        "bool stand_in_hook(::p3fes::EEContext& ctx, std::uint32_t va);\n"
        "void stand_in_or_missing(::p3fes::EEContext& ctx, std::uint32_t va);\n"
        "}  // namespace p3fes::game_test\n")
    file(READ "${EMIT}/missing_stubs.cpp" stubs)
    string(REPLACE "(p3fes::EEContext&) { rt::missing_function(" "(p3fes::EEContext& ctx) { ::p3fes::game_test::stand_in_or_missing(ctx, "
        stubs "${stubs}")
    file(WRITE "${EMIT}/missing_stubs.cpp" "${stubs}")
    string(REPLACE "," ";" hooks "${STAND_INS}")
    list(REMOVE_ITEM hooks on ON)
    if(hooks)
        foreach(u IN LISTS units)
            file(READ "${EMIT}/${u}" text)
            set(changed OFF)
            foreach(h IN LISTS hooks)
                string(TOLOWER "${h}" h)
                string(REGEX REPLACE "^0x" "" h "${h}")
                string(LENGTH "${h}" n)
                while(n LESS 8)
                    set(h "0${h}")
                    math(EXPR n "${n} + 1")
                endwhile()
                set(head "_${h}(p3fes::EEContext& ctx) {\n")
                string(FIND "${text}" "${head}" at)
                if(NOT at EQUAL -1)
                    string(REPLACE "${head}"
                        "${head}    if (::p3fes::game_test::g_stand_ins_active && ::p3fes::game_test::stand_in_hook(ctx, 0x${h}u)) return;\n"
                        text "${text}")
                    set(changed ON)
                endif()
            endforeach()
            if(changed)
                file(WRITE "${EMIT}/${u}" "${text}")
            endif()
        endforeach()
    endif()
endif()

if(BUCKETS)
    # copy the final text into OUT where it changed (an unchanged file keeps its timestamp: restat), drop stale units
    file(GLOB emitted RELATIVE "${EMIT}" "${EMIT}/*")
    foreach(f IN LISTS emitted)
        if(IS_DIRECTORY "${EMIT}/${f}")
            continue()
        endif()
        file(COPY_FILE "${EMIT}/${f}" "${OUT}/${f}" ONLY_IF_DIFFERENT)
    endforeach()
    file(GLOB old RELATIVE "${OUT}" "${OUT}/fn_*.cpp")
    foreach(f IN LISTS old)
        list(FIND units "${f}" at)  # (script mode: no IN_LIST without CMP0057)
        if(at EQUAL -1)
            file(REMOVE "${OUT}/${f}")
        endif()
    endforeach()

    file(READ "${OUT}/manifest.json" manifest)
    if(NOT manifest MATCHES "\"functions\": {\"total\": ([0-9]+)")
        message(FATAL_ERROR "emit_units: no function total in ${OUT}/manifest.json")
    endif()
    math(EXPR bands "(${CMAKE_MATCH_1} + ${group} - 1) / ${group}")
    math(EXPR last "${BUCKETS} - 1")
    foreach(b RANGE 0 ${last})
        set(text_${b} "// Generated by tests/rt/emit_units.cmake: bucket ${b} of ${BUCKETS} of this subset's units (bands of ${group}).\n")
    endforeach()
    foreach(u IN LISTS units)
        if(NOT u MATCHES "^fn_0*([0-9]+)_")
            message(FATAL_ERROR "emit_units: unexpected unit name ${u}")
        endif()
        math(EXPR b "${CMAKE_MATCH_1} * ${BUCKETS} / ${bands}")
        # the unit's hash: ninja learns the units only as discovered includes (not outputs of this command), so a
        # bucket must change text whenever one of its units does, or its object would not be rebuilt
        file(SHA1 "${OUT}/${u}" h)
        string(APPEND text_${b} "#include \"${u}\"  // sha1 ${h}\n")
    endforeach()
    foreach(b RANGE 0 ${last})
        set(bb ${b})
        if(b LESS 10)
            set(bb "0${b}")
        endif()
        set(path "${OUT}/gen_units_${bb}.cpp")
        set(old_text "")
        if(EXISTS "${path}")
            file(READ "${path}" old_text)
        endif()
        if(NOT old_text STREQUAL text_${b})
            file(WRITE "${path}" "${text_${b}}")
        endif()
    endforeach()
else()
    set(text "// Generated by tests/rt/emit_units.cmake: the emitted units of this subset.\n")
    foreach(u IN LISTS units)
        string(APPEND text "#include \"${u}\"\n")
    endforeach()
    file(WRITE "${OUT}/gen_units.cpp" "${text}")
endif()
file(TOUCH "${OUT}/emit.stamp")
