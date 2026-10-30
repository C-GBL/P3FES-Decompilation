# p3fes_recomp: the R5900 -> C++ static recompiler (Phase 3).
#
#   p3fes_recomp_lib        static lib   decoder (r5900_decode), ELF view (elf_image), function scope
#                                        (function_list, json_lite), emitter (emit_program/analyze/cgen/driver).
#                                        No dependencies, no exceptions.
#   p3fes_recomp            exe          CLI: --dump-decode for the oracle test, --out for emission.
#   p3fes_recomp_rt_api     interface    include path of recomp/include/p3fes_recomp_rt.h (+ runtime headers).
#   p3fes_recomp_rt_stubs   static lib   aborting p3fes::rt stand-ins so generated code links for compile tests.
#   p3fes_recomp_generated  object lib   recomp/generated/*.cpp (gitignored output), compiled once; only
#                                        with -DP3FES_RECOMP_GENERATED=ON and after a --out run.
#   p3fes_program           static lib   those objects + dispatch.cpp + missing_stubs.cpp, linked with the
#                                        real adapter p3fes_rt (runtime/rt/) -- what the game host links.
#                                        In-tree builds only (p3fes_rt comes from runtime/).
#   p3fes_recomp_linkcheck  exe          generated code + a main calling lookup_func(start): whole-program
#                                        link against the stubs (default) or p3fes_rt (-DP3FES_LINKCHECK_RT=rt).
#   recomp/tests/           doctest      decoder tests, emitter flow tests, subset emit+compile+link (ctest).
#
# Normally built from the repository root. `cmake -S recomp -B <dir>` also works: the recompiler
# and the generated code need nothing from runtime/ but its headers, so they can be configured
# and built without the rest of the tree (the shared compile options are then defined here, with
# the same switches as the top-level CMakeLists.txt).
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.25)
    project(p3fes_recomp_standalone LANGUAGES CXX)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    add_library(p3fes_common_options INTERFACE)
    target_compile_options(p3fes_common_options INTERFACE /W4 /permissive- /utf-8 /EHsc
        $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus> $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>
        $<$<CXX_COMPILER_ID:Clang>:-Wno-unused-command-line-argument>)
    target_compile_definitions(p3fes_common_options INTERFACE
        WIN32_LEAN_AND_MEAN NOMINMAX UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS)
    enable_testing()
endif()
get_filename_component(P3FES_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)

