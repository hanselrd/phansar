CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2 # v2.x
    GIT_TAG 469a7173951eb490c933bef1b214a0e4492b4686
    OPTIONS "CATCH_BUILD_TESTING OFF" "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_HELPERS OFF")

if(Catch2_ADDED)
    include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)
endif()

# cmake-format: off
set(system_libs
    Catch2)
# cmake-format: on

ph_add_generic_vendor_interface_library(
    ph_vendor_catch2
    ""
    ""
    "${system_libs}")
