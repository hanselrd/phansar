CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2 # v2.x
    GIT_TAG b8b03da534ef6245c90698eff3123576b93162b9
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
