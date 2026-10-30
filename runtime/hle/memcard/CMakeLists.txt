# p3fes_memcard: the PS2 memory card behind DBCMAN/MC2_S1 -- 8 MiB NAND image (512+16-byte pages, 16-page
# erase blocks), ECC, the card file system (superblock/FAT/directories, formatter, read-only view) and the
# card sources (PCSX2's card read-only with copy-on-write, our own images, "new"/"blank"/"none").
# docs/ANALYSIS/17_memory_card.md. No SIF dependency: the DBCMAN server in runtime/hle/sif/iop/ uses it.

add_library(p3fes_memcard STATIC
    include/p3fes/hle/memcard/ecc.h
    include/p3fes/hle/memcard/card.h
    include/p3fes/hle/memcard/fs.h
    include/p3fes/hle/memcard/source.h
    include/p3fes/hle/memcard/iop_slot.h
    ecc.cpp
    card.cpp
    fs.cpp
    source.cpp
)
add_library(p3fes::memcard ALIAS p3fes_memcard)
target_include_directories(p3fes_memcard PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
)
target_link_libraries(p3fes_memcard PUBLIC p3fes_common_options)

# The SIF/IOP HLE serves the card (srv_dbcman.cpp); linked from here (CMP0079) so runtime/hle/sif's
# CMakeLists keeps its own link line.
target_link_libraries(p3fes_sif PUBLIC p3fes_memcard)
