# p3fes_audio_tests: doctest suite for runtime/audio -- ADX decoder vectors (synthetic frames computed
# independently, see test_adx_decoder.cpp), sink timeline math, WAV output, the SPU2 voice model and mixer
# (test_spu2_voice.cpp). No game data; the real-file cases (BGM/0501.ADX, SOUND/SPU/COMSE.{HD,BD}) read
# extracted/ when present and skip otherwise.

add_executable(p3fes_audio_tests
    main.cpp
    test_adx_decoder.cpp
    test_sinks.cpp
    test_spu2_voice.cpp
)
target_include_directories(p3fes_audio_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../vendor)
target_link_libraries(p3fes_audio_tests PRIVATE p3fes_common_options p3fes_audio)
target_compile_definitions(p3fes_audio_tests PRIVATE
    P3FES_EXTRACTED_DIR="${CMAKE_SOURCE_DIR}/extracted"
    P3FES_TEST_TMP_DIR="${CMAKE_CURRENT_BINARY_DIR}/tmp"
)

add_test(NAME p3fes_audio_tests COMMAND p3fes_audio_tests)
