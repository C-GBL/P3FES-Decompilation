# p3fes:        the host executable (window + D3D11 + XAudio2, or --headless).
# p3fes_app_io: the host's input and presentation policy, pure C++ without a window (tests/app links it):
#               input.h (keyboard/XInput -> PadInput mapping, config/input.ini, scripts, record/replay logs, the
#               per-vblank PadFeed and the feed_pad_input hook GameHost calls) and present.h (letterbox rectangle,
#               wall-clock pacing, --stats), modernize.h (the --native switch set, the --scene-log line). The Win32 halves (host_display: window + presenter + screenshots;
#               input_win32: GetAsyncKeyState/XInput sampling) are compiled into p3fes.
# p3fes_host:   the composed runtime (game_host.h): kernel + GS + IPU + SIF/IOP over the user's disc + rt hooks +
#               the recompiled program, memory card (p3fes_memcard) and host audio (p3fes_audio), ELF loading, stop
#               conditions, snapshots and traces. Only with the
#               recompiled program (-DP3FES_RECOMP_GENERATED=ON; p3fes_program and p3fes_recomp_lib come from
#               recomp/, resolved at generate time). Without it p3fes runs the GS self-test only.

add_library(p3fes_app_io STATIC
    input.h
    input.cpp
    present.h
    present.cpp
    frame_pacing.h
    frame_pacing.cpp
    pc_text.h
    pc_text.cpp
    modernize.h
    modernize.cpp
)
target_include_directories(p3fes_app_io PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(p3fes_app_io PUBLIC p3fes_common_options p3fes_sif)

add_executable(p3fes
    main.cpp
    host_display.h
    host_display.cpp
    input_win32.h
    input_win32.cpp
    frame_telemetry.h
    frame_telemetry.cpp
    frame_overlay.h
    frame_overlay.cpp
    host_timing.h
    host_timing.cpp
)
target_link_libraries(p3fes PRIVATE p3fes_runtime p3fes_app_io p3fes_gs_d3d11 p3fes_hfr_d3d11 user32 gdi32 xinput shell32 dwmapi winmm)
# Machine states (runtime/STATE.md): a DEV-ONLY build option, default OFF. A state carries raw host stacks (return
# addresses, saved registers) of the suspended guest threads, so loading one is equivalent to running code from its
# author. ON: the image loads at a fixed base (/DYNAMICBASE:NO, i.e. no ASLR for p3fes.exe), guest RAM / the
# EEContext / the kernel object come from a fixed-address arena, and state_boot.cpp replaces the process's /GS cookie
# with the one in the state named by --load-state; --save-state-at / --load-state work. OFF (play builds, any build
# that is shipped): a normal ASLR executable with its own /GS cookie and the normal allocator; both flags refuse.
# The gate, slice and segment trees configure with ON. Never ship an ON build; never load a state from someone else.
option(P3FES_MACHINE_STATES "Dev-only: machine-state save/restore (fixed image base, fixed arena, /GS cookie adoption)" OFF)
if(P3FES_MACHINE_STATES)
    target_sources(p3fes PRIVATE state_boot.cpp)
    target_link_options(p3fes PRIVATE /DYNAMICBASE:NO)
endif()
if(P3FES_RECOMP_GENERATED)
    add_library(p3fes_host STATIC
        game_host.h
        game_host.cpp
        game_state.cpp
        guest_symbols.h
        guest_symbols.cpp
        kernel_census.h
        kernel_census.cpp
        host_backtrace.h
        host_backtrace.cpp
        host_crash.h
        host_crash.cpp
        host_profile.h
        host_profile.cpp
        host_watch.h
        host_watch.cpp
        gs_probe.h
        gs_probe.cpp
        host_zones.h
        host_zones.cpp
    )
    target_include_directories(p3fes_host PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(p3fes_host
        PUBLIC p3fes_common_options p3fes_runtime p3fes_kernel p3fes_sif p3fes_cdvd p3fes_gs p3fes_ipu p3fes_rt p3fes_app_io
               p3fes_audio p3fes_memcard p3fes_native p3fes_native_files p3fes_native_input p3fes_native_sound
               p3fes_native_movies p3fes_native_graphics p3fes_native_kernel
        PRIVATE p3fes_program p3fes_recomp_lib dbghelp)
    target_compile_definitions(p3fes PRIVATE P3FES_HAVE_PROGRAM=1)
    if(P3FES_MACHINE_STATES)
        target_compile_definitions(p3fes_host PUBLIC P3FES_MACHINE_STATES=1)
    endif()
    target_link_libraries(p3fes PRIVATE p3fes_host p3fes_program)
endif()
