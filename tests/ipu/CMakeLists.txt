# p3fes_ipu_tests: doctest suite for runtime/ipu (VLC tables, IQ, IDCT, CSC/PACK, the command engine, FIFO/BP
# semantics, stalls) plus end-to-end runs through the kernel's DMAC (runtime/hle/kernel). No game data: every
# bit stream is built by hand in the tests.
add_executable(p3fes_ipu_tests
    main.cpp
    ipu_test_util.h
    test_vlc.cpp
    test_idct_iq.cpp
    test_csc_pack.cpp
    test_core.cpp
    test_system.cpp
)
target_include_directories(p3fes_ipu_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
target_link_libraries(p3fes_ipu_tests PRIVATE p3fes_common_options p3fes_ipu p3fes_kernel p3fes_recomp_rt_api)

add_test(NAME p3fes_ipu_tests COMMAND p3fes_ipu_tests)
