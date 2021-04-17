CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2 # v2.x
    GIT_TAG 5c88067bd339465513af4aec606bd2292f1b594a
    OPTIONS "CATCH_BUILD_TESTING OFF" "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_HELPERS OFF"
    EXCLUDE_FROM_ALL YES)

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
