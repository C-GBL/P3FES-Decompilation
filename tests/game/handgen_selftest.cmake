# p3fes_handgen self-test (recomp/README.md "p3fes_handgen"; included by tests/game/CMakeLists.txt).
#
# At build time p3fes_handgen regenerates the functions of P3FES_HANDGEN_SELFTEST_LIST (default handgen_selftest.txt: a
# dozen functions covering loops, jump tables, jalr, FPU, VU0 macro code, 128-bit spills, delay slots kept after their
# link or test) together with their pair-test skeleton, compiles them with the shim suffix __hg, and runs every body
# against its recompiled body (the plain fn_<name>_<addr8> of an emission without --replace) on random worlds through
# tests/game/handgen_pairs.h. A function that does not generate, does not compile on either compiler, or differs from its
# recompiled body in any register at any check point, in memory or in cycles fails the build or the ctest entry.
# P3FES_HANDGEN_SELFTEST_CALLEES: further functions to emit recompiled (the callees the runs reach; the others stop,
# identically, at their missing-function stop). P3FES_HG_SEEDS (environment) sets the pairs per function (default 64).
if(NOT EXISTS ${P3FES_RT_EXEC_ELF})
    return()
endif()
set(P3FES_HANDGEN_SELFTEST_LIST "${CMAKE_CURRENT_SOURCE_DIR}/handgen_selftest.txt" CACHE FILEPATH
    "Function starts p3fes_handgen_selftest regenerates and pairs with their recompiled bodies (one hex address per line)")
set(P3FES_HANDGEN_SELFTEST_CALLEES "0x524388,0x524128,0x524270,0x521250,0x521408" CACHE STRING
    "Recompiled callees p3fes_handgen_selftest emits besides the listed functions (comma separated)")

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${P3FES_HANDGEN_SELFTEST_LIST})  # the list is read here: re-configure when it changes
file(STRINGS ${P3FES_HANDGEN_SELFTEST_LIST} _hg_lines)
set(_hg_only "")
foreach(_l IN LISTS _hg_lines)
    string(REGEX REPLACE "#.*$" "" _l "${_l}")
    string(STRIP "${_l}" _l)
    if(_l)
        list(APPEND _hg_only ${_l})
    endif()
endforeach()
string(REPLACE ";" "," _hg_only "${_hg_only}")
if(P3FES_HANDGEN_SELFTEST_CALLEES)
    string(APPEND _hg_only ",${P3FES_HANDGEN_SELFTEST_CALLEES}")
endif()

set(_hg_dir ${CMAKE_CURRENT_BINARY_DIR}/handgen_selftest)
file(MAKE_DIRECTORY ${_hg_dir})
add_custom_command(
    OUTPUT ${_hg_dir}/hg_bodies.cpp ${_hg_dir}/test_handgen_selftest.cpp
    COMMAND $<TARGET_FILE:p3fes_handgen> --elf ${P3FES_RT_EXEC_ELF}
            --functions ${CMAKE_SOURCE_DIR}/symbols/functions.json --chunks ${CMAKE_SOURCE_DIR}/symbols/function_chunks.txt
            --jumptables ${CMAKE_SOURCE_DIR}/symbols/jumptables.json --sym ${CMAKE_SOURCE_DIR}/symbols/p3fes.sym
            --only @${P3FES_HANDGEN_SELFTEST_LIST} --slice handgen_selftest --shim-suffix __hg --body-suffix _hg
            --out-cpp ${_hg_dir}/hg_bodies.cpp --out-test ${_hg_dir}/test_handgen_selftest.cpp
    DEPENDS p3fes_handgen ${P3FES_HANDGEN_SELFTEST_LIST} ${CMAKE_SOURCE_DIR}/symbols/functions.json
            ${CMAKE_SOURCE_DIR}/symbols/function_chunks.txt ${CMAKE_SOURCE_DIR}/symbols/jumptables.json
            ${CMAKE_SOURCE_DIR}/symbols/p3fes.sym ${P3FES_RT_EXEC_ELF}
    COMMENT "p3fes_handgen: the self-test bodies and their pair-test skeleton"
    VERBATIM)
