set(sources
    common_memory.cpp)

set(libs
    ph_common_log
    ph_common_macros)

ph_add_generic_library(ph_common_memory "${sources}" "${libs}" "")
