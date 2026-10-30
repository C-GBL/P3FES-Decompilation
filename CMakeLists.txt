# Persona 3 FES native port — top-level build.
#
# Targets (see GOAL.md "Phase 0" / "Phase 3"):
#   p3fes_runtime  static lib   runtime/   CPU context, EE memory, HLE, GS/SPU2 backends
#   p3fes          executable   runtime/   the game host (window + D3D11 + XAudio2)
#   p3fes_recomp   executable   recomp/    static recompiler (R5900 -> C++)
#   p3fes_game     static lib   game/      hand-decompiled game code
#   p3fes_tests    executable   tests/     doctest unit tests (ctest)
#   tools/ours/    helper tools (tracediff stub for now)
#
# MSVC is the primary compiler; clang-cl must also build. Only Windows x64 is
# a supported host. No network access is needed at configure time.
cmake_minimum_required(VERSION 3.25)

project(p3fes_port
    VERSION 0.0.1
    DESCRIPTION "Persona 3 FES (SLUS_216.21) native Windows x64 port"
    LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "p3fes_port targets Windows x64 only (D3D11 / XAudio2 / XInput).")
endif()
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "p3fes_port requires a 64-bit (x64) toolchain.")
endif()

option(P3FES_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Keep all binaries in one place per configuration so smoke/test commands are
# predictable: build/<preset>/bin/*.exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Shared compile options, applied to every target via an INTERFACE library.
# Both cl.exe and clang-cl accept the MSVC-style flags used here.
add_library(p3fes_common_options INTERFACE)
target_compile_options(p3fes_common_options INTERFACE
    /W4
    /permissive-
    /utf-8
    /EHsc
    # MSVC-only conformance switches (clang-cl is already conforming here).
    $<$<CXX_COMPILER_ID:MSVC>:/Zc:__cplusplus>
    $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>
)
target_compile_definitions(p3fes_common_options INTERFACE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    UNICODE
    _UNICODE
    _CRT_SECURE_NO_WARNINGS
)
if(P3FES_WARNINGS_AS_ERRORS)
    target_compile_options(p3fes_common_options INTERFACE /WX)
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # clang-cl: keep the MSVC flag set but silence noise that is irrelevant
    # for a code base that is MSVC-first.
    target_compile_options(p3fes_common_options INTERFACE
        -Wno-unused-command-line-argument
    )
endif()

enable_testing()

add_subdirectory(runtime)
add_subdirectory(game)
add_subdirectory(recomp)
add_subdirectory(tools/ours)
add_subdirectory(tests)

# -DP3FES_UNIT_CACHE=<dir> (gate.ps1): runtime/ and game/ compile through the shared object cache too (the generated
# units opt in where they are defined); tools/ours/gate/unit_cache.cmake.
include(tools/ours/gate/unit_cache.cmake)
p3fes_unit_cache_dir(runtime)
p3fes_unit_cache_dir(game)
