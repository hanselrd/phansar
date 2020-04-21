# cmake-format: off
set(sources
    main.cpp)

set(libs
    ph_common)

set(system_libs
    ph_vendor_raygui
    ph_vendor_raylib)
# cmake-format: on

ph_add_generic_executable(ph_client "${sources}" "${libs}" "${system_libs}")