add_library(p3fes_recomp_lib STATIC
    src/r5900_decode.h
    src/r5900_decode.cpp
    src/elf_image.h
    src/elf_image.cpp
    src/json_lite.h
    src/function_list.h
    src/function_list.cpp
    src/emit_program.h
    src/emit_program.cpp
    src/emit_analyze.h
    src/emit_analyze.cpp
    src/emit_cgen.h
    src/emit_cgen.cpp
    src/emit_driver.h
    src/emit_driver.cpp
)
target_include_directories(p3fes_recomp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(p3fes_recomp_lib PUBLIC p3fes_common_options)

add_executable(p3fes_recomp
    src/main.cpp
)
# The recompiler links nothing from the runtime: it reads the ELF and the symbol files only.
target_link_libraries(p3fes_recomp PRIVATE p3fes_common_options p3fes_recomp_lib)

# p3fes_handgen: the register-faithful converter (recomp/README.md "p3fes_handgen"): the C++ body a Phase 5 slice
# starts from, on game/include/p3fes/game/hg_cpu.h, with the pair-test skeleton (tests/game/handgen_pairs.h).
add_executable(p3fes_handgen
    src/handgen.h
    src/handgen.cpp
    src/handgen_test.h
    src/handgen_test.cpp
    src/handgen_main.cpp
)
target_link_libraries(p3fes_handgen PRIVATE p3fes_common_options p3fes_recomp_lib)

# p3fes_types: whole-program struct-layout recovery (docs/ANALYSIS/28_types.md, tools/ours/types/): accesses through
# tracked base pointers, union-find over type variables, raw JSON for tools/ours/types/types_build.py.
add_executable(p3fes_types
    src/types.h
    src/types_analyze.cpp
    src/types_solve.cpp
    src/types_main.cpp
)
target_link_libraries(p3fes_types PRIVATE p3fes_common_options p3fes_recomp_lib)

# The adapter API header the generated code targets. Header-only; the runtime's EEContext
# header is taken straight from runtime/include (no link dependency on the backends).
add_library(p3fes_recomp_rt_api INTERFACE)
target_include_directories(p3fes_recomp_rt_api INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${P3FES_REPO_ROOT}/runtime/include
)

add_library(p3fes_recomp_rt_stubs STATIC
    rt_stubs/rt_stubs.cpp
    include/p3fes_recomp_rt.h
)
target_link_libraries(p3fes_recomp_rt_stubs PUBLIC p3fes_common_options p3fes_recomp_rt_api)

option(P3FES_RECOMP_GENERATED "Compile recomp/generated/ (output of p3fes_recomp --out): p3fes_program and p3fes_recomp_linkcheck" OFF)
set(P3FES_RECOMP_GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated" CACHE PATH "Directory written by p3fes_recomp --out")
if(P3FES_RECOMP_GENERATED)
    set(_gen_dir ${P3FES_RECOMP_GENERATED_DIR})
    file(GLOB _gen_units CONFIGURE_DEPENDS ${_gen_dir}/fn_*.cpp)
    if(NOT EXISTS ${_gen_dir}/dispatch.cpp OR NOT _gen_units)
        message(FATAL_ERROR "P3FES_RECOMP_GENERATED=ON but ${_gen_dir} holds no emitted code; run p3fes_recomp --out first")
    endif()
    # Compiled once, linked two ways: p3fes_program (with the real adapter) and the stubs linkcheck.
    add_library(p3fes_recomp_generated OBJECT
        ${_gen_units}
        ${_gen_dir}/dispatch.cpp
        ${_gen_dir}/missing_stubs.cpp
    )
    target_include_directories(p3fes_recomp_generated PRIVATE ${_gen_dir})
    target_link_libraries(p3fes_recomp_generated PUBLIC p3fes_common_options p3fes_recomp_rt_api)
    # Large generated units (~200 functions, up to 1.7 MB of source each) exceed the default
    # COFF section limit.
    target_compile_options(p3fes_recomp_generated PRIVATE /bigobj)
    # -DP3FES_UNIT_CACHE=<dir>: the units come from the shared object cache when another tree compiled the same text
    include(${P3FES_REPO_ROOT}/tools/ours/gate/unit_cache.cmake)
    p3fes_unit_cache(p3fes_recomp_generated)

    # The program: generated code + p3fes_rt instead of the aborting stubs. It lives here rather
    # than in game/ because recomp/ owns the generated output's contract (P3FES_RECOMP_GENERATED,
    # the directory option and the emptiness check above); game/ holds the hand-decompiled
    # replacements of Phase 5, which the host links next to this library.
    if(TARGET p3fes_rt)
        # p3fes_game supplies the hand-decompiled replacements (game/replaced.txt, Phase 5) and
        # p3fes_game_forwarders their plain entry points (recomp/README.md "Forwarders"); the
        # emission must have used --replace game/replaced.txt or the link reports duplicate symbols.
        add_library(p3fes_program STATIC $<TARGET_OBJECTS:p3fes_recomp_generated>)
        target_link_libraries(p3fes_program PUBLIC p3fes_common_options p3fes_recomp_rt_api p3fes_rt p3fes_game_forwarders)
    endif()

    set(P3FES_LINKCHECK_RT "stubs" CACHE STRING
        "p3fes::rt implementation p3fes_recomp_linkcheck links: stubs (rt_stubs/, aborting) or rt (p3fes_rt)")
    set_property(CACHE P3FES_LINKCHECK_RT PROPERTY STRINGS stubs rt)
    add_executable(p3fes_recomp_linkcheck linkcheck/linkcheck_main.cpp)
    if(P3FES_LINKCHECK_RT STREQUAL "rt")
        if(NOT TARGET p3fes_program)
            message(FATAL_ERROR "P3FES_LINKCHECK_RT=rt needs p3fes_rt: configure from the repository root, not -S recomp")
        endif()
        target_link_libraries(p3fes_recomp_linkcheck PRIVATE p3fes_common_options p3fes_program)
    elseif(P3FES_LINKCHECK_RT STREQUAL "stubs")
        # lookup_func lives in the generated objects, everything else of p3fes::rt in the stubs;
        # the replaced functions (game/replaced.txt) come from p3fes_game, their plain entry points from
        # p3fes_game_forwarders.
        target_sources(p3fes_recomp_linkcheck PRIVATE $<TARGET_OBJECTS:p3fes_recomp_generated>)
        if(TARGET p3fes_game_forwarders)
            target_link_libraries(p3fes_recomp_linkcheck PRIVATE p3fes_game_forwarders)
        else()
            message(STATUS "recomp: standalone configure; the link check has no p3fes_game (emit without --replace)")
        endif()
        target_link_libraries(p3fes_recomp_linkcheck PRIVATE p3fes_common_options p3fes_recomp_rt_api p3fes_recomp_rt_stubs)
    else()
        message(FATAL_ERROR "P3FES_LINKCHECK_RT must be stubs or rt, got '${P3FES_LINKCHECK_RT}'")
    endif()
endif()

add_subdirectory(tests)
