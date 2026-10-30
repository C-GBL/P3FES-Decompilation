# p3fes_recomp_tests: doctest tests for the recompiler.
#
# decode_census_test.cpp needs the real ELF for its census part and skips cleanly (doctest
# MESSAGE + return) when it is absent. Override the ELF location with the P3FES_ELF environment
# variable at run time. emit_flow_test.cpp runs the emitter on synthetic word sequences and
# needs nothing from the disc.
#
# p3fes_recomp_emit_subset (ctest): emits a reviewed subset of real functions with the built
# p3fes_recomp, compiles every generated unit with this configuration's compiler at /W4 /WX and
# links them against the rt stubs. Skipped (return code 77) when the ELF is absent.

add_executable(p3fes_recomp_tests
    test_main.cpp
    decode_census_test.cpp
    emit_flow_test.cpp
)
target_include_directories(p3fes_recomp_tests PRIVATE ${P3FES_REPO_ROOT}/tests/vendor)  # doctest.h, read-only
target_link_libraries(p3fes_recomp_tests PRIVATE p3fes_common_options p3fes_recomp_lib)
target_compile_definitions(p3fes_recomp_tests PRIVATE
    P3FES_ELF_DEFAULT="${P3FES_REPO_ROOT}/extracted/disc/SLUS_216.21"
    P3FES_FUNCTIONS_JSON="${P3FES_REPO_ROOT}/symbols/functions.json"
    P3FES_CENSUS_JSON="${P3FES_REPO_ROOT}/symbols/insn_census.json"
    P3FES_FUNCTION_CHUNKS="${P3FES_REPO_ROOT}/symbols/function_chunks.txt"
)

add_test(NAME p3fes_recomp_tests COMMAND p3fes_recomp_tests)

add_test(NAME p3fes_recomp_emit_subset
    COMMAND ${CMAKE_COMMAND}
        -DRECOMP=$<TARGET_FILE:p3fes_recomp>
        -DCXX=${CMAKE_CXX_COMPILER}
        -DSRC=${P3FES_REPO_ROOT}
        -DOUT=${CMAKE_BINARY_DIR}/recomp_subset
        -P ${CMAKE_CURRENT_SOURCE_DIR}/compile_subset.cmake
)
set_tests_properties(p3fes_recomp_emit_subset PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 1800)
