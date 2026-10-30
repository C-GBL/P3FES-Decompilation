# p3fes_runtime: everything that replaces PS2 hardware/SDK for recompiled code.
# p3fes:         the host executable (window + backends + frame loop).

add_library(p3fes_runtime STATIC
    include/p3fes/ee_types.h
    include/p3fes/ee_context.h
    include/p3fes/ee_memory.h
    include/p3fes/pinned.h
    include/p3fes/state_io.h
    # R5900 semantics ported from ps2-web-recomp (ADR-0010 §2); header-only, see include/p3fes/ee/THIRD_PARTY.md.
    include/p3fes/ee/hilo.h
    include/p3fes/ee/mmi.h
    include/p3fes/ee/fpu.h
    include/p3fes/ee/vu0.h
    include/p3fes/syscalls.h
    include/p3fes/prof.h
    include/p3fes/hle/sdk_stubs.h
    include/p3fes/vu1/vu1_interp.h
    include/p3fes/gs/gs_backend.h
    include/p3fes/gs/d3d11_backend.h
    include/p3fes/audio/spu2_backend.h
    src/ee_memory.cpp
    src/pinned.cpp
    src/state_io.cpp
    src/gs/d3d11_backend.cpp
    src/audio/spu2_backend.cpp
)
add_library(p3fes::runtime ALIAS p3fes_runtime)

target_include_directories(p3fes_runtime PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(p3fes_runtime
    PUBLIC
        p3fes_common_options
        d3d11
        dxgi
        xaudio2
        ole32
)

# p3fes_formats: parsers for the Atlus/CRI/RenderWare data formats on disc
# (GOAL.md Phase 1, ADR-0008 §3). Pure C++20 views over std::span; no exceptions,
# no OS dependencies, so tools and tests can link it without the backends.
add_library(p3fes_formats STATIC
    include/p3fes/formats/result.h
    include/p3fes/formats/bytes.h
    include/p3fes/formats/formats.h
    include/p3fes/formats/pak.h
    include/p3fes/formats/bf.h
    include/p3fes/formats/bmd.h
    include/p3fes/formats/tmx.h
    include/p3fes/formats/rmd.h
    include/p3fes/formats/adx.h
    include/p3fes/formats/afs.h
    formats/formats.cpp
    formats/pak.cpp
    formats/bf.cpp
    formats/bmd.cpp
    formats/tmx.cpp
    formats/rmd.cpp
    formats/adx.cpp
    formats/afs.cpp
)
add_library(p3fes::formats ALIAS p3fes_formats)
target_include_directories(p3fes_formats PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(p3fes_formats PUBLIC p3fes_common_options)


# VU1 decoder + interpreter (Phase 3): runtime/vu1/, links itself into p3fes_runtime.
add_subdirectory(vu1)

# Native renderer (docs/ANALYSIS/31_native_renderer.md): runtime/native/, library p3fes_native.
add_subdirectory(native)

# CDVD sector HLE (ADR-0008 §1): runtime/hle/, library p3fes_cdvd.
add_subdirectory(hle)

# GS core, GIF, VIF1, CRTC output (Phase 3): runtime/gs/, library p3fes_gs, links itself into p3fes_runtime.
add_subdirectory(gs)

# Frame interpolation for display rates above the game's 30 fps (track H, docs/ANALYSIS/32): runtime/hfr/.
add_subdirectory(hfr)

# EE kernel / timing HLE (ADR-0013 §3): runtime/hle/kernel/, library p3fes_kernel.
add_subdirectory(hle/kernel)

# rt adapter (ADR-0013 §3): runtime/rt/, library p3fes_rt (implements recomp/include/p3fes_recomp_rt.h).
add_subdirectory(rt)

# The host: the p3fes executable and, with the recompiled program, the composition library p3fes_host.
add_subdirectory(app)

# IPU (MPEG-1/2 macroblock decoder + CSC, DMAC ch3/ch4 data paths): runtime/ipu/, library p3fes_ipu.
add_subdirectory(ipu)

# Host audio (sinks, WAV, XAudio2, host ADX decoder): runtime/audio/, library p3fes_audio.
add_subdirectory(audio)