p3fes_rt_emitted_lib(p3fes_handgen_selftest_gen "${_hg_only}" 0)
add_executable(p3fes_handgen_selftest
    ${CMAKE_SOURCE_DIR}/tests/rt/test_main.cpp
    handgen_pairs.h
    write_tracker.h
    write_tracker.cpp
    ${_hg_dir}/hg_bodies.cpp
    ${_hg_dir}/test_handgen_selftest.cpp
)
target_include_directories(p3fes_handgen_selftest PRIVATE ${_vendor} ${CMAKE_SOURCE_DIR}/tests/rt ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/game/include)
target_link_libraries(p3fes_handgen_selftest PRIVATE p3fes_common_options p3fes_handgen_selftest_gen p3fes_rt p3fes_recomp_lib
    p3fes_recomp_rt_api)
target_compile_definitions(p3fes_handgen_selftest PRIVATE P3FES_ELF_DEFAULT="${P3FES_RT_EXEC_ELF}" P3FES_GAME_HAVE_GENERATED=1)
target_compile_options(p3fes_handgen_selftest PRIVATE /bigobj)
# The generated bodies compile warning-free at /W4 on both compilers: kept that way.
set_source_files_properties(${_hg_dir}/hg_bodies.cpp PROPERTIES COMPILE_OPTIONS /WX)
# Deep guest recursion on a random world (up to the runner's 20,000 check points) needs more than the default 1 MiB stack.
target_link_options(p3fes_handgen_selftest PRIVATE /STACK:536870912)
add_test(NAME p3fes_handgen_selftest COMMAND p3fes_handgen_selftest)

# The deep variant (opt-in, local): the same skeleton against the WHOLE recompiled program (p3fes_program, a tree
# configured with -DP3FES_RECOMP_GENERATED=ON), so every callee is there and the runs go past the first call. A listed
# function of game/replaced.txt pairs with its fn_X__recomp, any other with the plain fn_X. Not a ctest entry.
option(P3FES_HANDGEN_DEEP "Build p3fes_handgen_deep: p3fes_handgen bodies paired against the whole recompiled program" OFF)
if(P3FES_HANDGEN_DEEP AND TARGET p3fes_program)
    set(P3FES_HANDGEN_DEEP_LIST "${P3FES_HANDGEN_SELFTEST_LIST}" CACHE FILEPATH "Function starts p3fes_handgen_deep pairs")
    add_custom_command(
        OUTPUT ${_hg_dir}/hg_deep_bodies.cpp ${_hg_dir}/test_handgen_deep.cpp
        COMMAND $<TARGET_FILE:p3fes_handgen> --elf ${P3FES_RT_EXEC_ELF}
                --functions ${CMAKE_SOURCE_DIR}/symbols/functions.json --chunks ${CMAKE_SOURCE_DIR}/symbols/function_chunks.txt
                --jumptables ${CMAKE_SOURCE_DIR}/symbols/jumptables.json --sym ${CMAKE_SOURCE_DIR}/symbols/p3fes.sym
                --only @${P3FES_HANDGEN_DEEP_LIST} --slice handgen_deep --shim-suffix __hgdeep --body-suffix _hgdeep
                --replaced ${CMAKE_SOURCE_DIR}/game/replaced.txt
                --out-cpp ${_hg_dir}/hg_deep_bodies.cpp --out-test ${_hg_dir}/test_handgen_deep.cpp
        DEPENDS p3fes_handgen ${P3FES_HANDGEN_DEEP_LIST} ${CMAKE_SOURCE_DIR}/game/replaced.txt ${P3FES_RT_EXEC_ELF}
        COMMENT "p3fes_handgen: the deep self-test bodies"
        VERBATIM)
    add_executable(p3fes_handgen_deep
        ${CMAKE_SOURCE_DIR}/tests/rt/test_main.cpp
        write_tracker.cpp
        ${_hg_dir}/hg_deep_bodies.cpp
        ${_hg_dir}/test_handgen_deep.cpp
    )
    target_include_directories(p3fes_handgen_deep PRIVATE ${_vendor} ${CMAKE_SOURCE_DIR}/tests/rt ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/game/include)
    target_link_libraries(p3fes_handgen_deep PRIVATE p3fes_common_options p3fes_program p3fes_recomp_lib)
    target_compile_definitions(p3fes_handgen_deep PRIVATE P3FES_ELF_DEFAULT="${P3FES_RT_EXEC_ELF}" P3FES_GAME_HAVE_GENERATED=1)
    target_compile_options(p3fes_handgen_deep PRIVATE /bigobj)
    target_link_options(p3fes_handgen_deep PRIVATE /STACK:536870912)
endif()
