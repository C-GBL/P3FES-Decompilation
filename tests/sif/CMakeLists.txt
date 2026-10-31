# p3fes_sif_tests: doctest suite for runtime/hle/sif (SIF registers/syscalls, sifcmd/sifrpc packet
# flow against a re-enactment of the game's EE libraries, the IOP servers). Real-disc cases read the
# user's input/persona3fes.iso (P3FES_ISO overrides) and extracted/ (P3FES_EXTRACTED overrides) and
# skip cleanly when absent.

add_executable(p3fes_sif_tests
    main.cpp
    sif_harness.h
    test_protocol.cpp
    test_sif_core.cpp
    test_servers.cpp
    test_cdvdfsv.cpp
    test_adxi.cpp
    test_dbcman.cpp
    test_sk_modules.cpp
    test_sk_native.cpp
)
# runtime/hle/sif/iop: test_adxi.cpp checks the PSM volume law (srv_adxi.h) directly.
target_include_directories(p3fes_sif_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor ${CMAKE_SOURCE_DIR}/runtime/hle/sif/iop)
# test_sk_native.cpp: the native SK stack (modernize layer 3 steps 2-3) against the interpreted modules.
target_link_libraries(p3fes_sif_tests PRIVATE p3fes_common_options p3fes_sif p3fes_native_sound)
target_compile_definitions(p3fes_sif_tests PRIVATE
    P3FES_EXTRACTED_DIR="${CMAKE_SOURCE_DIR}/extracted"
    P3FES_INPUT_DIR="${CMAKE_SOURCE_DIR}/input"
)

add_test(NAME p3fes_sif_tests COMMAND p3fes_sif_tests)
