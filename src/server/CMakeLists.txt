# cmake-format: off
set(sources
    application.cpp
    main.cpp)

set(pch
    <phansar/server/pch.hpp>)

set(libs
    ph_common)

set(system_libs
    ph_vendor_libpqxx)
# cmake-format: on

ph_add_generic_executable(
    ph_server
    "${sources}"
    "${pch}"
    "${libs}"
    "${system_libs}")

install(TARGETS ph_server RUNTIME DESTINATION bin)
