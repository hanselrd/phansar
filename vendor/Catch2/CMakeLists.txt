CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2 # v2.x
    GIT_TAG 958944d27a2d2fb82aa008377bf4f8752f6b848e
    OPTIONS "CATCH_BUILD_TESTING OFF" "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_HELPERS OFF"
    EXCLUDE_FROM_ALL YES)

if(Catch2_ADDED)
    include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)
endif()

ph_add_library(
    NAME ph_vendor_catch2
    TYPE INTERFACE
    LINK_LIBRARIES SYSTEM INTERFACE Catch2)
