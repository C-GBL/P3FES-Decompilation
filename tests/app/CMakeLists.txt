# p3fes_app_tests: doctest suite for the host's input and presentation policy (runtime/app/input.h, present.h):
# key -> button mapping and config/input.ini, stick dead zone math, input scripts, record/replay round trips, the
# per-vblank latch (and its hand-over to PADMAN through tests/sif's EE re-enactment), letterbox rectangles, pacing
# and the stats readout. No window, no game data.

add_executable(p3fes_app_tests
    main.cpp
    test_input_map.cpp
    test_gamepad.cpp
    test_pad_feed.cpp
    test_pad_hook.cpp
    test_present.cpp
    test_frame_pacing.cpp
    test_pc_text.cpp
    test_modernize.cpp
    test_native_input.cpp
    test_native_sound.cpp
    test_native_movies.cpp
    test_native_graphics.cpp
)
target_include_directories(p3fes_app_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
target_link_libraries(p3fes_app_tests PRIVATE p3fes_common_options p3fes_app_io p3fes_native_input p3fes_native_sound
                      p3fes_native_movies p3fes_native_graphics)
target_compile_definitions(p3fes_app_tests PRIVATE P3FES_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
# test_pc_text.cpp reads the user's ELF (P3FES_ELF overrides; the case skips without it).
if(DEFINED P3FES_RT_EXEC_ELF)
    target_compile_definitions(p3fes_app_tests PRIVATE P3FES_ELF_DEFAULT="${P3FES_RT_EXEC_ELF}")
else()
    target_compile_definitions(p3fes_app_tests PRIVATE P3FES_ELF_DEFAULT="${CMAKE_SOURCE_DIR}/extracted/disc/SLUS_216.21")
endif()

add_test(NAME p3fes_app_tests COMMAND p3fes_app_tests)
