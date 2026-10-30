# tests/rt: the rt adapter (runtime/rt/, library p3fes_rt).
#
#   p3fes_rt_tests       adapter unit tests against a recording RtHooks/HwBus (fake_hooks.h) and the
#                        declaration-coverage table. Needs nothing from the disc.
#   p3fes_ee_core_tests  tests/ee/test_core.cpp + test_cop0.cpp: the ee/core.h and ee/cop0.h semantics
#                        that were added with the adapter. They live next to the other tests/ee/ files
#                        and are built here only so that tests/CMakeLists.txt changes by one line; they
#                        can move into p3fes_tests unchanged.
#   p3fes_rt_exec_tests  first execution of recompiled code: a libc subset is emitted from the user's
#                        ELF at build time (emit_units.cmake), compiled against p3fes_rt and run against
#                        the host C library. Without the ELF at configure time it is built without
#                        generated code and its test skips with a message.
#   p3fes_rt_perf[_off]  -DP3FES_RT_PERF=ON: memset(1 MiB) timing with and without the ADR-0013
#                        statements (--no-cycles --no-check-events), for runtime/rt/README.md.

set(_vendor ${CMAKE_SOURCE_DIR}/tests/vendor)

add_executable(p3fes_rt_tests
    test_main.cpp
    fake_hooks.h
    test_rt_core.cpp
    test_rt_mem.cpp
    test_rt_hooks.cpp
    test_rt_units.cpp
    test_rt_coverage.cpp
)
target_include_directories(p3fes_rt_tests PRIVATE ${_vendor})
target_link_libraries(p3fes_rt_tests PRIVATE p3fes_common_options p3fes_rt)
target_compile_definitions(p3fes_rt_tests PRIVATE
    P3FES_RECOMP_RT_HEADER="${CMAKE_SOURCE_DIR}/recomp/include/p3fes_recomp_rt.h")
add_test(NAME p3fes_rt_tests COMMAND p3fes_rt_tests)

add_executable(p3fes_ee_core_tests
    test_main.cpp
    ${CMAKE_SOURCE_DIR}/tests/ee/ee_test_util.h
    ${CMAKE_SOURCE_DIR}/tests/ee/test_core.cpp
    ${CMAKE_SOURCE_DIR}/tests/ee/test_cop0.cpp
)
target_include_directories(p3fes_ee_core_tests PRIVATE ${_vendor})
target_link_libraries(p3fes_ee_core_tests PRIVATE p3fes_common_options p3fes_runtime)
add_test(NAME p3fes_ee_core_tests COMMAND p3fes_ee_core_tests)

# --- First execution of recompiled code -------------------------------------------------------
set(P3FES_RT_EXEC_ELF "${CMAKE_SOURCE_DIR}/extracted/disc/SLUS_216.21" CACHE FILEPATH
    "ELF the rt execution tests emit their subset from (never committed)")
# memcmp memcpy memmove memset strchr strcmp strcpy strlen strncat strncmp strncpy (symbols/p3fes.sym)
set(P3FES_RT_EXEC_SUBSET "0x5211b8,0x521250,0x521300,0x521408,0x523f98,0x524128,0x524270,0x524388,0x5244c0,0x524670,0x524828")
set(_symbols
    ${CMAKE_SOURCE_DIR}/symbols/functions.json
    ${CMAKE_SOURCE_DIR}/symbols/function_chunks.txt
    ${CMAKE_SOURCE_DIR}/symbols/jumptables.json)

