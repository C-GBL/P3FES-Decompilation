# p3fes_kernel_tests: doctest suite for runtime/hle/kernel (the EE kernel / timing HLE). Synthetic guest
# functions only; no game data. main.cpp also defines the test-only p3fes::rt::lookup_func table.
add_executable(p3fes_kernel_tests
    main.cpp
    kernel_test_util.h
    test_bus_time.cpp
    test_interrupts.cpp
    test_dmac.cpp
    test_scheduler.cpp
    test_syscalls.cpp
)
target_include_directories(p3fes_kernel_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
target_link_libraries(p3fes_kernel_tests PRIVATE p3fes_common_options p3fes_kernel p3fes_recomp_rt_api)

add_test(NAME p3fes_kernel_tests COMMAND p3fes_kernel_tests)
