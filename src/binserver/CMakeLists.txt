# cmake-format: off
set(sources
    main.cpp)

set(libs
    ph_common)
# cmake-format: on

ph_add_generic_executable(ph_server "${sources}" "${libs}" "")