# Emits `only` into ${CMAKE_CURRENT_BINARY_DIR}/<name> and defines static library <name>
# (generated units + dispatch.cpp + missing_stubs.cpp, linked with p3fes_rt; the emission runs in target <name>_emit).
# Optional 4th argument: a `--replace` list (game/replaced.txt); the caller then also links p3fes_game.
# Optional 5th argument: test stand-ins (tests/game/stand_ins.h): "on" or a comma list of emitted function starts.
# Every not-emitted function's stub then asks the installed stand-ins before its missing_function stop, and each listed
# emitted function asks them at its entry; the caller defines p3fes::game_test::stand_in_hook / stand_in_or_missing.
function(p3fes_rt_emitted_lib name only no_adr13)
    set(gen ${CMAKE_CURRENT_BINARY_DIR}/${name})
    set(replace "")
    if(ARGC GREATER 3)
        set(replace ${ARGV3})
    endif()
    set(stand_ins "")
    if(ARGC GREATER 4)
        set(stand_ins ${ARGV4})
    endif()
    # Callable from other test directories (tests/game): paths are taken from this file, not the caller.
    set(_symbols
        ${CMAKE_SOURCE_DIR}/symbols/functions.json
        ${CMAKE_SOURCE_DIR}/symbols/function_chunks.txt
        ${CMAKE_SOURCE_DIR}/symbols/jumptables.json)
    # The address list goes through a file: tests/game's list (replaced + callees, ~3,000 addresses) overflows the
    # Windows command-line limit. Rewritten only when it changes, so an unchanged list does not re-emit.
    set(_only_file ${gen}.only.txt)
    set(_old_only "")
    if(EXISTS ${_only_file})
        file(READ ${_only_file} _old_only)
    endif()
    if(NOT _old_only STREQUAL only)
        file(WRITE ${_only_file} "${only}")
    endif()
    string(REGEX MATCHALL "," _commas "${only}")
    list(LENGTH _commas _n_commas)
    math(EXPR _n_only "${_n_commas} + 1")
    # Big lists (tests/game: ~4,000 addresses) are emitted as stable units (--stable-units: grouped by the whole
    # program's bands of 200 functions, rewritten only when their text changes) and compiled as 16 translation units
    # gen_units_NN.cpp, each #including the units of a fixed range of bands: a change of the list or of
    # game/replaced.txt recompiles only the buckets whose units changed, in parallel (one 3,600-function unit took
    # ~45 s on one core and recompiled on every change). Small lists keep the single gen_units.cpp.
    set(_buckets 0)
    if(_n_only GREATER 256)
        set(_buckets 16)
    endif()
    if(_buckets)
        set(_units)
        math(EXPR _last "${_buckets} - 1")
        foreach(_b RANGE 0 ${_last})
            if(_b LESS 10)
                set(_b "0${_b}")
            endif()
            list(APPEND _units ${gen}/gen_units_${_b}.cpp)
        endforeach()
    else()
        set(_units ${gen}/gen_units.cpp)
    endif()
    # The emission is its own target (${name}_emit) so it waits only for p3fes_recomp: a custom command of the
    # library itself would wait for every library the library links (p3fes_game, the runtime), i.e. most of the
    # build. Its output is emit.stamp, touched on every run; the sources are byproducts, rewritten only when their
    # text changes (restat: unchanged ones keep their time and their objects).
    add_custom_command(
        OUTPUT ${gen}/emit.stamp
        BYPRODUCTS ${_units} ${gen}/dispatch.cpp ${gen}/missing_stubs.cpp
        COMMAND ${CMAKE_COMMAND} -DRECOMP=$<TARGET_FILE:p3fes_recomp> -DELF=${P3FES_RT_EXEC_ELF}
                -DSRC=${CMAKE_SOURCE_DIR} -DOUT=${gen} -DONLY_FILE=${_only_file} -DNO_ADR13=${no_adr13} -DREPLACE=${replace}
                -DBUCKETS=${_buckets} -DSTAND_INS=${stand_ins}
                -P ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/emit_units.cmake
        DEPENDS p3fes_recomp ${_symbols} ${P3FES_RT_EXEC_ELF} ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/emit_units.cmake ${replace}
                ${_only_file}
        COMMENT "p3fes_recomp --out ${name} (--only: ${_n_only} addresses from ${name}.only.txt)"
        VERBATIM)
    add_custom_target(${name}_emit DEPENDS ${gen}/emit.stamp)
    add_library(${name} STATIC ${_units} ${gen}/dispatch.cpp ${gen}/missing_stubs.cpp)
    add_dependencies(${name} ${name}_emit)
    include(${CMAKE_SOURCE_DIR}/tools/ours/gate/unit_cache.cmake)
    p3fes_unit_cache(${name})   # -DP3FES_UNIT_CACHE=<dir>: generated code only, so the shared object cache applies
    target_include_directories(${name} PRIVATE ${gen})
    target_link_libraries(${name} PUBLIC p3fes_common_options p3fes_rt)
    target_compile_options(${name} PRIVATE /bigobj)
endfunction()

add_executable(p3fes_rt_exec_tests test_main.cpp fake_hooks.h test_rt_exec.cpp)
target_include_directories(p3fes_rt_exec_tests PRIVATE ${_vendor})
target_link_libraries(p3fes_rt_exec_tests PRIVATE p3fes_common_options p3fes_rt p3fes_recomp_lib)
target_compile_definitions(p3fes_rt_exec_tests PRIVATE P3FES_ELF_DEFAULT="${P3FES_RT_EXEC_ELF}")
if(EXISTS ${P3FES_RT_EXEC_ELF})
    p3fes_rt_emitted_lib(p3fes_rt_exec_gen "${P3FES_RT_EXEC_SUBSET}" 0)
    target_link_libraries(p3fes_rt_exec_tests PRIVATE p3fes_rt_exec_gen)
    target_compile_definitions(p3fes_rt_exec_tests PRIVATE P3FES_RT_EXEC_HAVE_GENERATED=1)
else()
    message(STATUS "tests/rt: ${P3FES_RT_EXEC_ELF} not found; p3fes_rt_exec_tests is built without recompiled code and skips")
endif()
add_test(NAME p3fes_rt_exec_tests COMMAND p3fes_rt_exec_tests)

option(P3FES_RT_PERF "Build the ADR-0013 hot-path timing harness (tests/rt/perf_main.cpp)" OFF)
if(P3FES_RT_PERF AND EXISTS ${P3FES_RT_EXEC_ELF})
    p3fes_rt_emitted_lib(p3fes_rt_perf_gen_off "0x521408" 1)
    add_executable(p3fes_rt_perf perf_main.cpp)
    target_link_libraries(p3fes_rt_perf PRIVATE p3fes_common_options p3fes_rt p3fes_rt_exec_gen)
    target_compile_definitions(p3fes_rt_perf PRIVATE P3FES_RT_PERF_VARIANT="cycles+check_events")
    add_executable(p3fes_rt_perf_off perf_main.cpp)
    target_link_libraries(p3fes_rt_perf_off PRIVATE p3fes_common_options p3fes_rt p3fes_rt_perf_gen_off)
    target_compile_definitions(p3fes_rt_perf_off PRIVATE P3FES_RT_PERF_VARIANT="--no-cycles --no-check-events")
endif()
