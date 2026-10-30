# p3fes_unit_cache(<target>): compile <target>'s sources through tools/ours/gate/unit_cache.py, the shared object
# cache for generated translation units, when -DP3FES_UNIT_CACHE=<directory> is set (gate.ps1 sets it to the main
# tree's build\_unit_cache). Off by default: nothing changes without the option. Only for generated code (no
# __FILE__ or other path-dependent text; unit_cache.py explains why).
set(P3FES_UNIT_CACHE "" CACHE PATH "Shared object cache for the generated units (tools/ours/gate/unit_cache.py); empty = off")
get_filename_component(_p3fes_unit_cache_dir "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
get_filename_component(_p3fes_unit_cache_root "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)
function(p3fes_unit_cache target)
    if(NOT P3FES_UNIT_CACHE)
        return()
    endif()
    if(NOT P3FES_UNIT_CACHE_PYTHON)
        if(DEFINED ENV{P3FES_PYTHON} AND EXISTS "$ENV{P3FES_PYTHON}")
            set(P3FES_UNIT_CACHE_PYTHON "$ENV{P3FES_PYTHON}" CACHE FILEPATH "Python for unit_cache.py")
        else()
            find_package(Python3 3.8 COMPONENTS Interpreter QUIET)
            if(NOT Python3_Interpreter_FOUND)
                message(WARNING "P3FES_UNIT_CACHE: no Python (set P3FES_UNIT_CACHE_PYTHON); ${target} compiles without the cache")
                return()
            endif()
            set(P3FES_UNIT_CACHE_PYTHON "${Python3_EXECUTABLE}" CACHE FILEPATH "Python for unit_cache.py")
        endif()
    endif()
    set_property(TARGET ${target} PROPERTY CXX_COMPILER_LAUNCHER
        "${P3FES_UNIT_CACHE_PYTHON}" -I "${_p3fes_unit_cache_dir}/unit_cache.py"
        --cache "${P3FES_UNIT_CACHE}" --root "${_p3fes_unit_cache_root}" --build "${CMAKE_BINARY_DIR}" --)
endfunction()

# p3fes_unit_cache_dir(<dir>): every compiled target defined in <dir> and below (the top level applies it to runtime/
# and game/: no __FILE__ in their code and assert() compiles out in Release; unit_cache.py passes Debug compiles --
# /Zi, /Z7 -- straight to the compiler). Never for tests/ or tools/ (doctest records __FILE__).
function(p3fes_unit_cache_dir dir)
    if(NOT P3FES_UNIT_CACHE)
        return()
    endif()
    get_property(_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    foreach(_t IN LISTS _targets)
        get_target_property(_type ${_t} TYPE)
        if(_type MATCHES "^(STATIC_LIBRARY|OBJECT_LIBRARY|SHARED_LIBRARY|EXECUTABLE)$")
            p3fes_unit_cache(${_t})
        endif()
    endforeach()
    get_property(_subdirs DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(_d IN LISTS _subdirs)
        p3fes_unit_cache_dir(${_d})
    endforeach()
endfunction()
