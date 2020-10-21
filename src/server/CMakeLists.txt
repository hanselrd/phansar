# cmake-format: off
set(sources
    main.cpp)

set(libs
    ph_common)

set(system_libs
    ph_vendor_libpqxx)
# cmake-format: on

ph_add_generic_executable(ph_server "${sources}" "${libs}" "${system_libs}")
