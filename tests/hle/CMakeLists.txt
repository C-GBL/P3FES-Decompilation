# p3fes_hle_tests: doctest suite for runtime/hle (CDVD HLE). Real-disc cases read the user's
# input/persona3fes.iso (P3FES_ISO overrides) and extracted/ (P3FES_EXTRACTED overrides) at run
# time and skip cleanly when absent; synthetic-image cases always run.

add_executable(p3fes_hle_tests
    main.cpp
    hle_fixtures.h
    test_disc_sources.cpp
    test_cdvd_hle.cpp
    test_mods_overlay.cpp
)
target_include_directories(p3fes_hle_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
# p3fes_runtime: EEMemory for guest_read_buffer().
target_link_libraries(p3fes_hle_tests PRIVATE p3fes_common_options p3fes_cdvd p3fes_runtime p3fes_native_files)
target_compile_definitions(p3fes_hle_tests PRIVATE
    P3FES_EXTRACTED_DIR="${CMAKE_SOURCE_DIR}/extracted"
    P3FES_INPUT_DIR="${CMAKE_SOURCE_DIR}/input"
)

add_test(NAME p3fes_hle_tests COMMAND p3fes_hle_tests)
