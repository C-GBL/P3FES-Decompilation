# p3fes_audit_faithful (opt-in, local; not a ctest entry, not part of the gate): EVERY function of game/replaced.txt, its
# hand-written body (the plain fn_<name>_<addr8> that game/ defines) against its recompiled body (fn_<name>_<addr8>__recomp),
# both inside the WHOLE recompiled program (p3fes_program: every callee is there), on random worlds and real replay
# snapshots. Compared at every check point and at the return / stop: the whole register file (GPRs in 128 bits, HI/LO,
# SA, FCR31, ACC, FPRs, VU0) and the cycle count; afterwards all 32 MiB of RAM INCLUDING the dead stack below $sp, the
# scratchpad, the BIOS window, the bus log. One verdict per function with the difference classes (missing frame /
# spills, scratch / HI/LO / FPR leftovers, $v0, cycles, real logic) -- tests/game/test_audit_faithful.cpp,
# tools/ours/audit/audit_faithful.py (the driver: crash / hang safe, per-slice table). Configure a tree with
#   -DP3FES_RECOMP_GENERATED=ON -DP3FES_LINKCHECK_RT=rt -DP3FES_RT_EXEC_ELF=<ELF> -DP3FES_AUDIT_FAITHFUL=ON
# (after emitting recomp/generated with --replace game/replaced.txt) and build p3fes_audit_faithful.
option(P3FES_AUDIT_FAITHFUL "Build p3fes_audit_faithful: every hand-written body against its recompiled body, whole register file + all RAM" OFF)
if(NOT P3FES_AUDIT_FAITHFUL OR NOT TARGET p3fes_program OR NOT EXISTS ${P3FES_RT_EXEC_ELF})
    return()
endif()

set(_au_dir ${CMAKE_CURRENT_BINARY_DIR}/audit_faithful)
file(MAKE_DIRECTORY ${_au_dir})
# The address list (game/replaced.txt's first column); re-configured when the list changes.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/game/replaced.txt)
file(STRINGS ${CMAKE_SOURCE_DIR}/game/replaced.txt _au_rows)
set(_au_list "")
foreach(_r IN LISTS _au_rows)
    string(REGEX REPLACE "#.*$" "" _r "${_r}")
    string(STRIP "${_r}" _r)
    if(_r MATCHES "^(0x[0-9A-Fa-f]+)")
        string(APPEND _au_list "${CMAKE_MATCH_1}\n")
    endif()
endforeach()
file(WRITE ${_au_dir}/audit_list.txt.new "${_au_list}")
file(COPY_FILE ${_au_dir}/audit_list.txt.new ${_au_dir}/audit_list.txt ONLY_IF_DIFFERENT)

# p3fes_handgen writes the case table (its pair-test skeleton with an empty shim suffix pairs fn_X with fn_X__recomp);
# audit_cases.cmake cuts the declarations and the table out of it. The generated bodies (audit_bodies.cpp, not compiled)
# are the faithful versions of every replaced function, for reference.
add_custom_command(
    OUTPUT ${_au_dir}/audit_cases.inc ${_au_dir}/audit_bodies.cpp
    COMMAND $<TARGET_FILE:p3fes_handgen> --elf ${P3FES_RT_EXEC_ELF}
            --functions ${CMAKE_SOURCE_DIR}/symbols/functions.json --chunks ${CMAKE_SOURCE_DIR}/symbols/function_chunks.txt
            --jumptables ${CMAKE_SOURCE_DIR}/symbols/jumptables.json --sym ${CMAKE_SOURCE_DIR}/symbols/p3fes.sym
            --only @${_au_dir}/audit_list.txt --slice audit --replaced ${CMAKE_SOURCE_DIR}/game/replaced.txt
            --out-cpp ${_au_dir}/audit_bodies.cpp --out-test ${_au_dir}/audit_skeleton.cpp
    COMMAND ${CMAKE_COMMAND} -DIN=${_au_dir}/audit_skeleton.cpp -DOUT=${_au_dir}/audit_cases.inc
            -P ${CMAKE_CURRENT_SOURCE_DIR}/audit_cases.cmake
    DEPENDS p3fes_handgen ${_au_dir}/audit_list.txt ${CMAKE_SOURCE_DIR}/game/replaced.txt ${CMAKE_SOURCE_DIR}/symbols/functions.json
            ${CMAKE_CURRENT_SOURCE_DIR}/audit_cases.cmake ${P3FES_RT_EXEC_ELF}
    COMMENT "p3fes_handgen: the audit's case table (every function of game/replaced.txt)"
    VERBATIM)
add_executable(p3fes_audit_faithful
    ${CMAKE_SOURCE_DIR}/tests/rt/test_main.cpp
    handgen_pairs.h
    write_tracker.cpp
    test_audit_faithful.cpp
    ${_au_dir}/audit_cases.inc
)
target_include_directories(p3fes_audit_faithful PRIVATE ${_vendor} ${CMAKE_SOURCE_DIR}/tests/rt ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/game/include ${_au_dir})
target_link_libraries(p3fes_audit_faithful PRIVATE p3fes_common_options p3fes_program p3fes_recomp_lib)
target_compile_definitions(p3fes_audit_faithful PRIVATE P3FES_ELF_DEFAULT="${P3FES_RT_EXEC_ELF}" P3FES_GAME_HAVE_GENERATED=1)
target_compile_options(p3fes_audit_faithful PRIVATE /bigobj)
target_link_options(p3fes_audit_faithful PRIVATE /STACK:536870912)
