# p3fes_tests: doctest unit tests for the runtime (and later the recompiler's
# instruction translations, GOAL.md Phase 4).

add_executable(p3fes_tests
    test_main.cpp
    test_ee_types.cpp
    test_ee_memory.cpp
    test_ee_context.cpp
    test_state_io.cpp
    # runtime/include/p3fes/ee/ (Phase 3 R5900 semantics, ADR-0010 §2): hand-derived vectors per
    # instruction plus the SSE2-vs-scalar MMI equivalence test. See tests/ee/vectors/README.md.
    ee/ee_test_util.h
    ee/test_hilo.cpp
    ee/test_mmi.cpp
    ee/test_mmi_paths.cpp
    ee/test_fpu.cpp
    ee/test_vu0.cpp
    # PCSX2 2.8.2 observed vectors (tools/ours/eevec/, tests/ee/vectors/pcsx2_vectors.json): every family replayed
    # through the headers, lane-parallel MMI ops on both paths; documented disagreements are classified in the test.
    ee/test_pcsx2_vectors.cpp
    # runtime/formats/ (Phase 1). These read real files from extracted/ at run
    # time and skip (doctest MESSAGE + return) when a file is absent.
    formats/fixtures.h
    formats/test_pak.cpp
    formats/test_bf.cpp
    formats/test_bmd.cpp
    formats/test_tmx.cpp
    formats/test_rmd.cpp
    formats/test_adx.cpp
    formats/test_afs.cpp
)
target_include_directories(p3fes_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_link_libraries(p3fes_tests PRIVATE p3fes_common_options p3fes_runtime p3fes_formats)
# Default location of the gitignored extraction; P3FES_EXTRACTED overrides at run time.
target_compile_definitions(p3fes_tests PRIVATE
    P3FES_EXTRACTED_DIR="${CMAKE_SOURCE_DIR}/extracted"
    P3FES_REPO_DIR="${CMAKE_SOURCE_DIR}"
)

add_test(NAME p3fes_tests COMMAND p3fes_tests)

# VU1 decoder/interpreter tests (runtime/vu1/): census reproduction, semantic vectors, batch runs.
add_subdirectory(vu1)

# CDVD HLE tests (runtime/hle/): disc sources, async N-command contract, real-disc byte checks.
add_subdirectory(hle)

# SIF + IOP HLE tests (runtime/hle/sif/): packet layouts, RPC flow, servers, real-disc cdvdfsv.
add_subdirectory(sif)

# GS / GIF / VIF1 tests (runtime/gs/): swizzle, rasteriser, CLUTs, paths, VIF1 + VU1 start, CRTC output (no game data).
add_subdirectory(gs)

# Kernel HLE tests (runtime/hle/kernel/): handler chains, scheduler, timers, DMAC, syscalls (no game data).
add_subdirectory(kernel)

# rt adapter tests (runtime/rt/) and the first execution of recompiled code (needs the ELF; skips without).
add_subdirectory(rt)

# Phase 5 replacements (game/): hand-written functions against their recompiled bodies (needs the ELF; skips without).
add_subdirectory(game)

# Host input + presentation policy tests (runtime/app/input.h, present.h): mapping, dead zones, record/replay, letterbox.
add_subdirectory(app)

# IPU tests (runtime/ipu/): VLC/IQ/IDCT/CSC/PACK vectors, command engine, FIFO stalls, DMAC ch3/ch4 through the kernel.
add_subdirectory(ipu)

# Host audio tests (runtime/audio/): ADX decoder vectors, sink timeline math, WAV output (no game data).
add_subdirectory(audio)
