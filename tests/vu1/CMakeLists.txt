# p3fes_vu1_tests: doctest tests for runtime/vu1/ (decoder census reproduction, hand-derived semantic vectors,
# batch runs of dumped game microcode). Game-data tests read ida/logs/vu1/*.bin in place (P3FES_VU1_DUMPS
# overrides) and skip when the dumps are absent.
add_executable(p3fes_vu1_tests
    vu1_test_main.cpp
    vu1_test_util.h
    mini_json.h
    test_vu1_decode.cpp
    test_vu1_census.cpp
    test_vu1_semantics.cpp
    test_vu1_batch.cpp
    test_vu1_aot.cpp
)
target_include_directories(p3fes_vu1_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor ${PROJECT_SOURCE_DIR}/runtime/vu1)
target_link_libraries(p3fes_vu1_tests PRIVATE p3fes_common_options p3fes_vu1)
target_compile_definitions(p3fes_vu1_tests PRIVATE P3FES_REPO_DIR="${PROJECT_SOURCE_DIR}")

# test_vu1_aot.cpp calls the SSE4.1 kernels of runtime/vu1/vu1_aot_rt.h (strict FP model: see runtime/vu1/CMakeLists.txt)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set_source_files_properties(test_vu1_aot.cpp PROPERTIES COMPILE_OPTIONS "-msse4.1;/fp:strict")
endif()

add_test(NAME p3fes_vu1_tests COMMAND p3fes_vu1_tests)
