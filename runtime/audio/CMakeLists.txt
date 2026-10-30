# p3fes_audio: host audio (runtime/audio/README.md) -- the AudioSink/StreamTap interfaces the IOP
# HLE renders into (virtual-time timeline), Null/Tee/WAV sinks, the per-stream WAV dumper, the
# XAudio2 sink, the HostAudio composition, and the host-side CRI ADX decoder over p3fes_formats.
# runtime/hle/sif (the CRI_ADXI PSM model) links it for the interfaces.

add_library(p3fes_audio STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/audio/audio_sink.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/audio/wav.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/audio/adx_decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/audio/xaudio2_sink.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/audio/host_audio.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/p3fes/audio/spu2_voice.h
    audio_sink.cpp
    wav.cpp
    adx_decoder.cpp
    xaudio2_sink.cpp
    host_audio.cpp
    spu2_voice.cpp
)
add_library(p3fes::audio ALIAS p3fes_audio)
target_include_directories(p3fes_audio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)
target_link_libraries(p3fes_audio PUBLIC p3fes_common_options p3fes_formats PRIVATE xaudio2 ole32)
